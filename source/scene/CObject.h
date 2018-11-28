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
			virtual void GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 &hitNormal, base::Color &hitColor) {}
			virtual void GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor) {}
			virtual float GetAlbedo() const { return m_fAlbedo; }
			virtual void SetAlbedo(float fAlbedo) { m_fAlbedo = fAlbedo; }
		protected:
			uint m_Id;
			ISceneNode *m_pSceneNode;
			float m_fAlbedo;
		};
	}
}

#endif