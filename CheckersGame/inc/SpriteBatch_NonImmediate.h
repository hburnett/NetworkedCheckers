/*---------------------------------------------------------
	Author: Heath Burnett
	Description: Draws images to the screen using VBO's
---------------------------------------------------------*/

#ifndef   SPRITEBATCH_NONIMMEDIATE
#define	  SPRITEBATCH_NONIMMEDIATE

#include "glfw3.h"
#include "SpriteBatch.h"

class Vec2;

class Mat3;

class Texture;

struct TexturedVertex
{
	TexturedVertex(float x, float y, float r, float g, float b, float a, float u, float v)
	{
		vPosition[0] = x;
		vPosition[1] = y;
		vPosition[2] = 0;
		vPosition[3] = 1;

		vColour[0] = r;
		vColour[1] = g;
		vColour[2] = b;
		vColour[3] = a;

		vUV[0] = u;
		vUV[1] = v;
	}

	float vPosition[4];	
	float vColour[4];	
	float vUV[2];
};


class SpriteBatch_NonImmediate : public SpriteBatch
{
public:

	SpriteBatch_NonImmediate( Game *pGame );

	~SpriteBatch_NonImmediate();

	virtual void Load();

	void Begin(const Mat3 &camera);

	virtual void DrawSprite( Texture *texture, const Mat3 &transform, const Vec2 &size );
	
private:

	// builds a 4x4 orthographic projection matrix
	// usage:	float orthoMat[16];
	//			BuildOrthoProjectionMatrix( orthoMat, 0, windowWidth, 0, windowHeight, 0, 1);
	void BuildOrthoProjectionMatrix( float *pMat4x4, float left, float right, float bottom, float top, float near, float far) const;
	
	// builds is an OpenGL Shader Program...
	// a_vertex and a_frag refer to filenames for our vertex and fragment shader source files.
	GLuint CreateProgram(const char *a_vertex, const char *a_frag) const;

	// Create shader used only within the Create Program function
	GLuint CreateShader(GLenum a_eShaderType, const char *a_strShaderFile) const;

	

	void Unload();

private:

	GLuint m_texture;

	GLuint m_shader;

	GLuint m_vao;

	GLuint m_vbo;

	GLuint m_ibo;

};

#endif
