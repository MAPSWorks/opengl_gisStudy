#pragma once
#include "lifeiTask_2.h"
namespace CELL
{
	class lifeiTaskObserver
	{
	public:
		//����ִ��֪ͨ
		virtual void onTaskExe(lifeiTask_2* task) = 0;
		//�������֪ͨ
		virtual void onTaskFinish(lifeiTask_2* task) = 0;
		//����ȡ��֪ͨ
		virtual void onTaskCancel(lifeiTask_2* task) = 0;
	};

}