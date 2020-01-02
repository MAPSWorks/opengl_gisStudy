#include "lifeiTaskSystem.h"
#include "lifeiTaskThread.h"

namespace CELL
{
	lifeiTaskSystem::lifeiTaskSystem()
	{
		_observer = 0;
		_threads.clear();
	}
	lifeiTaskSystem::~lifeiTaskSystem()
	{
		_threads.clear();
	}
	void lifeiTaskSystem::setObserver(lifeiTaskObserver * observer)
	{
		_observer = observer;
	}
	void lifeiTaskSystem::start(int threadNum)
	{
		destroy();
		for (size_t i = 0; i < threadNum; i++)
		{
			lifeiTaskThread * pThread = new lifeiTaskThread(this);
			pThread->start();
			_threads.push_back(pThread);
		}
	}
	void lifeiTaskSystem::destroy()
	{
		for (int i = 0; i < _threads.size(); i++)
		{
			_threads[i]->join();
			delete _threads[i];
		}
		_threads.clear();
	}
	void lifeiTaskSystem::addTask(CELLTask* task)
	{
		{
			lifeiMutex::ScopeLock lk(_mutex);
			_tasks.push_back(task);
		}
		_semphore.set(1);
	}
	void lifeiTaskSystem::run()
	{
		if (!_semphore.wait())
		{
			return;
		}

		CELLTask* pTask = 0;
		{
			lifeiMutex::ScopeLock lk(_mutex);
			bool taskEmpty = _tasks.empty();
			if (taskEmpty)
			{
				return;
			}
			//ȡ����
			pTask = _tasks.front();
			_tasks.pop_front();
		}
		//2ִ�й���
		//3֪ͨ����
		if (_observer && pTask)
		{
			_observer->onTaskExe(pTask);
			_observer->onTaskFinish(pTask);
		}
	}

}

