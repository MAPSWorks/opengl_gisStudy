#pragma once
#include "CELLTask.hpp"
#include "lifeiThread.h"
#include <list>
#include "lifeiSemaphore.h"
#include "lifeiMutex.h"
namespace CELL
{

	class CELLTaskObserver
	{
	public:
		//����ִ��֪ͨ
		virtual void onTaskEXE(CELLTask* task) = 0;
		//�������֪ͨ
		virtual void onTaskFinish(CELLTask* task) = 0;		
		//����ȡ��֪ͨ
		virtual void onTaskCancel(CELLTask* task) = 0;
	};
	class CELLTaskSystem
	{
	public:
		class TaskThread : public lifeiThread
		{
		public:
			//�˳���־
			bool _exitFlag;
			CELLTaskSystem* _system;

		public:
			TaskThread( CELLTaskSystem* pSystem)
			{
				_exitFlag = true;
				_system = pSystem;
			}
			//�˳�
			virtual void join()
			{
				_exitFlag = true;
				lifeiThread::join();
			}
			virtual bool onCreate()
			{
				_exitFlag = false;
				return false;
			}
			virtual bool onRun()
			{
				while (!_exitFlag)
				{
					_system->run();
				}
				return false;
			}
			virtual bool onDestroy()
			{
				return false;
			}
		};
		typedef std::vector<lifeiThread* >	arrayThread;
		typedef std::list<CELLTask*>		arrayTask;
	public:
		CELLTaskObserver* _observer;
		arrayThread _threads;
		arrayTask _tasks;
		lifeiSemaphore _semphore;
		lifeiMutex _mutex;
	public:
		CELLTaskSystem()
		{
			_observer = 0;
			_threads.clear();
		}
		virtual~ CELLTaskSystem()
		{
			_threads.clear();
		}

		//���ù۲���ָ��
		virtual void setObserver(CELLTaskObserver* observer)
		{
			_observer = observer;
		}
	public:
		//����������
		virtual void start(int threadNum = 4)
		{
			destroy();
			for (size_t i = 0; i < threadNum; i++)
			{
				TaskThread * pThread = new TaskThread(this);
				pThread->start();
				_threads.push_back(pThread);
			}
		}
		//����
		virtual void destroy()
		{
			for (int i = 0; i < _threads.size(); i++)
			{
				_threads[i]->join();
				delete _threads[i];
			}
			_threads.clear();
		}
		//�������ӿ�
		virtual void addTask(CELLTask* task)
		{
			{
				lifeiMutex::ScopeLock lk(_mutex);
				_tasks.push_back(task);
			}
			
			_semphore.set(1);
		}

	public:
		virtual void run()
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
				//1��ȡ����
				pTask = _tasks.front();
				_tasks.pop_front();
			}

			//2,ִ�й���
			//3,֪ͨ����
			if (_observer && pTask)
			{
				_observer->onTaskEXE(pTask);
				_observer->onTaskFinish(pTask);
			}
		}
	};
}
