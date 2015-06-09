#include "Game.h"
#include "SpriteBatch_NonImmediate.h"
#include "glfw3.h"
#include "Texture.h"
#include "Vec2.h"
#include "Mat3.h"
#include <string>
#include <fstream>
#include <vector>

SpriteBatch_NonImmediate::SpriteBatch_NonImmediate( Game * pGame ) : SpriteBatch( pGame )
{
	Load();
}

SpriteBatch_NonImmediate::~SpriteBatch_NonImmediate()
{
	Unload();
}

void SpriteBatch_NonImmediate::Begin(const Mat3 &camera)
{
	m_camera = camera;
}


void SpriteBatch_NonImmediate::Load()
{
	if(m_shader != 3)
		m_shader	= CreateProgram("./shaders/TexturedVertexShader.glsl", "./shaders/TexturedFragmentShader.glsl");
	
	//Generate buffers for openGL to store data on the graphics card
	glGenVertexArrays( 1, &m_vao );
	glGenBuffers( 1, &m_vbo );
	glGenBuffers( 1, &m_ibo );

	//Binds buffers to appropriate type
	//Array buffer stores vertices
	//Element buffer stores indices
	glBindVertexArray( m_vao );
	glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );

	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );

	//ColorVertex is the structure containing Vertex data
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, sizeof( TexturedVertex ), (void *) 0 );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( TexturedVertex ), (void *) 16);
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( TexturedVertex ), (void *) 32);

	glBindVertexArray( 0 );
}

void SpriteBatch_NonImmediate::Unload()
{
	glDeleteProgram( m_shader );

	glDeleteBuffers(1, &m_vbo );
	glDeleteBuffers(1, &m_ibo );
	glDeleteVertexArrays(1, &m_vao );
}

void SpriteBatch_NonImmediate::DrawSprite( Texture *pTexture, const Mat3 &transform, const Vec2 &size )
{
	m_texture	= pTexture->GetTextureHandle();

	Vec2 m_topLeftVertex;
		 m_topLeftVertex.x		= -0.5f	* size.x;
		 m_topLeftVertex.y		=  0.5f	* size.y;

	Vec2 m_topRightVertex;
		 m_topRightVertex.x		= 0.5f * size.x;
		 m_topRightVertex.y		= 0.5f * size.y;

	Vec2 m_bottomRightVertex;
		 m_bottomRightVertex.x	= 0.5f	* size.x;
		 m_bottomRightVertex.y	= -0.5f	* size.y;

	Vec2 m_bottomLeftVertex;
		 m_bottomLeftVertex.x	= -0.5f * size.x;
		 m_bottomLeftVertex.y	= -0.5f * size.y;

	m_topLeftVertex				= m_camera * (m_topLeftVertex		* transform); 
	m_topRightVertex			= m_camera * (m_topRightVertex		* transform); 
	m_bottomRightVertex			= m_camera * (m_bottomRightVertex	* transform);
	m_bottomLeftVertex			= m_camera * (m_bottomLeftVertex	* transform); 


	TexturedVertex verts[4] =
	{
		//						x,						y,				  r,		g,		 b,		  a,			u,				 v
		TexturedVertex(	m_bottomLeftVertex.x,	m_bottomLeftVertex.y,	m_fRed, m_fGreen, m_fBlue, m_fAlpha, m_bottomLeftUV.x,	m_bottomLeftUV.y	), //vert 0 - top left
		TexturedVertex(	m_bottomRightVertex.x,	m_bottomRightVertex.y,	m_fRed, m_fGreen, m_fBlue, m_fAlpha, m_bottomRightUV.x,	m_bottomRightUV.y	), //vert 1 - top right
		TexturedVertex(	m_topRightVertex.x,		m_topRightVertex.y,		m_fRed, m_fGreen, m_fBlue, m_fAlpha, m_topRightUV.x,	m_topRightUV.y		), //vert 2 - bottom right
		TexturedVertex(	m_topLeftVertex.x,		m_topLeftVertex.y,		m_fRed, m_fGreen, m_fBlue, m_fAlpha, m_topLeftUV.x,		m_topLeftUV.y		), //vert 3 - bottom left
	};

	GLubyte indices[6] =
	{
		0, 1, 2, //face 1
		0, 2, 3	 //face 2
	};

	float ortho[16];
	BuildOrthoProjectionMatrix( ortho, 0, m_pGame->GetWindowWidth(), 0, m_pGame->GetWindowHeight(), 0, 1 );

	glUseProgram( m_shader );

	//bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//diffuse texture
	GLuint diffuseTexture = glGetUniformLocation( m_shader, "diffuse");
	glUniform1i( diffuseTexture, 0 );

	//tell shader about ortho projection
	GLuint projectionLoc = glGetUniformLocation( m_shader, "projection" );
	glUniformMatrix4fv( projectionLoc, 1, false, ortho );

	//Move those to pointers ^^^

	//bind vertex array object
	//should contain vertex data
	glBindVertexArray( m_vao );

	glBufferData( GL_ARRAY_BUFFER,			sizeof( TexturedVertex ) * 4,	verts,	 GL_STATIC_DRAW );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER,	sizeof( GLubyte )		 * 6,	indices, GL_STATIC_DRAW );

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL );

	glBindVertexArray( 0 );
	glUseProgram( 0 );

}


