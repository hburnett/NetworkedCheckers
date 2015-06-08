#include <Windows.h>
#include "Game.h"
#include "SpriteBatch.h"
#include <iostream>
#include "StaticSprite.h"
#include "GameStateManager.h"
#include "MenuState.h"
#include "Globals.h"
#include "InputManager.h"
#include <math.h>

Game::Game(float windowWidth, float windowHeight, const char *windowTitle, bool fullscreen)
{
	CreateNewWindow(windowWidth, windowHeight, windowTitle, fullscreen);

	m_fWindowWidth	= windowWidth;
	m_fWindowHeight = windowHeight;

	m_pSpriteBatch	 = SpriteBatch::Create( this, SpriteBatch::IMMEDIATE );


	m_pGameStateManager = new GameStateManager();
	m_pGameStateManager->SetState("MenuState", new MenuState( m_pGameStateManager, this )); 
	m_pGameStateManager->PushState("MenuState");
	
	g_inputManager.DefineWindow(m_pWindow);
		
	m_fCurrentTime			= glfwGetTime();
	m_fLastTime				= 0.0f;
	m_fDeltaTime			= 0.0f;
	m_fTotalTime			= 0.0f;
	m_fFPS					= 0.0f;
	m_iTotalFrames			= 0;

	m_vSyncEnabled  = true;

	VSyncEnabled( true );
	
	m_bGameOver = false;
	
	mx = 0;
	my = 0;
	
}

Game::~Game()
{
	m_pSpriteBatch->Destroy( m_pSpriteBatch );
		
	delete m_pGameStateManager;

	glfwTerminate();
}

