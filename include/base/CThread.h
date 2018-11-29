#ifndef _BASE_C_THREAD_H_
#define _BASE_C_THREAD_H_

#include <thread>

namespace se
{
	namespace base
	{		
		class CTask
		{
		public:
			void operator()(int i);
		private:

		};

		class CThread
		{
		public:
			CThread(int index);
			~CThread();			
		private:
			std::thread m_thread;
			CTask m_task;
		};
	}
}

#endif