#include "InputManager.h"
#include "Vec2.h"

InputManager::InputManager()
{
	for(int i = 0; i < 349; i++)
	{	m_iaKeyboardState[i] = 0;	}

	for( int i = 0; i < 8; i++)
	{	m_iaMouseState[i] = 0;	}
}

void InputManager::DefineWindow( GLFWwindow *pWindow )
{	
	m_pWindow = pWindow;	
}

bool InputManager::KeyHeldDown( int keyInput)
{		
	if( glfwGetKey(m_pWindow, keyInput ) == GLFW_PRESS)
	{
		KeyboardPressed( keyInput );
		return true;
	}

	KeyboardReleased( keyInput );
	return false;

	/*int glfwGetKey( 48 );				0
	int glfwGetKey( 49 );			 	1
	int glfwGetKey( 50 );				2
	int glfwGetKey( 51 );				3
	int glfwGetKey( 52 );				4
	int glfwGetKey( 53 );				5
	int glfwGetKey( 54 );				6
	int glfwGetKey( 55 );				7
	int glfwGetKey( 56 );				8
	int glfwGetKey( 57 );				9
	int glfwGetKey( 59 );				;
	int glfwGetKey( 61 );				=
	int glfwGetKey( 65 );				A
	int glfwGetKey( 66 );				B
	int glfwGetKey( 67 );				C
	int glfwGetKey( 68 );				D
	int glfwGetKey( 69 );				E
	int glfwGetKey( 70 );				F
	int glfwGetKey( 71 );				G
	int glfwGetKey( 72 );				H
	int glfwGetKey( 73 );				I
	int glfwGetKey( 74 );				J
	int glfwGetKey( 75 );				K
	int glfwGetKey( 76 );				L
	int glfwGetKey( 77 );				N
	int glfwGetKey( 78 );				M
	int glfwGetKey( 79 );				O
	int glfwGetKey( 80 );				P
	int glfwGetKey( 81 );				Q
	int glfwGetKey( 82 );				R
	int glfwGetKey( 83 );				S
	int glfwGetKey( 84 );				T
	int glfwGetKey( 85 );				U
	int glfwGetKey( 86 );				V
	int glfwGetKey( 87 );				W
	int glfwGetKey( 88 );				X
	int glfwGetKey( 89 );				Y
	int glfwGetKey( 90 );				Z
	int glfwGetKey( 256 );				Escape
	int glfwGetKey( 257);				Enter
	int glfwGetKey( 258 );				Tab
	int glfwGetKey( 259 );				Backspace
	int glfwGetKey( 262 );				Right
	int glfwGetKey( 263 );				Left
	int glfwGetKey( 264 );				Down
	int glfwGetKey( 265 );				Up		*/
}

bool InputManager::KeyPressedOnce(int keyInput)
{	
	if( glfwGetKey(m_pWindow, keyInput ) == GLFW_PRESS && m_iaKeyboardState[keyInput] == 0)
	{		
		KeyboardPressed( keyInput );
		return true;
	}

	//Checks if input is still held down or not
	KeyHeldDown( keyInput );
	
	return false;
}

bool InputManager::KeyReleased( int keyInput )
{
	if( glfwGetKey(m_pWindow, keyInput ) == GLFW_RELEASE && m_iaKeyboardState[keyInput] == 1)
	{		
		KeyboardReleased( keyInput );
		return true;
	}
	
	KeyboardPressed( keyInput );
	return false;
}

bool InputManager::GetMouseHeldDown( int mouseInput )
{
	if( glfwGetMouseButton( m_pWindow, mouseInput ) == GLFW_PRESS )
	{
		MousePressed( mouseInput );
		return true;
	}

	MouseReleased( mouseInput );
	return false;
}

bool InputManager::GetMouseReleased( int mouseInput )
{
	if( glfwGetMouseButton( m_pWindow, mouseInput ) == GLFW_RELEASE )
	{
		MouseReleased( mouseInput );
		return true;
	}

	MousePressed( mouseInput );
	return false;
}

