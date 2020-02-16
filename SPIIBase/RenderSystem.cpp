// RenderSystem.cpp

#include "stdafx.h"
#include "SystemUtils.h"
#include "RenderWindow.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshUtils.h"
#include "Texture.h"
#include "RenderNode.h"
#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
	mWnd=NULL;
	mpDevice=NULL;
	mpSwapChain=NULL;
	mpRenderTargetView=NULL;
	mpDepthStencilView=NULL;
	mpDepthStencilBuffer=NULL;

	mpGlobalEffect=NULL;
	mpGlobalTechnique=NULL;

	mpDeltaTimeVariable=NULL;
	mpViewProjMatrixVariable=NULL;
	mpWorldMatrixVariable=NULL;

	mpRenderWindow=NULL;

	mpCamera=NULL;
	mpInputLayout=NULL;

	mpSkyboxTechnique =NULL;
};

RenderSystem::~RenderSystem()
{
};

bool RenderSystem::Init(RenderWindow *pRenderWindow)
{
	// default parameters from parent window
	mpRenderWindow=pRenderWindow;
	WindowParams params=pRenderWindow->GetParams();
	mWnd=(HWND)pRenderWindow->GetHandle();

	// set up a swapchain for rendering
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	::memset(&swapChainDesc,0,sizeof(swapChainDesc));
	swapChainDesc.OutputWindow=mWnd;
	swapChainDesc.BufferCount=1;
	swapChainDesc.BufferDesc.Width=params.mWidth;
	swapChainDesc.BufferDesc.Height=params.mHeight;
	swapChainDesc.BufferDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.RefreshRate.Numerator=60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator=1;
	swapChainDesc.SampleDesc.Count=1;
	swapChainDesc.SampleDesc.Quality=0;
	swapChainDesc.Windowed=params.mFullscreen?FALSE:TRUE;

	// create the device and swapchain
	if(S_OK!=D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D10_CREATE_DEVICE_DEBUG,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&mpSwapChain,
		&mpDevice))
	{
		return false;
	};

	// grab the backbuffer and create a rendertargetview
	ID3D10Texture2D *pBackBuffer=NULL;
	if(mpSwapChain->GetBuffer(0,__uuidof(ID3D10Texture2D),(void**)&pBackBuffer)!=S_OK)
	{
		return false;
	};
	if(mpDevice->CreateRenderTargetView(pBackBuffer,NULL,&mpRenderTargetView)!=S_OK)
	{
		return false;
	};
	pBackBuffer->Release();

	// create and set depth buffer for proper depth
	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width=mpRenderWindow->GetParams().mWidth;
	descDepth.Height=mpRenderWindow->GetParams().mHeight;
	descDepth.MipLevels=1;
	descDepth.ArraySize=1;
	descDepth.Format=DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count=1;
	descDepth.SampleDesc.Quality=0;
	descDepth.Usage=D3D10_USAGE_DEFAULT;
	descDepth.BindFlags=D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags=0;
	descDepth.MiscFlags=0;

	mpDepthStencilBuffer=NULL;
	if(mpDevice->CreateTexture2D(&descDepth,NULL,&mpDepthStencilBuffer)!=S_OK)
	{
		return false;
	};

	D3D10_DEPTH_STENCIL_VIEW_DESC descDepthStencilView;
	::memset(&descDepthStencilView,0,sizeof(D3D10_DEPTH_STENCIL_VIEW_DESC));
	descDepthStencilView.Format=descDepth.Format;
	descDepthStencilView.ViewDimension=D3D10_DSV_DIMENSION_TEXTURE2D;
	descDepthStencilView.Texture2D.MipSlice=0;

	if(mpDevice->CreateDepthStencilView(mpDepthStencilBuffer,&descDepthStencilView,&mpDepthStencilView)!=S_OK)
	{
		return false;
	};

	// set rendertarget and viewport settings
	D3D10_VIEWPORT viewport={0,0,params.mWidth,params.mHeight,0.0f,1.0f};
	mpDevice->RSSetViewports(1,&viewport);

	// set both rendertargets
	mpDevice->OMSetRenderTargets(1,&mpRenderTargetView,mpDepthStencilView);

	// set the primitive rendering mode
	mpDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// load default shader
	ID3D10Blob *pBlob=NULL;
	dword shaderFlags=D3D10_SHADER_ENABLE_STRICTNESS;
	HRESULT hr=D3DX10CreateEffectFromFile(
		"..\\data\\sh\\basic.fx",
		NULL,NULL,
		"fx_4_0",
		shaderFlags,
		0,
		mpDevice,
		NULL,NULL,
		&mpGlobalEffect,
		&pBlob,NULL);
	if(hr!=S_OK)
	{
		MessageBox(mWnd,(char*)pBlob->GetBufferPointer(),"ERROR!",MB_OK|MB_ICONERROR);
		pBlob->Release();
		return false;
	};

	// get the default render technique "Basic"
	mpGlobalTechnique=mpGlobalEffect->GetTechniqueByName("Basic");
	mpOrthoTechnique=mpGlobalEffect->GetTechniqueByName("BasicOrtho");
	mpSkyboxTechnique=mpGlobalEffect->GetTechniqueByName("Skybox");

	// get default shader parameters for deltatime, world transform and view projection matrices
	mpViewProjMatrixVariable=mpGlobalEffect->GetVariableByName("g_ViewProj")->AsMatrix();
	mpWorldMatrixVariable=mpGlobalEffect->GetVariableByName("g_World")->AsMatrix();

	mpLightDirectionVariable=mpGlobalEffect->GetVariableByName("g_LightDirection")->AsVector();
	mpLightColorVariable=mpGlobalEffect->GetVariableByName("g_LightColor")->AsVector();

	mpDiffuseTextureVariable
		=mpGlobalEffect->GetVariableByName("g_DiffuseTexture")->AsShaderResource();

	create_resources();

	return true;
};

