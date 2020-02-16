// Texture.h

#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

class Texture {
	friend class RenderSystem;
public:
	Texture(ID3D10Device *device);
	~Texture();

	bool Create(const char *filename);
	void Release();

private:
	ID3D10ShaderResourceView *mpShaderResourceView;
	ID3D10Texture2D *mpTexture;
	ID3D10Device *mpDevice;
};

#endif // TEXTURE_H_INCLUDED
