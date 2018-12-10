#include "CObjectManager.h"
#include "CSphereObject.h"
#include "CTriangleMeshObject.h"
#include "CPointLight.h"
#include "CDirectionLight.h"

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

		bool CObjectManager::Trace(base::Color *color, const math::CRay &ray, const std::vector<std::shared_ptr<ILight> > &lights, int depth /* = 5 */)
		{
			float tnear = INFINITY;
			IObject *pObject = nullptr;
			math::CVector2 uv;
			uint triIndex = 0;
			float bias = 0.001f;
			*color = base::Color();

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

				for (auto light : lights)
				{
					base::Color lightColor = light->GetColor();
					switch (light->GetType())
					{
					case ELightType::LT_AMBIENT:
					{
						*color = base::Color(hitColor.a, MIN((color->r + lightColor.r * hitColor.r), 1), MIN(color->g + lightColor.g * hitColor.g, 1), MIN(color->b + lightColor.b * hitColor.b, 1));
					}
						break;
					case ELightType::LT_DIRECTION:
					{
						CDirectionLight *pLight = dynamic_cast<CDirectionLight *>(light.get());
						if (pLight)
						{
							if (hitNormal.dotProduct(-pLight->GetDirection()) > 0)
							{
								for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
								{
									float tmpDis = 0;
									if (!it->second->Intersect(math::CRay(hitPoint - pLight->GetDirection() * bias, -pLight->GetDirection()), &tmpDis))
									{
										lightColor *= light->GetIntensity() * MAX(-pLight->GetDirection().dotProduct(hitNormal), 0);
										*color = base::Color(hitColor.a, MIN((color->r + lightColor.r * hitColor.r), 1), MIN(color->g + lightColor.g * hitColor.g, 1), MIN(color->b + lightColor.b * hitColor.b, 1));
									}
								}
							}
						}
					}
						break;
					case ELightType::LT_POINT:
					{
						CPointLight *pLight = dynamic_cast<CPointLight *>(light.get());
						if (pLight)
						{
							math::CVector3 lightPos = pLight->GetPosition();
							
							math::CVector3 dir = lightPos - hitPoint;
							dir.normalize();
							float hit2Light = lightPos.getDistanceFromSQ(hitPoint);

							if (hitNormal.dotProduct(dir) > 0)
							{
								for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
								{
									float tmpDis = 0;
									if (!it->second->Intersect(math::CRay(hitPoint + dir * bias, dir), &tmpDis) && tmpDis * tmpDis < hit2Light)
									{
										lightColor *= light->GetIntensity() * MAX(dir.dotProduct(hitNormal), 0) * (1 / (lightPos.getDistanceFromSQ(hitPoint)));	
										*color = base::Color(hitColor.a, MIN((color->r + lightColor.r * hitColor.r), 1), MIN(color->g + lightColor.g * hitColor.g, 1), MIN(color->b + lightColor.b * hitColor.b, 1));
									}
								}
							}
						}
					}
						break;
					default:
						break;
					}

					
				}

				if (color->a < 1.f && depth > 0)
				{
					base::Color refractionColor;

					float kr = 0;
					fresnel(ray.GetDirection(), hitNormal, pObject->GetIndexOfRefraction(), kr);
					bool outside = ray.GetDirection().dotProduct(hitNormal) < 0;
					math::CVector3 vBias = bias * hitNormal;
					if (kr < 1)
					{
						math::CVector3 refractionDirection = refract(ray.GetDirection(), hitNormal, pObject->GetIndexOfRefraction()).normalize();
						math::CVector3 refractionRayOrig = outside ? hitPoint - vBias : hitPoint + vBias;
						if (Trace(&refractionColor, math::CRay(refractionRayOrig, refractionDirection), lights, depth - 1))
						{
							int a = 3;
						}
					}
					base::Color reflectionColor;
					math::CVector3 reflectDir =  reflect(ray.GetDirection(), hitNormal);
					Trace(&reflectionColor, math::CRay(hitPoint + hitNormal * bias, reflectDir), lights, depth - 1);

					*color += reflectionColor * kr + refractionColor * (1 - kr);
					color->a = hitColor.a;

				}

				if (pObject->GetAlbedo() > 0)
				{
					math::CVector3 reflectDir = reflect(ray.GetDirection(), hitNormal);
					base::Color color2;
					if (depth > 0 && Trace(&color2, math::CRay(hitPoint + reflectDir * bias, reflectDir), lights, depth - 1))
					{
						color->r = (1 - pObject->GetAlbedo()) * color->r + pObject->GetAlbedo() * color2.r;
						color->g = (1 - pObject->GetAlbedo()) * color->g + pObject->GetAlbedo() * color2.g;
						color->b = (1 - pObject->GetAlbedo()) * color->b + pObject->GetAlbedo() * color2.b;
					}
				}
			}

			return pObject != nullptr;
		}

		IObject * CObjectManager::Trace(const math::CRay &ray)
		{
			float tnear = INFINITY;
			IObject *pObject = nullptr;

			for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
			{
				float dis = INFINITY;
				if (it->second->Intersect(ray, &dis) && dis < tnear)
				{
					pObject = it->second;
					tnear = dis;
				}
			}

			return pObject;
		}

	}
}