//Author: Heath Burnett
//Description: Texture stuff

#ifndef	  TEXTURE_H
#define   TEXTURE_H

class Texture
{
public:

	Texture(const char *filename);
	
	~Texture();
	
	unsigned int GetWidth()			{ return m_width;		}

	unsigned int GetHeight()		{ return m_height;		}

	unsigned int GetTextureHandle() { return m_textureID;	}


protected:



private:

	unsigned int m_width;
	unsigned int m_height;

	unsigned int m_textureID;

	// Load PNG images only
	// Returns an OpenGL texture ID
	// out_width and out_height are pointers, the function will return the textures width and height
	// through these paramaters if not NULL
	unsigned int LoadTexture(const char *filename, unsigned int *out_width = nullptr, unsigned int *out_height = nullptr);

	// unloads the texture from graphics memory
	// expects a valid openGL texture ID, as returned from the LoadTexture function
	

};
#endif