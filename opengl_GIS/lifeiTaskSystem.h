#pragma once
#include "lifeiTask_2.h"
#include "lifeiThread_2.h"
#include <vector>
#include <list>
#include "lifeiSemaphore.h"
#include "lifeiMutex.h"
#include "lifeiTaskObserver_2.h"
namespace CELL
{
	typedef std::vector<lifeiThread_2* >	arrayThread;
	typedef std::list<lifeiTask_2*>		arrayTask;
	class lifeiTaskSystem  //Ӧ����Ҫ�������Ƭ�ļ���
	{
	public:
		lifeiTaskObserver_2 * _observer;
		arrayThread _threads;
		arrayTask _tasks;
		lifeiSemaphore _semphore;
		lifeiMutex _mutex;
	public:
		lifeiTaskSystem();
		virtual ~lifeiTaskSystem();
	//���ù۲���ָ��
		virtual void setObserver(lifeiTaskObserver_2 * observer);
	public:
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
