#pragma once
#include "lifeiPlatform.h"
#include "CELLMath.hpp"
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH 1024
namespace CELL
{
	class lifeiFrame;
	class lifeiShaderManager;
	class lifeiOpenGL;
	class CELLGIS3DPlatform;
	class lifeiContext
	{
	public:
		//ȫ�ֵ�app
		CELLGIS3DPlatform * _app;
		lifeiOpenGL *		_device;
		//shaderָ��
		lifeiShaderManager *_shaderMgr;
		//���ĵ�ǰλ��
		int					_mouseX;
		//���ĵ�ǰλ��
		int					_mouseY;
		//���ڵĴ�С
		int					_width;
		int					_height;
		//ÿһ֡��������Ҫ��ʱ��
		float				_timePerFrame;
		//2d��ĻͶӰ����
		matrix4r			_screenPrj;
		//�۲����
		lifeiCamera			_camera;
		//mvp
		matrix4r			_mvp;
		matrix4r			_vp;
		//��׶�ü�
		Frustum				_frustum;
		byte				_keyState[256];
		lifeiContext()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
	};
}