#ifndef Defines_H
/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#define Defines_H

#define UP 0    // z+
#define RIGHT 1 // x+
#define DOWN 2  // z-
#define LEFT 3  // x-

#define NONE 4  // keine Bewegung
#define BOMB 5

#define DRAWGAME 666


#define SPEEDUP 4
#define POWERUP 5
#define BOMBUP  6
#define ENABLEKICK 7
#define JOINT 9
#define COCAINE 10
#define VIAGRA 11
#define CONDOM 35

// Typ Definitionen für Felder
#define FIELD 0
#define HOLE 1
#define ARROW_UP 14
#define ARROW_DOWN 15 
#define ARROW_LEFT 16
#define ARROW_RIGHT 17
#define BLOCK 6
#define VOID 7
#define ICE 8

#define PLAYER1_TEXTURE 0
#define PLAYER2_TEXTURE 1
#define PLAYER3_TEXTURE 2
#define PLAYER4_TEXTURE 3
#define PLAYER_HAPPY_TEXTURE 4
#define PLAYER_FRAGGED_TEXTURE 5
 
#define GOODIE_SPEEDUP_TEXTURE 6
#define GOODIE_POWERUP_TEXTURE 7
#define GOODIE_BOMBUP_TEXTURE 8
#define GOODIE_ENABLEKICK_TEXTURE 9
#define GOODIE_ENABLETHROW_TEXTURE 10
#define BADIE_JOINT_TEXTURE 11
#define BADIE_COCAINE_TEXTURE 12
#define BADIE_VIAGRA_TEXTURE 13
#define BADIE_CONDOM_TEXTURE 14 

#define FIELD_PLAIN0_TEXTURE 15
#define FIELD_PLAIN1_TEXTURE 16
#define FIELD_MUD0_TEXTURE 17
#define FIELD_MUD1_TEXTURE 44
#define FIELD_CRATEDEBRIS_TEXTURE 45
#define FIELD_HOLE 18
#define FIELD_ARROW 19
#define FIELD_RANDOM_TEXTURE 20

#define BLOCK_TEXTURE 21
#define CRATE_TEXTURE 22
#define BOMB_TEXTURE 23
#define DESTROYER_TEXTURE 24
#define CUP_TEXTURE 25

#define KEYBOARD_IJKL_TEXTURE 26
#define KEYBOARD_ARROWS_TEXTURE 27
#define KEYBOARD_WASD_TEXTURE 28
#define KEYBOARD_FCVB_TEXTURE 29
#define JOYSTICK_TEXTURE 30
#define PLAYER_DISABLED_TEXTURE 31


#define EXPLOSION_TEXTURE1 32
#define EXPLOSION_TEXTURE2 46
#define EXPLOSION_TEXTURE3 47

#define PARTICLE_SMOKE0_TEXTURE 33	//Large Smoke
#define PARTICLE_SMOKE1_TEXTURE 34	//Small Smoke
#define PARTICLE_GOODIE_TEXTURE 35
#define PARTICLE_BADIE_TEXTURE 36
#define PARTICLE_CRATE_TEXTURE 37
#define PARTICLE_SPARK_TEXTURE 38
#define PARTICLE_WILEY_TEXTURE 48


#define MENU_ARROW_TEXTURE 39
#define MENU_BACKGROUND_TEXTURE 40
#define TIMEBAR_TEXTURE 41
#define CLOCK_TEXTURE 42
#define EYE_TEXTURE 43
#define GAME_BACKGROUND_TEXTURE 49	

// Typedefs for sounds & Music
#define EXPlOSION_SOUND 0
#define PUTBOMB_SOUND 1
#define CRUNCH_SOUND 2

#define MENU_MUSIC 0
#define GAME_MUSIC 2
#define SCORESCREEN_MUSIC 1

// Typedefs for objects
#define PLAYER_OBJECT 0
#define ITEM_OBJECT 1
#define FIELD_OBJECT 2
#define BLOCK_OBJECT 3
#define CRATE_OBJECT 4
#define BOMB_OBJECT 5
#define CUP_OBJECT 6

//Typedefs for font size
#define SMALL 0
#define STD 1
#define BIG 2

//Typedefs for MenuItems
#define CLABELITEM 0
#define CMENUSWITCHITEM 1
#define CTOGGLEITEM 2
#define CVALUEITEM 3

#endif