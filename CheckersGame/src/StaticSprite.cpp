#include "StaticSprite.h"
#include "SpriteBatch.h"

StaticSprite::StaticSprite() : Node()
{
	m_pTexture	= nullptr;
	
	m_size		= Vec2(16, 16);
	
	m_cRed	    = 255;
	m_cGreen    = 255;
	m_cBlue	    = 255;
	m_cAlpha    = 255;
	
	m_topLeftUV.x		= 0.0f;
	m_topLeftUV.y		= 0.0f;
	
	m_topRightUV.x		= 1.0f;
	m_topRightUV.y		= 0.0f;
	
	m_bottomRightUV.x	= 1.0f;
	m_bottomRightUV.y	= 1.0f;
	
	m_bottomLeftUV.x	= 0.0f;
	m_bottomLeftUV.y	= 1.0f; 

}

StaticSprite::StaticSprite( Texture *pTexture )
{
	m_pTexture	= pTexture;
	
	m_size		= Vec2(16, 16);
	
	m_cRed	    = 255;
	m_cGreen    = 255;
	m_cBlue	    = 255;
	m_cAlpha    = 255;

	m_topLeftUV.x		= 0.0f;
	m_topLeftUV.y		= 0.0f;
	
	m_topRightUV.x		= 1.0f;
	m_topRightUV.y		= 0.0f;
	
	m_bottomRightUV.x	= 1.0f;
	m_bottomRightUV.y	= 1.0f;
	
	m_bottomLeftUV.x	= 0.0f;
	m_bottomLeftUV.y	= 1.0f;
	
}

StaticSprite::StaticSprite( Texture *pTexture, Vec2 size )
{
	m_pTexture	= pTexture;
	
	m_size		= size;
	
	m_cRed	    = 255;
	m_cGreen    = 255;
	m_cBlue	    = 255;
	m_cAlpha    = 255;

	m_topLeftUV.x		= 0.0f;
	m_topLeftUV.y		= 0.0f;
	
	m_topRightUV.x		= 1.0f;
	m_topRightUV.y		= 0.0f;
	
	m_bottomRightUV.x	= 1.0f;
	m_bottomRightUV.y	= 1.0f;
	
	m_bottomLeftUV.x	= 0.0f;
	m_bottomLeftUV.y	= 1.0f;
}

StaticSprite::~StaticSprite()
{

}


//Colour functions
void StaticSprite::SetColour( unsigned char r, unsigned char g, unsigned char b, unsigned char a )
{
	m_cRed	= r;  m_cGreen	= g;  m_cBlue  = b;  m_cAlpha  = a;
}

//UV Coords functions
void StaticSprite::SetUVCoordinates( Vec2 topLeft, Vec2 topRight, Vec2 bottomRight, Vec2 bottomLeft )
{
	m_topLeftUV = topLeft;				
	m_topRightUV = topRight;
	m_bottomRightUV = bottomRight;		
	m_bottomLeftUV = bottomLeft;
}

void StaticSprite::SetUVCoordinates( Vec2 topLeft, Vec2 bottomRight )
{
	m_topLeftUV = topLeft;				
	m_topRightUV.x = bottomRight.x;
	m_topRightUV.y = topLeft.y;
	m_bottomRightUV = bottomRight;		
	m_bottomLeftUV.x = topLeft.x;
	m_bottomLeftUV.y = bottomRight.y;
}

void StaticSprite::Draw( SpriteBatch *sb )
{
	worldTransform = GetWorldTransform();

	sb->SetColour( (float) m_cRed/255, (float) m_cGreen/255, (float) m_cBlue/255, (float) m_cAlpha/255);
	sb->SetUVCoordinates(m_topLeftUV, m_topRightUV, m_bottomRightUV, m_bottomLeftUV);
	sb->DrawSprite(m_pTexture, worldTransform, m_size );
}

void StaticSprite::Draw( SpriteBatch *sb, int direction )
{
	worldTransform = GetWorldTransform();

	sb->SetColour( (float) m_cRed/255, (float) m_cGreen/255, (float) m_cBlue/255, (float) m_cAlpha/255);
	sb->SetUVCoordinates(m_topLeftUV, m_topRightUV, m_bottomRightUV, m_bottomLeftUV);
	sb->DrawSprite(m_pTexture, worldTransform, m_size, direction );
}
