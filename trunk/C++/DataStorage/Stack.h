/*
||
|| @file	Stack.h
|| @version 1.0
|| @author	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | A dynamic stack
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
#ifndef STACK_H
#define STACK_H

#include "List.h"

#define AB_STACK_DEFAULT_SIZE 8

namespace ab {
	template<typename T, uint stackSize=AB_STACK_DEFAULT_SIZE>
	class Stack : public List<T,stackSize> {
		public:
			Stack( void );
			virtual ~Stack( void ) {}

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

template<typename T, uint stackSize>
ab::Stack<T,stackSize>::Stack() {
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
bool ab::Stack<T,stackSize>::push( T element) {
	return List::push(0,element);
}

/*
|| T pop( void )
||
|| @description
|| | Pop/remove an element from this Stack
|| | It is implemented in such a way that it will pop the element:T at the end
|| | FILO
|| #
||
|| @override	T List::pop( void )
|| @return		removed:T you might want to delete this
*/
template<typename T, uint stackSize>
T ab::Stack<T,stackSize>::pop( void ) {
	return List::remove( raw[0] );
}

#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Created file
|| #
*/