/*-----------------------------------------------------------------------------

		Author:			Heath Burnett
		Description:	Menu State

-----------------------------------------------------------------------------*/

#ifndef MENUSTATE_H
#define	MENUSTATE_H

#include "GameStateManager.h"
#include "Vec2.h"
#include "Camera.h"
#include <vector>
#include "Tile.h"
#include "Checker.h"


class GameStateManager;
class Game;
class StaticSprite;
class Texture;
class SpriteBatch;
class Vec2;
class Camera;
class Player;
class Block;
class Tile;
class Checker;

class MenuState : public IGameState
{
public:

	MenuState(GameStateManager *pGameStateManager, Game *pGame);

	virtual ~MenuState();

	virtual void Update(float dt);
	
	virtual void Draw();

	bool m_bWhiteTurn;
		

protected:

	std::vector<Tile> m_vrBoardTiles;
	std::vector<Checker> m_vrCheckerPieces;

private:


	Texture			*m_pBackgroundTexture;
	StaticSprite	*m_pBackgroundSprite;

	SpriteBatch		*m_pSpriteBatch;
	
	Camera	m_gameCamera;

	Vec2	m_v2cameraLastPosition;

	std::vector<Block*> m_vecLevel;

};

#endif