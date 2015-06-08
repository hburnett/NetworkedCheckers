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

	m_pBackgroundTexture	= new Texture("./images/checkersboardNumbered.png");

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
		m_vrWhitePieces.push_back(Checker(pos.x, pos.y, (width / 8 / 2), (height / 8 / 2), currentTile, true));
		
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
		m_vrBlackPieces.push_back(Checker(pos.x, pos.y, (width / 8 / 2), (height / 8 / 2), currentTile, false));

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

		//for (int i = 0; i < m_vrCheckerPieces.size(); i++)
		//{
		//	if (m_vrCheckerPieces[i].m_bIsSelected)
		//	{
		//		for (int j = 0; j < m_vrBoardTiles.size(); j++)
		//		{
		//			if (m_vrBoardTiles[j].m_rRectangle.Contains(mousePos))
		//			{
		//				printf("Moving piece %i to tile %i\n", m_vrCheckerPieces[i].m_iCurrentTile, m_vrBoardTiles[j].m_iTileNumber);
		//				
		//				if (m_vrCheckerPieces[i].TryMoveToTarget(m_vrBoardTiles[j].m_iTileNumber))
		//				{
		//					printf("Move Success\n");
		//					m_bWhiteTurn = !m_bWhiteTurn;
		//					m_vrBoardTiles[m_vrCheckerPieces[i].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
		//
		//					if (m_vrCheckerPieces[i].m_bIsWhite)
		//					{
		//						m_vrBoardTiles[j].m_eCurrentState = Tile::WHITE;
		//					}
		//
		//					else
		//					{
		//						m_vrBoardTiles[j].m_eCurrentState = Tile::BLACK;
		//					}
		//
		//					m_vrCheckerPieces[i].m_iCurrentTile = m_vrBoardTiles[j].m_iTileNumber;
		//					m_vrCheckerPieces[i].KingMe();
		//					m_vrCheckerPieces[i].m_bIsSelected = false;
		//					return;
		//				}
		//
		//				else if (m_vrCheckerPieces[i].TryJumpToTarget(m_vrBoardTiles[j].m_iTileNumber))
		//				{
		//					for each (JumpTarget set in m_vrCheckerPieces[i].m_vrTilesCanJumpTo)
		//					{
		//						if (set.jumpTile == m_vrBoardTiles[j].m_iTileNumber)
		//						{
		//							printf("Jump Success\n");
		//							for (int k = 0; k < m_vrCheckerPieces.size(); k++)
		//							{
		//								m_vrBoardTiles[m_vrCheckerPieces[i].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
		//								m_vrBoardTiles[set.targetTile].m_eCurrentState = Tile::EMPTY;
		//
		//								if (m_vrCheckerPieces[i].m_bIsWhite)
		//								{
		//									m_vrBoardTiles[set.jumpTile].m_eCurrentState = Tile::WHITE;
		//								}
		//
		//								else
		//								{
		//									m_vrBoardTiles[set.jumpTile].m_eCurrentState = Tile::BLACK;
		//								}
		//
		//								m_vrCheckerPieces[i].m_iCurrentTile = set.jumpTile;
		//								m_vrCheckerPieces[i].m_bIsSelected = false;
		//								m_vrCheckerPieces[i].KingMe();
		//
		//								if (m_vrCheckerPieces[k].m_iCurrentTile == set.targetTile)
		//								{
		//									m_vrCheckerPieces.erase(m_vrCheckerPieces.begin() + k);
		//									m_bWhiteTurn = !m_bWhiteTurn;
		//									return;
		//								}
		//							}
		//						}
		//					}
		//				}
		//				
		//				else
		//					printf("Move Failed\n");
		//
		//				//break;
		//			}					
		//		}
		//	}
		//
		//
		//
		//	if (m_vrCheckerPieces[i].m_rRectangle.Contains(mousePos))
		//	{			
		//		if (m_vrCheckerPieces[i].m_bIsWhite == m_bWhiteTurn || !m_vrCheckerPieces[i].m_bIsWhite == !m_bWhiteTurn)
		//		{
		//			printf("Clicked piece %i at position %f %f\n", m_vrCheckerPieces[i].m_iCurrentTile, mousePos.x, mousePos.y);
		//			m_vrCheckerPieces[i].m_bIsSelected = true;
		//			m_vrCheckerPieces[i].m_vrTileList = m_vrBoardTiles;
		//			m_vrCheckerPieces[i].UpdateMoves();
		//		}
		//		
		//		break;
		//	}
		//}				

		#pragma region WHITE TURN

		if (m_bWhiteTurn)
		{
			bool anyJumps = false;
			m_vrWhitePiecesThatCanJump.clear();

			// Updates all white piece moves
			for (int i = 0; i < m_vrWhitePieces.size(); i++)
			{
				m_vrWhitePieces[i].m_vrTileList = m_vrBoardTiles;
				m_vrWhitePieces[i].UpdateMoves();

				// Checks if the piece can jump (kill another piece).
				// If it can, it adds the piece number to an array.
				// Will use this array to determine valid moves.
				if (m_vrWhitePieces[i].m_vrTilesCanJumpTo.size() > 0)
				{
					anyJumps = true;
					m_vrWhitePiecesThatCanJump.push_back(i);
				}
			}

			#pragma region IF A PIECE CAN JUMP OVER AN ENEMY

			// If any piece can jump another piece, 
			// Then that move must happen. (Mandatory jumps)
			if (anyJumps)
			{
				bool isPieceSelected = false;
				int pieceSelected = -1;
				int tileSelected = -1;

				// Checks if any piece is selected, 
				for (int i = 0; i < m_vrWhitePieces.size(); i++)
				{
					if (m_vrWhitePieces[i].m_bIsSelected)
					{
						isPieceSelected = true;
						pieceSelected = i;
					}
				}

				#pragma region IF PIECE IS SELECTED

				// If a piece is selected,
				// Then checks for the tile selected.
				if (isPieceSelected)
				{
					for (int i = 0; i < m_vrBoardTiles.size(); i++)
					{
						if (m_vrBoardTiles[i].m_rRectangle.Contains(mousePos))
						{
							tileSelected = i;
							printf("Moving piece %i to tile %i\n", m_vrWhitePieces[pieceSelected].m_iCurrentTile, m_vrBoardTiles[tileSelected].m_iTileNumber);

							// Checks whether the tile selected can be jumped to.
							if (m_vrWhitePieces[pieceSelected].TryJumpToTarget(m_vrBoardTiles[tileSelected].m_iTileNumber))
							{
								bool killedEnemy = false;

								for each (JumpTarget jumpTilePair in m_vrWhitePieces[pieceSelected].m_vrTilesCanJumpTo)
								{
									if (jumpTilePair.jumpTile == m_vrBoardTiles[tileSelected].m_iTileNumber)
									{
										printf("Jump Success\n");

										// Sets the selected pieces tile and 
										// The enemy being jumped overs tile to empty. 
										// Then sets the selected pieces tile to White.
										m_vrBoardTiles[m_vrWhitePieces[pieceSelected].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.targetTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.jumpTile].m_eCurrentState = Tile::WHITE;

										// Sets the selected pieces tile to the jumping position.
										// Checks if the piece should be a king or not.
										m_vrWhitePieces[pieceSelected].m_iCurrentTile = jumpTilePair.jumpTile;
										m_vrWhitePieces[pieceSelected].KingMe();

										// Checks for the black piece on the tile jumped over.
										// Once found, deletes it from the game.
										for (int j = 0; j < m_vrBlackPieces.size(); j++)
										{
											if (m_vrBlackPieces[j].m_iCurrentTile == jumpTilePair.targetTile)
											{
												m_vrBlackPieces.erase(m_vrBlackPieces.begin() + j);
												killedEnemy = true;
												break;
											}
										}
									}
								}

								if (killedEnemy)
								{
									m_vrWhitePieces[pieceSelected].m_vrTileList = m_vrBoardTiles;
									m_vrWhitePieces[pieceSelected].UpdateMoves();

									// Checks if the piece can jump (kill another piece).
									// If it can, it adds the piece number to an array.
									// Will use this array to determine valid moves.
									if (m_vrWhitePieces[pieceSelected].m_vrTilesCanJumpTo.size() > 0)
									{
										//printf("%i Can jump:  Size %i\n", m_vrBlackPieces[pieceSelected].m_iCurrentTile, m_vrBlackPieces[pieceSelected].m_vrTilesCanJumpTo.size());
										anyJumps = true;
										break;
									}

									else
										m_bWhiteTurn = !m_bWhiteTurn;
								}
							}
						}
					}
				}
#pragma endregion


				#pragma region IF PIECE IS NOT SELECTED
				// If no piece was selected,
				// Then check if one was selected.
				if (!isPieceSelected)
				{
					for (int i = 0; i < m_vrWhitePieces.size(); i++)
					{
						if (m_vrWhitePieces[i].m_rRectangle.Contains(mousePos))
						{											
							printf("Clicked piece %i at position %f %f\n", m_vrWhitePieces[i].m_iCurrentTile, mousePos.x, mousePos.y);
							
							for (int j = 0; j < m_vrWhitePiecesThatCanJump.size(); j++)
							{
								// Checks whether the piece clicked is one that can jump
								// If it is, the the piece is selected successfully.
								if (i == m_vrWhitePiecesThatCanJump[j])
								{
									m_vrWhitePieces[i].m_bIsSelected = true;
									m_vrWhitePieces[i].m_vrTileList = m_vrBoardTiles;

									printf("Piece selected successfully");
								}
							}				
						}
					}
				}

				#pragma endregion

			}


			#pragma endregion

			#pragma region IF A PIECE CANT JUMP OVER AN ENEMY

			else
			{
				// If any piece can jump another piece, 
				// Then that move must happen. (Mandatory jumps)
				
				bool isPieceSelected = false;
				int pieceSelected = -1;
				int tileSelected = -1;

				// Checks if any piece is selected, 
				for (int i = 0; i < m_vrWhitePieces.size(); i++)
				{
					if (m_vrWhitePieces[i].m_bIsSelected)
					{
						isPieceSelected = true;
						pieceSelected = i;
					}
				}

				#pragma region IF PIECE IS SELECTED

				// If a piece is selected,
				// Then checks for the tile selected.
				if (isPieceSelected)
				{
					for (int i = 0; i < m_vrBoardTiles.size(); i++)
					{
						if (m_vrBoardTiles[i].m_rRectangle.Contains(mousePos))
						{
							tileSelected = i;
							printf("Moving piece %i to tile %i\n", m_vrWhitePieces[pieceSelected].m_iCurrentTile, m_vrBoardTiles[tileSelected].m_iTileNumber);
							

							// Checks whether the tile selected can be moved to
							if (m_vrWhitePieces[pieceSelected].TryMoveToTarget(m_vrBoardTiles[tileSelected].m_iTileNumber))
							{
								printf("Move Success\n");

								// Sets the selected pieces tile to empty.
								// Then sets the selected pieces new tile to White.
								m_bWhiteTurn = !m_bWhiteTurn;
								m_vrBoardTiles[m_vrWhitePieces[pieceSelected].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;														
								m_vrBoardTiles[tileSelected].m_eCurrentState = Tile::WHITE;
								

								// Sets the selected pieces tile to the jumping position.
								// Deselects the piece.
								// Checks if the piece should be a king or not.
								m_vrWhitePieces[pieceSelected].m_iCurrentTile = m_vrBoardTiles[tileSelected].m_iTileNumber;
								m_vrWhitePieces[pieceSelected].KingMe();
								m_vrWhitePieces[pieceSelected].m_bIsSelected = false;
								break;
							}


							// Checks whether the tile selected can be jumped to.
							else if (m_vrWhitePieces[pieceSelected].TryJumpToTarget(m_vrBoardTiles[tileSelected].m_iTileNumber))
							{
								for each (JumpTarget jumpTilePair in m_vrWhitePieces[pieceSelected].m_vrTilesCanJumpTo)
								{
									if (jumpTilePair.jumpTile == m_vrBoardTiles[tileSelected].m_iTileNumber)
									{
										printf("Jump Success\n");

										// Sets the selected pieces tile and 
										// The enemy being jumped overs tile to empty. 
										// Then sets the selected pieces new tile to White.
										m_vrBoardTiles[m_vrWhitePieces[pieceSelected].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.targetTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.jumpTile].m_eCurrentState = Tile::WHITE;

										// Sets the selected pieces tile to the jumping position.
										// Deselects the piece.
										// Checks if the piece should be a king or not.
										m_vrWhitePieces[pieceSelected].m_iCurrentTile = jumpTilePair.jumpTile;
										m_vrWhitePieces[pieceSelected].m_bIsSelected = false;
										m_vrWhitePieces[pieceSelected].KingMe();

										// Checks for the black piece on the tile jumped over.
										// Once found, deletes it from the game.
										for (int j = 0; j < m_vrBlackPieces.size(); j++)
										{
											if (m_vrBlackPieces[j].m_iCurrentTile == jumpTilePair.targetTile)
											{
												m_vrBlackPieces.erase(m_vrBlackPieces.begin() + j);
												m_bWhiteTurn = !m_bWhiteTurn;
												break;
											}
										}
									}
								}
							}
						}
					}
				}
				#pragma endregion
				
				
				#pragma region IF PIECE IS NOT SELECTED
				// If no piece was selected,
				// Then check if one was selected.
				if (!isPieceSelected)
				{
					for (int i = 0; i < m_vrWhitePieces.size(); i++)
					{
						if (m_vrWhitePieces[i].m_rRectangle.Contains(mousePos))
						{
							printf("Clicked piece %i at position %f %f\n", m_vrWhitePieces[i].m_iCurrentTile, mousePos.x, mousePos.y);
														
							// Checks whether the piece clicked is one that can jump
							// If it is, the the piece is selected successfully.
							
							m_vrWhitePieces[i].m_bIsSelected = true;
							m_vrWhitePieces[i].m_vrTileList = m_vrBoardTiles;

							printf("Piece selected successfully");														
						}
					}
				}

				#pragma endregion
				
			}

			#pragma endregion

		}

		#pragma endregion



		#pragma region BLACK TURN

		if (!m_bWhiteTurn)
		{
			bool anyJumps = false;
			m_vrBlackPiecesThatCanJump.clear();

			// Updates all white piece moves
			for (int i = 0; i < m_vrBlackPieces.size(); i++)
			{
				m_vrBlackPieces[i].m_vrTileList = m_vrBoardTiles;
				m_vrBlackPieces[i].UpdateMoves();

				// Checks if the piece can jump (kill another piece).
				// If it can, it adds the piece number to an array.
				// Will use this array to determine valid moves.
				if (m_vrBlackPieces[i].m_vrTilesCanJumpTo.size() > 0)
				{					
					anyJumps = true;
					m_vrBlackPiecesThatCanJump.push_back(i);
				}
			}

			#pragma region IF A PIECE CAN JUMP OVER AN ENEMY

			// If any piece can jump another piece, 
			// Then that move must happen. (Mandatory jumps)
			if (anyJumps)
			{
				bool isPieceSelected = false;
				int pieceSelected = -1;
				int tileSelected = -1;

				// Checks if any piece is selected, 
				for (int i = 0; i < m_vrBlackPieces.size(); i++)
				{
					if (m_vrBlackPieces[i].m_bIsSelected)
					{
						isPieceSelected = true;
						pieceSelected = i;
					}
				}

				#pragma region IF PIECE IS SELECTED

				// If a piece is selected,
				// Then checks for the tile selected.
				if (isPieceSelected)
				{
					for (int i = 0; i < m_vrBoardTiles.size(); i++)
					{
						if (m_vrBoardTiles[i].m_rRectangle.Contains(mousePos))
						{
							tileSelected = i;
							printf("Moving piece %i to tile %i\n", m_vrBlackPieces[pieceSelected].m_iCurrentTile, m_vrBoardTiles[tileSelected].m_iTileNumber);

							// Checks whether the tile selected can be jumped to.
							if (m_vrBlackPieces[pieceSelected].TryJumpToTarget(m_vrBoardTiles[tileSelected].m_iTileNumber))
							{
								bool killedEnemy = false;

								for each (JumpTarget jumpTilePair in m_vrBlackPieces[pieceSelected].m_vrTilesCanJumpTo)
								{
									if (jumpTilePair.jumpTile == m_vrBoardTiles[tileSelected].m_iTileNumber)
									{

										// Sets the selected pieces tile and 
										// The enemy being jumped overs tile to empty. 
										// Then sets the selected pieces tile to White.
										m_vrBoardTiles[m_vrBlackPieces[pieceSelected].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.targetTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.jumpTile].m_eCurrentState = Tile::BLACK;

										// Sets the selected pieces tile to the jumping position.
										// Checks if the piece should be a king or not.
										m_vrBlackPieces[pieceSelected].m_iCurrentTile = jumpTilePair.jumpTile;
										m_vrBlackPieces[pieceSelected].KingMe();


										//m_vrBlackPieces[pieceSelected].m_bIsSelected = false;


										// Checks for the black piece on the tile jumped over.
										// Once found, deletes it from the game.
										for (int j = 0; j < m_vrWhitePieces.size(); j++)
										{
											if (m_vrWhitePieces[j].m_iCurrentTile == jumpTilePair.targetTile)
											{
												m_vrWhitePieces.erase(m_vrWhitePieces.begin() + j);
												printf("Jump Success\n");
												killedEnemy = true;
												break;
											}
										}
									}
								}

								if (killedEnemy)
								{
									m_vrBlackPieces[pieceSelected].m_vrTileList = m_vrBoardTiles;
									m_vrBlackPieces[pieceSelected].UpdateMoves();

									// Checks if the piece can jump (kill another piece).
									// If it can, the turn does not end.
									if (m_vrBlackPieces[pieceSelected].m_vrTilesCanJumpTo.size() > 0)
									{
										//printf("%i Can jump:  Size %i\n", m_vrBlackPieces[pieceSelected].m_iCurrentTile, m_vrBlackPieces[pieceSelected].m_vrTilesCanJumpTo.size());
										anyJumps = true;
										break;
									}

									// If the piece can't jump again, the turn is over.
									else
										m_bWhiteTurn = !m_bWhiteTurn;
								}
							}
						}
					}
				}
		
			#pragma endregion
				
				
				#pragma region IF PIECE IS NOT SELECTED
				// If no piece was selected,
				// Then check if one was selected.
				if (!isPieceSelected)
				{
					for (int i = 0; i < m_vrBlackPieces.size(); i++)
					{
						if (m_vrBlackPieces[i].m_rRectangle.Contains(mousePos))
						{
							printf("Clicked piece %i at position %f %f\n", m_vrBlackPieces[i].m_iCurrentTile, mousePos.x, mousePos.y);

							for (int j = 0; j < m_vrBlackPiecesThatCanJump.size(); j++)
							{
								// Checks whether the piece clicked is one that can jump
								// If it is, the the piece is selected successfully.
								if (i == m_vrBlackPiecesThatCanJump[j])
								{
									m_vrBlackPieces[i].m_bIsSelected = true;
									m_vrBlackPieces[i].m_vrTileList = m_vrBoardTiles;

									printf("Piece selected successfully");
								}
							}
						}
					}
				}

			#pragma endregion

			}


			#pragma endregion
			
			#pragma region IF A PIECE CANT JUMP OVER AN ENEMY

			else
			{
				// If any piece can jump another piece, 
				// Then that move must happen. (Mandatory jumps)

				bool isPieceSelected = false;
				int pieceSelected = -1;
				int tileSelected = -1;

				// Checks if any piece is selected, 
				for (int i = 0; i < m_vrBlackPieces.size(); i++)
				{
					if (m_vrBlackPieces[i].m_bIsSelected)
					{
						isPieceSelected = true;
						pieceSelected = i;
					}
				}

				#pragma region IF PIECE IS SELECTED

				// If a piece is selected,
				// Then checks for the tile selected.
				if (isPieceSelected)
				{
					for (int i = 0; i < m_vrBoardTiles.size(); i++)
					{
						if (m_vrBoardTiles[i].m_rRectangle.Contains(mousePos))
						{
							tileSelected = i;
							printf("Moving piece %i to tile %i\n", m_vrBlackPieces[pieceSelected].m_iCurrentTile, m_vrBoardTiles[tileSelected].m_iTileNumber);


							// Checks whether the tile selected can be moved to
							if (m_vrBlackPieces[pieceSelected].TryMoveToTarget(m_vrBoardTiles[tileSelected].m_iTileNumber))
							{
								printf("Move Success\n");

								// Sets the selected pieces tile to empty.
								// Then sets the selected pieces new tile to White.
								m_bWhiteTurn = !m_bWhiteTurn;
								m_vrBoardTiles[m_vrBlackPieces[pieceSelected].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
								m_vrBoardTiles[tileSelected].m_eCurrentState = Tile::BLACK;


								// Sets the selected pieces tile to the jumping position.
								// Deselects the piece.
								// Checks if the piece should be a king or not.
								m_vrBlackPieces[pieceSelected].m_iCurrentTile = m_vrBoardTiles[tileSelected].m_iTileNumber;
								m_vrBlackPieces[pieceSelected].KingMe();
								m_vrBlackPieces[pieceSelected].m_bIsSelected = false;
								break;
							}


							// Checks whether the tile selected can be jumped to.
							else if (m_vrBlackPieces[pieceSelected].TryJumpToTarget(m_vrBoardTiles[tileSelected].m_iTileNumber))
							{
								for each (JumpTarget jumpTilePair in m_vrBlackPieces[pieceSelected].m_vrTilesCanJumpTo)
								{
									if (jumpTilePair.jumpTile == m_vrBoardTiles[tileSelected].m_iTileNumber)
									{

										// Sets the selected pieces tile and 
										// The enemy being jumped overs tile to empty. 
										// Then sets the selected pieces new tile to White.
										m_vrBoardTiles[m_vrBlackPieces[pieceSelected].m_iCurrentTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.targetTile].m_eCurrentState = Tile::EMPTY;
										m_vrBoardTiles[jumpTilePair.jumpTile].m_eCurrentState = Tile::BLACK;

										// Sets the selected pieces tile to the jumping position.
										// Deselects the piece.
										// Checks if the piece should be a king or not.
										m_vrBlackPieces[pieceSelected].m_iCurrentTile = jumpTilePair.jumpTile;
										m_vrBlackPieces[pieceSelected].m_bIsSelected = false;
										m_vrBlackPieces[pieceSelected].KingMe();

										// Checks for the black piece on the tile jumped over.
										// Once found, deletes it from the game.
										for (int j = 0; j < m_vrWhitePieces.size(); j++)
										{
											if (m_vrWhitePieces[j].m_iCurrentTile == jumpTilePair.targetTile)
											{
												m_vrWhitePieces.erase(m_vrWhitePieces.begin() + j);
												m_bWhiteTurn = !m_bWhiteTurn;
												printf("Jump Success\n");
												break;
											}
										}
									}
								}
							}
						}
					}
				}
				#pragma endregion
				
				
				#pragma region IF PIECE IS NOT SELECTED
				// If no piece was selected,
				// Then check if one was selected.
				if (!isPieceSelected)
				{
					for (int i = 0; i < m_vrBlackPieces.size(); i++)
					{
						if (m_vrBlackPieces[i].m_rRectangle.Contains(mousePos))
						{
							printf("Clicked piece %i at position %f %f\n", m_vrBlackPieces[i].m_iCurrentTile, mousePos.x, mousePos.y);

							// Checks whether the piece clicked is one that can jump
							// If it is, the the piece is selected successfully.

							m_vrBlackPieces[i].m_bIsSelected = true;
							m_vrBlackPieces[i].m_vrTileList = m_vrBoardTiles;

							printf("Piece selected successfully");
						}
					}
				}

			#pragma endregion

			}

		#pragma endregion

		}

	#pragma endregion


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

	for each (Checker gamePiece in m_vrWhitePieces)
	{
		gamePiece.Draw(m_pSpriteBatch);
	}

	for each (Checker gamePiece in m_vrBlackPieces)
	{
		gamePiece.Draw(m_pSpriteBatch);
	}
		
	m_pSpriteBatch->End();
}