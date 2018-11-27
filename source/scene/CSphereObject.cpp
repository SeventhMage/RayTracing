#include "CSphereObject.h"
#include "math/math.h"

namespace se
{
	namespace scene
	{
		CSphereObject::CSphereObject(uint id, float fRadius, const base::Color &color)
			:CObject(id), m_fRadius(fRadius), m_Color(color)
		{			
		}

		CSphereObject::~CSphereObject()
		{			
		}

		bool CSphereObject::Interset(const math::CRay &ray, float *distance /*= nullptr*/)
		{			
			float t0, t1; // solutions for t if the ray intersects
#if 0
			// geometric solution
			math::CVector3 L = m_pSceneNode->GetAbslutePosition() - ray.GetOrigin();
			float tca = L.dotProduct(ray.GetDirection());
			if (tca < 0) 
				return false;
			float d2 = L.dotProduct(L) - tca * tca;
			if (d2 > m_fRadius * m_fRadius) 
				return false;
			float thc = sqrt(m_fRadius * m_fRadius - d2);
			t0 = tca - thc;
			t1 = tca + thc;
#else
			// analytic solution
			math::CVector3 L = ray.GetOrigin() - m_pSceneNode->GetAbslutePosition();
			const math::CVector3 &dir = ray.GetDirection();
			float a = dir.dotProduct(dir);
			float b = 2 * dir.dotProduct(L);
			float c = L.dotProduct(L) - m_fRadius * m_fRadius;
			if (!solveQuadratic(a, b, c, t0, t1)) return false;
#endif
			if (t0 > t1) std::swap(t0, t1);

			if (t0 < 0) {
				t0 = t1; // if t0 is negative, let's use t1 instead
				if (t0 < 0) return false; // both t0 and t1 are negative
			}

			*distance = t0;
			return true;
		}

		void CSphereObject::GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 *normal, base::Color *color)
		{
			*normal = hitPoint - m_pSceneNode->GetAbslutePosition();
			(*normal).normalize();
			*color = m_Color;			
		}

	}
}