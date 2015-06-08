/*--------------------------------------------------------------------
Author: Heath Burnett

Description: Input manager, handles all keyboard and mouse input
---------------------------------------------------------------------*/


#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include "glfw3.h"

class Mat3;
class Vec2;

class InputManager
{

public:	

	InputManager();

	void DefineWindow( GLFWwindow *pWindow );
	//Start keyboard functions ------------------------------------------------------

	// Checks if key was released last frame
	// and held down this frame
	bool KeyPressedOnce( int keyInput );			

	// Checks if key is held down
	bool KeyHeldDown( int keyInput );


	// Checks if the key was held down last frame
	// and was released this frame
	bool KeyReleased( int keyInput );

	//End keyboard functions --------------------------------------------------------


	//Start mouse functions ---------------------------------------------------------

	bool	GetMouseClicked(  int mouseInput );
	bool	GetMouseHeldDown( int mouseInput );
	bool	GetMouseReleased( int mouseInput );

	// Camera matrix is taken into account before calculating mouse position
	Vec2	GetMouseLocation();
	Vec2	GetMouseLocation( Mat3 camera );
	
	bool	MouseOverAtPosition( Vec2 position, Vec2 size );
	bool	IsClickedAtPosition( Vec2 position, Vec2 size );

	//End mouse functions -----------------------------------------------------------

	void ProcessMouseCommands();

	void ProcessKeyboardCommands();

private:

	void KeyboardPressed( int keyInput );

	void KeyboardReleased( int keyInput );

	void MousePressed( int mouseInput );

	void MouseReleased( int mouseInput );
		
	int	m_iaKeyboardState[349];
	int	m_iaMouseState[8];

	
	enum InputCommands
	{
		PRESSED,
		RELEASED,
	};

	struct MouseInputCommands
	{
		int input;
		InputCommands cmd;
	};

	struct KeyboardInputCommands
	{
		int input;
		InputCommands cmd;
	};
		
	std::vector< MouseInputCommands > m_vMouseCommands;
	std::vector< KeyboardInputCommands > m_vKeyboardCommands;

	GLFWwindow	*m_pWindow;

};
#endif