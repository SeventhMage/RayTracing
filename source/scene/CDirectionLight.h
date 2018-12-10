#ifndef _C_DIRECTION_LIGHT_H_
#define _C_DIRECTION_LIGHT_H_

#include "CLight.h"

namespace se
{
	namespace scene
	{
		class CDirectionLight : public CLight
		{
		public:
			CDirectionLight(const math::CVector3 &direction, const base::Color &color, float fIntensity);
			ELightType GetType() const { return LT_DIRECTION; }
			void SetDirection(const math::CVector3 &dir);
			const math::CVector3 &GetDirection() const { return m_vDirection; }
		private:
			math::CVector3 m_vDirection;
		};
	}
}

#endif