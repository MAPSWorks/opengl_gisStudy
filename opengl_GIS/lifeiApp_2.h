#pragma once
#include "lifeiFrame.h"
#include <Windows.h>

namespace CELL
{
	class lifeiApp_2
	{
	public:
		//�������ں���
		virtual bool createWindow(HWND hParantWnd, int width, int height, HINSTANCE hInst) = 0;
		//�������
		virtual lifeiFrame* createFrame() = 0;
		//��ں���
		virtual void main(int argc, char** argv) = 0;
	};
}