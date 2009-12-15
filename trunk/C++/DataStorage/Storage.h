/*
||
|| @file Storage.h
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of managing raw c++ arrays
|| #
||
|| @dependencies
|| | Functional.h
|| | Functor.h
|| | Call.h
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
#ifndef STORAGE_H
#define STORAGE_H

#include "PushPop.h"
#include "Functional.h"
#include "Functor.h"
#include "Call.h"

typedef unsigned int uint;

namespace ab {
	template<typename T>
	class Storage : public PushPop<T> {
	public: 
		typedef ab::functional::Call<void,T> callback;
		typedef ab::functional::Functor<void,T> functor;

		virtual ~Storage(){}

		static void		foreach			( Storage &storage, ab::functional::Functional<void,T> &action );

		//Storage
		//	modification
		virtual T		remove			( T ) = 0;			//remove an item from the Storage
		virtual T*		clear			( void ) = 0;		//clear the Storage
		//	access
		virtual bool	isEmpty			( void ) const = 0;	//check to see if the Storage is empty
		virtual uint	size			( void ) const = 0;	//request the size of the Storage
		virtual T		get				( int ) = 0;		//get an element from the Storage at specified index
		virtual bool	contains		( T ) = 0;			//check to see if the Storage contains specified element
		virtual uint	capacity		( void ) = 0;		//request the current capacity of the Storage
		//  operators
		virtual T&	operator[]			( int ) = 0;		//acces modifiable element at specified index
		virtual T	operator[]			( int ) const = 0;	//acces unmodifiable element at specified index
	};
}

/*
Implementation of public functions
==============================================================================
*/

/*
|| void foreach( storage, action )
||
|| @description
|| | Do the same action on all elements in a storage
|| #
|| 
|| @parameter	storage:Storage& that will be used
|| @parameter	action:Functional<void,T>& that triggers on every element
*/
template<typename T>
void ab::Storage<T>::foreach( Storage &storage, ab::functional::Functional<void,T> &action ){
	uint size = storage.size();
	for (uint i=0; i<size; i++){
		action(storage[i]);
	}
}

#endif
/*
|| @changelog
|| | 1.0 2009-09-18 - Alexander Brevig : Created Rule
|| #
*/