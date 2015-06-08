#include "Texture.h"
#include "glfw3.h"
#include "lodepng.h"
#include <vector>

Texture::Texture(const char *filename)
{
	m_textureID = LoadTexture(filename, &m_width, &m_height);
}

Texture::~Texture()
{
	unsigned int textureID = 0;
	textureID = GetTextureHandle();	
	glDeleteTextures( 1, &textureID );
}


// Load PNG images only
// Returns an OpenGL texture ID
// out_width and out_height are pointers, the function will return the textures width and height
// through these paramaters if not NULL
unsigned int Texture::LoadTexture(const char *filename, unsigned int *out_width, unsigned int *out_height)
{	
	unsigned int width	= 0;
	unsigned int height = 0;
	std::vector< unsigned char > pixels;

	// populates "pixels" vector with pixel data formated as RGBA
	// width and height are passed in as reference. If the function succeeds, 
	// with and height should be populated with the loaded textures widht and height in pixels
	lodepng::decode( pixels, width, height, filename );

	if( out_width	!= NULL )	*out_width	= width;
	if( out_height	!= NULL )	*out_height = height;

	// create an openGL texture
	//-------------------------------------------------------------------------

		unsigned int textureID = 0;
		glGenTextures(1, &textureID); // genorate the texture and store the unique id in textureID

		glBindTexture(GL_TEXTURE_2D, textureID); // make the genorated texture the current texture

		// send the pixel data to the current texture
		// NOTE: we need to tell openGL what the current format of the pixels is in RAM,
		//       we then need to tell it what format we want the pixels to be formatted in within video memory (openGL will do the conversion)
		//		 we also need to tell it the size of each color channel, which is GL_UNSIGNED_BYTE (one byte each for Red, Green, Blue and Alpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glBindTexture(GL_TEXTURE_2D, 0);

	//-------------------------------------------------------------------------

	// return the genorated texture ID
	return textureID;
}
