#include "CObject.h"

namespace se
{
	namespace scene
	{


		CObject::CObject(uint id)
			:m_Id(id)
			, m_pSceneNode(nullptr)
			, m_fAlbedo(0.f)
			, m_fIOR(1.f)
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