#pragma once
#include "CELLPlatform.hpp"
#include "CELLObject.hpp"
#if CELL_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class CELLThread : public CELLObject
	{
	public:
		DWORD _threadId;
		HANDLE _thread;
	public:
		CELLThread()
		{
			_thread = 0;
		}
	
		virtual ~CELLThread()
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
			if (_thread != 0 )
			{
				return false;
			}
			else
			{
				_thread = CreateThread(0, 0, &CELLThread::threadEnter, this, HIGH_PRIORITY_CLASS, &_threadId);
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
	protected:
		//�߳���ں���
		static unsigned long __stdcall threadEnter(void * pVoid)
		{
			CELLThread * pThis = (CELLThread*)pVoid;
			if (pThis)
			{
				pThis->onCreate();
				pThis->onRun();
				pThis->onDestroy();
			}
			return 0;
		}

	private:

	};


}
#endif