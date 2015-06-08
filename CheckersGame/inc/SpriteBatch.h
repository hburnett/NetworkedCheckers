//Author: Heath Burnett
//Description: Sprite Batch interface class and Factory

#ifndef	SPRITEBATCH_H
#define	SPRITEBATCH_H

#include "Mat3.h"
#include "Vec2.h"

class Texture;

class Game;

class Mat3;

class Vec2;

class SpriteBatch
{
public:
	
	enum ESpriteBatchType
	{
		NONE,
		IMMEDIATE,
		NON_IMMEDIATE,
	};


public:

	static SpriteBatch *Create( Game *pGame, ESpriteBatchType type );
	static void Destroy( SpriteBatch *pSpriteBatch );
	
	virtual void Begin(const Mat3 &camera) {};
	virtual void Begin()	{}
	virtual void End()		{}

	//xPos and yPos will be a Vec2
	virtual void DrawSprite( Texture *pTexture, Vec2 &pos ) {}
	virtual void DrawSprite( Texture *pTexture, Vec2 &pos, Vec2 &dimensions ) {}

	virtual void DrawSprite( Texture *texture, float xPos, float yPos ) {}
	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width, float height ) {}

	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size ) {}
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size, int direction ) {}

	void		 DrawLine( Vec2 startingPoint, Vec2 endingPoint, const Mat3 &transform );
	
	virtual void Load() {}
	
	//Used to change the tint on rendered textures

	//Used to set UV coordinates of a texture
	virtual void SetUVCoordinates(Vec2 &topLeft, Vec2 &topRight, Vec2 &bottomRight, Vec2& bottomLeft );
	virtual void SetUVCoordinates(Vec2 &topLeft, Vec2 &bottomRight);
	
	virtual void SetColour( unsigned int colour );

	//Values between 0 and 255
	//Is recommended to change colours in StaticSprite instead
	virtual void SetColour( float r, float g, float b, float a );
		

protected:
	Mat3 m_camera;

	float m_fRed, m_fGreen, m_fBlue, m_fAlpha;

	Vec2 m_topLeftUV, m_topRightUV, m_bottomLeftUV, m_bottomRightUV;

	SpriteBatch(Game *pGame);

	virtual ~SpriteBatch() {}

	Game *m_pGame;



private:

	


};
#endif