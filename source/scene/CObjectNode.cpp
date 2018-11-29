#include "CObjectNode.h"

namespace se
{
	namespace scene
	{		
		CObjectNode::CObjectNode(IScene *pScene, uint objID)
			:CSceneNode(pScene), m_ObjectID(objID)
		{
		}

		CObjectNode::~CObjectNode()
		{

		}

		void CObjectNode::Update(int delta)
		{
			CSceneNode::Update(delta);
			//float x = (rand() % 2 - 0.5) * 0.2f;
			//float y = (rand() % 2 - 0.5) * 0.2f;
			//float z = (rand() % 2 - 0.5) * 0.2f;
			//SetPosition(GetAbslutePosition() + math::CVector3(x, y, z));
		}
	}
}