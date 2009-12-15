#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
using std::string;

#include "Log.h"

namespace ab {
	namespace xml {
		class Attribute {
		public:
			Attribute() {LOG(Log::LOG_INFO, "Constructing");}
			~Attribute() {
				LOG(Log::LOG_INFO, "Destructing");
				name.clear();
				value.clear();
			}
			void print() { cout << " "<<name<<"=\"" << value << "\""; }
			string name;
			string value;
		};
	}
}

#endif