// Texture.cpp

#include "stdafx.h"
#include "Texture.h"

Texture::Texture(ID3D10Device *device) : mpDevice(device) {
	mpShaderResourceView=NULL;
	mpTexture=NULL;
};

Texture::~Texture() {
	Release();
};

bool Texture::Create(const char *filename) {
	ID3D10Resource *pResource=NULL;

	HRESULT hr=D3DX10CreateTextureFromFile(
		mpDevice,
		filename,
		NULL,NULL,
		&pResource,
		NULL);
	if(hr!=S_OK) {
		MessageBox(NULL,"ERROR: Could not load texture","ERROR!",MB_OK|MB_ICONERROR);
		return false;
	};

	D3D10_RESOURCE_DIMENSION type;
	static_cast<ID3D10Texture2D*>(pResource)->GetType(&type);
	if(type!=D3D10_RESOURCE_DIMENSION_TEXTURE2D) {
		pResource->Release();
		MessageBox(NULL,"ERROR: Resource not a texture","ERROR!",MB_OK|MB_ICONERROR);
		return false;
	};

	D3D10_TEXTURE2D_DESC desc;
	static_cast<ID3D10Texture2D*>(pResource)->GetDesc(&desc);

	D3D10_SHADER_RESOURCE_VIEW_DESC descSRV;
	descSRV.Format=desc.Format;
	descSRV.ViewDimension=D3D10_SRV_DIMENSION_TEXTURE2D;
	descSRV.Texture2D.MipLevels=desc.MipLevels;
	descSRV.Texture2D.MostDetailedMip=0;

	hr=mpDevice->CreateShaderResourceView(pResource,&descSRV,&mpShaderResourceView);
	if(hr!=S_OK) {
		pResource->Release();
		MessageBox(NULL,"ERROR: Could not create shader resource view","ERROR!",
			MB_OK|MB_ICONERROR);
		return false;
	};

	mpTexture=static_cast<ID3D10Texture2D*>(pResource);

	return true;
};

void Texture::Release() {
	if(mpTexture!=NULL) {
		mpTexture->Release();
		mpTexture=NULL;
	};
	if(mpShaderResourceView!=NULL) {
		mpShaderResourceView->Release();
		mpShaderResourceView=NULL;
	};
};
