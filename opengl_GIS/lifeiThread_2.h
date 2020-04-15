#pragma once
#include "export.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiThread_2 : public lifeiObject_2
	{
	public:
		DWORD		_threadId;
		HANDLE		_thread;

	protected:
		//�߳���ں���
		static unsigned long __stdcall threadEnter(void* ptr);

	public:
		lifeiThread_2();
		virtual ~lifeiThread_2();
		DWORD threadId() const;
		bool isRun() const;
		//�������֪ͨ����
		virtual bool onCreate();
		//�߳�ִ�к���
		virtual bool onRun();
		//��������
		virtual bool onDestroy();
		//�����̺߳���
		virtual bool start();
		//�ȴ��˳�����
		virtual void join();
		//�ر�
		virtual void close();
	};
}