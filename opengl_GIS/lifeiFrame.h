#pragma once

#include "lifeiContext.h"
#include "lifeiInput.h"

namespace CELL
{
	class lifeiFrame : public lifeiInput
	{
	public:
		lifeiContext&  _context;
	public:
		lifeiFrame(lifeiContext& context)
			: _context(context)
		{

		}
		virtual ~lifeiFrame()
		{

		}
		//��������
		virtual void update(lifeiContext& context) = 0;
		//��ʼ����
		virtual void onFrameStart(lifeiContext& context) = 0;
		//��������
		virtual void onFrameEnd(lifeiContext& context) = 0;
	};
}