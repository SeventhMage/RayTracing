#include "CPointLight.h"

namespace se
{
	namespace scene
	{
		CPointLight::CPointLight(math::CVector3 &pos, const base::Color &color, float fIntensity)
			:CLight(color, fIntensity)
			, m_vPosition(pos)
		{

		}

		CPointLight::~CPointLight()
		{

		}

	}
}