void RenderSystem::Exit() {
	SAFE_RELEASE(mpSkyboxInputLayout);
	if(mpCamera!=NULL) {
		delete mpCamera;
		mpCamera=NULL;
	};

	if(mpInputLayout!=NULL) {
		mpInputLayout->Release();
		mpInputLayout=NULL;
	};

	SAFE_RELEASE(mpOrthoInputLayout);

	// general systems cleanup
	if(mpGlobalEffect!=NULL)
	{
		mpGlobalEffect->Release();
		mpGlobalEffect=NULL;
	};
	if(mpDepthStencilBuffer!=NULL)
	{
		mpDepthStencilBuffer->Release();
		mpDepthStencilBuffer=NULL;
	};
	if(mpDepthStencilView!=NULL)
	{
		mpDepthStencilView->Release();
		mpDepthStencilView=NULL;
	};
	if(mpRenderTargetView!=NULL)
	{
		mpRenderTargetView->Release();
		mpRenderTargetView=NULL;
	};
	if(mpSwapChain!=NULL)
	{
		mpSwapChain->Release();
		mpSwapChain=NULL;
	};
	if(mpDevice!=NULL)
	{
		mpDevice->Release();
		mpDevice=NULL;
	};
};

f32 rot=0.0f;

void RenderSystem::PreRender() {
	mpCamera->Update();

	// clear the screen
	mpDevice->ClearRenderTargetView(mpRenderTargetView,Vector4(0.15f,0.175f,0.2f,1.0f));

	// clear the backbuffer
	mpDevice->ClearDepthStencilView(mpDepthStencilView,D3D10_CLEAR_DEPTH,1.0f,0);
	if(mpSkyboxRenderNode != NULL) {
		render_skybox();
	}
	mpDevice->IASetInputLayout(mpInputLayout);

	mpViewProjMatrixVariable->SetMatrix(mpCamera->mTransform);

	rot+=0.01f;

	Vector3 light_direction(0,-1,1);
	D3DXVec3Normalize(&light_direction,&light_direction);
	mpLightDirectionVariable->SetFloatVector(light_direction);

	Vector4 light_color(1,1,1,1);
	mpLightColorVariable->SetFloatVector(light_color);
};

void RenderSystem::Render(RenderNode *node) {
	mpWorldMatrixVariable->SetMatrix(node->mWorld);
	mpDevice->IASetVertexBuffers(0,1,&node->mpMesh->mpVertexBuffer,&node->mpMesh->mStride,&node->mpMesh->mOffset);
	mpDevice->IASetIndexBuffer(node->mpMesh->mpIndexBuffer,DXGI_FORMAT_R16_UINT,0);

	mpDiffuseTextureVariable->SetResource(node->mpTexture->mpShaderResourceView);

	D3D10_TECHNIQUE_DESC desc;
	mpGlobalTechnique->GetDesc(&desc);
	for(u32 i=0;i<desc.Passes;i++) {
		mpGlobalTechnique->GetPassByIndex(i)->Apply(0);
		mpDevice->DrawIndexed(node->mpMesh->mIndexCount,0,0);
	};
};

