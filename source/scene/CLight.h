#ifndef _C_SCENE_LIGHT_H_
#define _C_SCENE_LIGHT_H_

#include "scene/ILight.h"

namespace se
{
	namespace scene
	{
		class CLight : public ILight
		{
		public:
			CLight(const base::Color &color, float fIntensity);
			virtual ~CLight();			
			virtual void SetColor(const base::Color &);
			virtual const base::Color &GetColor() const;
			virtual void SetIntensity(float);
			virtual float GetIntensity() const;
		private:			
			base::Color m_Color;
			float m_fIntensity;
		};
	}
}

#endif