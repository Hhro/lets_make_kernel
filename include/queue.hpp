#ifndef QUEUE_H
#define QUEUE_H

#define BUFFERSIZE 101
template<class T> class Queue
{
private:
	int front;
	int rear;
	T values[BUFFERSIZE];

public:
	Queue()
	{
		front = 0;
		rear = 0;
	}

    bool push(T value);
    bool pop(T* target);
	bool isEmpty();
	bool isFull();
};

#endif