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

void TextureManager::loadTextures()
{
	//go ahead and load all Textures into our textureArray

	loadTexture(
		m_TextureArray, PLAYER1_TEXTURE,
		Application::expandResourcePath("/Textures/Players/RedMac.png")
			.c_str(),
		true);
	loadTexture(m_TextureArray, PLAYER2_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Players/BrownMac.png")
			    .c_str(),
		    true);
	loadTexture(
		m_TextureArray, PLAYER3_TEXTURE,
		Application::expandResourcePath("/Textures/Players/BlueMac.png")
			.c_str(),
		true);
	loadTexture(m_TextureArray, PLAYER4_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Players/WhiteMac.png")
			    .c_str(),
		    true);
	loadTexture(m_TextureArray, PLAYER_HAPPY_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Players/Player_happy.png")
			    .c_str(),
		    true);
	loadTexture(m_TextureArray, PLAYER_FRAGGED_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Players/Player_fragged.png")
			    .c_str(),
		    true);

	loadTexture(
		m_TextureArray, GOODIE_SPEEDUP_TEXTURE,
		Application::expandResourcePath("/Textures/Items/ItemSpeed.png")
			.c_str(),
		true);
	loadTexture(
		m_TextureArray, GOODIE_POWERUP_TEXTURE,
		Application::expandResourcePath("/Textures/Items/ItemPower.png")
			.c_str(),
		true);
	loadTexture(
		m_TextureArray, GOODIE_BOMBUP_TEXTURE,
		Application::expandResourcePath("/Textures/Items/ItemBomb.png")
			.c_str(),
		true);
	loadTexture(
		m_TextureArray, GOODIE_ENABLEKICK_TEXTURE,
		Application::expandResourcePath("/Textures/Items/ItemKick.png")
			.c_str(),
		true);
	loadTexture(m_TextureArray, GOODIE_ENABLETHROW_TEXTURE,
		    Application::expandResourcePath("/Textures/Items/item.png")
			    .c_str(),
		    true);
	loadTexture(
		m_TextureArray, BADIE_JOINT_TEXTURE,
		Application::expandResourcePath("/Textures/Items/ItemHash.png")
			.c_str(),
		true);
	loadTexture(m_TextureArray, BADIE_COCAINE_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Items/ItemCocaine.png")
			    .c_str(),
		    true);
	loadTexture(m_TextureArray, BADIE_VIAGRA_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Items/itemViagra.png")
			    .c_str(),
		    true);
	loadTexture(m_TextureArray, BADIE_CONDOM_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Items/itemCondom.png")
			    .c_str(),
		    true);

	loadTexture(m_TextureArray, FIELD_PLAIN0_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_plain0.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_PLAIN1_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_plain1.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_MUD0_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_Mud0.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_MUD1_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_Mud1.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_CRATEDEBRIS_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_CrateDebris.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_HOLE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_Hole2.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_ARROW,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_Arrow2.png")
			    .c_str());
	loadTexture(m_TextureArray, FIELD_RANDOM_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Fields/field_Random.png")
			    .c_str());

	loadTexture(
		m_TextureArray, BLOCK_TEXTURE,
		Application::expandResourcePath("/Textures/Blocks/block1.png")
			.c_str(),
		true);
	loadTexture(
		m_TextureArray, CRATE_TEXTURE,
		Application::expandResourcePath("/Textures/Crates/crate.png")
			.c_str());
	loadTexture(m_TextureArray, BOMB_TEXTURE,
		    Application::expandResourcePath("/Textures/Bomb/bomb.png")
			    .c_str());
	loadTexture(m_TextureArray, DESTROYER_TEXTURE,
		    Application::expandResourcePath("/Textures/Bomb/wiley.png")
			    .c_str());
	loadTexture(m_TextureArray, CUP_TEXTURE,
		    Application::expandResourcePath("/Textures/Cup/cup.png")
			    .c_str());

	loadTexture(m_TextureArray, KEYBOARD_IJKL_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Keyboards/keyboard-ijkl.png")
			    .c_str());
	loadTexture(m_TextureArray, KEYBOARD_ARROWS_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Keyboards/keyboard-arrows.png")
			    .c_str());
	loadTexture(m_TextureArray, KEYBOARD_WASD_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Keyboards/keyboard-wasd.png")
			    .c_str());
	loadTexture(m_TextureArray, KEYBOARD_FCVB_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Keyboards/keyboard-fcvb.png")
			    .c_str());
	loadTexture(m_TextureArray, JOYSTICK_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Keyboards/joystick.png")
			    .c_str());
	loadTexture(m_TextureArray, PLAYER_DISABLED_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Keyboards/Disabled.png")
			    .c_str());

	loadTexture(m_TextureArray, EXPLOSION_TEXTURE1,
		    Application::expandResourcePath(
			    "/Textures/Explosions/explosion1.png")
			    .c_str());
	loadTexture(m_TextureArray, EXPLOSION_TEXTURE2,
		    Application::expandResourcePath(
			    "/Textures/Explosions/explosion2.png")
			    .c_str());
	loadTexture(m_TextureArray, EXPLOSION_TEXTURE3,
		    Application::expandResourcePath(
			    "/Textures/Explosions/explosion3.png")
			    .c_str());

	loadTexture(m_TextureArray, PARTICLE_SMOKE0_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_smoke.png")
			    .c_str());
	loadTexture(m_TextureArray, PARTICLE_SMOKE1_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_smoke_small.png")
			    .c_str());
	loadTexture(m_TextureArray, PARTICLE_GOODIE_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_item.png")
			    .c_str());
	loadTexture(m_TextureArray, PARTICLE_BADIE_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_item.png")
			    .c_str());
	loadTexture(m_TextureArray, PARTICLE_CRATE_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_crate.png")
			    .c_str());
	loadTexture(m_TextureArray, PARTICLE_SPARK_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_spark.png")
			    .c_str());
	loadTexture(m_TextureArray, PARTICLE_WILEY_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/Particles/particle_wiley.png")
			    .c_str());

	loadTexture(m_TextureArray, MENU_ARROW_TEXTURE,
		    Application::expandResourcePath("/Textures/Menu/arrow.png")
			    .c_str());
	loadTexture(
		m_TextureArray, MENU_BACKGROUND_TEXTURE,
		Application::expandResourcePath("/Textures/Menu/background.png")
			.c_str());
	loadTexture(
		m_TextureArray, TIMEBAR_TEXTURE,
		Application::expandResourcePath("/Textures/Menu/timebar.png")
			.c_str());
	loadTexture(m_TextureArray, CLOCK_TEXTURE,
		    Application::expandResourcePath("/Textures/Menu/clock.png")
			    .c_str());
	loadTexture(m_TextureArray, EYE_TEXTURE,
		    Application::expandResourcePath("/Textures/Menu/eye.png")
			    .c_str());
	loadTexture(m_TextureArray, GAME_BACKGROUND_TEXTURE,
		    Application::expandResourcePath(
			    "/Textures/GameBackgrounds/clouds.png")
			    .c_str());
}

void TextureManager::bindTexture(int index)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureArray[index]);
}
