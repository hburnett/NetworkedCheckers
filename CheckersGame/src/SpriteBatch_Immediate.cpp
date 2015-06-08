#include "SpriteBatch_Immediate.h"
#include "Game.h"
#include "glfw3.h"
#include "Texture.h"
#include "Vec2.h"
#include "Mat3.h"


SpriteBatch_Immediate::SpriteBatch_Immediate(Game *pGame) : SpriteBatch(pGame)
{

}

void SpriteBatch_Immediate::Begin()
{
	
	// Initialise openGL 2.0 and setup orthographic view
	// Note some of this code is depreciated as of OpenGL 3.0
	//----------------------------------------------------------------------------
	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glMatrixMode(GL_PROJECTION); // DEPRECIATED: shaders used instead - user to provide projection matrix to the shader
		glLoadIdentity();			 // sets the GL_PROJECTION matrix to the identity matrix

		// setup orthographic projection (for rendering 2D)
		// DEPRECIATED: the projection matrix would be sent to the active shader
		//	glOrtho(0.0f, m_pGame->GetWindowWidth(), m_pGame->GetWindowHeight(), 0, -1, 1);		// WINDOW ORIGIN: Top Left
			glOrtho(0.0f, m_pGame->GetWindowWidth(), 0, m_pGame->GetWindowHeight(), -1, 1);		// WINDOW ORIGIN: Bottom Left
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		

		// DEPRECIATED: pixel shaders define the final color after rasterization step in the graphics pipeline
		glEnable(GL_TEXTURE_2D); 

		// DEPRECIATED: again, Matrices do not exist on future versions of OpenGL.
		// a model view matrix would be sent to the shader... 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	//----------------------------------------------------------------------------

		m_camera.CreateIdentity();
}

void SpriteBatch_Immediate::Begin(const Mat3 &camera)
{
	Begin();
	m_camera = camera;
}

void SpriteBatch_Immediate::End()		
{

}

//xPos and yPos will be a Vec2
void SpriteBatch_Immediate::DrawSprite( Texture *pTexture, Vec2 &pos ) 
{
	unsigned int width = pTexture->GetWidth() / 2;
	unsigned int height = pTexture->GetHeight() / 2;

	// bind the texture that we wish to use for rendering
	glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureHandle() );

	glBegin(GL_QUADS);
	
	glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glTexCoord2f( m_bottomLeftUV.x,		m_bottomLeftUV.y	);	glVertex2f( pos.x - width,	pos.y + height	);		//bottom left
		glTexCoord2f( m_bottomRightUV.x,	m_bottomRightUV.y	);	glVertex2f( pos.x + width,	pos.y + height	);		//bottom right
		glTexCoord2f( m_topRightUV.x,		m_topRightUV.y		);	glVertex2f( pos.x + width,	pos.y - height	);		//Top right
		glTexCoord2f( m_topLeftUV.x,		m_topLeftUV.y		);	glVertex2f( pos.x - width,	pos.y - height	);		//Top left

	glEnd();
}

void SpriteBatch_Immediate::DrawSprite( Texture *pTexture, Vec2 &pos, Vec2 &dimensions )
{
	unsigned int width  = (unsigned int) dimensions.x / 2;
	unsigned int height = (unsigned int) dimensions.y / 2;
	
	// bind the texture that we wish to use for rendering
	glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureHandle() );
	
	glBegin(GL_QUADS);
	
	glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);
	
		glTexCoord2f( m_bottomLeftUV.x,		m_bottomLeftUV.y	);	glVertex2f( pos.x - dimensions.x,	pos.y + dimensions.y	);		//bottom left
		glTexCoord2f( m_bottomRightUV.x,	m_bottomRightUV.y	);	glVertex2f( pos.x + dimensions.x,	pos.y + dimensions.y	);		//bottom right
		glTexCoord2f( m_topRightUV.x,		m_topRightUV.y		);	glVertex2f( pos.x + dimensions.x,	pos.y - dimensions.y	);		//Top right
		glTexCoord2f( m_topLeftUV.x,		m_topLeftUV.y		);	glVertex2f( pos.x - dimensions.x,	pos.y - dimensions.y	);		//Top left
	
	glEnd(); 
 }

//If anything rotates, ever, use a matrix!
void SpriteBatch_Immediate::DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size )
{
	Vec2 m_topLeftVertex;
		 m_topLeftVertex.x		= -0.5f	* size.x;
		 m_topLeftVertex.y		= 0.5f	* size.y;

	Vec2 m_topRightVertex;
		 m_topRightVertex.x		= 0.5f * size.x;
		 m_topRightVertex.y		= 0.5f * size.y;

	Vec2 m_bottomRightVertex;
		 m_bottomRightVertex.x	= 0.5f	* size.x;
		 m_bottomRightVertex.y	= -0.5f	* size.y;

	Vec2 m_bottomLeftVertex;
		 m_bottomLeftVertex.x	= -0.5f * size.x;
		 m_bottomLeftVertex.y	= -0.5f * size.y;


	m_topLeftVertex		=  m_camera * (m_topLeftVertex		* transform); 
	m_topRightVertex	=  m_camera * (m_topRightVertex		* transform); 
	m_bottomRightVertex	=  m_camera * (m_bottomRightVertex	* transform);
	m_bottomLeftVertex	=  m_camera * (m_bottomLeftVertex	* transform); 

	if( texture != NULL )
	{

		glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() );
		glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glBegin(GL_QUADS);
		
			glTexCoord2f( m_bottomLeftUV.x,		m_bottomLeftUV.y	);		glVertex2f( m_bottomLeftVertex.x,	m_bottomLeftVertex.y	);
			glTexCoord2f( m_bottomRightUV.x,	m_bottomRightUV.y	);		glVertex2f( m_bottomRightVertex.x,	m_bottomRightVertex.y	);
			glTexCoord2f( m_topRightUV.x,		m_topRightUV.y		);		glVertex2f( m_topRightVertex.x,		m_topRightVertex.y		);
			glTexCoord2f( m_topLeftUV.x,		m_topLeftUV.y		);		glVertex2f( m_topLeftVertex.x,		m_topLeftVertex.y		);
		
		glEnd();

	}

	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glBegin(GL_QUADS);
	
			glVertex2f( m_topLeftVertex.x,		m_topLeftVertex.y		);
			glVertex2f( m_topRightVertex.x,		m_topRightVertex.y	);
			glVertex2f( m_bottomRightVertex.x,	m_bottomRightVertex.y	);
			glVertex2f( m_bottomLeftVertex.x,	m_bottomLeftVertex.y	);
	
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

}

