#ifndef _C_SCENE_POINT_LIGHT_H_
#define _C_SCENE_POINT_LIGHT_H_

#include "CLight.h"

namespace se
{
	namespace scene
	{
		class CPointLight : public CLight
		{
		public:
			CPointLight(math::CVector3 &pos, const base::Color &color, float fIntensity);
			~CPointLight();
			void SetPosition(const math::CVector3 &pos) { m_vPosition = pos; }
			math::CVector3 GetPosition() const { return m_vPosition; }
			ELightType GetType() const { return LT_POINT; }
		private:
			math::CVector3 m_vPosition;
			
		};
	}
}

#endif