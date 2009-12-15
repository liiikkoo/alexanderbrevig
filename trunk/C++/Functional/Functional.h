/*
||
|| @file 	Functional.h
|| @version 1.1
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Implements a generic interface for Functional programming
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
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

namespace ab {
	namespace functional {
		template<typename R,typename P>
		class Functional {
		public:
			virtual ~Functional(){}
			virtual R operator()(P) = 0;
		};
	}
}

#endif
/*
|| @changelog
|| | 1.1 2009-09-18 - Alexander Brevig : Filename is Functional.h
|| | 1.1 2009-09-18 - Alexander Brevig : Moved to namespace ab::functional
|| | 1.0 2009-09-14 - Alexander Brevig : Initial release
|| #
*/