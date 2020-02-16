// MeshUtils.cpp

#include "stdafx.h"
#include "RenderSystemPrereq.h"
#include "Mesh.h"
#include "ObjParser.h"
#include "MeshUtils.h"
#include <iostream>

#pragma pack(push,1)
struct bmpheader_s {
	u16 ident;
	u32 filesize;
	u32 reserverd0;
	u32 data_offset;
};

struct bmpinfo_s {
	u32 header_size;
	u32 width;
	u32 height;
	u16 planes;
	u16 bits_per_pixel;
	u32 compression;
	u32 data_size;
	u32 hresolution;
	u32 vresolution;
	u32 colors_in_image;
	u32 important_colors;
};
#pragma pack(pop)

namespace MeshUtils {

	bool CreateSkybox(Mesh *&mesh) {
		f32 xz=1.0f;
		f32 yy=1.0f;

		f32 fx0=0.0f;
		f32 fx1=252.0f/1024.0f;
		f32 fy0=252.0f/1024.0f;
		f32 fy1=771.0f/1024.0f;

		f32 bx0=772.0f/1024.0f;
		f32 bx1=1024.0f/1024.0f;
		f32 by0=252.0f/1024.0f;
		f32 by1=771.0f/1024.0f;

		f32 rx0=252.0f/1024.0f;
		f32 rx1=771.0f/1024.0f;
		f32 ry0=772.0f/1024.0f;
		f32 ry1=1024.0f/1024.0f;

		f32 lx0=252.0f/1024.0f;
		f32 lx1=771.0f/1024.0f;
		f32 ly0=0.0f;
		f32 ly1=251.0f/1024.0f;

		f32 tx0=252.0f/1024.0f;
		f32 tx1=771.0f/1024.0f;
		f32 ty0=252.0f/1024.0f;
		f32 ty1=771.0f/1024.0f;

		f32 bbx0=0.0f;
		f32 bby0=320.0f/1024.0f;

		skybox_s vertices[]={

			// front //
			{Vector3(-xz, xz,-xz),Vector2(fx1,fy0)},
			{Vector3( xz, xz,-xz),Vector2(fx1,fy1)},
			{Vector3(-xz,-yy,-xz),Vector2(fx0,fy0)},
			{Vector3( xz,-yy,-xz),Vector2(fx0,fy1)},

			// back //
			{Vector3( xz, xz, xz),Vector2(bx0,by1)},
			{Vector3(-xz, xz, xz),Vector2(bx0,by0)},
			{Vector3( xz,-yy, xz),Vector2(bx1,by1)},
			{Vector3(-xz,-yy, xz),Vector2(bx1,by0)},

			// right //
			{Vector3( xz, xz,-xz),Vector2(rx0,ry0)},
			{Vector3( xz, xz, xz),Vector2(rx1,ry0)},
			{Vector3( xz,-yy,-xz),Vector2(rx0,ry1)},
			{Vector3( xz,-yy, xz),Vector2(rx1,ry1)},

			// left //
			{Vector3(-xz, xz, xz),Vector2(lx1,ly1)},
			{Vector3(-xz, xz,-xz),Vector2(lx0,ly1)},
			{Vector3(-xz,-yy, xz),Vector2(lx1,ly0)},
			{Vector3(-xz,-yy,-xz),Vector2(lx0,ly0)},

			// top //
			{Vector3(-xz, xz, xz),Vector2(tx1,ty0)},
			{Vector3( xz, xz, xz),Vector2(tx1,ty1)},
			{Vector3(-xz, xz,-xz),Vector2(tx0,ty0)},
			{Vector3( xz, xz,-xz),Vector2(tx0,ty1)},

			// bottom //
			{Vector3(-xz,-yy,-xz),Vector2(bbx0,bby0)},
			{Vector3( xz,-yy,-xz),Vector2(bbx0,bby0)},
			{Vector3(-xz,-yy, xz),Vector2(bbx0,bby0)},
			{Vector3( xz,-yy, xz),Vector2(bbx0,bby0)}
		};

		u16 indices[]={
			0,2,1, 2,3,1,
			4,6,5, 6,7,5,
			8,10,9, 10,11,9,
			12,14,13, 14,15,13,
			16,18,17, 18,19,17,
			20,22,21, 22,23,21
		};

		bool success=true;
		if(!mesh->Init(sizeof(skybox_s),sizeof(vertices)/sizeof(vertices[0]),vertices,
			sizeof(indices)/sizeof(indices[0]),indices,false))
		{
			success=false;
		};
		return success;
	};
	bool CreateHeightmapFromBmp(const char *filename,Mesh *&mesh) {
		FILE *file=NULL;
		fopen_s(&file,filename,"rb");
		if(file==NULL) {
			return false;
		};

		bmpheader_s header;
		bmpinfo_s info;

		fread(&header,sizeof(header),1,file);
		fread(&info,sizeof(info),1,file);

		s32 bpp=info.bits_per_pixel/8;
		s32 width=info.width;
		s32 height=info.height;
		s32 size=bpp*width*height;
		u8 *data=(u8*)malloc(size);

		fseek(file,header.data_offset,SEEK_SET);
		fread(data,1,size,file);
		fclose(file);

		// work with the data
		s32 vertex_count=width*height;
		vertex_s *vertices=new vertex_s[vertex_count];
		for(s32 i=0;i<vertex_count;i++) {
			f32 x=(f32)(i%width);
			f32 y=(f32)data[i]*0.02f;
			f32 z=(f32)(i/width);

			f32 tu=x*(1.0f/(f32)width);
			f32 tv=z*(1.0f/(f32)height);

			vertices[i].position=Vector3(x,y,z);
			vertices[i].texcoord=Vector2(tu,tv);
			vertices[i].normal=Vector3(0,0,0);
			vertices[i].color=0xff005411;
		};

		free(data);

		// TODO: Create indices for index buffer
		s32 index_count=(width-1)*(height-1)*6;
		u16 *indices=new u16[index_count];
		s32 index=0;
		for(s32 y=0;y<(height-1);y++) {
			for(s32 x=0;x<(width-1);x++) {
				indices[index]=y*width+x;		index++;
				indices[index]=(y+1)*width+x;	index++;
				indices[index]=y*width+x+1;		index++;

				indices[index]=y*width+x+1;		index++;
				indices[index]=(y+1)*width+x;	index++;
				indices[index]=(y+1)*width+x+1;	index++;
			};
		};

		for(s32 i=0;i<index_count;i+=3) {
			Vector3 p0=vertices[indices[i+0]].position;
			Vector3 p1=vertices[indices[i+1]].position;
			Vector3 p2=vertices[indices[i+2]].position;


			Vector3 r=p1-p0;
			Vector3 t=p2-p0;

			Vector3 n;
			D3DXVec3Cross(&n,&r,&t);
			D3DXVec3Normalize(&n,&n);

			vertices[indices[i+0]].normal+=n;
			vertices[indices[i+1]].normal+=n;
			vertices[indices[i+2]].normal+=n;
		};

		for(s32 i=0;i<index_count;i++) {
			D3DXVec3Normalize(&vertices[indices[i]].normal,&vertices[indices[i]].normal);
		};

		bool success=true;
		if(!mesh->Init(sizeof(vertex_s),vertex_count,vertices,index_count,indices)) {
			success=false;
		};

		delete[] vertices;
		delete[] indices;

		return success;
	};

	bool MeshUtils::CreateMeshFromObj(const char *filename,Mesh *&mesh) {
		std::vector<Token> stream;
		if(!obj::parse(filename,stream)) {
			return false;
		};
		if(!obj::construct(stream,mesh)) {
			return false;
		};
		return true;
	};
}; // MeshUtils