//Uses a direction (-1 or 1) to invert the image if needed
void SpriteBatch_Immediate::DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size, int direction )
{
	Vec2 m_topLeftVertex;
		 m_topLeftVertex.x		= -0.5f	* size.x * direction;
		 m_topLeftVertex.y		= 0.5f	* size.y;
	
	Vec2 m_topRightVertex;
		 m_topRightVertex.x		= 0.5f * size.x * direction;
		 m_topRightVertex.y		= 0.5f * size.y;
	
	Vec2 m_bottomRightVertex;
		 m_bottomRightVertex.x	= 0.5f	* size.x * direction;
		 m_bottomRightVertex.y	= -0.5f	* size.y;
	
	Vec2 m_bottomLeftVertex;
		 m_bottomLeftVertex.x	= -0.5f * size.x * direction;
		 m_bottomLeftVertex.y	= -0.5f * size.y;
	
	m_topLeftVertex		=  m_camera * (m_topLeftVertex		* transform); 
	m_topRightVertex	=  m_camera * (m_topRightVertex		* transform); 
	m_bottomRightVertex	=  m_camera * (m_bottomRightVertex	* transform);
	m_bottomLeftVertex	=  m_camera * (m_bottomLeftVertex	* transform); 

	if( texture != NULL )
	{

		glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() );
		glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glBegin(GL_QUADS);
		
			glTexCoord2f( m_bottomLeftUV.x,		m_bottomLeftUV.y	);		glVertex2f( m_bottomLeftVertex.x,	m_bottomLeftVertex.y	);
			glTexCoord2f( m_bottomRightUV.x,	m_bottomRightUV.y	);		glVertex2f( m_bottomRightVertex.x,	m_bottomRightVertex.y	);
			glTexCoord2f( m_topRightUV.x,		m_topRightUV.y		);		glVertex2f( m_topRightVertex.x,		m_topRightVertex.y		);
			glTexCoord2f( m_topLeftUV.x,		m_topLeftUV.y		);		glVertex2f( m_topLeftVertex.x,		m_topLeftVertex.y		);
		
		glEnd();

	}

	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glBegin(GL_QUADS);
	
			glVertex2f( m_topLeftVertex.x,		m_topLeftVertex.y		);
			glVertex2f( m_topRightVertex.x,		m_topRightVertex.y	);
			glVertex2f( m_bottomRightVertex.x,	m_bottomRightVertex.y	);
			glVertex2f( m_bottomLeftVertex.x,	m_bottomLeftVertex.y	);
	
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

}


void SpriteBatch_Immediate::DrawSprite( Texture *texture, float xPos, float yPos )
{	
	unsigned int width = texture->GetWidth();
	unsigned int height = texture->GetHeight();

	glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() );
	glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

	glBegin(GL_QUADS);
	
		glTexCoord2f( m_bottomLeftUV.x,		m_bottomLeftUV.y	);	glVertex2f(xPos,			yPos);
		glTexCoord2f( m_bottomRightUV.x,	m_bottomRightUV.y	);	glVertex2f(xPos + width,	yPos);
		glTexCoord2f( m_topRightUV.x,		m_topRightUV.y		);	glVertex2f(xPos + width,	yPos + height);
		glTexCoord2f( m_topLeftUV.x,		m_topLeftUV.y		);	glVertex2f(xPos,			yPos + height);
	
	glEnd();
}

void SpriteBatch_Immediate::DrawSprite( Texture *texture, float xPos, float yPos, float width, float height )
{
	
	if( texture != NULL )
	{
		glBindTexture( GL_TEXTURE_2D,  texture->GetTextureHandle() );
		glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glBegin(GL_QUADS);
	
			glTexCoord2f( m_bottomLeftUV.x,		m_bottomLeftUV.y	);	glVertex2f(xPos,			yPos);
			glTexCoord2f( m_bottomRightUV.x,	m_bottomRightUV.y	);	glVertex2f(xPos + width,	yPos);
			glTexCoord2f( m_topRightUV.x,		m_topRightUV.y		);	glVertex2f(xPos + width,	yPos + height);
			glTexCoord2f( m_topLeftUV.x,		m_topLeftUV.y		);	glVertex2f(xPos,			yPos + height);
	
		glEnd();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(m_fRed, m_fGreen, m_fBlue, m_fAlpha);

		glBegin(GL_QUADS);
	
			glVertex2f(xPos,			yPos);
			glVertex2f(xPos + width,	yPos);
			glVertex2f(xPos + width,	yPos + height);
			glVertex2f(xPos,			yPos + height);
	
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}
}