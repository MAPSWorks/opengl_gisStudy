#pragma once
#include "lifeiApp_2.h"
#include <Windows.h>
#include <tchar.h>
#include "lifeiGLContext.h"
#include "lifeiOpengl.h"
#include "lifeiFrameBigMap_2.h"
#include "lifeiContext_2.h"
#include "lifeiThread_2.h"
#include "lifeiEvent_2.h"
#include "lifeiShaderManager_2.h"
#include <assert.h>

namespace CELL
{
	class lifeiWinApp_2 : public lifeiApp_2, public lifeiThread_2
	{
	public:
		HWND					_hParentWnd;
		LifeiGLContext			_contextGL;
		lifeiContext_2			_context;
		lifeiShaderManager_2	_shaderMgr;
		lifeiOpenGL				_device;
		lifeiFrame_2	*		_frame;
		bool					_threadRun;
		bool					_makeResult;
		lifeiEvent_2			_event;

	public:
		lifeiWinApp_2();
		//�������ں���
		virtual bool createWindow(HWND hParentWnd, int width, int height, HINSTANCE hInst);
		//��ʼ��������
		void initContext();
		//�������
		virtual lifeiFrame_2* createFrame();		
		//��ں���
		virtual void main(int argc, char** argv);
		//���ƺ���
		virtual void render();
		//�������֪ͨ����
		virtual bool onCreate();
		//�߳�ִ�к���
		virtual bool onRun();
		//��������
		virtual bool onDestroy();
		//�¼�
		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	};
}