/*
||
|| @file 	ReferenceList.h
|| @version 1.0
|| @author 	Alexander Brevig / Robin B. Pettersen
|| @contact alexanderbrevig@gmail.com / ssbmtonberry@gmail.com
||
|| @description
|| | Implements a generic list of References.
|| | This list implementes reference counting, and provides functions for adding to, retrieving - and removing from.
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
#ifndef REFERENCELIST_H
#define REFERENCELIST_H

//TODO

#include "Log.h"
#include "List.h"
using ae::List;
#include "Reference.h"

typedef unsigned int uint;

namespace ae {
	template<class T>
	class ReferenceList {
	public:
		ReferenceList() { 
			LOG(Log::LOG_INFO, "Constructing");
		}

		/*virtual*/ ~ReferenceList() {	
			LOG(Log::LOG_INFO, "Destructing");
		}

		//get the size of the ReferenceList
		uint size() { return referenceList.size(); }
		
		List< Reference<T>* >& getList( void ) { return referenceList; }

		//get the reference at the specified index:uint 
		Reference<T>* get( uint index ) { return referenceList.get(index); }

		//add ref:T* to the ReferenceList
		bool add( T* ref ) {
			Reference<T>* reference = getReferenceFor(ref);
			if (reference) { //this address is already used
				LOG(Log::LOG_INFO, "Incrementing a reference count");
				reference->referenceCount++;
				return false;
			} else {
				LOG(Log::LOG_INFO, "Adding a reference to the list");
				referenceList.push(new Reference<T>(ref));
			}
			return true;
		}

		//remove ref:T* from the ReferenceList
		bool remove( T* ref ) {
			Reference<T>* reference = getReferenceFor(ref);
			if (reference) {
				reference->referenceCount--;
				if (reference->referenceCount<=0) {
				LOG(Log::LOG_INFO, "Removing a reference from the list");
					//TODO define criteria
					collect();
				}
				return true;
			} 
			return false;
		}

		//get a reference for the address ref:T* (NULL if unavailable)
		Reference<T>* getReferenceFor( T* ref ) {
			for (uint i=0; i<referenceList.size(); i++) {
				if (referenceList.get(i)->address == ref) {
					return referenceList.get(i);
				}
			}
			return 0;
		}

		//TODO reimplement using LinkedList library
		//remove all references with referenceCound <= 0
		bool collect() {
			LOG(Log::LOG_INFO, "Collecting unreferenced pointers from the list");
			writeList();
			bool collected = false;
			for  (uint i=0; i<referenceList.size(); i++) {
				if (referenceList.get(i)->referenceCount <= 0) {
					referenceList.pop(); //current
				}
			}
			writeList();
			return collected;
		}

		//write the contents of this list to the log
		void writeList() {
			char out[128];
			sprintf_s(out,128, " MemPtr:   RefCount:");
			LOG(Log::LOG_DEBUG,out);
			if(referenceList.size() > 0) {
				for (uint i=0; i<referenceList.size(); i++) {
					sprintf_s(out,128, "[%08d]     %d", referenceList.get(i)->address, referenceList.get(i)->referenceCount);
					LOG(Log::LOG_DEBUG,out);
				}
			} else {
				LOG(Log::LOG_DEBUG, " (empty)    (empty)");
			}
		}

	private:
		List< Reference<T>* > referenceList;
	};
}

#endif
/*
|| @changelog
|| | 1.1 2009-09-16 - Alexander Brevig : Added logging
|| | 1.0 2009-09-14 - Alexander Brevig : Created file
|| #
*/