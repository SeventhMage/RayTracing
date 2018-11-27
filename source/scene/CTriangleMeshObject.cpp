#include "CTriangleMeshObject.h"
#include "tracer.h"

namespace se
{
	namespace scene
	{
		CTriangleMeshObject::CTriangleMeshObject(uint id)
			:CObject(id)
		{

		}

		CTriangleMeshObject::CTriangleMeshObject(uint id, std::vector<math::CVector3> &vertices, 
			std::vector<ushort> &indices, std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords)
			: CObject(id), m_Vertices(vertices), m_Indices(indices), m_Normals(normals), m_TexCoords(texCoords)
		{

		}

		CTriangleMeshObject::~CTriangleMeshObject()
		{

		}

		bool CTriangleMeshObject::LoadMeshFromFile(const char *fileName)
		{
			return CTracer::GetResourceManager()->LoadFile(fileName, m_Vertices, m_Indices, m_Normals, m_TexCoords);
		}

		bool CTriangleMeshObject::Interset(const math::CRay &ray, float *distance /*= nullptr*/)
		{

			return true;
		}

		void CTriangleMeshObject::GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 *normal, base::Color *color)
		{

		}

	}
}