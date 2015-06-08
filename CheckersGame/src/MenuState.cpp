#include "MenuState.h"
#include "Game.h"
#include "StaticSprite.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "GameStateManager.h"
#include "Vec2.h"
#include "Camera.h"
#include "InputManager.h"
#include "Globals.h"
#include "Player.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

MenuState::MenuState(GameStateManager *pGameStateManager, Game *pGame) : IGameState(pGameStateManager, pGame)
{
	m_pGame					= pGame;

	m_gameCamera			= Camera();
	m_v2cameraLastPosition  = m_gameCamera.cameraMatrix.GetTranslation();
		
	Vec2 border( m_pGame->GetWindowWidth(), m_pGame->GetWindowHeight() );
			
	m_pSpriteBatch			= m_pGame->GetSpriteBatch();

	m_pBackgroundTexture	= new Texture("./images/checkersboard.png");

	m_pBackgroundSprite		= new StaticSprite( m_pBackgroundTexture, (border) );
	m_pBackgroundSprite->Transform().SetTranslation( border / 2 );

	m_bWhiteTurn = true;
	
	float height = m_pGame->GetWindowHeight();
	float width = m_pGame->GetWindowWidth();

	

	float x = 0;
	float y = -(height/8/2);
	bool offset = true;

	// Create the nodes/tiles for the checkerboard
	for (int i = 0; i < 8; i++)
	{
		y += (height / 8);
		x = (width / 8 / 2);
		
		for (int j = 0; j < 8; j++)
		{
			m_vrBoardTiles.push_back(Tile(x, y, width / 8, height / 8, i * 8 + j, Tile::EMPTY));
			x += (width / 8);
		}			
	}


	// Create the white pieces
	int currentTile = 1;
	for (int i = 0; i < 12; i++)
	{
		m_vrBoardTiles[currentTile].m_eCurrentState = Tile::WHITE;
		Vec2 pos = m_vrBoardTiles[currentTile].m_v2Position;
		m_vrCheckerPieces.push_back(Checker(pos.x, pos.y, (width / 8 / 2), (height / 8 / 2), currentTile, true));
		
		if (i == 3)
		{
			currentTile += 1;
		}
		
		else if (i == 7)
		{
			currentTile += 3;
		}
		
		else
		{
			currentTile += 2;
		}
	}

	// Create the black pieces

	currentTile = 40;
	for (int i = 0; i < 12; i++)
	{
		m_vrBoardTiles[currentTile].m_eCurrentState = Tile::BLACK;
		Vec2 pos = m_vrBoardTiles[currentTile].m_v2Position;
		m_vrCheckerPieces.push_back(Checker(pos.x, pos.y, (width / 8 / 2), (height / 8 / 2), currentTile, false));

		if (i == 3)
		{
			currentTile += 3;
		}

		else if (i == 7)
		{
			currentTile += 1;
		}

		else
		{
			currentTile += 2;
		}
	}

	
}

MenuState::~MenuState()
{	
	for( auto iter = 0; iter != m_vecLevel.size(); iter++)
	{
		delete m_vecLevel[iter];
	}

	delete m_pBackgroundTexture;
	delete m_pBackgroundSprite; 
}

void MenuState::Update(float dt)
{
	if (g_inputManager.GetMouseClicked(0))
	{
		Vec2 mousePos = g_inputManager.GetMouseLocation();		

		for (int i = 0; i < m_vrCheckerPieces.size(); i++)
		{
			if (m_vrCheckerPieces[i].m_bIsSelected)
			{
				for (int j = 0; j < m_vrBoardTiles.size(); j++)
				{
					if (m_vrBoardTiles[j].m_rRectangle.Contains(mousePos))
					{
						printf("Moving piece %i to tile %i\n", m_vrCheckerPieces[i].m_iCurrentTile, m_vrBoardTiles[j].m_iTileNumber);
						
						if (m_vrCheckerPieces[i].TryMoveToTarget(m_vrBoardTiles[j].m_iTileNumber))
						{
							printf("Move Success\n");
							m_bWhiteTurn = !m_bWhiteTurn;
							m_vrBoardTiles[m_vrCheckerPieces[i].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;

							if (m_vrCheckerPieces[i].m_bIsWhite)
							{
								m_vrBoardTiles[j].m_eCurrentState = Tile::WHITE;
							}

							else
							{
								m_vrBoardTiles[j].m_eCurrentState = Tile::BLACK;
							}

							m_vrCheckerPieces[i].m_iCurrentTile = m_vrBoardTiles[j].m_iTileNumber;
							m_vrCheckerPieces[i].KingMe();
							m_vrCheckerPieces[i].m_bIsSelected = false;
							return;
						}

						else if (m_vrCheckerPieces[i].TryJumpToTarget(m_vrBoardTiles[j].m_iTileNumber))
						{
							for each (JumpTarget set in m_vrCheckerPieces[i].m_vrTilesCanJumpTo)
							{
								if (set.jumpTile == m_vrBoardTiles[j].m_iTileNumber)
								{
									printf("Jump Success\n");
									for (int k = 0; k < m_vrCheckerPieces.size(); k++)
									{
										m_vrBoardTiles[m_vrCheckerPieces[i].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[set.targetTile].m_eCurrentState = Tile::EMPTY;

										if (m_vrCheckerPieces[i].m_bIsWhite)
										{
											m_vrBoardTiles[set.jumpTile].m_eCurrentState = Tile::WHITE;
										}

										else
										{
											m_vrBoardTiles[set.jumpTile].m_eCurrentState = Tile::BLACK;
										}

										m_vrCheckerPieces[i].m_iCurrentTile = set.jumpTile;
										m_vrCheckerPieces[i].m_bIsSelected = false;
										m_vrCheckerPieces[i].KingMe();

										if (m_vrCheckerPieces[k].m_iCurrentTile == set.targetTile)
										{
											m_vrCheckerPieces.erase(m_vrCheckerPieces.begin() + k);
											m_bWhiteTurn = !m_bWhiteTurn;
											return;
										}
									}
								}
							}
						}
						
						else
							printf("Move Failed\n");

						//break;
					}					
				}
			}



			if (m_vrCheckerPieces[i].m_rRectangle.Contains(mousePos))
			{			
				if (m_vrCheckerPieces[i].m_bIsWhite == m_bWhiteTurn || !m_vrCheckerPieces[i].m_bIsWhite == !m_bWhiteTurn)
				{
					printf("Clicked piece %i at position %f %f\n", m_vrCheckerPieces[i].m_iCurrentTile, mousePos.x, mousePos.y);
					m_vrCheckerPieces[i].m_bIsSelected = true;
					m_vrCheckerPieces[i].m_vrTileList = m_vrBoardTiles;
					m_vrCheckerPieces[i].UpdateMoves();
				}
				
				break;
			}
		}				
	}


	
	
}

void MenuState::Draw()
{
	//------------------------
	m_pSpriteBatch->Begin(m_gameCamera.cameraMatrix);

	m_pBackgroundSprite->Draw(m_pSpriteBatch);	
	
	for each (Tile gameTile in m_vrBoardTiles)
	{
		gameTile.Draw(m_pSpriteBatch);
	}

	for each (Checker gamePiece in m_vrCheckerPieces)
	{
		gamePiece.Draw(m_pSpriteBatch);
	}

	
		
	m_pSpriteBatch->End();
}