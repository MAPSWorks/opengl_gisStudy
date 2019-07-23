#pragma once

#include    "CELLMath.hpp"
#include    "CELLCamera.hpp"
namespace   CELL
{
    class   CELLResourceMgr;
    class   CELLOpenGL;
    class   CELLContext
    {
    public:
        CELLContext()
        {
            memset(_keyState,0,sizeof(_keyState));
        }
        CELLOpenGL*         _device;
        /// ��Դ������ָ��
        CELLResourceMgr*    _resMgr;
        /// ���ĵ�ǰλ��X
        int         _mouseX;
        /// ���ĵ�ǰλ��Y
        int         _mouseY;

        /// ���ڵĴ�С
        int         _width;
        int         _height;
        /// ÿһ֡��������Ҫ��ʱ��
        float       _timePerFrame;
        /// 2d ��ĻͶӰ����
        matrix4r    _screenPrj;
        /// �۲����
        CELLCamera  _camera;
        /// mvp;
        matrix4r    _mvp;
        matrix4r    _vp;

		byte_lf        _keyState[256];

    };
}
