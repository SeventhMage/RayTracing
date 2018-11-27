#ifndef _RESOURCE_I_RESOURCE_MANAGER_H_
#define _RESOURCE_I_RESOURCE_MANAGER_H_

#include "math/CVector3.h"
#include "math/CVector2.h"

#include <vector>

namespace se
{
	namespace resource
	{
		class IResourceManager
		{
		public:
			virtual ~IResourceManager(){}
			virtual bool LoadFile(const char *fileName, 
				std::vector<math::CVector3> &vertices, std::vector<ushort> &indices, std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords) = 0;
		};
	}
}

#endif