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
			uint numTris = m_Indices.size() / 3;
			uint j = 0;
			float tNear = INFINITY;
			bool isect = false;
			for (uint i = 0; i < numTris; ++i) {
				const CVector3 &v0 = m_Vertices[m_Indices[j]];
				const CVector3 &v1 = m_Vertices[m_Indices[j + 1]];
				const CVector3 &v2 = m_Vertices[m_Indices[j + 2]];
				float t = INFINITY, u, v;
				if (rayTriangleIntersect(ray, v0, v1, v2, t, u, v) && t < tNear) {
					tNear = t;
					//uv.x = u;
					//uv.y = v;
					//triIndex = i;
					isect = true;
				}
				j += 3;
			}

			return isect;			
		}

		void CTriangleMeshObject::GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 *normal, base::Color *color)
		{

		}

		bool CTriangleMeshObject::rayTriangleIntersect(const math::CRay &ray, const math::CVector3 &v0, const math::CVector3 &v1, const math::CVector3 &v2, float &t, float &u, float &v)
		{
			CVector3 v0v1 = v1 - v0;
			CVector3 v0v2 = v2 - v0;
			CVector3 dir = ray.GetDirection();
			CVector3 pvec = dir.crossProduct(v0v2);
			float det = v0v1.dotProduct(pvec);

			// ray and triangle are parallel if det is close to 0
			if (fabs(det) < ROUNDING_ERROR_FLOAT) return false;

			float invDet = 1 / det;

			CVector3 tvec = ray.GetOrigin() - v0;
			u = tvec.dotProduct(pvec) * invDet;
			if (u < 0 || u > 1) return false;

			CVector3 qvec = tvec.crossProduct(v0v1);
			v = dir.dotProduct(qvec) * invDet;
			if (v < 0 || u + v > 1) return false;

			t = v0v2.dotProduct(qvec) * invDet;

			return (t > 0) ? true : false;
		}

	}
}