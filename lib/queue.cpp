#include <queue.hpp>

template<class T>
bool Queue<T>::push(T value){
    if(!isFull()){
	    values[rear] = value;
		rear = (rear + 1) % BUFFERSIZE;
        return true;
	}
	return false;
}

template<class T>
bool Queue<T>::pop(T* target){
    if(!isEmpty()){
        *target = values[front];
        front = (front + 1) % BUFFERSIZE;
        return true;
    }
    return false;
}

template<class T>
bool Queue<T>::isEmpty(){
    if(rear == front)
			return true;
		else 
			return false;
}

template<class T>
bool Queue<T>::isFull(){
    if((rear + 1) % BUFFERSIZE == front) 
		return true;
	else 
		return false;
}