// MeshUtils.h

#ifndef MESHUTILS_H_INCLUDED
#define MESHUTILS_H_INCLUDED

class Mesh;

namespace MeshUtils {
	bool CreateSkybox(Mesh *&mesh);
	bool CreateHeightmapFromBmp(const char *filename,Mesh *&mesh);
	bool CreateMeshFromObj(const char *filename,Mesh *&mesh);
}; // MeshUtils

#endif // MESHUTILS_H_INCLUDED
