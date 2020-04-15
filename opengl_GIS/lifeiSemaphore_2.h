#pragma once
#include "lifeiObject_2.h"
#include <Windows.h>

namespace CELL
{
	class lifeiSemaphore_2
	{
	protected:
		HANDLE _semaphore;

	public:
		lifeiSemaphore_2(long lMax = 0x7FFFFFFF, long lInit = 1);
		virtual ~lifeiSemaphore_2();
		virtual void create(long lMax = 0x7FFFFFFF, long lInit = 1);
		//�����ź���(�ź���-1��
		virtual bool wait(unsigned long ms = INFINITE);
		//�����ź���
		virtual bool set(long number = 1);
		//����
		virtual void destroy();
	};
}