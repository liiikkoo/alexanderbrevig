/*
||
|| @file Array.h
|| @version 1.1
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of managing raw c++ arrays
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
|| #
||
*/
#ifndef ARRAY_H
#define ARRAY_H

typedef unsigned int uint;

template<class T,uint size>
class Array {
public:
	Array( void ) : length(size) {/*nothing to construct*/}
	Array( T* arr ) : length(size) { setRaw(arr); }
	~Array() {/*nothing to destruct*/}

	T &operator=( T* arr ) { setRaw(arr); return raw; }

	T &operator[]( int index ) { return raw[(index<length?index:(length-1))]; }
	
	operator T*() { return raw; }

	uint length;

private:
	void setRaw( T *arr ) { 
		for (uint i=0; i<length; i++) { 
			raw[i] = arr[i]; 
		}
	}
	T raw[size];
};

#endif
/*
|| @changelog
|| | 1.1 2009-09-17 - Alexander Brevig : Added conversion operator
|| | 1.0 2009-09-14 - Alexander Brevig : Created file
|| #
*/