bool InputManager::GetMouseClicked( int mouseInput )
{
	if( glfwGetMouseButton( m_pWindow, mouseInput ) == GLFW_PRESS && m_iaMouseState[mouseInput] == 0 )
	{
		MousePressed( mouseInput );
		return true;
	}

	GetMouseHeldDown( mouseInput );
	return false;

	/*
	#define GLFW_MOUSE_BUTTON_1         0
	#define GLFW_MOUSE_BUTTON_2         1
	#define GLFW_MOUSE_BUTTON_3         2
	#define GLFW_MOUSE_BUTTON_4         3
	#define GLFW_MOUSE_BUTTON_5         4
	#define GLFW_MOUSE_BUTTON_6         5
	#define GLFW_MOUSE_BUTTON_7         6
	#define GLFW_MOUSE_BUTTON_8         7
	*/
}

void InputManager::KeyboardPressed( int keyInput )
{
	KeyboardInputCommands command;
	command.input = keyInput;
	command.cmd = PRESSED;
	m_vKeyboardCommands.push_back( command );
}

void InputManager::KeyboardReleased( int keyInput )
{
	KeyboardInputCommands command;
	command.input = keyInput;
	command.cmd = RELEASED;
	m_vKeyboardCommands.push_back( command );
}

void InputManager::MousePressed( int mouseInput )
{
	MouseInputCommands command;
	command.input = mouseInput;
	command.cmd = PRESSED;
	m_vMouseCommands.push_back( command );
}

void InputManager::MouseReleased( int mouseInput )
{
	MouseInputCommands command;
	command.input = mouseInput;
	command.cmd = RELEASED;
	m_vMouseCommands.push_back( command );
}

void InputManager::ProcessMouseCommands()
{
	for( size_t i = 0; i < m_vMouseCommands.size(); i++ )
	{		
		if( m_vMouseCommands[i].cmd == PRESSED )
		{
			m_iaMouseState[m_vMouseCommands[i].input] = GLFW_PRESS;
		}

		else if( m_vMouseCommands[i].cmd == RELEASED )
		{
			m_iaMouseState[m_vMouseCommands[i].input] = GLFW_RELEASE;
		}
	}

	m_vMouseCommands.clear();
}

void InputManager::ProcessKeyboardCommands()
{
	for( size_t i = 0; i < m_vKeyboardCommands.size(); i++ )
	{		
		if( m_vKeyboardCommands[i].cmd == PRESSED )
		{
			m_iaKeyboardState[m_vKeyboardCommands[i].input] = GLFW_PRESS;
		}

		else if( m_vKeyboardCommands[i].cmd == RELEASED )
		{
			m_iaKeyboardState[m_vKeyboardCommands[i].input] = GLFW_RELEASE;
		}
	}

	m_vKeyboardCommands.clear();
}

bool InputManager::MouseOverAtPosition( Vec2 position, Vec2 size )
{
	Vec2 mousePosition = GetMouseLocation();

	if( mousePosition.x > position.x - size.x/2 && mousePosition.x < position.x + size.x/2 &&
		mousePosition.y > position.y - size.y/2 && mousePosition.y < position.y + size.y/2 )
	{
		return true;
	}
	
	else return false;



}

bool InputManager::IsClickedAtPosition( Vec2 position, Vec2 size )
{
	if( MouseOverAtPosition(position, size) && GetMouseClicked(0))
	{
		return true;
	}

	else return false;

}

Vec2 InputManager::GetMouseLocation()
{
	//Vec2 cameraTranslation( GetCamera().GetTranslation() );

	//cameraTranslation = Vec2( std::abs( cameraTranslation.x), std::abs( cameraTranslation.y ));
	double xpos, ypos;
	int w, h;
	glfwGetCursorPos(m_pWindow, &xpos, &ypos);
	glfwGetWindowSize(m_pWindow, &w, &h);
	ypos = h - ypos;

	Vec2 mousePosition(xpos, ypos);


	//return Vec2((mx / GetCamera().GetScale().x)  - cameraTranslation.x  / GetCamera().GetScale().x, (my / GetCamera().GetScale().y) - cameraTranslation.y / GetCamera().GetScale().y);	

	return mousePosition;
}
