/*-----------------------------------------------------------------------------
		Author:			Shane Coates
		Description:	Basic Game State manager
						Handles a stack of game states
-----------------------------------------------------------------------------*/

#ifndef GAMESTATEMANAGER_H
#define	GAMESTATEMANAGER_H

#include <map>
#include <vector>

//predefinition
class GameStateManager;

class Game;

class IGameState
{
public:

	IGameState(GameStateManager * pGameStateManager, Game * pGame );
	virtual ~IGameState() {}

	virtual void Update(float dt) {}

	virtual void Draw() {}

	virtual void Load() {}

	virtual void Unload() {}

protected:

	GameStateManager * m_pGameStateManager;

	Game * m_pGame;
	
private:

};


class GameStateManager
{
public:


	//constructor
	GameStateManager();

	//destructor
	virtual ~GameStateManager();

	//should be called each frame by the "Game" class
	void UpdateGameStates(float dt);
	void DrawGameStates();

	//used to manipulate the game state stack
	void SetState(const char *name,  IGameState *pState);
	
	void PushState(const char *name);
	
	void PopState();
	

protected:

	void ProcessCommands();

protected:

	//contains all of the available game states that have been
	//registered with the game state manager
	std::map<const char *, IGameState *> m_availableStates;

	//list of game states that are being updated and drawn
	std::vector< IGameState* > m_gameStateStack;

	
	enum ECommands
	{
		E_PUSH,
		E_POP,
	};


	struct SCommand
	{
		const char *name;
		ECommands cmd;
	};

	std::vector< SCommand > m_commands;
private:
};

#endif