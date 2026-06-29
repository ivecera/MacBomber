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

#include <string>
#include <iostream>
using namespace std;

#include "TextureManager.h"
#include "loadTexture.h"
#include "../Defines.h"
#include "../Application.h"

TextureManager::TextureManager()
{
}

const char *TextureManager::expand(const char *path)
{
	string tmp = Application::m_strResourcePath;
	tmp = tmp + path;
	return tmp.c_str();
}

void TextureManager::loadTextures()
{
	//go ahead and load all Textures into our textureArray

	loadTexture(m_TextureArray, PLAYER1_TEXTURE,
		    expand("/Textures/Players/RedMac.png"), true);
	loadTexture(m_TextureArray, PLAYER2_TEXTURE,
		    expand("/Textures/Players/BrownMac.png"), true);
	loadTexture(m_TextureArray, PLAYER3_TEXTURE,
		    expand("/Textures/Players/BlueMac.png"), true);
	loadTexture(m_TextureArray, PLAYER4_TEXTURE,
		    expand("/Textures/Players/WhiteMac.png"), true);
	loadTexture(m_TextureArray, PLAYER_HAPPY_TEXTURE,
		    expand("/Textures/Players/Player_happy.png"), true);
	loadTexture(m_TextureArray, PLAYER_FRAGGED_TEXTURE,
		    expand("/Textures/Players/Player_fragged.png"), true);

	loadTexture(m_TextureArray, GOODIE_SPEEDUP_TEXTURE,
		    expand("/Textures/Items/ItemSpeed.png"), true);
	loadTexture(m_TextureArray, GOODIE_POWERUP_TEXTURE,
		    expand("/Textures/Items/ItemPower.png"), true);
	loadTexture(m_TextureArray, GOODIE_BOMBUP_TEXTURE,
		    expand("/Textures/Items/ItemBomb.png"), true);
	loadTexture(m_TextureArray, GOODIE_ENABLEKICK_TEXTURE,
		    expand("/Textures/Items/ItemKick.png"), true);
	loadTexture(m_TextureArray, GOODIE_ENABLETHROW_TEXTURE,
		    expand("/Textures/Items/item.png"), true);
	loadTexture(m_TextureArray, BADIE_JOINT_TEXTURE,
		    expand("/Textures/Items/ItemHash.png"), true);
	loadTexture(m_TextureArray, BADIE_COCAINE_TEXTURE,
		    expand("/Textures/Items/ItemCocaine.png"), true);
	loadTexture(m_TextureArray, BADIE_VIAGRA_TEXTURE,
		    expand("/Textures/Items/itemViagra.png"), true);
	loadTexture(m_TextureArray, BADIE_CONDOM_TEXTURE,
		    expand("/Textures/Items/itemCondom.png"), true);

	loadTexture(m_TextureArray, FIELD_PLAIN0_TEXTURE,
		    expand("/Textures/Fields/field_plain0.png"));
	loadTexture(m_TextureArray, FIELD_PLAIN1_TEXTURE,
		    expand("/Textures/Fields/field_plain1.png"));
	loadTexture(m_TextureArray, FIELD_MUD0_TEXTURE,
		    expand("/Textures/Fields/field_Mud0.png"));
	loadTexture(m_TextureArray, FIELD_MUD1_TEXTURE,
		    expand("/Textures/Fields/field_Mud1.png"));
	loadTexture(m_TextureArray, FIELD_CRATEDEBRIS_TEXTURE,
		    expand("/Textures/Fields/field_CrateDebris.png"));
	loadTexture(m_TextureArray, FIELD_HOLE,
		    expand("/Textures/Fields/field_Hole2.png"));
	loadTexture(m_TextureArray, FIELD_ARROW,
		    expand("/Textures/Fields/field_Arrow2.png"));
	loadTexture(m_TextureArray, FIELD_RANDOM_TEXTURE,
		    expand("/Textures/Fields/field_Random.png"));

	loadTexture(m_TextureArray, BLOCK_TEXTURE,
		    expand("/Textures/Blocks/block1.png"), true);
	loadTexture(m_TextureArray, CRATE_TEXTURE,
		    expand("/Textures/Crates/crate.png"));
	loadTexture(m_TextureArray, BOMB_TEXTURE,
		    expand("/Textures/Bomb/bomb.png"));
	loadTexture(m_TextureArray, DESTROYER_TEXTURE,
		    expand("/Textures/Bomb/wiley.png"));
	loadTexture(m_TextureArray, CUP_TEXTURE,
		    expand("/Textures/Cup/cup.png"));

	loadTexture(m_TextureArray, KEYBOARD_IJKL_TEXTURE,
		    expand("/Textures/Keyboards/keyboard-ijkl.png"));
	loadTexture(m_TextureArray, KEYBOARD_ARROWS_TEXTURE,
		    expand("/Textures/Keyboards/keyboard-arrows.png"));
	loadTexture(m_TextureArray, KEYBOARD_WASD_TEXTURE,
		    expand("/Textures/Keyboards/keyboard-wasd.png"));
	loadTexture(m_TextureArray, KEYBOARD_FCVB_TEXTURE,
		    expand("/Textures/Keyboards/keyboard-fcvb.png"));
	loadTexture(m_TextureArray, JOYSTICK_TEXTURE,
		    expand("/Textures/Keyboards/joystick.png"));
	loadTexture(m_TextureArray, PLAYER_DISABLED_TEXTURE,
		    expand("/Textures/Keyboards/Disabled.png"));

	loadTexture(m_TextureArray, EXPLOSION_TEXTURE1,
		    expand("/Textures/Explosions/explosion1.png"));
	loadTexture(m_TextureArray, EXPLOSION_TEXTURE2,
		    expand("/Textures/Explosions/explosion2.png"));
	loadTexture(m_TextureArray, EXPLOSION_TEXTURE3,
		    expand("/Textures/Explosions/explosion3.png"));

	loadTexture(m_TextureArray, PARTICLE_SMOKE0_TEXTURE,
		    expand("/Textures/Particles/particle_smoke.png"));
	loadTexture(m_TextureArray, PARTICLE_SMOKE1_TEXTURE,
		    expand("/Textures/Particles/particle_smoke_small.png"));
	loadTexture(m_TextureArray, PARTICLE_GOODIE_TEXTURE,
		    expand("/Textures/Particles/particle_item.png"));
	loadTexture(m_TextureArray, PARTICLE_BADIE_TEXTURE,
		    expand("/Textures/Particles/particle_item.png"));
	loadTexture(m_TextureArray, PARTICLE_CRATE_TEXTURE,
		    expand("/Textures/Particles/particle_crate.png"));
	loadTexture(m_TextureArray, PARTICLE_SPARK_TEXTURE,
		    expand("/Textures/Particles/particle_spark.png"));
	loadTexture(m_TextureArray, PARTICLE_WILEY_TEXTURE,
		    expand("/Textures/Particles/particle_wiley.png"));

	loadTexture(m_TextureArray, MENU_ARROW_TEXTURE,
		    expand("/Textures/Menu/arrow.png"));
	loadTexture(m_TextureArray, MENU_BACKGROUND_TEXTURE,
		    expand("/Textures/Menu/background.png"));
	loadTexture(m_TextureArray, TIMEBAR_TEXTURE,
		    expand("/Textures/Menu/timebar.png"));
	loadTexture(m_TextureArray, CLOCK_TEXTURE,
		    expand("/Textures/Menu/clock.png"));
	loadTexture(m_TextureArray, EYE_TEXTURE,
		    expand("/Textures/Menu/eye.png"));
	loadTexture(m_TextureArray, GAME_BACKGROUND_TEXTURE,
		    expand("/Textures/GameBackgrounds/clouds.png"));
}

void TextureManager::bindTexture(int index)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureArray[index]);
}
