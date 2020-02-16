// RenderSystem.h

#ifndef RENDERSYSTEM_H_INCLUDED
#define RENDERSYSTEM_H_INCLUDED

#include "RenderSystemPrereq.h"

class RenderWindow;
class Camera;
class Mesh;
class Texture;
class RenderNode;

class RenderSystem {
public:
	RenderSystem();
	~RenderSystem();

	bool Init(RenderWindow *pRenderWindow);
	void Exit();

	void PreRender();
	void Render(RenderNode *node);
	void Render(OrthoNode *node);
	void PostRender();

	void SetSkybox(RenderNode *skybox);

	Camera *GetCamera();

	Mesh *CreateMesh();
	Texture *CreateTexture();

private:
	void create_resources();
	void create_ortho();
	void render_ortho();
	void create_skybox();
	void render_skybox();

private:
	HWND mWnd;
	ID3D10Device *mpDevice;
	IDXGISwapChain *mpSwapChain;
	ID3D10RenderTargetView *mpRenderTargetView;
	ID3D10DepthStencilView *mpDepthStencilView;
	ID3D10Texture2D *mpDepthStencilBuffer;

	Camera *mpCamera;

	ID3D10Effect *mpGlobalEffect;
	ID3D10EffectTechnique *mpGlobalTechnique;
	ID3D10EffectTechnique *mpOrthoTechnique;
	ID3D10EffectVariable *mpDeltaTimeVariable;
	ID3D10EffectMatrixVariable *mpViewProjMatrixVariable;
	ID3D10EffectMatrixVariable *mpWorldMatrixVariable;
	ID3D10EffectShaderResourceVariable *mpDiffuseTextureVariable;
	ID3D10EffectVectorVariable *mpLightDirectionVariable;
	ID3D10EffectVectorVariable *mpLightColorVariable;

	ID3D10InputLayout *mpInputLayout;
	ID3D10InputLayout *mpOrthoInputLayout;

	ID3D10EffectTechnique *mpSkyboxTechnique;
	ID3D10InputLayout *mpSkyboxInputLayout;
	RenderNode *mpSkyboxRenderNode;

	u32 mOrthoVertexCount;
	ID3D10Buffer *mpOrthoVertexBuffer;
	Matrix4 mOrthoProj;
	std::vector<OrthoNode*> mOrthoNodes;

	RenderWindow *mpRenderWindow;
};

#endif // RENDERSYSTEM_H_INCLUDED
