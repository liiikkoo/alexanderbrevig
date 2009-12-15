#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#define AB_ARRAY_DEFAULT_SIZE 10

typedef unsigned int uint;
namespace ab {
	template<typename T, uint size=AB_ARRAY_DEFAULT_SIZE>
	class BinaryHeap : public PushPop<T> {
	public:
		BinaryHeap( void );
		~BinaryHeap( void );

		virtual bool	push			( T element );			//push an item into the PushPop BinaryHeap
		virtual T		pop				( void );				//pop an element from the PushPop BinaryHeap
	
	protected:
		T raw[size];
		uint currentSize;
	};
}

template<typename T, uint size>
ab::BinaryHeap<T,size>::BinaryHeap( void ) {
	currentSize = 0;
}
template<typename T, uint size>
ab::BinaryHeap<T,size>::~BinaryHeap( void ) {
	//
}

template<typename T, uint size>
bool ab::BinaryHeap<T,size>::push( T element ) {
	//TODO
	if (currentSize+1<=size) {
		uint i = ++currentSize;
		/*while (i>1 && ()) {
		}*/
		raw[] = element;
		return true;
	}
	return false;
}

template<typename T, uint size>
T ab::BinaryHeap<T,size>::pop( void ) {
	T* buffer = &raw[0];
	T* move = &raw[currentSize-1];
	bool notDone = true;
	uint currentMother = 0;
	while (notDone) {
		//s
		currentMother++;
	}
}

#endif