void SpriteBatch_NonImmediate::BuildOrthoProjectionMatrix( float *pMat4x4, float left, float right, float bottom, float top, float nearF, float farF) const
{
	float w = right - left;
	float h = top - bottom;
	float d = farF - nearF;

	pMat4x4[0]	=  2.0f / w;
	pMat4x4[1]	=  0.0f;
	pMat4x4[2]	=  0.0f;
	pMat4x4[3]	=  0.0f;
	pMat4x4[4]	=  0.0f;
	pMat4x4[5]	=  2.0f / h;
	pMat4x4[6]	=  0.0f;
	pMat4x4[7]	=  0.0f;
	pMat4x4[8]	=  0.0f;
	pMat4x4[9]	=  0.0f;
	pMat4x4[10] =  2.0f / d;
	pMat4x4[11] =  0.0f;
	pMat4x4[12] = -1.0f * ( (right + left) / w );
	pMat4x4[13] = -1.0f * ( (top + bottom) / h );
	pMat4x4[14] = -1.0f * ( (farF + nearF)   / d );
	pMat4x4[15] =  1.0f;
}

GLuint SpriteBatch_NonImmediate::CreateShader(GLenum a_eShaderType, const char *a_strShaderFile) const
{
	std::string strShaderCode;

	//open shader file
	std::ifstream shaderStream(a_strShaderFile);

	//if that worked ok, load file line by line
	if(shaderStream.is_open())
	{
		std::string Line = "";
		while(std::getline(shaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();
	
	//create shader ID
	GLuint uiShader = glCreateShader(a_eShaderType);

	//attach the shader source to our generated shader ID
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);

	//compile shader - GL nust compile the shader source code.
	//as each graphics card is different, instructions may differ on the hardware GPU
	glCompileShader(uiShader);

	//check for compilation errors and output them
	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);

	//if there is an error, print the error to the console window
	if (iStatus == GL_FALSE)
	{

		// how long is the of the error
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		// create memory for the error message
		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(a_eShaderType)
		{
			case GL_VERTEX_SHADER:		strShaderType = "vertex"; break;
			case GL_FRAGMENT_SHADER:	strShaderType = "fragment"; break;
		}

		// print the error to the console window.
		printf("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		
		// remember the memory we created 13 lines above...
		delete[] strInfoLog;
	}

	// return the shader ID...
	return uiShader;
}

GLuint SpriteBatch_NonImmediate::CreateProgram(const char *a_vertex, const char *a_frag) const
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint uiProgram = glCreateProgram();

	//attach shaders
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);

	//link program
	glLinkProgram(uiProgram);

	//check for link errors and output them
	GLint status;
	glGetProgramiv (uiProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	// now that the program has been built, we can get rid of the individual shaders...
	for(auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	// return our compiled shader program.
	return uiProgram;
}
