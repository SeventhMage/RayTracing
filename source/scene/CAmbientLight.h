#ifndef _C_SCENE_AMBIENT_LIGHT_H_
#define _C_SCENE_AMBIENT_LIGHT_H_

#include "CLight.h"

namespace se
{
	namespace scene
	{
		class CAmbientLight : public CLight
		{
		public:
			CAmbientLight(const base::Color &color, float fIntensity);
			virtual ELightType GetType() const { return LT_AMBIENT; }
		};
	}
}

#endif