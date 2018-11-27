#ifndef _SCENE_I_OBJECT_MANAGER_H_
#define _SCENE_I_OBJECT_MANAGER_H_

#include "IObject.h"
#include "base/type.h"

namespace se
{
	namespace scene
	{
		class IObjectManager
		{
		public:
			virtual ~IObjectManager(){}

			virtual IObject *GetObject(uint id) = 0;
			virtual IObject *CreateSphere(float fRadius, const base::Color &color) = 0;	

			virtual bool Trace(const math::CRay &ray, base::Color *color, int depth = 5) = 0;
		};
	}
}

#endif