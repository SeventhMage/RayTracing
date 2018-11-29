#include "CSceneManager.h"
#include "CScene.h"
#include "tracer.h"

namespace se
{
	namespace scene
	{

		CSceneManager::CSceneManager()
			:m_pCurrentScene(new CScene())
		{			
		}

		CSceneManager::~CSceneManager()
		{
			SAFE_DEL(m_pCurrentScene);
		}


		IScene * CSceneManager::LoadScene(const char *filename)
		{
			SAFE_DEL(m_pCurrentScene);
			m_pCurrentScene = new CScene(filename);
			return m_pCurrentScene;
		}

		void CSceneManager::Update(int delta)
		{
			if (m_pCurrentScene)
			{				
				m_pCurrentScene->Update(delta);
				m_pCurrentScene->Render();
			}
		}

	}
}