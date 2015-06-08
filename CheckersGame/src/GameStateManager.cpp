#include "GameStateManager.h"
#include "Game.h"

// IGameState
//-----------------------------------------------------------------------------
IGameState::IGameState(GameStateManager * pGameStateManager, Game *pGame)
{
	m_pGameStateManager = pGameStateManager;
	m_pGame				= pGame;
}

//-----------------------------------------------------------------------------
// IGameState


//constructor
GameStateManager::GameStateManager()
{

}

//destructor
GameStateManager::~GameStateManager()
{
	for( auto iter = m_availableStates.begin(); iter != m_availableStates.end(); iter++)
	{	
		if(iter->second != NULL)
			delete iter->second;
	}

	m_availableStates.clear();
}

//should be called each frame by the "Game" class
void GameStateManager::UpdateGameStates(float dt)
{
	ProcessCommands();

	for(auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{
		(*itr)->Update(dt);
	}
}

void GameStateManager::DrawGameStates()
{

	for(auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void GameStateManager::ProcessCommands()
{
	for(size_t i = 0; i < m_commands.size(); i++)
	{
		if(m_commands[i].cmd == E_PUSH)
		{
			auto iter = m_availableStates.find(m_commands[i].name);
			if(iter != m_availableStates.end())
			{
				m_gameStateStack.push_back(iter->second);
			}
		}

		else if(m_commands[i].cmd == E_POP)
		{
			if(m_gameStateStack.size() > 0)
				m_gameStateStack.pop_back();
		}
	}

	//now that all commands have been processed, clear the list for the next frame...
	m_commands.clear();
}

//used to manipulate the game state stack

void GameStateManager::PushState(const char *name)
{
	SCommand command;
	command.name = name;
	command.cmd = E_PUSH;
	m_commands.push_back(command);
}

void GameStateManager::PopState()
{
	SCommand command;
	command.cmd = E_POP;

	m_commands.push_back(command);
}


void GameStateManager::SetState(const char *name,  IGameState *pState)
{
	auto iter = m_availableStates.find(name);
	if(iter != m_availableStates.end())
	{
		if(iter->second != NULL)
			delete iter->second;
	}

	m_availableStates[ name ] = pState;
}