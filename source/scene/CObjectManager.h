#ifndef _SCENE_C_OBJECT_MANAGER_H_
#define _SCENE_C_OBJECT_MANAGER_H_

#include "scene/IObjectManager.h"
#include "base/CSingleton.h"

#include <map>

namespace se
{
	namespace scene
	{
		class CObjectManager : public IObjectManager, public base::CSingleton<CObjectManager>
		{
		public:
			CObjectManager();
			virtual ~CObjectManager();

			virtual IObject *GetObject(uint id);
			virtual IObject *CreateSphere(float fRadius, const base::Color &color);
			virtual IObject *GreateTriangleMesh(const char *fileName);
			virtual IObject *GreateTriangleMesh(std::vector<math::CVector3> &vertices, std::vector<ushort> &indices,
				std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords);
			virtual bool Trace(const math::CRay &ray, base::Color *color, int depth = 5);
		private:
			std::map<uint, IObject *> m_mapObjects;
		};
	}
}

#endif