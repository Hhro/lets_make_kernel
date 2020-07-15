#include<buddy_alloc.hpp>


BuddyAllocator BAllocator;
bool BuddyAllocator::update_max(uint8_t * new_max){
    if(heap_max < new_max){
        if((uint64_t)new_max > HEAP_LIMIT) return false;
        heap_max = new_max;
    }
    return true;
}

uint8_t* BuddyAllocator::ptr_for_node(uint32_t index, uint32_t bucket) {
  return heap_base + ((index - (1 << bucket) + 1) << (MAX_ALLOC_LOG2 - bucket));
}
uint32_t BuddyAllocator::node_for_ptr(uint8_t *ptr, uint32_t bucket) {
  return ((ptr - heap_base) >> (MAX_ALLOC_LOG2 - bucket)) + (1 << bucket) - 1;
}

bool BuddyAllocator::parent_is_split(uint32_t index) {
  index = (index - 1) / 2;
  return (node_is_split[index / 8] >> (index % 8)) & 1;
}

void BuddyAllocator::flip_parent_is_split(uint32_t index) {
  index = (index - 1) / 2;
  node_is_split[index / 8] ^= 1 << (index % 8);
}

uint32_t BuddyAllocator::bucket_for_request(uint32_t request) {
  uint32_t bucket = BUCKET_COUNT - 1;
  uint32_t size = MIN_ALLOC;

  while (size < request) {
    bucket--;
    size *= 2;
  }

  return bucket;
}

bool BuddyAllocator::lower_bucket_limit(uint32_t bucket) {
  while (bucket < bucket_limit) {
    uint32_t root = node_for_ptr(heap_base, bucket_limit);
    uint8_t *right_child;

    if (!parent_is_split(root)) {
      list_remove((BlockHeader *)heap_base);
      list_init(&buckets[--bucket_limit]);
      list_push(&buckets[bucket_limit], (BlockHeader *)heap_base);
      continue;
    }

    right_child = ptr_for_node(root + 1, bucket_limit);
    if (!update_max(right_child + sizeof(BlockHeader))) {
      return false;
    }
    list_push(&buckets[bucket_limit], (BlockHeader *)right_child);
    list_init(&buckets[--bucket_limit]);

    root = (root - 1) / 2;
    if (root != 0) {
      flip_parent_is_split(root);
    }
  }

  return true;
}


void * BuddyAllocator::malloc(uint32_t request) {
  uint32_t original_bucket, bucket;

  if (request + HEADER_SIZE > MAX_ALLOC) {
    return NULL;
  }
  
  bucket = bucket_for_request(request + HEADER_SIZE);
  original_bucket = bucket;

  /*
   * Search for a bucket with a non-empty free list that's as large or larger
   * than what we need. If there isn't an exact match, we'll need to split a
   * larger one to get a match.
   */
  while (bucket + 1 != 0) {
    uint32_t size, bytes_needed, i;
    uint8_t *ptr;

    /*
     * We may need to grow the tree to be able to fit an allocation of this
     * size. Try to grow the tree and stop here if we can't.
     */
    if (!lower_bucket_limit(bucket)) {
      return NULL;
    }

    /*
     * Try to pop a block off the free list for this bucket. If the free list
     * is empty, we're going to have to split a larger block instead.
     */
    ptr = (uint8_t *)list_pop(&buckets[bucket]);
    if (!ptr) {
      /*
       * If we're not at the root of the tree or it's impossible to grow the
       * tree any more, continue on to the next bucket.
       */
      if (bucket != bucket_limit || bucket == 0) {
        bucket--;
        continue;
      }

      /*
       * Otherwise, grow the tree one more level and then pop a block off the
       * free list again. Since we know the root of the tree is used (because
       * the free list was empty), this will add a parent above this node in
       * the SPLIT state and then add the new right child node to the free list
       * for this bucket. Popping the free list will give us this right child.
       */
      if (!lower_bucket_limit(bucket - 1)) {
        return NULL;
      }
      ptr = (uint8_t *)list_pop(&buckets[bucket]);
    }

    /*
     * Try to expand the address space first before going any further. If we
     * have run out of space, put this block back on the free list and fail.
     */
    size = (uint32_t)1 << (MAX_ALLOC_LOG2 - bucket);
    bytes_needed = bucket < original_bucket ? size / 2 + sizeof(BlockHeader) : size;
    if (!update_max(ptr + bytes_needed)) {
      list_push(&buckets[bucket], (BlockHeader *)ptr);
      return NULL;
    }

    /*
     * If we got a node off the free list, change the node from UNUSED to USED.
     * This involves flipping our parent's "is split" bit because that bit is
     * the exclusive-or of the UNUSED flags of both children, and our UNUSED
     * flag (which isn't ever stored explicitly) has just changed.
     *
     * Note that we shouldn't ever need to flip the "is split" bit of our
     * grandparent because we know our buddy is USED so it's impossible for our
     * grandparent to be UNUSED (if our buddy chunk was UNUSED, our parent
     * wouldn't ever have been split in the first place).
     */
    i = node_for_ptr(ptr, bucket);
    if (i != 0) {
      flip_parent_is_split(i);
    }

    /*
     * If the node we got is larger than we need, split it down to the correct
     * size and put the new unused child nodes on the free list in the
     * corresponding bucket. This is done by repeatedly moving to the left
     * child, splitting the parent, and then adding the right child to the free
     * list.
     */
    while (bucket < original_bucket) {
      i = i * 2 + 1;
      bucket++;
      flip_parent_is_split(i);
      list_push(&buckets[bucket], (BlockHeader *)ptr_for_node(i + 1, bucket));
    }

    /*
     * Now that we have a memory address, write the block header (just the size
     * of the allocation) and return the address immediately after the header.
     */
    *(uint64_t *)ptr = request;
    return ptr + HEADER_SIZE;
  }

  return NULL;
}



bool BuddyAllocator::free(void *ptr) {
  uint32_t bucket, i;

  if (!ptr) {
    return false;
  }

  ptr = (uint8_t *)ptr - HEADER_SIZE;
  bucket = bucket_for_request(*(uint64_t *)ptr + HEADER_SIZE);
  i = node_for_ptr((uint8_t *)ptr, bucket);

  while (i != 0) {
    flip_parent_is_split(i);

    if (parent_is_split(i) || bucket == bucket_limit) {
      break;
    }

    list_remove((BlockHeader *)ptr_for_node(((i - 1) ^ 1) + 1, bucket));
    i = (i - 1) / 2;
    bucket--;
  }

  list_push(&buckets[bucket], (BlockHeader *)ptr_for_node(i, bucket));
  return true;
}