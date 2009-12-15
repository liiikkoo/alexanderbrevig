/*
||
|| @file 	VoidCall.h
|| @version 1.0
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Implements a generic VoidCall object.
|| | VoidCall calls functions on object, on the form
|| | R class::function( P )
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
#ifndef VOIDCALL_H
#define VOIDCALL_H

#include "Functional.h"

namespace ab {
	namespace functional {
		template<typename R=void>
		class VoidCall : public Functional<R,void> {
		public:
			VoidCall( R (*funct)(void) );
			virtual ~VoidCall() {}

			virtual R operator()( void );
		protected:
			R (*function)();	// pointer to member function
		};
	}
}

/*
Implementation of public functions
==============================================================================
*/

/*
|| VoidCall( callFunction )
|| 
|| @description
|| | Constructor for VoidCalls
|| #
*/
template<typename R>
ab::functional::VoidCall<R>::VoidCall( R (*callFunction)(void) ) { 
	function = callFunction; 
}

/*
|| R operator()( void )
|| 
|| @description
|| | VoidCall the function associated with this VoidCall
|| #
|| 
|| @override	R Functional<R,P>::operator( void )
*/
template<typename R>
R ab::functional::VoidCall<R,P>::operator()( P parameter ) { return (*function)(void); }

#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Initial release
|| #
*/