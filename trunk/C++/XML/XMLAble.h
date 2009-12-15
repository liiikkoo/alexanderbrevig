#ifndef XMLABLE_H
#define XMLABLE_H

#include <iostream>
using std::ostream;

#include "Log.h"

namespace ab {
	namespace xml {
		class XMLAble {
		public:
			XMLAble() {LOG(Log::LOG_INFO, "Constructing");}
			~XMLAble() {
				LOG(Log::LOG_INFO, "Destructing");
			}
			virtual friend ostream &operator<<( ostream &, const XMLAble & ) = 0;
		};
	}
}

#endif