#ifndef _SCENE_I_OBJECT_MANAGER_H_
#define _SCENE_I_OBJECT_MANAGER_H_

#include "IObject.h"
#include "base/type.h"
#include "math/CVector2.h"
#include "scene/ILight.h"

#include <memory>

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
			virtual IObject *GreateTriangleMesh(const char *fileName) = 0;
			virtual IObject *GreateTriangleMesh(std::vector<math::CVector3> &vertices, std::vector<ushort> &indices,
				std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords) = 0;
			virtual bool Trace(base::Color *color, const math::CRay &ray, const std::vector<std::shared_ptr<ILight> > &lights, int depth = 5) = 0;
			virtual IObject *Trace(const math::CRay &ray) = 0;
		};
	}
}

#endif