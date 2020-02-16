#pragma once
#include "export.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiThread : public lifeiObject_2
	{
	public:
		DWORD			_threadId;
		HANDLE			_thread;

	protected:
		//�߳���ں���
		static unsigned long __stdcall threadEnter(void * ptr)
		{
			lifeiThread* pThis = (lifeiThread *)ptr;
			if (pThis)
			{
				pThis->onCreate();
				pThis->onRun();
				pThis->onDestroy();
			}
			return 0;
		}

	public:
		lifeiThread()
		{
			_thread = 0;
		}
		virtual ~lifeiThread()
		{
			join();
		}
		DWORD threadId() const
		{
			return _threadId;
		}
		bool isRun() const
		{
			return _thread != 0;
		}
		//�������֪ͨ����
		virtual bool onCreate()
		{
			return false;
		}
		//�߳�ִ�к���
		virtual bool onRun()
		{
			return false;
		}
		//��������
		virtual bool onDestroy()
		{
			return false;
		}
		//�����̺߳���
		virtual bool start()
		{
			if (_thread != 0)
			{
				return false;
			}
			else
			{
				_thread = CreateThread(0, 0, &lifeiThread::threadEnter, this, HIGH_PRIORITY_CLASS, &_threadId);
				return true;
			}
		}

		//�ȴ��˳�����
		virtual void join()
		{
			if (_thread)
			{
				WaitForSingleObject(_thread, 0xFFFFFFFF);
				CloseHandle(_thread);
				_thread = 0;
			}
		}
		//�ر�
		virtual void close()
		{
			CloseHandle(_thread);
			_thread = 0;
		}
	};
}
