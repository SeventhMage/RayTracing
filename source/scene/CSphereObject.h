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
			virtual bool Interset(const math::CRay &ray, float *distance = nullptr);
			virtual void GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 *normal, base::Color *color);
		private:			
			float m_fRadius;
			base::Color m_Color;
		};
	}
}

#endif