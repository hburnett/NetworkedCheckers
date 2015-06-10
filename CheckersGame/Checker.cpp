#include "Checker.h"
#include "SpriteBatch.h"
#include "Texture.h"
#include "StaticSprite.h"
#include "Globals.h"
#include "InputManager.h"
#include <iostream>

Checker::Checker(float x, float y, float w, float h, int currentTile, bool white)
{
	m_v2Position = Vec2(x, y);
	m_v2Dimensions = Vec2(w, h);
	m_bIsWhite = white;
	m_iCurrentTile = currentTile;
	m_bIsSelected = false;
	m_bIsKing = false;
	m_bIsCurrentTurn = white;

	m_texSelector = new Texture("./Images/whiteSelector.png");

	if (white)
	{
		m_texPiece = new Texture("./Images/whitePawn.png");
	}

	else
	{
		m_texPiece = new Texture("./Images/blackPawn.png");
	}


	m_sprPiece = new StaticSprite(m_texPiece, Vec2(w, h));
	m_sprPiece->Transform().SetTranslation(Vec2(x, y));

	m_sprSelector = new StaticSprite(m_texSelector, Vec2(w, h));
	m_sprSelector->Transform().SetTranslation(Vec2(x, y));

	m_rRectangle = RectangleHitbox(x, y, w, h);
}

Checker::~Checker()
{
	//delete m_sprPiece;
	//delete m_sprSelector;
	//
	//delete m_texPiece;
	//delete m_texSelector;

	
}

void Checker::Update(float dt)
{
}

void Checker::Draw(SpriteBatch *sb)
{
	m_sprPiece->Transform().SetTranslation(m_v2Position);
	m_sprPiece->Draw(sb);

	if (m_bIsCurrentTurn)
		m_sprSelector->SetColour(0, 0, 255, 122);

	else
	{
		m_sprSelector->SetColour(0, 0, 0, 0);
	}

	if (m_bIsSelected)
	{
		m_sprSelector->SetColour(255, 0, 0, 200);
	}
	
	m_sprSelector->Transform().SetTranslation(m_v2Position);
	m_sprSelector->Draw(sb);
}

void Checker::UpdateMoves()
{
	m_vrTilesCanMoveTo.clear();

	int moveUpRight		=	CheckIfCanMoveUpRight();
	int moveDownRight	=	CheckIfCanMoveDownRight();
	int moveUpLeft		=	CheckIfCanMoveUpLeft();
	int moveDownLeft	=	CheckIfCanMoveDownLeft();

	if (moveUpRight != -1)
	{
		m_vrTilesCanMoveTo.push_back(moveUpRight);
		printf("Can move piece %i to %i\n", m_iCurrentTile, moveUpRight);
	}


	if (moveDownRight != -1)
	{
		m_vrTilesCanMoveTo.push_back(moveDownRight);
		printf("Can move piece %i to %i\n", m_iCurrentTile, moveDownRight);
	}


	if(moveUpLeft    != -1)
	{
		m_vrTilesCanMoveTo.push_back(moveUpLeft);
		printf("Can move piece %i to %i\n", m_iCurrentTile, moveUpLeft);
	}

	
	if(moveDownLeft  != -1)
	{
		m_vrTilesCanMoveTo.push_back(moveDownLeft);
		printf("Can move piece %i to %i\n", m_iCurrentTile, moveDownLeft);
	}

	JumpTarget jumpUpRight		= CheckIfCanJumpUpRight();
	JumpTarget jumpDownRight	= CheckIfCanJumpDownRight();
	JumpTarget jumpUpLeft		= CheckIfCanJumpUpLeft();
	JumpTarget jumpDownLeft		= CheckIfCanJumpDownLeft(); 

	m_vrTilesCanJumpTo.clear();

	if (jumpUpRight.jumpTile != -1)
	{
		m_vrTilesCanJumpTo.push_back(jumpUpRight);
		printf("Piece at %i can jump %i and land on %i\n", m_iCurrentTile, jumpUpRight.targetTile, jumpUpRight.jumpTile);
	}


	if (jumpDownRight.jumpTile != -1)
	{
		m_vrTilesCanJumpTo.push_back(jumpDownRight);
		printf("Piece at %i can jump %i and land on %i\n", m_iCurrentTile, jumpDownRight.targetTile, jumpDownRight.jumpTile);
	}


	if (jumpUpLeft.jumpTile != -1)
	{
		m_vrTilesCanJumpTo.push_back(jumpUpLeft);
		printf("Piece at %i can jump %i and land on %i\n", m_iCurrentTile, jumpUpLeft.targetTile, jumpUpLeft.jumpTile);
	}


	if (jumpDownLeft.jumpTile != -1)
	{
		m_vrTilesCanJumpTo.push_back(jumpDownLeft);
		printf("Piece at %i can jump %i and land on %i\n", m_iCurrentTile, jumpDownLeft.targetTile, jumpDownLeft.jumpTile);
	}


	printf("\n");


}

