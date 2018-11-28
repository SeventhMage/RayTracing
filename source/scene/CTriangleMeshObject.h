#ifndef _SCENE_C_TRIANGLE_MESH_OBJECT_H_
#define _SCENE_C_TRIANGLE_MESH_OBJECT_H_

#include "CObject.h"
#include "math/CVector2.h"

namespace se
{
	namespace scene
	{
		class CTriangleMeshObject : public CObject
		{
		public:
			CTriangleMeshObject(uint id);
			CTriangleMeshObject(uint id, std::vector<math::CVector3> &vertices, std::vector<ushort> &indices, std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords);
			virtual ~CTriangleMeshObject();
			
			virtual EObjectType GetObjectType() const { return OBJ_TRIANGLE_MESH; }
			virtual bool LoadMeshFromFile(const char *fileName);
			virtual bool Intersect(const math::CRay &ray, float *distance = nullptr, math::CVector3 *hitPoint = nullptr, math::CVector2 *uv = nullptr, uint *triIndex = nullptr);
			virtual void GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor);
		private:
			virtual bool rayTriangleIntersect(const math::CRay &ray, const math::CVector3 &v0, const math::CVector3 &v1, const math::CVector3 &v2, float &t, float &u, float &v);
		private:			
			std::vector<math::CVector3> m_Vertices;			// 顶点列表
			std::vector<ushort> m_Indices;					// 索引列表
			std::vector<math::CVector3> m_Normals;			// 顶点对应法线列表
			std::vector<math::CVector2> m_TexCoords;		// 顶点对应纹理坐标
			
		};
	}
}

#endif