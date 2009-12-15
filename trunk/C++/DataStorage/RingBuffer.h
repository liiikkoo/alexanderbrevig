#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "PushPop.h"

namespace ab {
	template<typename T,int size=10>
	class RingBuffer : public PushPop<T> {
	public:
		RingBuffer();
		virtual ~RingBuffer() {}
		virtual bool	push	( T element );
		virtual T		pop		( void );
	protected:
		T data[size];
		unsigned int head;
		unsigned int tail;
	};
}

template<typename T,int size>
ab::RingBuffer<T,size>::RingBuffer() {
	head = tail = 0;
}

template<typename T,int size>
bool ab::RingBuffer<T,size>::push( T element ) {
	unsigned int index = head % size;
	data[index] = element;
	head++;
	return true; //always success
}

template<typename T,int size>
T ab::RingBuffer<T,size>::pop( void ) {
	unsigned int index = tail % size;
	T buffer = data[tail];
	data[tail] = 0;
	tail++; //increment for next pop
	return buffer;
}
#endif