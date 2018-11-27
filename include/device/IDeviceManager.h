/************************************************************************/
/* 设备管理接口                                                         */
/************************************************************************/

#ifndef _MX_DEVICE_I_DEVICE_MANAGER_H_
#define _MX_DEVICE_I_DEVICE_MANAGER_H_

#include "IDevice.h"

namespace se
{
	namespace device
	{
		class IDeviceManager
		{
		public:
			virtual ~IDeviceManager(){};

			virtual IDevice *CreateDevice(int x, int y, int width, int height, bool bFullScreen = false) = 0;
			virtual IDevice *GetDevice() = 0;
		};
	}
}

#endif