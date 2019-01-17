#include "stdafx.h"
#include "CELLPlatform.hpp"
#include "CELLFrameBigMap.h"
#include "CELLOpenGL.h"

namespace CELL
{
	CELLFrameBigMap::CELLFrameBigMap(CELLContext& context)
		:CELLFrame(context)
	{
	}

	CELLFrameBigMap::~CELLFrameBigMap()
	{
	}
	//开始绘制
	void CELLFrameBigMap::onFrameStart(CELLContext& context)
	{
		context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context._device->clearColor(0, 0, 0, 1);
	}
	//结束绘制
	void CELLFrameBigMap::onFrameEnd(CELLContext& context)
	{

	}
	//更新数据
	void CELLFrameBigMap::update(CELLContext& context)
	{

	}
	//鼠标左键按下
	void CELLFrameBigMap::onLButtonDown(int x, int y)
	{

	}
	//鼠标左键提起
	void CELLFrameBigMap::onLButtonUp(int x, int y)
	{

	}

	//鼠标移动
	void CELLFrameBigMap::onMouseMove(int x, int y)
	{

	}
}

