#include "CDirectionLight.h"

namespace se
{
	namespace scene
	{
		CDirectionLight::CDirectionLight(const math::CVector3 &direction, const base::Color &color, float fIntensity)
			:CLight(color, fIntensity)
			, m_vDirection(direction)
		{
			m_vDirection.normalize();
		}

		void CDirectionLight::SetDirection(const math::CVector3 &dir)
		{
			m_vDirection = dir; 
			m_vDirection.normalize();
		}

	}
}