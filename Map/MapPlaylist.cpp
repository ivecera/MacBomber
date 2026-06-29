/*
 *  MapPlaylist.cpp
 *  MacBomber
 *
 *  Created by Altay Cebe on 06.08.06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include "../Application.h"
#include "../Config.h"

#include "MapPlaylist.h"

MapPlaylist::MapPlaylist()
{
	m_bRandom = Application::m_pConfig->getRandomMapOrder();
	m_iTotalMapCount = 0;
	m_itCurrent = m_vMapEntryIndices.begin();
}

void MapPlaylist::addMapIndex(int index)
{
	m_iTotalMapCount++;
	if (m_bRandom) {
		if (m_vMapEntryIndices.size() == 0) {
			m_vMapEntryIndices.push_back(index);
		} else {
			//insert index at a random postion within the vector
			int iPosition = rand() % m_vMapEntryIndices.size();
			vector<int>::iterator it = m_vMapEntryIndices.begin();
			it += iPosition;
			m_vMapEntryIndices.insert(it, index);
		}

	} else
		m_vMapEntryIndices.push_back(index);

	m_itCurrent = m_vMapEntryIndices.begin();
}

void MapPlaylist::setNextMapIndex()
{
	// Did we reach the end of the vector ?
	if (m_itCurrent + 1 == m_vMapEntryIndices.end())
		m_itCurrent = m_vMapEntryIndices.begin();
	else
		m_itCurrent++;
}

int MapPlaylist::getCurrentMapIndex()
{
	return *m_itCurrent;
}

void MapPlaylist::showIndices()
{
	vector<int>::iterator it;
	for (it = m_vMapEntryIndices.begin(); it != m_vMapEntryIndices.end();
	     it++) {
		printf("%d\n", *it);
	}
	printf("\n");
}
