/*
||
|| @file 	VoidFunctor.h
|| @version 1.0
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Implements a generic VoidFunctor object.
|| | VoidFunctor calls functions on object, on the form
|| | R class::function( void )
|| #
||
|| @dependencies
|| | Functional.h
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
#ifndef VOIDFUNCTOR_H
#define VOIDFUNCTOR_H

#include "Functional.h"

namespace ab {
	namespace functional {
		template<class T,typename R=void>
		class VoidFunctor : public Functional<R,void> {
		public:
			VoidFunctor( T* statementObject, R (T::*statementFunction)(void) );
			virtual ~VoidFunctor() {}
			virtual R operator()( void );
		protected:
			R (T::*function)( void );	// pointer to member function
			T* object;				// pointer to object
		};
	}
}

/*
Implementation of public functions
==============================================================================
*/

/*
|| VoidFunctor( statementObject, statementFunction )
|| 
|| @description
|| | Constructor for Functors
|| #
*/
template<class T,typename R>
ab::functional::VoidFunctor<T,R>::VoidFunctor( T* statementObject, R (T::*statementFunction)(void) ) {
	object = statementObject;
	function = statementFunction;
}

/*
|| R operator( void )
|| 
|| @description
|| | Call the function associated with this VoidFunctor
|| #
|| 
|| @override	R Functional<R,P>::operator( void )
|| @parameter	parameter:P is sent to the object using function
|| @return		return:R is the result of function
*/
template<class T,typename R>
R ab::functional::VoidFunctor<T,R>::operator()( void ) { 
	return (*object.*function)(); 
}

#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Initial release
|| #
*/