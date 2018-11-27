#include "CObject.h"

namespace se
{
	namespace scene
	{


		CObject::CObject(uint id)
			:m_Id(id)
			, m_pSceneNode(nullptr)
		{

		}

		CObject::~CObject()
		{

		}

		void CObject::AddToSceneNode(ISceneNode *pSceneNode)
		{
			m_pSceneNode = pSceneNode;			
		}

	}
}