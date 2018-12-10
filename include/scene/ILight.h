#ifndef _I_SCENE_LIGHT_H_
#define _I_SCENE_LIGHT_H_

#include "ISceneNode.h"
#include "base/SColor.h"

namespace se
{
	namespace scene
	{
		enum ELightType
		{
			LT_AMBIENT,
			LT_DIRECTION,
			LT_POINT,
		};

		class ILight
		{
		public:
			virtual ~ILight(){}
			virtual void SetColor(const base::Color &) = 0;
			virtual const base::Color &GetColor() const = 0;
			virtual void SetIntensity(float) = 0;
			virtual float GetIntensity() const = 0;
			virtual ELightType GetType() const = 0;
		};
	}
}

#endif