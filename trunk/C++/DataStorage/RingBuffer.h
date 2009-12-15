//TODO
#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "Log.h"
#include "PushPop.h"

namespace ae {
	template<typename T>
	class RingBuffer : public PushPop<T> {
	public:
		RingBuffer(unsigned int size);
		virtual ~RingBuffer() { {LOG(Log::LOG_INFO,"Destructing");} delete[] data; }
		virtual bool	push	( T element );
		virtual T		pop		( void );
		void			setSize ( unsigned int newSize );
		unsigned int	size	( void );
	protected:
		T* data;
		unsigned int thisSize;
		unsigned int head;
		unsigned int tail;
	};
}

template<typename T>
ae::RingBuffer<T>::RingBuffer(unsigned int size) {
	LOG(Log::LOG_INFO,"Constructing");
	head = 0;
	tail = 0;
	thisSize = size;
	data = new T[thisSize];
}

template<typename T>
bool ae::RingBuffer<T>::push( T element ) {
	LOG(Log::LOG_INFO,"pushing an element ono the buffer");
	unsigned int index = head % thisSize;
	data[index] = element;
	if (index==0) { head = 0; }
	head++;
	return true; //always success
}

template<typename T>
T ae::RingBuffer<T>::pop( void ) {
	LOG(Log::LOG_INFO,"popping an element off the buffer");
	unsigned int index = tail % thisSize;
	T buffer = data[index];
	data[index] = 0;
	if (index==0) { tail = 0; }
	tail++; //increment for next pop
	return buffer;
}

template<typename T>
void ae::RingBuffer<T>::setSize( unsigned int newSize ) {
	LOG(Log::LOG_INFO,"setting the size of the buffer");
	delete[] data;
	thisSize = newSize;
	data = new T[thisSize];
}

template<typename T>
unsigned int ae::RingBuffer<T>::size( void ) {
	unsigned int size = thisSize - (tail-head);
	if (size>=thisSize){ 
		size = (head-tail); 
	}
	return size;
}
#endif