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

		bool CObject::Interset(const math::CRay &ray, math::CVector3 *hitPoint /*= nullptr*/)
		{			
			float distance = 0;			
			if (Interset(ray, &distance))
			{
				*hitPoint = ray.GetOrigin() + distance * ray.GetDirection();
				return true;
			}
			return false;
		}

	}
}