#include "base/CThread.h"

namespace se
{
	namespace base
	{
		CThread::CThread(int index)
			:m_thread(m_task, index)
		{
			
		}

		CThread::~CThread()
		{

		}

		void CTask::operator()(int i)
		{

		}

	}
}