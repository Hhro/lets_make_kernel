#ifndef BUDDY_ALLOC
#define BUDDY_ALLOC

#include<stdint.h>
#include<stddef.h>
#include<fried/string.h>

#define HEADER_SIZE 16

#define MIN_ALLOC_LOG2 5
#define MIN_ALLOC (1 << MIN_ALLOC_LOG2)
#define MAX_ALLOC_LOG2 21
#define MAX_ALLOC (1 << MAX_ALLOC_LOG2)

#define BUCKET_COUNT (MAX_ALLOC_LOG2 - MIN_ALLOC_LOG2 + 1)

#define HEAP_START 0xFFFFFFFF00000000
#define HEAP_LIMIT (HEAP_START + MAX_ALLOC)

#pragma pack(push, 1)
typedef struct _header{
    struct _header * next;
    struct _header * prev;
} BlockHeader;
#pragma pack(pop)

static void list_init(BlockHeader *list) {
  list->prev = list;
  list->next = list;
}

static void list_push(BlockHeader *list, BlockHeader *entry) {
  BlockHeader *prev = list->prev;
  entry->prev = prev;
  entry->next = list;
  prev->next = entry;
  list->prev = entry;
}

static void list_remove(BlockHeader *entry) {
  BlockHeader *prev = entry->prev;
  BlockHeader *next = entry->next;
  prev->next = next;
  next->prev = prev;
}

static BlockHeader *list_pop(BlockHeader *list) {
  BlockHeader *back = list->prev;
  if (back == list) return NULL;
  list_remove(back);
  return back;
}


class BuddyAllocator{
private:
    BlockHeader buckets[BUCKET_COUNT];
    uint8_t node_is_split[(1<<(BUCKET_COUNT-1))/8];
    uint8_t * heap_base;
    uint8_t * heap_max;
    int32_t bucket_limit;

    bool update_max(uint8_t * new_max);
    uint8_t *ptr_for_node(uint32_t index, uint32_t bucket);
    uint32_t node_for_ptr(uint8_t *ptr, uint32_t bucket);
    bool parent_is_split(uint32_t index);
    void flip_parent_is_split(uint32_t index);
    uint32_t bucket_for_request(uint32_t request);
    bool lower_bucket_limit(uint32_t bucket);
    
public:
    BuddyAllocator(){
        heap_base = heap_max = (uint8_t *)HEAP_START;
        bucket_limit =  BUCKET_COUNT-1;
        update_max(heap_base + sizeof(BlockHeader));
        list_init(&buckets[BUCKET_COUNT - 1]);
        list_push(&buckets[BUCKET_COUNT - 1], (BlockHeader *)heap_base);
    }

    void init() {
        heap_base = heap_max = (uint8_t *)HEAP_START;
        bucket_limit =  BUCKET_COUNT-1;
        update_max(heap_base + sizeof(BlockHeader));
        list_init(&buckets[BUCKET_COUNT - 1]);
        list_push(&buckets[BUCKET_COUNT - 1], (BlockHeader *)heap_base);
    }
    void* malloc(uint32_t request);
    bool free(void* ptr);
};

extern BuddyAllocator BAllocator;
#endif