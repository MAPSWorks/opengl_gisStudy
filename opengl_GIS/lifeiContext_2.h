#pragma once
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH	1024

namespace CELL
{
	class lifeiFrame;
	class lifeiShaderManager_2;
	class lifeiOpenGL;
	class IGISPlatform;
	class lifeiContext_2
	{
	public:
		//ȫ��app
		IGISPlatform*			_app;
		lifeiOpenGL*				_device;
		//shader������ָ��
		lifeiShaderManager_2*		_shaderMgr;
		//���ڵĴ�С
		int							_width;
		int							_height;
		//ÿ֡��������Ҫ��ʱ��
		float						_timePerFrame;
		//2d��ĻͶӰ����
		matrix4r					_screenPrj;
		//�۲����
		lifeiCamera					_camera;
		//mvp
		matrix4r					_mvp;
		matrix4r					_vp;
		//��׶�ü�
		Frustum						_frustum;
		byte						_keyState[256];

	public:
		lifeiContext_2()
		{
			memset(_keyState, 0, sizeof(_keyState));
		}
	};
}