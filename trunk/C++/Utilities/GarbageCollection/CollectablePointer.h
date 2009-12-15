/*
||
|| @file 	CollectablePointer.h
|| @version 1.1
|| @author 	Alexander Brevig / Robin B. Pettersen
|| @contact alexanderbrevig@gmail.com / ssbmtonberry@gmail.com
||
|| @description
|| | Implements a generic pointer with garbage collection.
|| | Collection will occur every time a reference count reaches 0, and/or when a CollectablePointer goes out of scope.
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
#ifndef COLLECTABLEPOINTER_H
#define COLLECTABLEPOINTER_H

#include "Log.h"
#include "ReferenceList.h"

namespace ae {
	template<class T>
	class CollectablePointer {
	public:
		CollectablePointer( void );
		CollectablePointer( T *address );
		virtual ~CollectablePointer( void );

		//request a T* to the data of this CollectablePointer
		T *operator->();

		//assign this CollectablePointer to address:T*
		T *operator=( T *address );

		static ReferenceList<T>& getReferenceList();

		bool operator==( T *address ) const;
		bool operator==( CollectablePointer &address ) const;

		//set the address of this CollectablePointer
		void setAddress( T *address );
	protected:
		bool hasAddress;
		T *thisAddress;
		static ReferenceList<T> referenceList;
	private:
	};
}

/*
Implementation of public functions
==============================================================================
*/

template<class T>
ae::CollectablePointer<T>::CollectablePointer( void ) {
	LOG(Log::LOG_INFO, "Constructing default");
	thisAddress = 0;
	hasAddress = false;
}

template<class T>
ae::CollectablePointer<T>::CollectablePointer( T *address ) {
	LOG(Log::LOG_INFO, "Constructing with address");
	hasAddress = false;
	setAddress(address);
}

template<class T>
ae::CollectablePointer<T>::~CollectablePointer() {
	{LOG(Log::LOG_INFO,"Destructing");}
	referenceList.remove(thisAddress);
}


template<class T>
ae::ReferenceList<T> ae::CollectablePointer<T>::referenceList;

template<class T>
T *ae::CollectablePointer<T>::operator->() {
	return thisAddress;
}

template<class T>
T *ae::CollectablePointer<T>::operator=( T *address ) {
	setAddress(address);
	return address;
}

template<class T>
ae::ReferenceList<T>& ae::CollectablePointer<T>::getReferenceList() {
	return referenceList;
}

template<class T>
bool ae::CollectablePointer<T>::operator==( T *address ) const {
	if (hasAddress) {
		return (address==thisAddress);
	}
	return false;
}

template<class T>
bool ae::CollectablePointer<T>::operator==( CollectablePointer &address ) const {
	if (hasAddress) {
		return (address.thisAddress == thisAddress);
	}
	return false;
}

template<class T>
void ae::CollectablePointer<T>::setAddress( T *address ) {
	LOG(Log::LOG_INFO, "Changing adress");
	if (hasAddress){
		referenceList.remove(thisAddress);	//decrement the referenceCount for thisAddress
	}
	if (!hasAddress) {
		hasAddress = true; 
	}	//if we had no address, that changed
	thisAddress = address; 			//set thisAddress
	referenceList.add(thisAddress);	//add thisAddress to the referenceList
}



#endif
/*
|| @changelog
|| | 1.1 2009-09-16 - Alexander Brevig : Added logging
|| | 1.0 2009-09-14 - Alexander Brevig : Created file
|| #
*/