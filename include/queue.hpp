#ifndef QUEUE_H
#define QUEUE_H

#define BUFFERSIZE 101
template <class T>
class Queue {
   private:
    int front;
    int rear;
    T values[BUFFERSIZE];

   public:
    Queue() {
        front = 0;
        rear = 0;
    }

    bool push(T value);
    bool pop(T* target);
    bool isEmpty();
    bool isFull();
};

template <class T>
bool Queue<T>::push(T value) {
    if (!isFull()) {
        values[rear] = value;
        rear = (rear + 1) % BUFFERSIZE;
        return true;
    }
    return false;
}

template <class T>
bool Queue<T>::pop(T* target) {
    if (!isEmpty()) {
        *target = values[front];
        front = (front + 1) % BUFFERSIZE;
        return true;
    }
    return false;
}

template <class T>
bool Queue<T>::isEmpty() {
    if (rear == front)
        return true;
    else
        return false;
}

template <class T>
bool Queue<T>::isFull() {
    if ((rear + 1) % BUFFERSIZE == front)
        return true;
    else
        return false;
}

#endif