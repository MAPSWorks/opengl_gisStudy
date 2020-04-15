#include "lifeiTaskSystem_2.h"
#include "lifeiTaskThread_2.h"

namespace CELL
{
	lifeiTaskSystem_2::lifeiTaskSystem_2()
	{
		_observer = 0;
		_threads.clear();
	}

	lifeiTaskSystem_2::~lifeiTaskSystem_2()
	{
		_threads.clear();
	}

	void lifeiTaskSystem_2::setObserver(lifeiTaskObserver_2 * observer)
	{
		_observer = observer;
	}

	void lifeiTaskSystem_2::start(int threadNum)
	{
		destroy();
		for (size_t i = 0; i < threadNum; i++)
		{
			lifeiTaskThread_2* pThread = new lifeiTaskThread_2(this);
			pThread->start();
			_threads.push_back(pThread);
		}
	}

	void lifeiTaskSystem_2::destroy()
	{
		for (size_t i = 0; i < _threads.size(); i++)
		{
			_threads[i]->join();
			delete _threads[i];
		}
		_threads.clear();
	}

	void lifeiTaskSystem_2::addTask(lifeiTask_2* task)
	{
		//���Ҫ�����Ƭ��������
		{
			lifeiMutex_2::ScopeLock lk(_mutex);
			_tasks_requestTile.push_back(task);
		}

		//��ʱ���������ˣ������ź���
		_semphore.set(1);
	}

	void lifeiTaskSystem_2::run()
	{
		if ( !_semphore.wait())
		{
			return;
		}

		//ȡ����,������Ƭ���ƽ��м�����Ƭ������texture
		lifeiTask_2 * pTask = 0;
		{
			lifeiMutex_2::ScopeLock lk(_mutex);
			bool taskEmpty = _tasks_requestTile.empty();
			if (taskEmpty)
			{
				return;
			}
			//ȡ����
			pTask = _tasks_requestTile.front();
			_tasks_requestTile.pop_front();
		}

		//ִ�й���
		//֪ͨ����
		if (_observer && pTask)
		{
			_observer->onTaskExe(pTask);   //ת��terrain
			_observer->onTaskFinish(pTask);
		}
	}

}
