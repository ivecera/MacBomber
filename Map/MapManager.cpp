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

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

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

void MapManager::readMap(StMapEntry &mapEntry)
{
	char *mapName = mapEntry.name;
	char fileName[150] = { 0 };

	strcat(fileName, m_cDirectory);
	strcat(fileName, mapName);

	ifstream in;
	in.open(fileName);

	if (!in) {
		printf("MapManager: File %s not found!", fileName);
		exit(-1);
	}

	in.getline(mapEntry.author, 100, '\n');
	in >> mapEntry.playerCount;

	// First, all fields are set to void
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 19; j++)
			mapEntry.cArray[i][j] = '-';

	// discard the extra line
	char panties[18];
	in.getline(panties, 18, '\n');

	//Read the array line by line from the file
	for (int i = 1; i < 14; i++) {
		char line[18];
		in.getline(line, 18, '\n');

		for (int j = 0; j < 17; j++)
			mapEntry.cArray[i][j + 1] = line[j];
	}
	mapEntry.enabled = true;
	in.close();
}

void MapManager::readMaps()
{
	DIR *pDir = opendir(m_cDirectory);
	struct dirent *entry;

	while ((entry = readdir(pDir)) != NULL) {
		if (strstr(entry->d_name, ".map") !=
		    NULL) //Filter out all non-.map files
		{
			StMapEntry mapEntry;

			//			mapEntry.name = entry->d_name;
			strcpy(mapEntry.name, entry->d_name);
			m_vMapEntries.push_back(mapEntry);
		}
	}

	vector<StMapEntry>::iterator it;

	for (it = m_vMapEntries.begin(); it != m_vMapEntries.end(); it++) {
		readMap((*it));
		//Edit Map Name, for e.g: "Big_Standard.map"  --> "Big Standard"

		// 1. Replace underscore by Space FIXME: Only replaces ONE _ !!!
		char *strTmp = strchr((*it).name, '_');
		if (strTmp != NULL)
			*strTmp = ' ';

		// 2. cut .map extension
		strtok((*it).name, ".");
	}

	closedir(pDir);
}

void MapManager::showMaps()
{
	vector<StMapEntry>::iterator it;

	for (it = m_vMapEntries.begin(); it != m_vMapEntries.end(); it++) {
		cout << endl << "Map: " << (*it).name << endl;
		cout << "Players: " << (*it).playerCount << endl;

		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 19; j++) {
				printf("%c", (*it).cArray[i][j]);
			}
			printf("\n");
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
