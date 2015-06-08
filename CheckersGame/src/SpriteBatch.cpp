#include "SpriteBatch.h"
#include "SpriteBatch_Immediate.h"
#include "SpriteBatch_NonImmediate.h"
#include "Vec2.h"
#include "Game.h"


SpriteBatch::SpriteBatch(Game *pGame)
{
	m_pGame = pGame;

	m_fRed				= 1.0f;
	m_fGreen			= 1.0f;
	m_fBlue				= 1.0f;
	m_fAlpha			= 1.0f;

	m_topLeftUV.x		= 0.0f;
	m_topLeftUV.y		= 0.0f;

	m_topRightUV.x		= 1.0f;
	m_topRightUV.y		= 0.0f;

	m_bottomRightUV.x	= 1.0f;
	m_bottomRightUV.y	= 1.0f;

	m_bottomLeftUV.x	= 0.0f;
	m_bottomLeftUV.y	= 1.0f;

}

SpriteBatch *SpriteBatch::Create( Game *pGame, ESpriteBatchType type )
{
	if( type == IMMEDIATE )
	{
		return new SpriteBatch_Immediate(pGame);
	}

	if( type == NON_IMMEDIATE )
	{
		return new SpriteBatch_NonImmediate(pGame);
	}

	return new SpriteBatch(pGame);

}

void SpriteBatch::Destroy( SpriteBatch *pSpriteBatch )
{
	delete pSpriteBatch;
}

void SpriteBatch::SetUVCoordinates(Vec2 &topLeft, Vec2 &topRight, Vec2 &bottomRight, Vec2 &bottomLeft)
{
	m_topLeftUV	    = topLeft;
	m_topRightUV	= topRight;
	m_bottomRightUV	= bottomRight;
	m_bottomLeftUV	= bottomLeft;
}

void SpriteBatch::SetUVCoordinates(Vec2 &topLeft, Vec2 &bottomRight)
{
	m_topLeftUV			= topLeft;
	m_topRightUV.x		= bottomRight.x;
	m_topRightUV.y		= topLeft.y;
	m_bottomRightUV		= bottomRight;
	m_bottomLeftUV.x	= topLeft.x;
	m_bottomLeftUV.y	= bottomRight.y;
}

void SpriteBatch::SetColour(unsigned int color)
{
	m_fRed		= ((color & 0xFF000000) >> 24 ) / 255.0f;
	m_fGreen	= ((color & 0x00FF0000) >> 16) / 255.0f;
	m_fBlue		= ((color & 0x0000FF00) >> 8 ) / 255.0f;
	m_fAlpha	= ((color & 0x000000FF) >> 0 ) / 255.0f;
}

void SpriteBatch::SetColour(float r, float g, float b, float a)
{
	m_fRed		= r;
	m_fGreen	= g;
	m_fBlue		= b;
	m_fAlpha	= a;
}

void SpriteBatch::DrawLine( Vec2 startingPoint, Vec2 endingPoint, const Mat3 &transform )
{
	glDisable(GL_TEXTURE_2D);
	glColor4f(m_fRed/255.0f, m_fGreen/255.0f, m_fBlue/255.0f, m_fAlpha/255.0f);
	glBegin(GL_LINES);
	
		glVertex2f((startingPoint.x * transform.GetScale().x)  +  transform.GetTranslation().x, (startingPoint.y * transform.GetScale().y) + transform.GetTranslation().y);	
		glVertex2f((endingPoint.x   * transform.GetScale().x)  +  transform.GetTranslation().x, (endingPoint.y   * transform.GetScale().y) + transform.GetTranslation().y);	
		
	glEnd();
	glEnable(GL_TEXTURE_2D);
}