#ifndef _SCENE_C_OBJECT_H_
#define _SCENE_C_OBJECT_H_

#include "scene/IObject.h"
#include "math/CRay.h"
#include "base/SColor.h"
#include "scene/ISceneNode.h"

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
		protected:
			uint m_Id;
			ISceneNode *m_pSceneNode;
		};
	}
}

#endif