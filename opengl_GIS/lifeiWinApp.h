
#pragma once
#include "lifeiApp_2.h"
#include <Windows.h>
#include <tchar.h>
#include "lifeiGLContext.h"
#include "lifeiOpengl.h"
#include "lifeiFrameBigMap.h"
#include "lifeiContext.h"
#include "lifeiThread_2.h"
#include "lifeiEvent_2.h"
#include "lifeiShaderManager_2.h"
#include <assert.h>

namespace CELL
{
	class lifeiWinApp : public lifeiApp_2, public lifeiThread_2
	{
	public:
		HWND					_hParentWnd;
		LifeiGLContext			_contextGL;
		lifeiContext			_context;
		lifeiShaderManager_2	_shaderMgr;
		lifeiOpenGL				_device;
		lifeiFrame_2	*		_frame;
		bool					_threadRun;
		bool					_makeResult;
		lifeiEvent_2			_event;

	public:
		lifeiWinApp()
		{
			_hParentWnd	= 0;
			_frame = 0;
			_threadRun = true;
			_makeResult = false;
			_context._device = &_device;
			_context._shaderMgr = &_shaderMgr;

		}

	public:
		//�������ں���
		virtual bool createWindow(HWND hParentWnd, int width, int height, HINSTANCE hInst)
		{
			_hParentWnd = hParentWnd;
			HDC hDC = GetDC(_hParentWnd);
			bool bInitContextGL = _contextGL.init(_hParentWnd, hDC);
			return bInitContextGL;
		}

		//��ʼ��������
		void initContext()
		{
			_context._device->initialize();
			_context._shaderMgr->initialize(_context._device);

			if (IsWindow(_hParentWnd))
			{
				RECT rect;
				GetClientRect(_hParentWnd, &rect);
				_context._width = rect.right - rect.left;
				_context._height = rect.bottom - rect.top;
			}
			else
			{
				_context._width = 64;
				_context._height = 64;
			}
		}
	
		//�������
		virtual lifeiFrame_2* createFrame()
		{
			return new lifeiFrameBigMap(_context);
		}

		//��ں���
		virtual void main(int argc, char** argv)
		{
			initContext();
			_frame = createFrame();

			//��������̵߳İ�
			_contextGL.makeCurrentNone();

			if ( 0 == _frame)
			{
				return;
			}

			//����opengl�������봰�ڰ󶨣�Ȼ��һ�߷���eventʱ���źţ���������������У�һ������߳���Ⱦ��
			lifeiThread_2::start();
			_event.wait();

			if (!_makeResult)
			{
				lifeiThread_2::join();
				delete _frame;
				_contextGL.shutdown();
				return;
			}
		}
	
		//���ƺ���
		virtual void render()
		{
			if ( 0 == _frame)
			{
				return;
			}
			_frame->update(_context);
			_frame->onFrameStart(_context);
			_frame->onFrameEnd(_context);
			_contextGL.swapBuffer();
		}

		//�������֪ͨ����
		virtual bool onCreate()
		{
			_makeResult = _contextGL.makeCurrent();
			assert(_makeResult);
			_event.set();
			return _makeResult;
		}

		//�߳�ִ�к���
		virtual bool onRun()
		{
			while (_threadRun)
			{
				render();
			}
			return false;
		}

		//��������
		virtual bool onDestroy()
		{
			_contextGL.shutdown();
			return false;
		}

	public:
		LRESULT eventProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			switch (message)
			{
			case WM_LBUTTONDOWN:
				_frame->onLButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_LBUTTONUP:
				_frame->onLButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_RBUTTONDOWN:
				_frame->onRButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_RBUTTONUP:
				_frame->onRButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MBUTTONDOWN:
				_frame->onMButtonDown(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MBUTTONUP:
				_frame->onMButtonUp(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MOUSEMOVE:
				_frame->onMouseMove(LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MOUSEWHEEL:

				_frame->onMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));
				break;
			case WM_KEYDOWN:
				_frame->onKeyDown(wParam);
				break;
			case WM_KEYUP:
				_frame->onKeyUp(wParam);
				break;
			case WM_PAINT:
			{
							 PAINTSTRUCT ps;
							 HDC hdc = BeginPaint(hWnd, &ps);
							 EndPaint(hWnd, &ps);
			}
				break;
			case WM_SIZE:
			{
							if (IsWindow(_hParentWnd))
							{
								RECT    rect;
								GetClientRect(_hParentWnd, &rect);
								_context._width = rect.right - rect.left;
								_context._height = rect.bottom - rect.top;
							}
			}
				break;
			case WM_DESTROY:
				_threadRun = false;
				lifeiThread_2::join();
				PostQuitMessage(0);
				break;
			default:
				return  DefWindowProc(hWnd, message, wParam, lParam);
			}
			return  S_OK;

		}
	};
}