void Game::CreateNewWindow(float windowWidth, float windowHeight, const char *windowTitle, bool fullscreen)
{
	//glfwWindowHint(GL_MAJOR_VERSION, 4.0);
	//glfwWindowHint(GL_MINOR_VERSION, 4.0);

	int errorCode = 0;

	if( !glfwInit() )
	{
		printf("Error initialising glfw\n");
	}
	
	if(fullscreen == true)
		m_pWindow = glfwCreateWindow( (int) windowWidth, (int) windowHeight, windowTitle, glfwGetPrimaryMonitor(), NULL);

	if(fullscreen == false)
		m_pWindow = glfwCreateWindow((int) windowWidth, (int) windowHeight, windowTitle, NULL, NULL);

	glfwSetWindowPos(m_pWindow, 250, 50);

	if( !m_pWindow )
	{
		printf("Error Creating window glfw\n");
		glfwTerminate();
	}
		
	glfwMakeContextCurrent(m_pWindow);
	GLenum err = glewInit();
	if( err != GLEW_OK )
	{
		// glew failed to initialise properly
		printf("Error: %s\n", glewGetErrorString(err));
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
}

void Game::RunGame()
{

	while( !glfwWindowShouldClose( m_pWindow ) && m_bGameOver == false )
	{
		//Calculates time between frames (Delta Time)
		m_fLastTime		=  m_fCurrentTime;
		m_fCurrentTime	=  glfwGetTime();
		m_fDeltaTime	=  m_fCurrentTime - m_fLastTime;
		m_fTotalTime	+= m_fDeltaTime;
		++m_iTotalFrames;

		m_fFPS	= m_iTotalFrames / m_fTotalTime;
		
		glfwGetCursorPos(m_pWindow, &mx, &my);
		my = GetWindowHeight() - my;
		

		glClear(GL_COLOR_BUFFER_BIT);
			
		Update();
		
		Draw();

		glfwSwapBuffers( m_pWindow );
		glfwPollEvents();		

	}
}

void Game::Update()
{
	m_pGameStateManager->UpdateGameStates(GetDeltaTime());
	
	if(g_inputManager.KeyPressedOnce(GLFW_KEY_ESCAPE))
		m_bGameOver = true;

	if(g_inputManager.KeyPressedOnce( GLFW_KEY_F1 ))
	{
		if( m_vSyncEnabled == false)
		{
			m_vSyncEnabled = true;
		}

		else if( m_vSyncEnabled == true)
		{
			m_vSyncEnabled = false;
		}
			VSyncEnabled( m_vSyncEnabled );
			m_fTotalTime	 = 0;
			m_iTotalFrames	 = 0;
	}

	g_inputManager.ProcessKeyboardCommands();
	g_inputManager.ProcessMouseCommands();
}

void Game::Draw()
{
	/*
	// Please Note:
	// most of the gl Functions within this draw method are imidiate mode rendering functions
	// which are all depreciated as of OpenGL 3.0 and above.
	// however, they are very convenient for learning the basics of openGL.


	// pre declaring some variables for use later on in this function
	float xPos, yPos, width, height;

	static float xTexCoordOffset = 0.0f;
	xTexCoordOffset += m_deltaTime * 0.5f;


	// Rendering first quad to the screen
	//----------------------------------------------------------------------------
		xPos		= 50;
		yPos		= 50;
		width		= 150;
		height		= 150;

		// bind the texture that we wish to use for rendering
		glBindTexture( GL_TEXTURE_2D, m_pTexture->GetTextureHandle() );

		glBegin(GL_QUADS);

			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);		glTexCoord2f(0.0f, 0.0f);	glVertex2f(xPos,			yPos);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);		glTexCoord2f(1.0f, 0.0f);	glVertex2f(xPos + width,	yPos);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);		glTexCoord2f(1.0f, 1.0f);	glVertex2f(xPos + width,	yPos + height);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);		glTexCoord2f(0.0f, 1.0f);	glVertex2f(xPos,			yPos + height);

		glEnd();
	//----------------------------------------------------------------------------

	// render a second quad to the screen
	// this time the texture coordinates are modified a bit
	// note what texture paramaters are used by defailt...
	// 
	// TODO: Change the Texture Paramaters from GL_REPEAT
	// to one of these:  GL_CLAMP, GL_REPEAT
	//-----------------------------------------------------------------
		xPos		= 250;
		yPos		= 50;
		width		= m_pTexture->GetWidth();
		height		= m_pTexture->GetHeight();

		glBindTexture( GL_TEXTURE_2D, m_pTexture->GetTextureHandle() );

		// note that we set these paramaters to a default value (GL_REPEAT) in the Load Texture function
		// these paramaters modify the texture properties of the currently bound texture.
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// also notice, i only have to change the color once...
		// and it will apply to all vertices until the color is changed again...
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);

			glTexCoord2f(0.0f + xTexCoordOffset, 0.0f);	glVertex2f(xPos,			yPos);
			glTexCoord2f(1.0f + xTexCoordOffset, 0.0f);	glVertex2f(xPos + width,	yPos);
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);	glTexCoord2f(1.0f + xTexCoordOffset, 1.0f);	glVertex2f(xPos + width,	yPos + height);
			glTexCoord2f(0.0f + xTexCoordOffset, 1.0f);	glVertex2f(xPos,			yPos + height);

		glEnd();
	//-----------------------------------------------------------------
	

	m_pSpriteBatch->Begin();

	m_pSpriteBatch->SetRenderColour(255.0f, 0.0f, 0.0f, 255.0f);

	m_pSpriteBatch->SetUVCoordinates(1.0f, 0.5f);
	SetUVCoordinates(Vec2(0.5f, 0), Vec2(1, 0), Vec2(1, 0.5f), Vec2(0.5f, 0.5f));
	
	DrawSprite( m_pCrate, Vec2(m_fWindowWidth/2, m_fWindowHeight/2) );

	m_pSpriteBatch->SetUVCoordinates(Vec2(m_ufMoveUVLeft,0), Vec2(m_ufMoveUVRight,0), Vec2(m_ufMoveUVRight,1), Vec2(m_ufMoveUVLeft, 1));
	
	DrawSprite( m_pCrate, Vec2(m_iMoveSpriteX,m_iMoveSpriteY), Vec2(100, 100) );
	m_pSpriteBatch->DrawSprite( m_pCrate, Vec2(400,200) );	

	m_pSpriteBatch->End();*/

	m_pGameStateManager->DrawGameStates();
}


void Game::VSyncEnabled( bool enable )
{
	//Pointer function to Open GL Swap Interval External Procedure
	typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(wglSwapIntervalEXT)
	{
		wglSwapIntervalEXT( (enable)? 1 : 0 );
	}
}