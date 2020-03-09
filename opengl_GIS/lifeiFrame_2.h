#pragma once

#include "lifeiContext_2.h"
#include "lifeiInput_2.h"

namespace CELL
{
	class lifeiFrame_2 : public lifeiInput_2
	{
	public:
		lifeiContext_2& _context;
		
	public:
		lifeiFrame_2(lifeiContext_2& context)
			: _context(context)
		{
		}

		virtual ~lifeiFrame_2()
		{
		}
		//���س���
		virtual bool loadScene(const char* fileName) = 0;
		//��������
		virtual void update(lifeiContext_2& context) = 0;
		//��ʼ����
		virtual void onFrameStart(lifeiContext_2& context) = 0;
		//��������
		virtual void onFrameEnd(lifeiContext_2& context) = 0;
	};
}
