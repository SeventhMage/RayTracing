#ifndef _SCENE_I_OBJECT_H_
#define _SCENE_I_OBJECT_H_

#include "base/SColor.h"
#include "math/CVector3.h"
#include "math/CRay.h"
#include "ISceneNode.h"

namespace se
{
	namespace scene
	{
		class IObject
		{
		public:
			virtual ~IObject(){}
			virtual void AddToSceneNode(ISceneNode *pSceneNode) = 0;
			virtual bool Interset(const math::CRay &ray, math::CVector3 *hitPoint = nullptr) = 0;
			virtual bool Interset(const math::CRay &ray, float *distance = nullptr) = 0;
			virtual void GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 *normal, base::Color *color) = 0;
			virtual bool LoadMeshFromFile(const char *fileName){ return false; };
			virtual uint GetID() const  = 0;
		};
	}
}

#endif