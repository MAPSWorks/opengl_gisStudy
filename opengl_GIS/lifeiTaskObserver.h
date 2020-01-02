#pragma once
#include "CELLTask.hpp"
namespace CELL
{
	class lifeiTaskObserver
	{
	public:
		//����ִ��֪ͨ
		virtual void onTaskExe(CELLTask* task) = 0;
		//�������֪ͨ
		virtual void onTaskFinish(CELLTask* task) = 0;
		//����ȡ��֪ͨ
		virtual void onTaskCancel(CELLTask* task) = 0;
	};

}