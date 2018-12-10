#include "CLight.h"

namespace se
{
	namespace scene
	{
		CLight::CLight(const base::Color &color, float fIntensity)			
			: m_Color(color)
			, m_fIntensity(fIntensity)
		{

		}

		CLight::~CLight()
		{

		}

		void CLight::SetColor(const base::Color &color)
		{
			m_Color = color;
		}

		const base::Color & CLight::GetColor() const
		{
			return m_Color;
		}

		void CLight::SetIntensity(float fIntensity)
		{
			m_fIntensity = fIntensity;
		}

		float CLight::GetIntensity() const
		{
			return m_fIntensity;
		}

	}
}