void RenderSystem::Render(OrthoNode *node) {
	mOrthoNodes.push_back(node);
};

void RenderSystem::PostRender() {
	render_ortho();

	// show backbuffer
	mpSwapChain->Present(0,0);
};

Camera *RenderSystem::GetCamera() {
	return mpCamera;
};
void RenderSystem::SetSkybox(RenderNode *skybox) {
	mpSkyboxRenderNode = skybox;
}
Mesh *RenderSystem::CreateMesh() {
	return new Mesh(mpDevice);
};

Texture *RenderSystem::CreateTexture() {
	return new Texture(mpDevice);
};


// private
void RenderSystem::create_resources() {
	D3D10_INPUT_ELEMENT_DESC input_desc[]={
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,12,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,16,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,28,D3D10_INPUT_PER_VERTEX_DATA,0}
	};

	D3D10_PASS_DESC pass_desc;
	mpGlobalTechnique->GetPassByIndex(0)->GetDesc(&pass_desc);
	HRESULT hr=mpDevice->CreateInputLayout(input_desc,
		sizeof(input_desc)/sizeof(input_desc[0]),
		pass_desc.pIAInputSignature,
		pass_desc.IAInputSignatureSize,
		&mpInputLayout);

	if(hr!=S_OK) {
		return;
	};

	mpDevice->IASetInputLayout(mpInputLayout);

	mpCamera=new Camera;
	mpCamera->DoView(Vector3(0,0,0),Vector3(0,0,0),Vector3(0,1,0));
	mpCamera->DoProj(
		(f32)mpRenderWindow->GetParams().mWidth/(f32)mpRenderWindow->GetParams().mHeight,
		Math::ToRad(45.0f),
		0.1f,300.0f);

	create_ortho();
	create_skybox();
};

void RenderSystem::create_ortho() {
	D3D10_INPUT_ELEMENT_DESC input_desc[]={
		{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,8,D3D10_INPUT_PER_VERTEX_DATA,0}
	};

	D3D10_PASS_DESC pass_desc;
	mpOrthoTechnique->GetPassByIndex(0)->GetDesc(&pass_desc);
	HRESULT hr=mpDevice->CreateInputLayout(input_desc,
		sizeof(input_desc)/sizeof(input_desc[0]),
		pass_desc.pIAInputSignature,
		pass_desc.IAInputSignatureSize,
		&mpOrthoInputLayout);

	if(hr!=S_OK) {
		MessageBox(NULL,"RenderSystem::create_ortho: Could not create input layout","ERROR!",MB_OK|MB_ICONERROR);
		return;
	};

	D3D10_BUFFER_DESC buffer_desc;
	buffer_desc.BindFlags=D3D10_BIND_VERTEX_BUFFER;
	buffer_desc.ByteWidth=sizeof(ortho_s)*1024*6;
	buffer_desc.CPUAccessFlags=D3D10_CPU_ACCESS_WRITE;
	buffer_desc.MiscFlags=0;
	buffer_desc.Usage=D3D10_USAGE_DYNAMIC;

	hr=mpDevice->CreateBuffer(&buffer_desc,NULL,&mpOrthoVertexBuffer);
	if(hr!=S_OK) {
		MessageBox(NULL,"RenderSystem::create_ortho: Could not create vertexbuffer","ERROR!",MB_OK|MB_ICONERROR);
		return;
	};

	mOrthoNodes.reserve(1024);

	f32 width=(f32)mpRenderWindow->GetParams().mWidth;
	f32 height=(f32)mpRenderWindow->GetParams().mHeight;
	D3DXMatrixOrthoOffCenterLH(&mOrthoProj,0.0f,width,height,0.0f,0.0f,1.0f);
};

