#ifndef INCLUDE_HPP_INCLUDED
#define INCLUDE_HPP_INCLUDED

#define WIDTH 1680

#define WIDTH_SPRITE 64
#define WIDTH_PLAYER_X 64
#define WIDTH_PLAYER_Y 64
#define WIDTH_NPC_X 64
#define WIDTH_NPC_Y 64
#define WIDTH_OBJECT_X 64
#define WIDTH_OBJECT_Y 64
#define WIDTH_OBJECT_DOOR_X 128
#define WIDTH_OBJECT_DOOR_Y 64
#define WIDTH_OBJECT_TELEPORTATION_X 64
#define WIDTH_OBJECT_TELEPORTATION_Y 64
#define WIDTH_LIGHT 512
#define WIDTH_MESSAGE_X 216
#define WIDTH_MESSAGE_Y 88
#define WIDTH_MENU_X 216
#define WIDTH_MENU_Y 88

#define WIDTH_BULLET_X_BULLET 6
#define WIDTH_BULLET_Y_BULLET 25
#define WIDTH_BULLET_X_FLAME 64
#define WIDTH_BULLET_Y_FLAME 100
#define WIDTH_BULLET_X_GRENADE 200
#define WIDTH_BULLET_Y_GRENADE 200
#define WIDTH_BULLET_X_MINE 200
#define WIDTH_BULLET_Y_MINE 200
#define WIDTH_BULLET_X_SWORD 128
#define WIDTH_BULLET_Y_SWORD 64

#define FPS 60
#define PI 3.14159265359
#define TIME_MAX_BULLET_BULLET 2500
#define TIME_MAX_BULLET_FLAME 100
#define TIME_MAX_BULLET_GRENADE 320
#define TIME_MAX_BULLET_MINE 320
#define TIME_MAX_BULLET_SWORD 120
#define TIME_BEFORE_BULLET_GRENADE_EXPLOSION 2000
#define TIME_BETWEEN_BULLET_GRENADE_MOUVEMENT 125
#define TIME_BETWEEN_DEGAT 500
#define TIME_BETWEEN_WIN_GAMEOVER 2000
#define TIME_BETWEEN_LOADING 3000
#define TIME_MAX_TELEPORTATION 3000
#define TIME_MAX_MESSAGE 4000
#define NUMBER_WEAPON_PLAYER 11
#define TIME_BETWEEN_CREATE_MESSAGE_ERROR_WINCHANGELEVEL 4500
#define TIME_BETWEEN_SEARCHPATHPLAYER 1500

#define FONT_GUI "fonts/Fishfingers.ttf"
#define FONT_GUI_MESSAGE "fonts/SourceSansPro-Semibold.ttf"
#define FONT_GUI_MENU "fonts/SourceSansPro-Semibold.ttf"

#define SPRITE_LIGHTS "sprites/lights.png"
#define SPRITE_OBJECT "sprites/object.png"
#define SPRITE_OBJECT_CARD "sprites/cards.png"
#define SPRITE_OBJECT_DOOR "sprites/doors.png"
#define SPRITE_OBJECT_WEAPON "sprites/weapons.png"
#define SPRITE_TILES "sprites/tiles.png"
#define SPRITE_BONUS "sprites/bonus.png"
#define SPRITE_MALUS "sprites/malus.png"
#define SPRITE_OBJECT_TELEPORTATION "sprites/teleportations.png"
#define SPRITE_LOGO "sprites/icone.png"
#define SPRITE_GAGNE "sprites/gagne.png"

#define SPRITE_BULLET_BULLET "sprites/bullets.png"
#define SPRITE_BULLET_FLAME "sprites/bulletFlame.png"
#define SPRITE_BULLET_GRENADE "sprites/bulletGrenade.png"
#define SPRITE_BULLET_MINE "sprites/bulletMine.png"
#define SPRITE_BULLET_SWORD "sprites/bulletSword.png"
#define SPRITE_BULLET_GRENADE_EXPLODED "sprites/bulletGrenadeExploded.png"
#define SPRITE_BULLET_MINE_EXPLODED "sprites/bulletMineExploded.png"

#define SPRITE_PLAYERS_WEAPON_1 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_2 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_3 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_4 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_5 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_6 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_7 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_8 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_9 "sprites/players.png"
#define SPRITE_PLAYERS_WEAPON_10 "sprites/players.png"

#define SPRITE_MESSAGE "sprites/message.png"
#define SPRITE_MENU "sprites/message.png"

#define NODE_DISTANCE_VALUE 64

#include <iostream>
#include <fstream>
#include <list>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include "tinyxml.h"
#include <SFML/Graphics.hpp>

int getScreen();
int getGameplay();

enum action { MENU = 0, NEWGAME = 1, LOADGAME = 2, GAMEOVER = 3, WIN = 4, PAUSE = 5, SAVE = 6 }; //l'action en cours à un moment donné

enum objet_bonus { BONUS_SPEED = 1, BONUS_LIFE = 2, BONUS_AMMUNITION = 3 }; //types de bonus

enum objet_malus { MALUS_SPEED = 1, MALUS_LIFE = 2, MALUS_AMMUNITION = 3 }; //types de malus

enum position_collision { HAUT = 0, BAS = 1, DROITE = 2, GAUCHE = 3 }; //types de malus

enum menu_pause { MENU_PAUSE_RETURN = 1, MENU_PAUSE_QUIT = 2, MENU_PAUSE_SAVE = 3 }; //les 3 boutons du menu pause

enum menu_game { MENU_NEW_GAME = 1, MENU_LOAD_GAME = 2, MENU_QUIT = 3 }; //les 3 boutons du menu pause

enum npc_action { STARTBASE_TO_ENDBASE = 0, ENDBASE_TO_STARTBASE = 1, NPC_TO_STARTBASE = 2, NPC_TO_ENDBASE = 3, NPC_TO_PLAYER = 4}; //les differentes actions remplies par un npc

enum npc_find_path { NPC_FIND_PATH_FALSE = false, NPC_FIND_PATH_TRUE = true}; //le npc a trouve son chemin ou non ?

typedef struct PositionItem PositionItem;
struct PositionItem{
    float x, y, rotate;
};

typedef struct GuiMessageItem GuiMessageItem;
struct GuiMessageItem{
    long time_max, execution_time;
    std::string message1, message2, message3;
    sf::Sprite sprite;
    PositionItem position;
};

typedef struct GuiMenuItem GuiMenuItem;
struct GuiMenuItem{
    int id, decalageLeftMessage;
    std::string message;
    sf::Sprite sprite;
    PositionItem position;
};

int distancePoint(int x1, int y1, int x2, int y2);

#include "soundmanager.hpp"
#include "musicmanager.hpp"

#endif // INCLUDE_HPP_INCLUDED
