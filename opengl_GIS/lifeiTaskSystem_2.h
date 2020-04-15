#pragma once
#include "lifeiTask_2.h"
#include "lifeiThread_2.h"
#include <vector>
#include <list>
#include "lifeiSemaphore_2.h"
#include "lifeiMutex_2.h"
#include "lifeiTaskObserver_2.h"

namespace CELL
{
	typedef std::vector<lifeiThread_2*>	arrayThread;
	typedef std::list<lifeiTask_2*>		arrayTask;

	class lifeiTaskSystem_2	//������Ƭ���ƻ�ȡҪ���ɵ�texture����
	{
	public:
		lifeiTaskObserver_2*	_observer;
		arrayThread				_threads;
		arrayTask				_tasks_requestTile;
		lifeiSemaphore_2		_semphore;
		lifeiMutex_2			_mutex;
		
	public:
		lifeiTaskSystem_2();
		virtual ~lifeiTaskSystem_2();
		//���ù۲���ָ��
		virtual void setObserver(lifeiTaskObserver_2* observer);

		//�����������
		virtual void start(int threadNum = 4);
		//����
		virtual void destroy();
		//�������ӿ�
		virtual void addTask(lifeiTask_2* task);
	public:
		virtual void run();
	};
}