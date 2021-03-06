﻿#ifndef _SCENE_C_SCENE_H_
#define _SCENE_C_SCENE_H_

#include "scene/IScene.h"
#include "scene/ISceneNode.h"
#include "CCamera.h"

#include <string>
#include <thread>


namespace se
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene();
			CScene(const char *name);			
			virtual ~CScene();

			//每个场景有唯一根结点，场景图的根
			virtual ISceneNode *GetRootNode(){ return m_pRootNode; }

			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			
			virtual ICamera *SetupCamera(float fDistance, ISceneNode *pFocusNode,
				const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip);
			virtual ICamera *GetCamera();

			virtual ISceneNode *AddObject(IObject *pObject);
			virtual void AddLight(const std::shared_ptr<ILight> &light);

			virtual void Update(int delta);
			virtual void Render();

		private:
			std::string m_strSceneName;
			ISceneNode *m_pRootNode;
			CCamera *m_pCamera;
			uint *m_Buffer;
			uint *m_pBufferBack;
			std::vector<std::shared_ptr<ILight> > m_Lights;
			
		};
	}
}

#endif