bool Checker::TryMoveToTarget(int targetTile)
{
	m_bIsSelected = false;

	for each (int tile in m_vrTilesCanMoveTo)
	{
		if (tile == targetTile)
		{
			m_v2Position = m_vrTileList[tile].m_v2Position;
			m_rRectangle = RectangleHitbox(m_v2Position, m_v2Dimensions);	
			return true;
		}
	}

	printf("Can't move there\n");

	return false;
}

bool Checker::TryJumpToTarget(int targetTile)
{
	m_bIsSelected = false;

	for each (JumpTarget set in m_vrTilesCanJumpTo)
	{
		if (set.jumpTile == targetTile)
		{
			m_v2Position = m_vrTileList[set.jumpTile].m_v2Position;
			m_rRectangle = RectangleHitbox(m_v2Position, m_v2Dimensions);
			return true;
		}
	}

	printf("Can't jump there\n");

	return false;
}

void Checker::KingMe()
{
	if (m_bIsWhite)
	{
		if (m_iCurrentTile > 55)
		{
			m_bIsKing = true;
			delete m_texPiece;
			delete m_sprPiece;
			m_texPiece = new Texture("./Images/whiteKingPiece.png");
			m_sprPiece = new StaticSprite(m_texPiece, m_v2Dimensions);
		}
	}

	else
	{
		if (m_iCurrentTile < 8)
		{
			m_bIsKing = true;
			delete m_texPiece;
			delete m_sprPiece;
			m_texPiece = new Texture("./Images/blackKingPiece.png");
			m_sprPiece = new StaticSprite(m_texPiece, m_v2Dimensions);
		}
	}


}


int Checker::CheckIfCanMoveUpRight()
{
	int iTargetTile = m_iCurrentTile + 9;
	int iJumpTile = iTargetTile + 9;

	if (m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 7 && m_iCurrentTile != 23 && m_iCurrentTile != 39 && m_iCurrentTile < 55)
		{
			if (m_vrTileList[iTargetTile].m_eCurrentState == Tile::EMPTY)
			{
				return iTargetTile;
			}
		}		
	}

	return -1;
}

int Checker::CheckIfCanMoveDownRight()
{
	int iTargetTile = m_iCurrentTile - 7;
	int iJumpTile = iTargetTile - 7;

	if (!m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 23 && m_iCurrentTile != 39 && m_iCurrentTile != 55 && m_iCurrentTile > 7)
		{
			if (m_vrTileList[iTargetTile].m_eCurrentState == Tile::EMPTY)
			{
				return iTargetTile;
			}
		}
	}

	return -1;
}

int Checker::CheckIfCanMoveUpLeft()
{
	int iTargetTile = m_iCurrentTile + 7;
	int iJumpTile = iTargetTile + 7;

	if (m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 8 && m_iCurrentTile != 24 && m_iCurrentTile != 40 && m_iCurrentTile < 56)
		{
			if (m_vrTileList[iTargetTile].m_eCurrentState == Tile::EMPTY)
			{
				return iTargetTile;
			}
		}
	}

	return -1;
}

