/*
||
|| @file 	Functor.h
|| @version 1.0
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Implements a generic function object
|| #
||
|| @usage
|| | class Example { public: int execute(bool doExecute){ return (doExecute?10:0); } };
|| | Example ex;
|| | Functor<Example,int,bool> f(ex, &Example::execute);
|| | f(true); //execute function
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

template<class T,typename R=void,typename P=void>
class Functor {
public:
	Functor( T* obj, R (T::*funct)(P) ) { object=obj; function = funct; }
	R operator()(P p) { return (*object.*function)(p); }
private:
	R (T::*function)(P);	// pointer to member function
	T* object;				// pointer to object
};

#endif
/*
|| @changelog
|| | 1.0 2009-09-14 - Alexander Brevig : Initial release
|| #
*/