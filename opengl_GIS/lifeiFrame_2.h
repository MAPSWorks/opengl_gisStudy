#pragma once

#include "lifeiContext.h"
#include "lifeiInput_2.h"

namespace CELL
{
	class lifeiFrame_2 : public lifeiInput_2
	{
	public:
		lifeiContext& _context;
		
	public:
		lifeiFrame_2(lifeiContext& context)
			: _context(context)
		{
		}

		virtual ~lifeiFrame_2()
		{
		}
		//���س���
		virtual bool loadScene(const char* fileName) = 0;
		//��������
		virtual void update(lifeiContext& context) = 0;
		//��ʼ����
		virtual void onFrameStart(lifeiContext& context) = 0;
		//��������
		virtual void onFrameEnd(lifeiContext& context) = 0;
	};
}