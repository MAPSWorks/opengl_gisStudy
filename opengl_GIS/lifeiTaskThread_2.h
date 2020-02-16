#pragma once
#include "lifeiThread_2.h"
namespace CELL
{
	class lifeiTaskSystem;
	class lifeiTaskThread_2 : public lifeiThread_2
	{
	public:
		lifeiTaskThread_2(lifeiTaskSystem* pSystem);
		~lifeiTaskThread_2();

	public:
		//�˳���־
		bool _exitFlag;
		//Ҫ�����Ƭ���Ƽ������ڵ�ϵͳ
		lifeiTaskSystem* _system;

		//�˳�
		virtual void join();
		virtual bool onCreate();
		virtual bool onRun();
		virtual bool onDestroy();
	};
}
