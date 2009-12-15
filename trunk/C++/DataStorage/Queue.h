/*
||
|| @file Queue.h
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | A dynamic Queue
|| #
||
|| @dependencies
|| | operators: new delete
|| | List.h
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
#ifndef QUEUE_H
#define QUEUE_H

#define AB_QUEUE_DEFAULT_SIZE 15

#include "Array.h"
#include "List.h"

namespace ab {
	template<typename T, uint stackSize=AB_QUEUE_DEFAULT_SIZE>
	class Queue : public List<T,stackSize> {
		public:
			Queue( void );
			virtual ~Queue( void ) {}

			//Array
			//	modification
			virtual bool	push	( T element );
			virtual T		pop		( void );
	};
}

/*
|| Implementation of public functions
|| ===========================================================================
*/

/*
|| Queue( void )
|| 
|| @description
|| | Constructor for Queues
|| #
*/
template<typename T, uint stackSize>
ab::Queue<T,stackSize>::Queue( void ) {
	//
}

/*
|| bool push( T )
||
|| @description
|| | Pust an element:T into this Stack
|| #
||
|| @override	bool List::push( T )
|| @parameter	element:T is the element to push into the array
|| @return		stateOfSuccess:bool
*/
template<typename T, uint stackSize>
bool ab::Queue<T,stackSize>::push( T element) {
	return ab::List<T,stackSize>::push(element);
}

/*
|| T pop( void )
||
|| @description
|| | Pop/remove an element from this Stack
|| | It is implemented in such a way that it will pop the element:T at the end
|| | FIFO
|| #
||
|| @override	T List::pop( void )
|| @return		removed:T you might want to delete this
*/
template<typename T, uint stackSize>
T ab::Queue<T,stackSize>::pop( void ) {
	return ab::List<T,stackSize>::remove(raw[0]);
}

#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Created file
|| #
*/