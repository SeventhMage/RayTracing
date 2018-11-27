#ifndef _SCENE_C_TRIANGLE_MESH_OBJECT_H_
#define _SCENE_C_TRIANGLE_MESH_OBJECT_H_

#include "CObject.h"

namespace se
{
	namespace scene
	{
		class CTriangleMeshObject : public CObject
		{
		public:
			CTriangleMeshObject(uint id);
			virtual ~CTriangleMeshObject();
		private:			
			std::vector<CVector3> m_Vertices;
			std::vector<CVector3> m_Normals;
			std::vector<CVector2> m_Texcoords;			
			std::vector<uint> m_Indices;
			std::vector<uint> 
		};
	}
}

#endif