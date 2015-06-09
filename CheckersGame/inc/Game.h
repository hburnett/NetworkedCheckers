/*-----------------------------------------------------------------------------
 Author: Heath Burnett
 Description: Creates a window, will contain a game later
-----------------------------------------------------------------------------*/

#ifndef GAME_H
#define GAME_H

#include "WindowsIncludes.h"
#include "glfw3.h"
#include "Vec2.h"
#include "Mat3.h"
#include <vector>
#include "RakPeerInterface.h"


class Texture;
class SpriteBatch;
class StaticSprite;
class GameStateManager;
class InputManager;
class Vec2;
class Mat3;


class Game
{
public:

	friend class GameStateManager;
	friend class IGameState;

	// constructor
	Game(float windowWidth, float windowHeight, const char *windowTitle, bool fullscreen, bool isServer, RakNet::RakPeerInterface* pPeerInterface);

	float GetWindowWidth()	{ return m_fWindowWidth;	}
	float GetWindowHeight()	{ return m_fWindowHeight;	}

	float GetDeltaTime() { return m_fDeltaTime; }

	// destructor
	~Game();

	
	RakNet::RakPeerInterface* m_pPeerInterface;
	
	void GameOver() { m_bGameOver = true; }
	
	void VSyncEnabled( bool enable );

	SpriteBatch* GetSpriteBatch()	{ return m_pSpriteBatch;	}

	void PlaySoundOnce( char* filename );

	// runs the game
	void RunGame();

	bool m_bIsServer;


private:


	void CreateNewWindow( float windowWidth, float windowHeight, const char *windowTitle, bool fullscreen );
	
	// called each frame from within RunGame()
	void Update();

	// called each frame from within RunGame()
	void Draw();


private:
		
	float			m_fWindowWidth;
	float			m_fWindowHeight;

	bool			m_bGameOver;	
	bool			m_vSyncEnabled;
	

	float			m_fLastTime, m_fCurrentTime, m_fDeltaTime, m_fTotalTime, m_fFPS;
	int				m_iTotalFrames;
	
	double			mx, my;
	
private:

	GLFWwindow			*m_pWindow;
	
	SpriteBatch			*m_pSpriteBatch;

	Game				*m_pGame;

	GameStateManager	*m_pGameStateManager;
	
	InputManager		*m_pInputManager;		
};
#endif