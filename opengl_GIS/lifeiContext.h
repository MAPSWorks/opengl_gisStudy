#pragma once
#include "lifeiPlatform.h"
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH 1024
namespace CELL
{
	class lifeiFrame;
	class lifeiShaderManager;
	class lifeiOpenGL;
	class lifeiGIS3DPlatform;
	class lifeiContext
	{
	public:
		//ȫ�ֵ�app
		lifeiGIS3DPlatform * _app;
		lifeiOpenGL *		_device;
		//shaderָ��
		lifeiShaderManager *_shaderMgr;
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

	public:
		lifeiContext()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
	};
}