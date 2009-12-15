/*
||
|| @file List.h
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | A dynamic list
|| #
||
|| @dependencies
|| | operators: new delete
|| | Array.h
|| | Storage.h
|| | Functional.h
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
|| #
||
*/
#ifndef LIST_H
#define LIST_H

#include "Array.h"
using ab::Array;

#define AB_LIST_DEFAULT_SIZE 10

namespace ab {
	template<typename T,uint listSize=AB_LIST_DEFAULT_SIZE>
	class List : public Array<T,listSize> {
		public:
			List( void );
			virtual ~List( void ) {}

			//Array
			//	modification
			virtual bool	push		( T element );
			virtual bool	push		( uint index, T element );

		protected:
			void			grow		( void );
	};
}

/*
|| Implementation of public functions
|| ===========================================================================
*/

/*
|| List( void )
||
|| @description
|| | Constructor for Lists
|| #
*/
template<class T,uint listSize>
ab::List<T,listSize>::List( void ){
	currentSize = 0;
	currentIndex = 0;
}

/*
|| bool push( T )
||
|| @description
|| | Pust an element:T into this List
|| #
||
|| @override	bool Array::push( T )
|| @parameter	element:T is the element to push into the List
|| @return		stateOfSuccess:bool
*/
template<class T,uint listSize>
bool ab::List<T,listSize>::push( T element ) {
	if (currentSize+1>=capacity()){
		grow();
	}
	raw[currentSize++] = element;
	return true;
}

/*
|| bool push( uint, T )
||
|| @description
|| | Pust an element:T into this List at index:uint
|| #
||
|| @override	bool Array::push( uint, T )
|| @parameter	index:uint of the requested element
|| @parameter	element:T is the element to push into the List
|| @return		stateOfSuccess:bool
*/
template<class T,uint listSize>
bool ab::List<T,listSize>::push( uint index, T element ){
	if (currentSize+1>=currentCapacity){
		grow();
	}
	//shift all elements, make room for element
	currentSize++;
	for (uint i=currentSize; i>index; i--){
		raw[i] = raw[i-1];
	}
	raw[index] = element;
	return true;
}

/*
|| Implementation of protected functions
|| ===========================================================================
*/

/*
|| void grow( void )
||
|| @description
|| | Grow the Lists capacity
|| #
*/
template<class T,uint listSize>
void ab::List<T,listSize>::grow( void ){
	LOG(Log::LOG_INFO, "Growing the list");
	currentCapacity *= 2;
	currentCapacity |= 0;
	T* newArray = new T[currentCapacity];
	for (uint i=0; i<currentSize; i++){
		newArray[i] = raw[i];
	}
	for (uint i=currentSize; i<currentCapacity; i++){
		newArray[i] = 0;
	}
	raw = &newArray[0];
}


#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Created file
|| #
*/