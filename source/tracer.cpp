#include "tracer.h"
#include "device/CDeviceManager.h"
#include "device/CEventManager.h"
#include "scene/CSceneManager.h"
#include "scene/CObjectManager.h"

namespace se
{
	device::IDeviceManager *CTracer::m_pDeviceMgr = nullptr;
	device::IEventManager *CTracer::m_pEventMgr = nullptr;
	scene::ISceneManager *CTracer::m_pSceneMgr = nullptr;
	scene::IObjectManager *CTracer::m_pObjectMgr = nullptr;

	CTracer::CTracer(int x, int y, int width, int height, bool fullScreen /*= false*/)
	{
		m_pDeviceMgr = device::CDeviceManager::NewInstance();
		m_pEventMgr = device::CEventManager::NewInstance();
		m_pSceneMgr = scene::CSceneManager::NewInstance();
		m_pObjectMgr = scene::CObjectManager::NewInstance();		

		m_pDeviceMgr->CreateDevice(x, y, width, height, fullScreen);
	}

	CTracer::~CTracer()
	{
		
		scene::CSceneManager::DeleteInstance();		
		device::CDeviceManager::DeleteInstance();
		device::CEventManager::DeleteInstance();

	}

}