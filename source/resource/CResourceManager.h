#ifndef _RESOURCE_C_RESOURCE_MANAGER_H_
#define _RESOURCE_C_RESOURCE_MANAGER_H_

#include "resource/IResourceManager.h"
#include "base/CSingleton.h"

namespace se
{
	namespace resource
	{
		class CResourceManager : public IResourceManager, public base::CSingleton < CResourceManager >
		{
		public:
			CResourceManager(){}
			~CResourceManager(){}
			virtual bool LoadFile(const char *fileName, std::vector<math::CVector3> &vertices, std::vector<ushort> &indices, 
				std::vector<math::CVector3> &normals, std::vector<math::CVector2> &texCoords);

		};
	}
}

#endif