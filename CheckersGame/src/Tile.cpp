#include "Tile.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "StaticSprite.h"
#include "Globals.h"
#include "InputManager.h"
#include <iostream>

Tile::Tile(float x, float y, float w, float h, int tileNumber, Tile::OccupantState state)
{	
	m_v2Position = Vec2(x, y);
	m_v2Dimensions = Vec2(w, h);
	m_iTileNumber = tileNumber;
	m_eCurrentState = state;

	m_rRectangle = RectangleHitbox(x, y, w, h);
}

Tile::~Tile()
{
} 

void Tile::Draw(SpriteBatch *sb)
{
}