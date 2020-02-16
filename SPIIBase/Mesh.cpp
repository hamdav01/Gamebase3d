// Mesh.cpp

#include "stdafx.h"
#include "Mesh.h"

#define SAFE_RELEASE(x) if(x!=NULL) {x->Release(); x=NULL;}

Mesh::Mesh(ID3D10Device *device) 
: mpDevice(device)
{
	mStride=0;
	mOffset=0;
	mIndexCount=0;
	mpVertexBuffer=NULL;
	mpIndexBuffer=NULL;
};

Mesh::~Mesh() {
	Release();
};

bool Mesh::Init(s32 vertex_size,s32 vertex_count,void *vertices,s32 index_count,u16 *indices,bool calculate_volume) {
	D3D10_BUFFER_DESC buffer_desc;
	buffer_desc.BindFlags=D3D10_BIND_VERTEX_BUFFER;
	buffer_desc.ByteWidth=vertex_size*vertex_count;
	buffer_desc.CPUAccessFlags=0;
	buffer_desc.MiscFlags=0;
	buffer_desc.Usage=D3D10_USAGE_DEFAULT;

	D3D10_SUBRESOURCE_DATA sub_data;
	sub_data.pSysMem=vertices;
	sub_data.SysMemPitch=0;
	sub_data.SysMemSlicePitch=0;

	HRESULT hr=mpDevice->CreateBuffer(&buffer_desc,&sub_data,&mpVertexBuffer);
	if(hr!=S_OK) {
		MessageBox(NULL,"ERROR: (Mesh::Init) Could not create vertexbuffer","ERROR!",MB_OK|MB_ICONERROR);
		return false;
	};
	
	buffer_desc.BindFlags=D3D10_BIND_INDEX_BUFFER;
	buffer_desc.ByteWidth=sizeof(u16)*index_count;

	sub_data.pSysMem=indices;

	hr=mpDevice->CreateBuffer(&buffer_desc,&sub_data,&mpIndexBuffer);
	if(hr!=S_OK) {
		MessageBox(NULL,"ERROR: (Mesh::Init) Could not create indexbuffer","ERROR!",MB_OK|MB_ICONERROR);
		return false;
	};

	if(calculate_volume) {
		s32 stride=vertex_size;
		s32 size=vertex_size*vertex_count;
		u8 *data=static_cast<u8*>(vertices);
		Vector3 vmin(9999,9999,9999),vmax(-9999,-9999,-9999),vpos;
		for(s32 i=0;i<size;i+=stride) {
			::memcpy(&vpos,data+i,sizeof(Vector3));

			if(vmin.x>vpos.x) vmin.x=vpos.x;
			if(vmin.y>vpos.y) vmin.y=vpos.y;
			if(vmin.z>vpos.z) vmin.z=vpos.z;

			if(vmax.x<vpos.x) vmax.x=vpos.x;
			if(vmax.y<vpos.y) vmax.y=vpos.y;
			if(vmax.z<vpos.z) vmax.z=vpos.z;
		};

		mLocalCenter=(vmax+vmin)*0.5f;
		mLocalRadius=(D3DXVec3Length(&vmax)+D3DXVec3Length(&vmin))*0.5f;
	};

	mIndexCount=index_count;
	mStride=vertex_size;
	mOffset=0;

	return true;
};

void Mesh::Release() {
	SAFE_RELEASE(mpVertexBuffer);
	SAFE_RELEASE(mpIndexBuffer);
	mIndexCount=0;
	mStride=0;
	mOffset=0;
};

f32 Mesh::GetRadius() const {
	return mLocalRadius;
};

const Vector3 &Mesh::GetCenter() const {
	return mLocalCenter;
};
