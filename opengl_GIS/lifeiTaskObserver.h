#pragma once
#include "lifeiTask.h"
namespace CELL
{
	class lifeiTaskObserver
	{
	public:
		//����ִ��֪ͨ
		virtual void onTaskExe(lifeiTask* task) = 0;
		//�������֪ͨ
		virtual void onTaskFinish(lifeiTask* task) = 0;
		//����ȡ��֪ͨ
		virtual void onTaskCancel(lifeiTask* task) = 0;
	};

}