#pragma once
#include "CELLFrame.h"
namespace CELL
{
	class CELLFrameBigMap : public CELLFrame
	{
	public:
		CELLFrameBigMap(CELLContext& context);
		virtual ~CELLFrameBigMap();
	public:
		//��ʼ����
		virtual void onFrameStart(CELLContext& context);
		//��������
		virtual void onFrameEnd(CELLContext& context);
		//��������
		virtual void update(CELLContext& context);
	};
}

