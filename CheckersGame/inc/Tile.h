/*----------------------------------------------------------------------------------
Author: Heath Burnett

Description: Checker class, contains the checkers the player plays with
----------------------------------------------------------------------------------*/

#ifndef	TILE_H
#define TILE_H

#include "Vec2.h"
#include <vector>
#include "Hitbox.h"

class Vec2;
class StaticSprite;
class Texture;
class SpriteBatch; 

class Tile
{
public:

	enum OccupantState
	{
		WHITE,
		BLACK,
		EMPTY
	};


	Tile(float x, float y, float w, float h, int tileNumber, OccupantState state);

	~Tile();

	void Draw(SpriteBatch *sb);
	RectangleHitbox m_rRectangle;
	
	int m_iTileNumber;
	Vec2 m_v2Position;

	OccupantState m_eCurrentState;


private:


	Vec2 m_v2Dimensions;


	// Texture is used for creating sprite
	Texture		 *m_texPiece;

	// Sprite is used for drawing
	StaticSprite *m_sprPiece;

};
#endif