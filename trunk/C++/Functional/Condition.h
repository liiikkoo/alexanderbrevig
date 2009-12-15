/*
||
|| @file	Condition.h
|| @version 1.0
|| @author	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide a framework for implementing generic conditions
|| | This will evaluate functions in any namespace that are on the form:
|| | bool namespace::name( void )
|| #
||
|| @dependencies
|| | VoidFunctor.h
|| #
||
|| @license
|| | Copyright (C) 2009  Alexander Brevig
|| |
|| | This program is free software: you can redistribute it and/or modify
|| | it under the terms of the GNU General Public License as published by
|| | the Free Software Foundation, either version 3 of the License, or
|| | (at your option) any later version.
|| |
|| | This program is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|| | GNU General Public License for more details.
|| |
|| | You should have received a copy of the GNU General Public License
|| | along with this program.  If not, see <http://www.gnu.org/licenses/>.
|| #
||
*/
#ifndef CONDITION_H
#define CONDITION_H

#include "VoidFunctor.h"
using ab::functional::VoidFunctor;

namespace ab {
	namespace functional {
		template<typename T,bool mode=true>
		class Condition : public VoidFunctor<T,bool> {
		public:
			Condition( T* statementObject, bool (T::*statementFunction)(void) );
			virtual ~Condition() {}
			virtual bool operator()(void);
		};
	}
}

/*
Implementation of public functions
==============================================================================
*/

/*
|| Condition( statementObject, statementFunction )
|| 
|| @description
|| | Constructor for Conditions
|| #
*/
template<typename T,bool mode>
ab::functional::Condition<T,mode>::Condition( T* statementObject, bool (T::*statementFunction)(void) ) : VoidFunctor(statementObject,statementFunction) {
	//
}

/*
|| bool operator()( void )
||
|| @description
|| | Check if the condition evaluates true
|| #
||
|| @override	bool VoidFunctor<T,bool>::operator()( void )
|| @return		stateOfSuccess:bool of the condition
*/
template<typename T,bool mode>
bool ab::functional::Condition<T,mode>::operator()(void){ 
	return (mode==(*object.*function)()); 
}

#endif 
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Created Condition
|| #
*/