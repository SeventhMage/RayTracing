#include "CObjectManager.h"
#include "CSphereObject.h"
#include "CTriangleMeshObject.h"

#include "base/def.h"
#include "math/math.h"

namespace se
{
	namespace scene
	{


		CObjectManager::CObjectManager()
		{

		}

		CObjectManager::~CObjectManager()
		{
			for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
			{
				SAFE_DEL(it->second);
			}
			m_mapObjects.clear();
		}

		IObject *CObjectManager::CreateSphere(float fRadius, const base::Color &color)
		{
			size_t size = m_mapObjects.size();
			uint id = size + 1;
			m_mapObjects[id] = new CSphereObject(id, fRadius, color);			
			return m_mapObjects[id];
		}

		IObject * CObjectManager::GreateTriangleMesh(const char *fileName)
		{
			size_t size = m_mapObjects.size();
			uint id = size + 1;
			m_mapObjects[id] = new CTriangleMeshObject(id);
			m_mapObjects[id]->LoadMeshFromFile(fileName);
			return m_mapObjects[id];
		}

		IObject * CObjectManager::GreateTriangleMesh(std::vector<math::CVector3> &vertices, std::vector<ushort> &indices, std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords)
		{
			size_t size = m_mapObjects.size();
			uint id = size + 1;
			m_mapObjects[id] = new CTriangleMeshObject(id, vertices, indices, normals, texCoords);
			return m_mapObjects[id];
		}

		IObject * CObjectManager::GetObject(uint id)
		{
			auto it = m_mapObjects.find(id);
			if (it != m_mapObjects.end())
				return it->second;
			return nullptr;
		}

		bool CObjectManager::Trace(const math::CRay &ray, base::Color *color, int depth /* = 5 */)
		{
			float tnear = INFINITY;
			IObject *pObject = nullptr;
			math::CVector2 uv;
			uint triIndex = 0;
			float bias = 1e-4;

			for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
			{
				float dis = INFINITY;
				if (it->second->Intersect(ray, &dis, nullptr, &uv, &triIndex) && dis < tnear)
				{
					tnear = dis;
					pObject = it->second;
				}
			}

			if (pObject)
			{				
				math::CVector3 hitPoint = ray.GetOrigin() + ray.GetDirection() * tnear;
				math::CVector3 hitNormal;
				base::Color hitColor;
				if (pObject->GetObjectType() == OBJ_SPHERE)
				{
					pObject->GetSurfaceData(hitPoint, hitNormal, hitColor);
				}
				else
				{
					pObject->GetSurfaceData(triIndex, uv, hitNormal, hitColor);
				}
				*color = hitColor;

				math::CVector3 lightPos(5, 10, 15);
				base::Color lightColor(1.f, 1.f, 1.f, 1.f);
				base::Color ambient(1.f, 0.3f, 0.3f, 0.3f);
				math::CVector3 dir = lightPos - hitPoint;
				dir.normalize();

				for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
				{					
					if (it->second->Intersect(math::CRay(hitPoint + dir * bias, dir)))
					{
						*color = base::Color(color->a, MIN(ambient.r * color->r, 1), MIN(ambient.g * color->g, 1), MIN(ambient.b * color->b, 1));
						return true;
					}
				}

				lightColor *= MAX(dir.dotProduct(hitNormal), 0);
				lightColor += ambient;
				*color = base::Color(color->a, MIN(lightColor.r * color->r, 1), MIN(lightColor.g * color->g, 1), MIN(lightColor.b * color->b, 1));

				if (color->a < 1.f )
				{										
					base::Color color2;
					if (depth > 0 && Trace(math::CRay(hitPoint + ray.GetDirection() * bias, ray.GetDirection()), &color2, depth - 1))
					{
						color->r = color->a * color->r + (1 - color->a) * color2.r;
						color->g = color->a * color->g + (1 - color->a) * color2.g;
						color->b = color->a * color->b + (1 - color->a) * color2.b;
					}
					else
					{
						color->r = color->a * color->r;
						color->g = color->a * color->g;
						color->b = color->a * color->b;
					}
				}

				if (pObject->GetAlbedo() > 0)
				{
					math::CVector3 reflectDir = reflect(ray.GetDirection(), hitNormal);
					float bias = 1e-4;
					base::Color color2;
					if (depth > 0 && Trace(math::CRay(hitPoint + reflectDir * bias, reflectDir), &color2, depth - 1))
					{
						color->r = (1 - pObject->GetAlbedo()) * color->r + pObject->GetAlbedo() * color2.r;
						color->g = (1 - pObject->GetAlbedo()) * color->g + pObject->GetAlbedo() * color2.g;
						color->b = (1 - pObject->GetAlbedo()) * color->b + pObject->GetAlbedo() * color2.b;					
					}
				}

			}

			return pObject != nullptr;
		}
	}
}