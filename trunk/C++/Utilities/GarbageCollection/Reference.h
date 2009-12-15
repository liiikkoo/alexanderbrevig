/*
||
|| @file 	Reference.h
|| @version 1.0
|| @author 	Alexander Brevig / Robin B. Pettersen
|| @contact alexanderbrevig@gmail.com / ssbmtonberry@gmail.com
||
|| @description
|| | Implements a generic References that counts the number of references to its address.
|| #
||
|| @license
|| | Copyright (C) 2009  Alexander Brevig & Robin B. Pettersen
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
#ifndef REFERENCE_H
#define REFERENCE_H

#include <iostream>
using std::ostream;
#include "Log.h"

typedef unsigned int uint;

namespace ae {
	template<class T>
	struct Reference {
		Reference( T* addr=0 ) : address(addr) { referenceCount=1; }
		~Reference(){ LOG(Log::LOG_INFO,"Destructing"); delete address; }
		T* address;
		uint referenceCount;
		bool operator==( T &rhs ){ return (address==rhs); }
	};
}

#endif
/*
|| @changelog
|| | 1.0 2009-09-14 - Alexander Brevig : Created file
|| #
*/