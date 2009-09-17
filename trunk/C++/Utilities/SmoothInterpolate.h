/*
||
|| @file 	SmoothInterpolate.h
|| @version 1.1
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way doint smooth interpolation
|| | Modeled after: http://danthompsonsblog.blogspot.com/2009/02/smoothstep-interpolation-with-arduino.html
|| #
||
|| @information
|| | This is a redundant release of the C++ library SmoothInterpolate.
|| | There might be a newer version online.
|| | Please refer to: http://code.google.com/p/alexanderbrevig/source/browse/trunk#trunk/C++/Utilities/SmoothInterpolate
|| #
||
|| @usage
|| | float arr[2] = { 0.0, 1.0}; //from 0.0 to 1.0
|| | SmoothInterpolate< 2 , 21 > smoothInterpolate = arr; //you start with 2 values, and you have 21 steps between each value
|| | smoothInterpolate.calculate(); //smooth interpolate
|| | float smoothed = smoothInterpolate[2]; //acces the third value (index 2)
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

#ifndef SmoothInterpolate_h
#define SmoothInterpolate_h

typedef unsigned int uint;

template<uint start,uint steps>
class SmoothInterpolate {
public:
	SmoothInterpolate( void ){/*default constructor*/}
	SmoothInterpolate( float* arr ){
		for (uint i=0; i<start; i++){
			raw[i*steps] = arr[i]; 
		}
	}
	void calculate(){
		for (uint i=0; i<(start-1); i++){
			float min = raw[i*steps];
			float max = raw[(i+1)*steps];
			for (uint j=1; j<steps; j++){
				float v = (steps-j) / (float)steps;  
				v = smooth(v);
				raw[(i*steps)+j] = (min * v) + (max * (1 - v)); 
			}
		}
	}
	const uint length() const { return (start*steps)-steps+1; }

	float* operator=( float* arr ){
		for (uint i=0; i<start; i++){
			raw[i*steps] = arr[i]; 
		}
	}
	float &operator[](uint index){
		return raw[index]; //unsafe
	}
	
	static float smooth( float var ){
		return (var * var * (3 - 2 * var));
	}
private:
	float raw[ (start*steps)-steps+1 ];
};

#endif

/*
|| @changelog
|| | 1.1 2008-09-16 - Alexander Brevig : Library require float arrays and values
|| | 1.0 2008-09-16 - Alexander Brevig : Initial Release
|| #
*/
