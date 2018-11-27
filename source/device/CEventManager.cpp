#include "CEventManager.h"
#include "CKeyEvent.h"
#include "CGesturePan.h"
#include "CGesturePinch.h"
#include "CGestureTap.h"
#include "base/def.h"

namespace se
{
	namespace device
	{
		CEventManager::CEventManager()
			:m_pDevice(nullptr)
		{
			m_pKeyEvent = new CKeyEvent();



		}
		CEventManager::~CEventManager()
		{
			SAFE_DEL(m_pKeyEvent);
		}

		void CEventManager::OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight)
		{
			if (m_pDevice)
				m_pDevice->OnSize(uPosX, uPosY, uWidth, uHeight);
		}
        
        void CEventManager::OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum)
        {
            for (auto it = m_mapGestureEvent.begin(); it != m_mapGestureEvent.end(); ++it)
            {
                it->second->OnTouchBegin(pointID, x, y, classID, touchNum);
            }
        }

        void CEventManager::OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum)
        {
            for (auto it = m_mapGestureEvent.begin(); it != m_mapGestureEvent.end(); ++it)
            {
                it->second->OnTouchMove(pointID, x, y, classID, touchNum);
            }
        }
        
        void CEventManager::OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum)
        {
            for (auto it = m_mapGestureEvent.begin(); it != m_mapGestureEvent.end(); ++it)
            {
                it->second->OnTouchEnd(pointID, x, y, classID, touchNum);
            }
        }
        
		void CEventManager::RegisterGestureCallback(EGestureType type, GestureCallback callback)
		{
			if (m_mapGestureEvent.find(type) == m_mapGestureEvent.end())
			{
				switch (type)
				{
				case se::device::GT_TAP:
					m_mapGestureEvent[type] = new CGestureTap();
					break;
				case se::device::GT_PAN:
					m_mapGestureEvent[type] = new CGesturePan();
					break;
				case se::device::GT_PINCH:
					m_mapGestureEvent[type] = new CGesturePinch();
					break;								
				default:
					m_mapGestureEvent[type] = new CGestureTap();
					break;
				}
			}
			m_mapGestureEvent[type]->SubscribeCallback(callback);
		}

		void CEventManager::UnRegisterGestureCallback(EGestureType type, GestureCallback callback)
		{			
			if (m_mapGestureEvent.find(type) != m_mapGestureEvent.end())
			{
				m_mapGestureEvent[type]->UnSubscribeCallback(callback);
			}
		}

	}
}
