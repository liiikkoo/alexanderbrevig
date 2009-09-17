/*
||
|| @file Button.h
|| @version 1.6
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Provide an easy way of making buttons
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

#ifndef BUTTON_H
#define BUTTON_H

#include <WProgram.h>

#define PULLUP HIGH
#define PULLDOWN LOW

#define CURRENT 0
#define PREVIOUS 1
#define CHANGED 2

class Button{
  public:
    Button(uint8_t buttonPin, uint8_t buttonMode=PULLDOWN);
    void pullup();
    void pulldown();
    bool isPressed();
    bool wasPressed();
    bool stateChanged();
	bool uniquePress();
  private: 
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
};

#endif

/*
|| @changelog
|| | 1.6 2009-05-05 - Alexander Brevig : Added uniquePress, it returns true if the state has changed AND the button is pressed
|| | 1.5 2009-04-24 - Alexander Brevig : Added stateChanged, @contribution http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=klickadiklick
|| | 1.4 2009-04-24 - Alexander Brevig : Added wasPressed, @contribution http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?action=viewprofile;username=klickadiklick
|| | 1.3 2009-04-12 - Alexander Brevig : Added constructor with one parameter Button(uint8_t buttonPin)
|| | 1.2 2009-04-10 - Alexander Brevig : Namechange from Switch to Button
|| | 1.1 2009-04-07 - Alexander Brevig : Altered API
|| | 1.0 2008-10-23 - Alexander Brevig : Initial Release
|| #
*/


