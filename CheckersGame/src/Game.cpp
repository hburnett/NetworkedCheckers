#include "WindowsIncludes.h"
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
#include <stdio.h>
#include <string.h>

Game::Game(float windowWidth, float windowHeight, const char *windowTitle, bool fullscreen, bool isServer, RakNet::RakPeerInterface* pPeerInterface)
{
	CreateNewWindow(windowWidth, windowHeight, windowTitle, fullscreen);

	m_pPeerInterface = pPeerInterface;
	m_bIsServer = isServer;

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