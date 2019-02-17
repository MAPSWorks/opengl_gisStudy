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
	//��ʼ����
	void CELLFrameBigMap::onFrameStart(CELLContext& context)
	{
		context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		context._device->clearColor(1, 0, 0, 1);
	}
	//��������
	void CELLFrameBigMap::onFrameEnd(CELLContext& context)
	{

	}
	//��������
	void CELLFrameBigMap::update(CELLContext& context)
	{
		_context._screenPrj = CELL::ortho<real>(0.0f, (real)_context._width, (real)_context._height, 0, -1000.0f, 1000.0f);
	}
	//����������
	void CELLFrameBigMap::onLButtonDown(int x, int y)
	{

	}
	//����������
	void CELLFrameBigMap::onLButtonUp(int x, int y)
	{

	}

	//����ƶ�
	void CELLFrameBigMap::onMouseMove(int x, int y)
	{

	}
}