void RenderSystem::render_ortho() {
	// prepare vertexbuffer
	u32 count=mOrthoNodes.size();
	if(count==0) {return;};

	u32 index=0;
	ortho_s *data=NULL;
	mpOrthoVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD,0,(void**)&data);
	for(u32 i=0;i<count;i++) {
		f32 x=mOrthoNodes[i]->mPosition.x;
		f32 y=mOrthoNodes[i]->mPosition.y;
		f32 w=mOrthoNodes[i]->mPosition.z;
		f32 h=mOrthoNodes[i]->mPosition.w;

		f32 ux=mOrthoNodes[i]->mTexCoords.x;
		f32 uy=mOrthoNodes[i]->mTexCoords.y;
		f32 vx=mOrthoNodes[i]->mTexCoords.z;
		f32 vy=mOrthoNodes[i]->mTexCoords.w;

		data[index].position.x=x;
		data[index].position.y=y;
		data[index].texcoord.x=ux;
		data[index].texcoord.y=uy;
		index++;

		data[index].position.x=x+w;
		data[index].position.y=y;
		data[index].texcoord.x=vx;
		data[index].texcoord.y=uy;
		index++;

		data[index].position.x=x+w;
		data[index].position.y=y+h;
		data[index].texcoord.x=vx;
		data[index].texcoord.y=vy;
		index++;

		data[index].position.x=x+w;
		data[index].position.y=y+h;
		data[index].texcoord.x=vx;
		data[index].texcoord.y=vy;
		index++;

		data[index].position.x=x;
		data[index].position.y=y+h;
		data[index].texcoord.x=ux;
		data[index].texcoord.y=vy;
		index++;

		data[index].position.x=x;
		data[index].position.y=y;
		data[index].texcoord.x=ux;
		data[index].texcoord.y=uy;
		index++;
	};
	mpOrthoVertexBuffer->Unmap();

	mOrthoVertexCount=index;

	Matrix4 identity;
	D3DXMatrixIdentity(&identity);
	mpWorldMatrixVariable->SetMatrix(identity);
	mpViewProjMatrixVariable->SetMatrix(mOrthoProj);

	const u32 stride=sizeof(ortho_s);
	u32 offset=0;
	mpDevice->IASetVertexBuffers(0,1,&mpOrthoVertexBuffer,&stride,&offset);
	mpDevice->IASetInputLayout(mpOrthoInputLayout);

	for(u32 i=0;i<count;i++) {
		mpDiffuseTextureVariable->SetResource(mOrthoNodes[i]->mpTexture->mpShaderResourceView);
		mpOrthoTechnique->GetPassByIndex(0)->Apply(0);
		mpDevice->Draw(6,i*6);
	};

	mOrthoNodes.clear();
};

void RenderSystem::create_skybox() {
	D3D10_INPUT_ELEMENT_DESC input_desc[]={
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D10_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D10_INPUT_PER_VERTEX_DATA,0}
	};

	D3D10_PASS_DESC pass_desc;
	mpSkyboxTechnique->GetPassByIndex(0)->GetDesc(&pass_desc);
	HRESULT hr=mpDevice->CreateInputLayout(input_desc,
		sizeof(input_desc)/sizeof(input_desc[0]),
		pass_desc.pIAInputSignature,
		pass_desc.IAInputSignatureSize,
		&mpSkyboxInputLayout);

	if(hr!=S_OK) {
		MessageBox(NULL,"RenderSystem::create_skybox: Could not create input layout","ERROR!",MB_OK|MB_ICONERROR);
		return;
	};
};
void RenderSystem::render_skybox() {
	Matrix4 world;
	D3DXMatrixIdentity(&world);
	mpWorldMatrixVariable->SetMatrix(world);

	Matrix4 view=mpCamera->mView;
	Matrix4 proj=mpCamera->mProj;

	view._41=0.0f; view._42=0.0f; view._43=0.0f;

	Matrix4 transform=view*proj;
	mpViewProjMatrixVariable->SetMatrix(transform);

	mpDevice->IASetInputLayout(mpSkyboxInputLayout);
	mpDevice->IASetVertexBuffers(0,1,
		&mpSkyboxRenderNode->mpMesh->mpVertexBuffer,
		&mpSkyboxRenderNode->mpMesh->mStride,
		&mpSkyboxRenderNode->mpMesh->mOffset);
	mpDevice->IASetIndexBuffer(mpSkyboxRenderNode->mpMesh->mpIndexBuffer,
		DXGI_FORMAT_R16_UINT,0);
	mpDiffuseTextureVariable->SetResource(mpSkyboxRenderNode->mpTexture->mpShaderResourceView);

	mpSkyboxTechnique->GetPassByIndex(0)->Apply(0);
	mpDevice->DrawIndexed(mpSkyboxRenderNode->mpMesh->mIndexCount,0,0);
};
