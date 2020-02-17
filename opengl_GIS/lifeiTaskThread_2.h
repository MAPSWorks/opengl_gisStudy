#pragma once
#include "lifeiThread_2.h"
namespace CELL
{
	class lifeiTaskSystem_2;
	class lifeiTaskThread_2 : public lifeiThread_2
	{
	public:
		lifeiTaskThread_2(lifeiTaskSystem_2* pSystem);
		~lifeiTaskThread_2();

	public:
		//�˳���־
		bool _exitFlag;
		//Ҫ�����Ƭ���Ƽ������ڵ�ϵͳ
		lifeiTaskSystem_2* _system;

		//�˳�
		virtual void join();
		virtual bool onCreate();
		virtual bool onRun();
		virtual bool onDestroy();
	};
}
