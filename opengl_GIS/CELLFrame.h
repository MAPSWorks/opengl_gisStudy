#pragma once
#include "CELLContext.h"
namespace CELL
{
	class CELLFrame
	{
	public:
		CELLContext& _context;
	public:
		CELLFrame(CELLContext& context) : 
			_context (context)
		{}
		virtual ~CELLFrame()
		{

		}
		//��ʼ����
		virtual void onFrameStart(CELLContext& context) = 0;
		//��������
		virtual void onFrameEnd(CELLContext& context) = 0;
		//��������
		virtual void update(CELLContext& context) = 0;
	};
}