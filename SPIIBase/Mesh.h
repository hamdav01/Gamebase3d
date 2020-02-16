// Mesh.h

#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

class Mesh {
	friend class RenderSystem;
public:
	Mesh(ID3D10Device *device);
	~Mesh();

	bool Init(s32 vertex_size,s32 vertex_count,void *vertices,
		s32 index_count,u16 *indices,bool calculate_volume=true);
	void Release();

	f32 GetRadius() const;
	const Vector3 &GetCenter() const;

private:
	u32 mStride,mOffset;
	u32 mIndexCount;
	ID3D10Device *mpDevice;
	ID3D10Buffer *mpVertexBuffer;
	ID3D10Buffer *mpIndexBuffer;

	Vector3 mLocalCenter;
	f32 mLocalRadius;
};

#endif // MESH_H_INCLUDED
