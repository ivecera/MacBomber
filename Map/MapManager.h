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

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <vector>
#include "StMapEntry.h"

using namespace std;
class MapPlaylist;

class MapManager {
private:
	vector<StMapEntry> m_vMapEntries;
	const char *m_cDirectory;
	//	vector<StMapEntry>::iterator currentMap;

	void readMaps();
	void readMap(StMapEntry &mapEntry);

	int m_iEnabledMapsCount;

public:
	MapManager();
	~MapManager();

	// goes back to the first enabled map entry
	//void reset();
	void showMaps();
	//void setNextMap();	// set Next Map (According to playlist)

	// returns total number of Maps
	int getMapCount();
	// returns total number of *enabled* Maps
	int getEnabledMapCount()
	{
		return m_iEnabledMapsCount;
	};

	//StMapEntry getCurrentMap();// return current Map
	// get Nap nr
	StMapEntry getMap(int nr);

	//disables Map Nr nr
	void toggleMap(int nr);

	MapPlaylist *getPlaylist();

	//enables all stored maps
	void enableAll();
	//disables all stored maps
	void disableAll();

	//stores Information about enabled Maps to the Config
	void storeSettings();
};

#endif
