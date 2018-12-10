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

		bool CTriangleMeshObject::Intersect(const math::CRay &ray, float *distance /* = nullptr */, math::CVector3 *hitPoint /* = nullptr */, math::CVector2 *uv /* = nullptr */, uint *triIndex /* = nullptr */)
		{
			uint numTris = m_Indices.size() / 3;
			uint j = 0;
			float tNear = INFINITY;
			bool bOnlyInsetTest = (distance == nullptr) && (hitPoint == nullptr) && (uv == nullptr) && (triIndex == nullptr);
			bool isect = false;
			for (uint i = 0; i < numTris; ++i) {
				CVector3 v0 = m_Vertices[m_Indices[j]];
				CVector3 v1 = m_Vertices[m_Indices[j + 1]];
				CVector3 v2 = m_Vertices[m_Indices[j + 2]];
				m_pSceneNode->GetAbsluateMatrix().TransformVect(v0);
				m_pSceneNode->GetAbsluateMatrix().TransformVect(v1);
				m_pSceneNode->GetAbsluateMatrix().TransformVect(v2);

				float t = INFINITY, u, v;
				if (rayTriangleIntersect(ray, v0, v1, v2, t, u, v) && t < tNear) 
				{
					if (bOnlyInsetTest)
						break;
					tNear = t;
					if (uv)
					{
						uv->x = u;
						uv->y = v;
					}
					if (triIndex)
						*triIndex = i;
					isect = true;
				}
				j += 3;
			}
			if (distance)
				*distance = tNear;
			if (hitPoint)
				*hitPoint = ray.GetOrigin() + ray.GetDirection() * tNear;
			return isect;			
		}

		void CTriangleMeshObject::GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor)
		{
			const math::CVector3 &n0 = m_Normals[triIndex * 3];
			const math::CVector3 &n1 = m_Normals[triIndex * 3 + 1];
			const math::CVector3 &n2 = m_Normals[triIndex * 3 + 2];
			hitNormal = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;			

			// doesn't need to be normalized as the N's are normalized but just for safety
			hitNormal.normalize();

			// texture coordinates
			const math::CVector2 &st0 = m_TexCoords[triIndex * 3];
			const math::CVector2 &st1 = m_TexCoords[triIndex * 3 + 1];
			const math::CVector2 &st2 = m_TexCoords[triIndex * 3 + 2];
			math::CVector2 hitTextureCoordinates = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2;
			hitColor = base::Color(.1f, 0.1f, 0.2f, .4f);
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