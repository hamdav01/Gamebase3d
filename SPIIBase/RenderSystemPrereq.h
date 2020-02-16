// RenderSystemPrereq.h

#ifndef RENDERSYSTEMPREREQ_H_INCLUDED
#define RENDERSYSTEMPREREQ_H_INCLUDED

struct vertex_s {
	Vector3 position;
	u32 color;
	Vector3 normal;
	Vector2 texcoord;
};
struct skybox_s {
	Vector3 position;
	Vector2 texcoord;
};

struct ortho_s {
	Vector2 position;
	Vector2 texcoord;
};

class OrthoNode {
public:
	class Texture *mpTexture;
	Vector4 mPosition;
	Vector4 mTexCoords;
};

#endif // RENDERSYSTEMPREREQ_H_INCLUDED
