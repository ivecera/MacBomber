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

#ifndef ORTHO_H
#define ORTHO_H

//enable /disable Ortho Mode
void enableOrthoMode();
void disableOrthoMode();

// calculates a relative position (e.g 0.65) to an absolute position in px (e.g 500)
float relToAbs(float relValue, int axis);

// calculates a absolute position (e.g 400px) to an rel position in px (e.g 0.4)
float absToRel(float absValue, int axis);
#endif