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

#ifndef STMAPENTRY_H
#define STMAPENTRY_H

struct StMapEntry {
	char name[256]; //Mapname
	char author[100]; //Created by...
	//		z(lines) x(cols)
	char cArray[15]
		   [19]; // [13][17] -- + bounding Voidfields ->  [15][19] [y][x]
	int playerCount; // number of Players
	bool enabled; // true if this map is not in Playlist
};

#endif