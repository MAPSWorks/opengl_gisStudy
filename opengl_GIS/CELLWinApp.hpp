#pragma once

#include    "CELLApp.hpp"
#include    <windows.h>
#include    <tchar.h>
#include "CELLGLContext.h"

namespace CELL
{
    class CELLWinApp :public CELLApp
    {
    public:
        HWND    _hWnd;
		CELLGLContext _context;
    public:
        CELLWinApp()
        {
            _hWnd   =   0;
        }
    public:
        /// �������ں���
        virtual bool    createWindow(int width, int height,HINSTANCE hInst)
        {
            /// 1.ע�ᴰ����
            /// 2.��������
            /// 3.������ʾ

            WNDCLASSEXW wcex;

            wcex.cbSize         =   sizeof(WNDCLASSEX);

            wcex.style          =   CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc    =   wndProc;
            wcex.cbClsExtra     =   0;
            wcex.cbWndExtra     =   0;
            wcex.hInstance      =   hInst;
            wcex.hIcon          =   0;
            wcex.hCursor        =   LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground  =   (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName   =   0;
            wcex.lpszClassName  =   _T("CELL.BigMap");
            wcex.hIconSm        =   0;
            RegisterClassExW(&wcex);
            /// ��������
            _hWnd   =   CreateWindow(
                                      _T("CELL.BigMap")
                                    , _T("BigMap")
                                    , WS_OVERLAPPEDWINDOW
                                    , CW_USEDEFAULT
                                    , 0
                                    , CW_USEDEFAULT
                                    , 0
                                    , nullptr
                                    , nullptr
                                    , hInst
                                    , nullptr);
            if (_hWnd == 0 )
            {
                return  false;
            }

            ShowWindow(_hWnd,SW_SHOW);
            UpdateWindow(_hWnd);

			HDC hDC = GetDC(_hWnd);
			if (!_context.Init(_hWnd, hDC))
			{
				DestroyWindow(_hWnd);
				return false;
			}
			return true;
        }
        ///  ��ں���
        virtual void    main(int argc, char** argv)
        {
            MSG msg =   {0};
            // ����Ϣѭ��: 
            while (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
			_context.shutdown();
        }
    protected:
        static  LRESULT CALLBACK  wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_COMMAND:
                break;
            case WM_PAINT:
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
                    EndPaint(hWnd, &ps);
                }
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            return 0;
        }
    };

}
