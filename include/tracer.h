#ifndef _TRACER_H_
#define _TRACER_H_

#include "base/Log.h"
#include "device/IDevice.h"
#include "device/IDeviceManager.h"
#include "device/IEventManager.h"
#include "scene/ISceneManager.h"
#include "scene/IObjectManager.h"
#include "resource/IResourceManager.h"

namespace se
{
	class CTracer
	{
	public:
		CTracer(int x, int y, int width, int height, bool fullScreen = false);	
		~CTracer();

		static device::IDevice *GetDevice() { return m_pDeviceMgr->GetDevice(); }
		static device::IEventManager *GetEventManager(){ return m_pEventMgr; }
		static scene::ISceneManager *GetSceneManager() { return m_pSceneMgr; }
		static scene::IObjectManager *GetObjectManager() { return m_pObjectMgr; }
		static resource::IResourceManager *GetResourceManager(){ return m_pResourceMgr; }
	private:
		static device::IDeviceManager *m_pDeviceMgr;
		static device::IEventManager *m_pEventMgr;
		static scene::ISceneManager *m_pSceneMgr;
		static scene::IObjectManager *m_pObjectMgr;
		static resource::IResourceManager *m_pResourceMgr;
	};
}

#endif