int Checker::CheckIfCanMoveDownLeft()
{
	int iTargetTile = m_iCurrentTile - 9;
	int iJumpTile = iTargetTile - 9;

	if (!m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 24 && m_iCurrentTile != 40 && m_iCurrentTile != 56 && m_iCurrentTile > 8)
		{
			if (m_vrTileList[iTargetTile].m_eCurrentState == Tile::EMPTY)
			{
				return iTargetTile;
			}
		}
	}

	return -1;
}



JumpTarget Checker::CheckIfCanJumpUpRight()
{
	int iTargetTile = m_iCurrentTile + 9;
	int iJumpTile = iTargetTile + 9;

	if (m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 7 && m_iCurrentTile != 23 && m_iCurrentTile != 39 && m_iCurrentTile < 55)
		{			
			// If checker is black and target is white or if checker is white and target is black
			if ((!m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::WHITE) || (m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::BLACK))
			{
				if (iTargetTile != 7 && iTargetTile != 23 && iTargetTile != 39 && iTargetTile < 55)
				{
					if (m_vrTileList[iJumpTile].m_eCurrentState == Tile::EMPTY)
					{
						return JumpTarget(iJumpTile, iTargetTile);
					}
				}
			}

		}
	}

	return JumpTarget(-1, -1);
}

JumpTarget Checker::CheckIfCanJumpDownRight()
{
	int iTargetTile = m_iCurrentTile - 7;
	int iJumpTile = iTargetTile - 7;

	if (!m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 23 && m_iCurrentTile != 39 && m_iCurrentTile != 55 && m_iCurrentTile > 7)
		{
			// If checker is black and target is white or if checker is white and target is black
			if ((!m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::WHITE) || (m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::BLACK))
			{
				if (iTargetTile != 23 && iTargetTile != 39 && iTargetTile != 55 && iTargetTile > 7)
				{
					if (m_vrTileList[iJumpTile].m_eCurrentState == Tile::EMPTY)
					{
						return JumpTarget(iJumpTile, iTargetTile);
					}
				}
			}

		}
	}

	return JumpTarget(-1, -1);
}

JumpTarget Checker::CheckIfCanJumpUpLeft()
{
	int iTargetTile = m_iCurrentTile + 7;
	int iJumpTile = iTargetTile + 7;

	if (m_bIsWhite || m_bIsKing)
	{
		if (m_iCurrentTile != 8 && m_iCurrentTile != 24 && m_iCurrentTile != 40 && m_iCurrentTile < 56)
		{
			// If checker is black and target is white or if checker is white and target is black
			if ((!m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::WHITE) || (m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::BLACK))
			{
				if (iTargetTile != 8 && iTargetTile != 24 && iTargetTile != 40 && iTargetTile < 56)
				{
					if (m_vrTileList[iJumpTile].m_eCurrentState == Tile::EMPTY)
					{
						return JumpTarget(iJumpTile, iTargetTile);
					}
				}
			}

		}
	}

	return JumpTarget(-1, -1);
}

JumpTarget Checker::CheckIfCanJumpDownLeft()
{
	int iTargetTile = m_iCurrentTile - 9;
	int iJumpTile = iTargetTile - 9;

	// Checks whether it is actually allowed to make the move
	if (!m_bIsWhite || m_bIsKing)
	{
		// Eliminates left side and bottom
		if (m_iCurrentTile != 24 && m_iCurrentTile != 40 && m_iCurrentTile != 56 && m_iCurrentTile > 8)
		{
			// If checker is black and target is white or if checker is white and target is black
			if ((!m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::WHITE) || (m_bIsWhite && m_vrTileList[iTargetTile].m_eCurrentState == Tile::BLACK))
			{
				if (iTargetTile != 24 && iTargetTile != 40 && iTargetTile != 56 && iTargetTile > 8)
				{
					if (m_vrTileList[iJumpTile].m_eCurrentState == Tile::EMPTY)
					{
						return JumpTarget(iJumpTile, iTargetTile);
					}
				}
			}

		}
	}

	return JumpTarget(- 1, -1);
}