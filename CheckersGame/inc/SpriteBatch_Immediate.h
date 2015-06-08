//Author: Heath Burnett
//Description: Immediate class

#ifndef	 SPRITEBATCH_IMMEDIATE_H
#define	 SPRITEBATCH_IMMEDIATE_H

#include "SpriteBatch.h"

class Vec2;

class Mat3;

class SpriteBatch_Immediate : public SpriteBatch
{
public:

	SpriteBatch_Immediate(Game *pGame);
	
	virtual void Begin();
	virtual void Begin(const Mat3 &camera);
	virtual void End();

	//xPos and yPos will be a Vec2
	virtual void DrawSprite( Texture *pTexture, Vec2 &pos );
	virtual void DrawSprite( Texture *pTexture, Vec2 &pos, Vec2 &dimensions );

	virtual void DrawSprite( Texture *texture, float xPos, float yPos );
	virtual void DrawSprite( Texture *texture, float xPos, float yPos, float width, float height );

	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size );
	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size, int direction );

protected:

	



private:




};
#endif