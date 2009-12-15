/*
||
|| @file 	Call.h
|| @version 1.0
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Implements a generic Call object.
|| | Call calls functions on object, on the form
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
#ifndef CALL_H
#define CALL_H

#include "Functional.h"

namespace ab {
	namespace functional {
		template<typename R=void,typename P=int>
		class Call : public Functional<R,P> {
		public:
			Call( R (*callFunction)(P) );
			virtual ~Call() {}
			virtual R operator()(P parameter);
		protected:
			R (*function)(P);	// pointer to member function
		};
	}
}


/*
Implementation of public functions
==============================================================================
*/

/*
|| Call( callFunction )
|| 
|| @description
|| | Constructor for Calls
|| #
*/
template<typename R,typename P>
ab::functional::Call<R,P>::Call( R (*callFunction)(P) ) { 
	function = callFunction; 
}

/*
|| R operator( parameter )
|| 
|| @description
|| | Call the function associated with this Call
|| #
|| 
|| @override	R Functional<R,P>::operator( P )
|| @parameter	parameter:P is sent to the function
|| @return		return:R is the result of function
*/
template<typename R,typename P>
R ab::functional::Call<R,P>::operator()( P parameter ) { return (*function)(parameter); }

#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Initial release
|| #
*/