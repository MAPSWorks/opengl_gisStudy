#pragma once

#include "lifeiPlatform.h"
#include "lifeiFrame.h"

namespace CELL
{
	class LifeiApp
	{
	public:
		//�������ں���
		virtual bool createWindow(HWND hParentWnd, int width, int height, INSTANCE hInst) = 0;
		//�������
		virtual lifeiFrame* createFrame() = 0;
		//��ں���
		virtual void main(int argc, char** argv) = 0;
	};
}