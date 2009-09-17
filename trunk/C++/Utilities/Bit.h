/*
||
|| @file 	Bit.h
|| @version 1.0
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide a set of functions for manipulating bits in a variable
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
#include "typedefs.h"

///a namespace for handling bit operations
namespace Bit {
	template<typename T>
	static void set( T &source , byte bit ){
		source |= (1UL << (bit));
	}

	template<typename T>
	static bool get( T &source , byte bit ){
		return ((source >> bit) & 0x01);
	}

	template<typename T>
	static void clear( T &source , byte bit ){
		 source &= ~(1UL << bit);
	}

	template<typename T>
	static void write( T &source , byte bit , bool value ){
		 value ? set(source, bit) : clear(source, bit);
	}
}

/*
|| @changelog
|| | 1.0 2009-09-14 - Alexander Brevig : Created file
|| #
*/