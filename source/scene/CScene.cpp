#include "CScene.h"

#include "base/def.h"
#include "CSceneNode.h"
#include "CObjectNode.h"
#include "base/SColor.h"
#include "tracer.h"

namespace se
{
	namespace scene
	{
		CScene::CScene()
			:m_strSceneName("")
			, m_pCamera(nullptr)
			, m_pRootNode(new CSceneNode(this))
			, m_Buffer(nullptr)
			, m_pBufferBack(nullptr)
		{			
		}
		CScene::CScene(const char *name)
			:m_strSceneName(name)
			, m_pCamera(nullptr)
			, m_pRootNode(new CSceneNode(this))		
			, m_Buffer(nullptr)
			, m_pBufferBack(nullptr)
		{
		}

		CScene::~CScene()
		{
			SAFE_DEL(m_pCamera);
			SAFE_DEL(m_pRootNode);
			SAFE_DEL(m_Buffer);
		}
		void CScene::Update(int delta)
		{
			if (m_pCamera)
				m_pCamera->Update(delta);
			if (m_pRootNode)
				m_pRootNode->Update(delta);
		}

		ICamera *CScene::SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			SAFE_DEL(m_pCamera);
			m_pCamera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::SetupCamera(float fDistance, ISceneNode *pFocusNode, const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip)
		{
			SAFE_DEL(m_pCamera);
			m_pCamera = new CCamera(fDistance, pFocusNode, vDirection, vUp, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::GetCamera()
		{
			return m_pCamera;
		}

		ISceneNode *CScene::AddObject(IObject *pObject)
		{
			CObjectNode *pNode = new CObjectNode(this, pObject->GetID());
			m_pRootNode->AddChildNode(pNode);
			pObject->AddToSceneNode(pNode);
			return pNode;
		}

		void CScene::Render()
		{
			int width = CTracer::GetDevice()->GetWindowWidth();
			int height = CTracer::GetDevice()->GetWindowHeight();
			if (m_Buffer == nullptr)
			{
				m_Buffer = new uint[width * height];
			}
			memset(m_Buffer, 0, sizeof(uint) * width * height);
			//for (int i = 0; i < width * height; ++i)
			{
				//m_Buffer[i] = base::Color(1.f, 0.5f, 0.5f, 0.9f).Get32BitColor();
				//m_Buffer[i] = base::Color(1.f, .5f, .5f, .5f).Get32BitColor();
			}

			uint *pixel = m_Buffer;		
			for (uint y = 0; y < height; ++y)
			{
				for (uint x = 0; x < width; ++x, ++pixel)
				{
					CRay ray = m_pCamera->GetCameraRay(x, y, width, height);
					base::Color color;
					if (CTracer::GetObjectManager()->Trace(&color, ray, m_Lights))
					{
						*pixel = color.Get32BitColor();
					}
				}
			}

			CTracer::GetDevice()->DrawBuffer(m_Buffer);
		}

		void CScene::AddLight(const std::shared_ptr<ILight> &light)
		{
			m_Lights.push_back(light);
		}


	}
}