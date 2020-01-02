#pragma once
#include "lifeiThread.h"
namespace CELL
{
	class lifeiTaskSystem;
	class lifeiTaskThread : public lifeiThread
	{
	public:
		lifeiTaskThread(lifeiTaskSystem* pSystem);
		~lifeiTaskThread();
	public:
		//�˳���־
		bool _exitFlag;
		lifeiTaskSystem* _system;

		//�˳�
		virtual void join();
		virtual bool onCreate();
		virtual bool onRun();
		virtual bool onDestroy();
	};

}

