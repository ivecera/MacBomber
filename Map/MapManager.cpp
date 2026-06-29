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

#include "../Application.h"
#include "../Config.h"
#include "MapManager.h"
#include "MapPlaylist.h"

using namespace std;
MapManager::MapManager()
{
	//	m_cDirectory = "../maps/";
	//create a path to the Maps Files within the Bundle
	string tmp = Application::expandResourcePath("/Maps/");
	m_cDirectory = tmp.c_str();
	readMaps();
	//	currentMap = m_vMapEntries.begin();

	m_iEnabledMapsCount = 0;
	// Load Map Status from Config
	for (int i = 0; i < (getMapCount()); i++) {
		m_vMapEntries[i].enabled =
			Application::m_pConfig->getMapStatus(i);
		//keep Track of the amount of enabled maps
		if (m_vMapEntries[i].enabled)
			m_iEnabledMapsCount++;
	}

	//	showMaps();
}

MapManager::~MapManager()
{
}

static char *readLine(char **pos, char *buf, int maxlen)
{
	if (!*pos)
		return NULL;
	char *nl = SDL_strchr(*pos, '\n');
	int len = nl ? (int)(nl - *pos) : SDL_strlen(*pos);
	if (len >= maxlen)
		len = maxlen - 1;
	SDL_memcpy(buf, *pos, len);
	buf[len] = '\0';
	*pos = nl ? nl + 1 : NULL;
	return buf;
}

void MapManager::readMap(StMapEntry &mapEntry)
{
	char *mapName = mapEntry.name;
	char fileName[150] = { 0 };

	SDL_strlcat(fileName, m_cDirectory, sizeof(fileName));
	SDL_strlcat(fileName, mapName, sizeof(fileName));

	SDL_IOStream *io = SDL_IOFromFile(fileName, "r");
	if (!io) {
		SDL_Log("MapManager: File %s not found!", fileName);
		exit(-1);
	}

	Sint64 size = SDL_GetIOSize(io);
	char *data = (char *)SDL_malloc(size + 1);
	SDL_ReadIO(io, data, size);
	data[size] = '\0';
	SDL_CloseIO(io);

	char *pos = data;

	readLine(&pos, mapEntry.author, 100);
	char tmp[18];
	readLine(&pos, tmp, sizeof(tmp));
	SDL_sscanf(tmp, "%d", &mapEntry.playerCount);

	// First, all fields are set to void
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 19; j++)
			mapEntry.cArray[i][j] = '-';

	//Read the array line by line from the file
	for (int i = 1; i < 14; i++) {
		char line[18];
		readLine(&pos, line, sizeof(line));

		for (int j = 0; j < 17; j++)
			mapEntry.cArray[i][j + 1] = line[j];
	}
	mapEntry.enabled = true;

	SDL_free(data);
}

void MapManager::readMaps()
{
	int count = 0;
	char **files = SDL_GlobDirectory(m_cDirectory, "*.map", 0, &count);
	if (!files)
		return;

	m_vMapEntries.reserve(count);

	for (int i = 0; i < count; i++) {
		StMapEntry mapEntry;
		SDL_strlcpy(mapEntry.name, files[i], sizeof(mapEntry.name));
		readMap(mapEntry);

		//Edit Map Name, for e.g: "Big_Standard.map"  --> "Big Standard"

		// 1. Replace underscores by spaces
		char *strTmp;
		while ((strTmp = SDL_strchr(mapEntry.name, '_')) != NULL)
			*strTmp = ' ';

		// 2. cut .map extension
		char *dot = SDL_strchr(mapEntry.name, '.');
		if (dot != NULL)
			*dot = '\0';

		m_vMapEntries.push_back(mapEntry);
	}
	SDL_free(files);
}

void MapManager::showMaps()
{
	vector<StMapEntry>::iterator it;

	for (it = m_vMapEntries.begin(); it != m_vMapEntries.end(); it++) {
		SDL_Log("Map: %s", (*it).name);
		SDL_Log("Players: %d", (*it).playerCount);

		for (int i = 0; i < 15; i++) {
			char row[20];
			for (int j = 0; j < 19; j++)
				row[j] = (*it).cArray[i][j];
			row[19] = '\0';
			SDL_Log("%s", row);
		}
	}
}

/*
void MapManager::reset()
{
	currentMap = m_vMapEntries.begin();
	while ((*currentMap).enabled == false)
		currentMap++;
	//FIX ME: runs forever if no map enabled !!!
}
*/

/*
void MapManager::setNextMap()
{
	// Did we reach the end of the vector ?
	if (currentMap+1 == m_vMapEntries.end())
		currentMap = m_vMapEntries.begin();
	else
		currentMap++;
	
	//check if currentMap is enabled. If not go to next map
	if ( (*currentMap).enabled == false) 
		setNextMap(); 
//	return *(currentMap);
}
*/
int MapManager::getMapCount()
{
	return m_vMapEntries.size();
}
/*
StMapEntry MapManager::getCurrentMap()
{
	return *currentMap;
}
*/
// get Nap nr
StMapEntry MapManager::getMap(int nr)
{
	if (nr < 0)
		nr = 0;
	if (nr > (int)m_vMapEntries.size())
		nr = m_vMapEntries.size();

	return (m_vMapEntries[nr]);
}

void MapManager::toggleMap(int nr)
{
	//m_vMapEntries[nr].enabled = !m_vMapEntries[nr].enabled;
	if (m_vMapEntries[nr].enabled) {
		m_iEnabledMapsCount--;
		m_vMapEntries[nr].enabled = false;

	} else {
		m_iEnabledMapsCount++;
		m_vMapEntries[nr].enabled = true;
	}
}

MapPlaylist *MapManager::getPlaylist()
{
	//build a playlist
	MapPlaylist *pPlaylist = new MapPlaylist();
	for (int i = 0; i < (int)m_vMapEntries.size(); i++) {
		if (m_vMapEntries[i].enabled)
			pPlaylist->addMapIndex(i);
	}

	//pPlaylist->showIndices();
	return pPlaylist;
}

void MapManager::enableAll()
{
	for (int i = 0; i < (int)m_vMapEntries.size(); i++) {
		if (!m_vMapEntries[i].enabled) {
			m_vMapEntries[i].enabled = true;
			m_iEnabledMapsCount++;
		}
	}
}

void MapManager::disableAll()
{
	for (int i = 0; i < (int)m_vMapEntries.size(); i++) {
		if (m_vMapEntries[i].enabled) {
			m_vMapEntries[i].enabled = false;
			m_iEnabledMapsCount--;
		}
	}
}

void MapManager::storeSettings()
{
	// tell Config about the total Map Count
	Application::m_pConfig->setMapCount(getMapCount());

	//loop through all Maps and check for their enabled/disabled status
	for (int i = 0; i < getMapCount(); i++) {
		Application::m_pConfig->setMapStatus(i,
						     m_vMapEntries[i].enabled);
	}
}
