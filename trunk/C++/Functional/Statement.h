/*
||
|| @file	Statement.h
|| @version 1.0
|| @author	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide a framework for implementing generic statements
|| | A statement has one or more conditions
|| #
||
|| @dependencies
|| | Condition.h
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
#ifndef STATEMENT_H
#define STATEMENT_H

#include "Condition.h"
#include "Functional.h"

typedef unsigned int uint;

namespace ab {
	namespace functional {
		template<typename P, uint size=1>
		class Statement : public Functional<bool,P>{
		public:
			typedef Functional<bool,P> function;

			Statement( void );
			Statement( function* conds[size] );
			virtual ~Statement() {}

			virtual bool operator()(void);

		protected:
			Functional<bool,P>* conditions[size];
		};
	}
}


/*
|| Statement( void )
|| 
|| @description
|| | Constructor for Statements
|| #
*/
template<typename P, uint size=1>
ab::functional::Statement<P,size>::Statement( void ){
	//
}

/*
|| Statement( functions* [] )
|| 
|| @description
|| | Constructor for Statements
|| #
||
|| @parameter	conds:function*[]
*/
template<typename P, uint size=1>
ab::functional::Statement<P,size>::Statement( function* conds[size] ) {
	for (uint i=0; i<size; i++){
		conditions[i] = conds[i];
	}
}

/*
|| bool operator( void )
|| 
|| @description
|| | Call the function associated with this Functoinal object
|| #
|| 
|| @override	bool Functional<bool,P>::operator( void )
|| @return		return:R is the result of function
*/
template<typename P, uint size=1>
bool ab::functional::Statement<P,size>::operator()(void) {
	bool stateOfSuccess = true;
	for (uint i=0; i<size; i++){
		if (! (*conditions[i])()){
			stateOfSuccess = false;
		}
	}
	return stateOfSuccess;
}

#endif 
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Created Condition
|| #
*/