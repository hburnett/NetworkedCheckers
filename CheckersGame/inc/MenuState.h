/*-----------------------------------------------------------------------------

		Author:			Heath Burnett
		Description:	Menu State

-----------------------------------------------------------------------------*/

#ifndef MENUSTATE_H
#define	MENUSTATE_H

#include "WindowsIncludes.h"
#include "GameStateManager.h"
#include "Vec2.h"
#include "Camera.h"
#include <vector>
#include "Tile.h"
#include "Checker.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include "irrKlang.h"


class GameStateManager;
class Game;
class StaticSprite;
class Texture;
class SpriteBatch;
class Vec2;
class Camera;
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

	enum GameMessages
	{
		ID_SERVER_TEXT_MESSAGE = 134 + 1,
		ID_OPPONENT_CLICKED_MOUSE = 134 + 2
	};

protected:

	std::vector<Tile> m_vrBoardTiles;
	std::vector<Checker> m_vrWhitePieces;
	std::vector<Checker> m_vrBlackPieces;
	std::vector<int> m_vrWhitePiecesThatCanJump;
	std::vector<int> m_vrBlackPiecesThatCanJump;


private:

	void HandleNetworkMessages(RakNet::RakPeerInterface* pPeerInterface);
	void SendClickedMessage(RakNet::RakPeerInterface* pPeerInterface);

	bool m_bPlayerIsWhite;
	bool m_bOpponentClicked;
	bool m_bGameOver;

	Texture			*m_pBackgroundTexture;
	StaticSprite	*m_pBackgroundSprite;

	SpriteBatch		*m_pSpriteBatch;
	
	Camera	m_gameCamera;

	Vec2	m_v2cameraLastPosition;
	Vec2	m_v2OpponentMousePos;

	irrklang::ISoundEngine* m_seSoundEngine;

	Texture		 *m_texWinner;

	StaticSprite *m_sprWinner;
};

#endif