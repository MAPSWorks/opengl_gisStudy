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
		//开始绘制
		virtual void onFrameStart(CELLContext& context);
		//结束绘制
		virtual void onFrameEnd(CELLContext& context);
		//更新数据
		virtual void update(CELLContext& context);
		//鼠标左键按下
		virtual void onLButtonDown(int x, int y);	
		//鼠标左键提起
		virtual void onLButtonUp(int x, int y);
		//鼠标移动
		virtual void onMouseMove(int x, int y);

	};
}

