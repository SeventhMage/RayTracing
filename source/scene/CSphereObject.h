#ifndef _SCENE_C_SPHERE_OBJECT_H_
#define _SCENE_C_SPHERE_OBJECT_H_

#include "CObject.h"

namespace se
{
	namespace scene
	{
		class CSphereObject : public CObject
		{
		public:
			CSphereObject(uint id, float fRadius, const base::Color &color);
			~CSphereObject();			
			virtual bool Intersect(const math::CRay &ray, float *distance = nullptr, math::CVector3 *hitPoint = nullptr, math::CVector2 *uv = nullptr, uint *triIndex = nullptr);
			virtual void GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 &hitNormal, base::Color &hitColor);
			virtual EObjectType GetObjectType() const { return OBJ_SPHERE; }
		private:			
			float m_fRadius;
			base::Color m_Color;
		};
	}
}

#endif