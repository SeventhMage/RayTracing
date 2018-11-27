#ifndef _SCENE_C_OBJECT_H_
#define _SCENE_C_OBJECT_H_

#include "scene/IObject.h"

namespace se
{
	namespace scene
	{
		class CObject : public IObject
		{
		public:
			CObject(uint id);
			virtual ~CObject();
			virtual void AddToSceneNode(ISceneNode *pSceneNode);
			virtual uint GetID() const { return m_Id; }
			virtual bool Interset(const math::CRay &ray, float *distance = nullptr){ return false; }
			virtual bool Interset(const math::CRay &ray, math::CVector3 *hitPoint = nullptr);
		protected:
			uint m_Id;
			ISceneNode *m_pSceneNode;
		};
	}
}

#endif