cmake_minimum_required(VERSION 3.10)
project(MacBomber LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)
pkg_check_modules(SDL3_MIXER REQUIRED sdl3-mixer)
pkg_check_modules(FTGL REQUIRED ftgl)

find_library(LIB3DS_LIBRARY NAMES 3ds 3ds-1)
find_path(LIB3DS_INCLUDE_DIR lib3ds/file.h)

set(SOURCES
    main.cpp
    Application.cpp
    Config.cpp
    Explosion.cpp

    Controller/Controller.cpp
    Controller/Controller_Joystick.cpp
    Controller/Controller_Keyboard.cpp

    Engine/3DMath.cpp
    Engine/Billboard.cpp
    Engine/BoundingBox_2D.cpp
    Engine/Camera.cpp
    Engine/checkScreenResolution.cpp
    Engine/Clock.cpp
    Engine/Init.cpp
    Engine/InputManager.cpp
    Engine/loadTexture.cpp
    Engine/MeshManager.cpp
    Engine/ortho.cpp
    Engine/ScreenFader.cpp
    Engine/SimpleBezier.cpp
    Engine/SoundManager.cpp
    Engine/TextDrawer.cpp
    Engine/TextureManager.cpp
    Engine/Timer.cpp
    Engine/TriangleMesh.cpp
    Engine/Wobbler.cpp

    Engine/ParticleSystem/Particle.cpp
    Engine/ParticleSystem/Particle_Crate.cpp
    Engine/ParticleSystem/Particle_Explosion.cpp
    Engine/ParticleSystem/Particle_Item.cpp
    Engine/ParticleSystem/ParticleManager.cpp
    Engine/ParticleSystem/Particle_Smoke.cpp
    Engine/ParticleSystem/Particle_SmokeTrail.cpp

    Gametypes/Game.cpp
    Gametypes/Game_MapDestruction.cpp
    Gametypes/Game_Standard.cpp

    Map/Field.cpp
    Map/Field_Arrow.cpp
    Map/Field_Block.cpp
    Map/Field_Hole.cpp
    Map/Field_Plain.cpp
    Map/Field_Void.cpp
    Map/Map.cpp
    Map/MapDestroyer.cpp
    Map/MapManager.cpp
    Map/MapPlaylist.cpp
    Map/Shaker.cpp

    Menu/ApplicationMenu.cpp
    Menu/ControllerSetupItem.cpp
    Menu/HUD.cpp
    Menu/LabelItem.cpp
    Menu/LevelScrollListItem.cpp
    Menu/LevelSelectionMenu.cpp
    Menu/MapPreview.cpp
    Menu/Menu.cpp
    Menu/MenuItem.cpp
    Menu/MenuSwitchItem.cpp
    Menu/PlayerSetupItem.cpp
    Menu/PlayerSetupMenu.cpp
    Menu/PlayerSetupRow.cpp
    Menu/ScoreScreen.cpp
    Menu/Timebar.cpp
    Menu/ToggleItem.cpp
    Menu/ValueItem.cpp

    MeshObjects/BlockMesh.cpp
    MeshObjects/BombMesh.cpp
    MeshObjects/CrateMesh.cpp
    MeshObjects/CupMesh.cpp
    MeshObjects/ItemMesh.cpp
    MeshObjects/Mesh.cpp
    MeshObjects/PlayerMesh.cpp
    MeshObjects/SquareMesh.cpp

    Objects/Bomb.cpp
    Objects/BombThrower.cpp
    Objects/Crate.cpp
    Objects/Item.cpp
    Objects/Item_BombUp.cpp
    Objects/Item_Cocaine.cpp
    Objects/Item_Condom.cpp
    Objects/Item_EnableKick.cpp
    Objects/Item_Joint.cpp
    Objects/Item_PowerUp.cpp
    Objects/Item_SpeedUp.cpp
    Objects/Item_Viagra.cpp
    Objects/ItemManager.cpp
    Objects/ItemThrower.cpp
    Objects/Object.cpp
    Objects/Object_Moving.cpp
    Objects/ObjectThrower.cpp
    Objects/ObjectThrowerManager.cpp
    Objects/Player.cpp
    Objects/Wiley.cpp
)

add_executable(macbomber ${SOURCES})

target_compile_definitions(macbomber PRIVATE
    GL_GLEXT_PROTOTYPES
    GLM_FORCE_CTOR_INIT
)

target_include_directories(macbomber PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${SDL3_INCLUDE_DIRS}
    ${SDL3_IMAGE_INCLUDE_DIRS}
    ${SDL3_MIXER_INCLUDE_DIRS}
    ${FTGL_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${LIB3DS_INCLUDE_DIR}
)

target_link_libraries(macbomber PRIVATE
    OpenGL::GL
    glm::glm
    ${SDL3_LIBRARIES}
    ${SDL3_IMAGE_LIBRARIES}
    ${SDL3_MIXER_LIBRARIES}
    ${FTGL_LIBRARIES}
    Freetype::Freetype
    ZLIB::ZLIB
    ${LIB3DS_LIBRARY}
)

