#pragma once
#include "lifeiPlatform.h"
#include "CELLMath.hpp"
#include "lifeiCamera.h"
#include "lifeiFrustum.h"

#define CELL_PATH_LENGTH 1024
namespace CELL
{
	class CELLFrame;
	class CELLResourceMgr;
	class CELLOpenGL;
	class CELLGIS3DPlatform;
	class lifeiContext
	{
	public:
		//ȫ�ֵ�app
		CELLGIS3DPlatform * _app;
		//���
		CELLFrame *			_frame;
		CELLOpenGL *		_device;
		//��Դ������ָ��
		CELLResourceMgr *	_resMgr;
		//����ʱĿ¼
		char				_pathEXE[CELL_PATH_LENGTH];
		//��ԴĿ¼
		char				_pathRes[CELL_PATH_LENGTH];
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