/*
||
|| @file 	Functor.h
|| @version 1.1
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Implements a generic Functor object.
|| | Functor calls functions on object, on the form
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
#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "Functional.h"

namespace ab {
	namespace functional {
		template<class T,typename R=void,typename P=void>
		class Functor : public Functional<R,P> {
		public:
			Functor( T* statementObject, R (T::*statementFunction)(P) );
			virtual ~Functor() {}
			virtual R operator()(P p);
		protected:
			R (T::*function)(P);	// pointer to member function
			T* object;				// pointer to object
		};
	}
}

/*
Implementation of public functions
==============================================================================
*/

/*
|| Functor( statementObject, statementFunction )
|| 
|| @description
|| | Constructor for Functors
|| #
*/
template<class T,typename R,typename P>
ab::functional::Functor<T,R,P>::Functor( T* statementObject, R (T::*statementFunction)(P) ) {
	object = statementObject;
	function = statementFunction;
}

/*
|| R operator( parameter )
|| 
|| @description
|| | Call the function associated with this functor
|| #
|| 
|| @override	R Functional<R,P>::operator( P )
|| @parameter	parameter:P is sent to the object using function
|| @return		return:R is the result of function
*/
template<class T,typename R,typename P>
R ab::functional::Functor<T,R,P>::operator()( P parameter ) { 
	return (*object.*function)(parameter); 
}

#endif
/*
|| @changelog
|| | 1.1 2009-09-18 - Alexander Brevig : Moved to namespace ab::functional in file Functor.h
|| | 1.0 2009-09-14 - Alexander Brevig : Initial release
|| #
*/