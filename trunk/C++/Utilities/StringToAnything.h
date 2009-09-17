/*
||
|| @file 	StringToAnything.cpp
|| @version 1.0
|| @author 	Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of retrieving data from char arrays
|| #
||
|| @usage
|| | char* str = "123.45"; //some string
|| | StringToAnything<float,5> readFloat = str; //initialize and prepare for 5 numerical symbols request integer result
|| | float fl = readFloat.convert();
|| | //- Alternatively you can 'build' your input on the run:
|| | StringToAnything<int,10> readBinary;
|| | readBinary += '1';
|| | readBinary += '0';
|| | readBinary += '0';
|| | readBinary += '1';
|| | int bn = readBinary.convert(BIN);
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
#ifndef STRINGTOANYTHING_H
#define STRINGTOANYTHING_H

typedef unsigned int uint;

#define ASCII_START 48
#define HEXA_TO_ASCII_MODIFIER 39

#ifndef DEC //not arduino platform, define base identifiers
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#endif


namespace ab {
	//a homemade recursive pow function
	template<typename b>
	b pow(b base, uint exponent){
		if (exponent==0){
			return 1;
		} else {
			return base * pow(base,exponent-1);
		}
	}
}

template<typename T,uint size>
class StringToAnything {
public:
	StringToAnything(){
		currentIndex = 0;
		for (uint i=0; i<size+1; i++) { input[i] = '\0'; }
	}
	StringToAnything(char *str){
		currentIndex = 0;
		setInput(str);
	}

	char *operator=( char *str ){
		setInput(str);
	}

	StringToAnything &operator+=( long in ){
		if (currentIndex+1<=size){
			input[currentIndex++] = (char)in;
		}
		return *this;
	}

	//a homemade atoT
	T convert( uint base=DEC ){
		
		float sum = 0;				//this is the return value of this function
		float current = 0;			//this value will store each calculation
		bool isNegative = false;	//becomes true if input string starts with '-'
		uint floatPunctuation = 0;	//this will contain the index of '.' if present
		uint length = 0;			//input string length
		char* str = &input[0];		//the string to convert
		
		//calulate str length
		while (*str){ 
			str++;
			if (*str) { length++; } //do not count '\0'
		}

		str=&input[0];//move pointer back to start

		uint i = 0;//iterator
		//check if user want a float as result
		while (*str){ 
			if ((*str)=='.' || (*str)==',') { 
				floatPunctuation = i; 
				length = (floatPunctuation-1);
				break;
			}
			i++;	//increment iterator
			str++;	//proceed to next char+;
		}

		str=&input[0];//move pointer back to start

		//check if user want a negative result
		if (*str=='-'){ 
			isNegative = true; 
			length--;//skip '-'
			str++;//skip '-'
		}
		
		i = 0; //reset iterator
		//calculate value
		while (*str){ //loop until end of string
			current = 0; //assume the current value to be 0
			if ((*str)>=ASCII_START&&(*str)<=ASCII_START+1){//[0,1]
				//calculate the current value
				current = ((*str)-ASCII_START) * ab::pow((float)base,length-i);
			} else if ((*str)>=ASCII_START+2&&(*str)<=ASCII_START+7){//[2,7]
				if (base!=BIN){
					current = ((*str)-ASCII_START) * ab::pow((float)base,length-i);
				}
			}  else if ((*str)>=ASCII_START+8&&(*str)<=ASCII_START+9){//[8,0]
				if (base!=BIN && base!=OCT){
					current = ((*str)-ASCII_START) * ab::pow((float)base,length-i);
				}
			} else if ( (*str)>=97 && (*str)<=108 && base==HEX ){//[a,f]
				current = ((*str)-ASCII_START-HEXA_TO_ASCII_MODIFIER) * ab::pow((float)base,length-i);
			}
			sum += current; //add the current calculated value to the sum
			i++;	//increment iterator
			str++;	//proceed to next char
			if (floatPunctuation){
				if (i>=floatPunctuation){ 
					break; 
				}
			}
		}

		str=&input[floatPunctuation+1];//move pointer to post punctuation

		i = 1; //start counting at 1 because 1/10^1 = 0.1
		
		//calculate decimals
		if (floatPunctuation){
			while (*str){
				current = 0; //assume the current value to be 0
				if ((*str)>=ASCII_START&&(*str)<=ASCII_START+1){//[0,1]
					//calculate the current value
					current = ((*str)-ASCII_START) * (1/ab::pow((float)base,i));
				} else if ((*str)>=ASCII_START+2&&(*str)<=ASCII_START+7){//[2,7]
					if (base!=BIN){
						current = ((*str)-ASCII_START) * (1/ab::pow((float)base,i));
					}
				}  else if ((*str)>=ASCII_START+8&&(*str)<=ASCII_START+9){//[8,9]
					if (base!=BIN && base!=OCT){
						current = ((*str)-ASCII_START) * (1/ab::pow((float)base,i));
					}
				} else if ( (*str)>=97 && (*str)<=108 && base==HEX ){//[a,f]
					current = ((*str)-ASCII_START-HEXA_TO_ASCII_MODIFIER) * (1/ab::pow((float)base,i));
				}
				sum += current; //add the current calculated value to the sum
				
				i++;	//increment iterator
				str++;	//proceed to next char
			}
		}
		return (T)(isNegative ? -sum : sum); //return the sum, either positive or negative
	}
	
private:
	void setInput( char *str ){
		currentIndex = 0;
		while (*str && currentIndex<=size){
			input[currentIndex] = *str;
			currentIndex++;
			str++;
		}
		input[currentIndex] = '\0';
	}
	
	char input[size+2]; //account for '.' and '\0'
	uint currentIndex;
};

#endif
/*
|| @changelog
|| | 1.0 2009-09-17 - Alexander Brevig : Initial Release
|| #
*/