/*----------------------------------------------------------------------------------
Author: Heath Burnett

Description: Checker class, contains the checkers the player plays with
----------------------------------------------------------------------------------*/

#ifndef	CHECKER_H
#define CHECKER_H

#include "Vec2.h"
#include <vector>
#include "Hitbox.h"
#include "Tile.h"

class Vec2;
class StaticSprite;
class Texture;
class SpriteBatch;

struct JumpTarget
{
	int jumpTile;
	int targetTile;

	JumpTarget(int j, int t) { jumpTile = j; targetTile = t; }
};

class Checker
{
public:


	//----------------- Functions -------------------------------


	Checker(float x, float y, float w, float h, int currentTile, bool white);

	~Checker();

	void Update(float dt);
	void Draw(SpriteBatch *sb);
	
	void UpdateMoves();
	bool TryMoveToTarget(int targetTile);
	bool TryJumpToTarget(int targetTile);
	void KingMe();

	//----------------- Variables -------------------------------


	RectangleHitbox m_rRectangle;

	// If not white, then it is black
	bool m_bIsWhite;
	bool m_bIsKing;
	bool m_bIsSelected;
	bool m_bIsCurrentTurn;

	int m_iCurrentTile;
	std::vector<int> m_vrTilesCanMoveTo;
	std::vector<JumpTarget> m_vrTilesCanJumpTo;
	std::vector<Tile> m_vrTileList;
	Vec2 m_v2Position;


	//-----------------------------------------------------------



private:


	//------------ Functions --------------------


	int CheckIfCanMoveUpRight();
	int CheckIfCanMoveDownRight();

	int CheckIfCanMoveUpLeft();
	int CheckIfCanMoveDownLeft();

	JumpTarget CheckIfCanJumpUpRight();
	JumpTarget CheckIfCanJumpDownRight();
				 
	JumpTarget CheckIfCanJumpUpLeft();
	JumpTarget CheckIfCanJumpDownLeft();

	//------------ Variables --------------------


	Vec2 m_v2Dimensions;

	// Texture is used for creating sprite
	Texture		 *m_texPiece;
	Texture		 *m_texSelector;

	// Sprite is used for drawing
	StaticSprite *m_sprPiece;
	StaticSprite *m_sprSelector;

	//-------------------------------------------

};
#endif