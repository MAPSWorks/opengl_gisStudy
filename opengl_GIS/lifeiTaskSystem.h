#pragma once
#include "CELLTask.hpp"
#include "lifeiThread.h"
#include <vector>
#include <list>
#include "lifeiSemaphore.h"
#include "lifeiMutex.h"
#include "lifeiTaskObserver.h"
namespace CELL
{
	typedef std::vector<lifeiThread* >	arrayThread;
	typedef std::list<CELLTask*>		arrayTask;
	class lifeiTaskSystem
	{
	public:
		lifeiTaskObserver * _observer;
		arrayThread _threads;
		arrayTask _tasks;
		lifeiSemaphore _semphore;
		lifeiMutex _mutex;
	public:
		lifeiTaskSystem();
		virtual ~lifeiTaskSystem();
	//���ù۲���ָ��
		virtual void setObserver(lifeiTaskObserver * observer);
	public:
	//�����������
		virtual void start(int threadNum = 4);
	//����
		virtual void destroy();
	//��������ӿ�
		virtual void addTask(CELLTask* task);
	public:
		virtual void run();
	};

}