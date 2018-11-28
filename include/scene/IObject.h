#ifndef _SCENE_I_OBJECT_H_
#define _SCENE_I_OBJECT_H_

#include "base/SColor.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include "math/CRay.h"
#include "ISceneNode.h"

namespace se
{
	namespace scene
	{
		enum EObjectType
		{
			OBJ_SPHERE,
			OBJ_TRIANGLE_MESH,
		};

		class IObject
		{
		public:
			virtual ~IObject(){}
			virtual void AddToSceneNode(ISceneNode *pSceneNode) = 0;			
			virtual bool Intersect(const math::CRay &ray, float *distance = nullptr, math::CVector3 *hitPoint = nullptr, math::CVector2 *uv = nullptr, uint *triIndex = nullptr) = 0;
			virtual void GetSurfaceData(const math::CVector3 &hitPoint, math::CVector3 &hitNormal, base::Color &hitColor) = 0;
			virtual void GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor) = 0;
			virtual bool LoadMeshFromFile(const char *fileName){ return false; };
			virtual uint GetID() const  = 0;
			virtual EObjectType GetObjectType() const = 0;
			virtual float GetAlbedo() const = 0;
			virtual void SetAlbedo(float fAlbedo) = 0;
		};
	}
}

#endif