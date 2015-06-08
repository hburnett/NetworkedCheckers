/*--------------------------------------------------------------------
Author: Heath Burnett

Description: Player class, contains the player character for the game
---------------------------------------------------------------------*/

#ifndef	PLAYER_H
#define PLAYER_H

#include "Vec2.h"
#include "Hitbox.h"

class Vec2;
class StaticSprite;
class Texture;
class SpriteBatch;

class Player
{

public:

	// Default constructor
	Player();

	~Player();

	void Update( float dt );

	void Draw( SpriteBatch *sb );
	

	//--------------------------------VARIABLES-------------------------------------
	
	


private:
	

};

#endif