//Author: Heath Burnett
//Credit to Aaron Cox
//
//Description: Static sprite class, inherits from node
//Draws a single sprite to the screen

#ifndef	  STATIC_SPRITE_H
#define	  STATIC_SPRITE_H

#include "Node.h"

#include "Vec2.h"

class SpriteBatch;

class Vec2;

class Texture;

class StaticSprite : public Node
{
public:
		
	StaticSprite();
	StaticSprite( Texture *pTexture );
	StaticSprite( Texture *pTexture, Vec2 size );
		
	virtual ~StaticSprite();

	virtual void Draw( SpriteBatch *sb );

	virtual void Draw( SpriteBatch *sb, int direction );

	//Texture functions
	void SetTexture(Texture *pTexture )							{ m_pTexture = pTexture; }
	Texture *GetTexture()										{ return m_pTexture; }

	//Size functions
	Vec2 GetSize()												{ return m_size; }
	void SetSize(Vec2 size )									{ m_size = size; }

	//Colour functions
	void SetColour( unsigned char r, unsigned char g, unsigned char b, unsigned char a );

	//UV Coords functions
	void SetUVCoordinates( Vec2 topLeft, Vec2 topRight, Vec2 bottomRight, Vec2 bottomLeft );
		
	//UV Coords functions
	void SetUVCoordinates( Vec2 topLeft, Vec2 bottomRight );

	Vec2 GetTopLeftUVCoordinates()								{ return m_topLeftUV;		}
	Vec2 GetTopRightUVCoordinates()								{ return m_topRightUV;		}
	Vec2 GetBottomRightUVCoordinates()							{ return m_bottomRightUV;	}
	Vec2 GetBottomLeftUVCoordinates()							{ return m_bottomLeftUV;	}


protected:

	Texture			*m_pTexture;

	Mat3			worldTransform;

	Vec2			m_size;

	Vec2			m_topLeftUV, m_topRightUV, m_bottomRightUV, m_bottomLeftUV;
	
	unsigned char	m_cRed, m_cGreen, m_cBlue, m_cAlpha;

private:


};
#endif