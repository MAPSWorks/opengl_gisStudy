#pragma once
#include "CELLMath.hpp"
#include "CELLResourceMgr.hpp"
namespace CELL
{
	class CELLResourceMgr;
	class CELLOpenGL;
	class CELLContext
	{
	public:
		CELLOpenGL * _device;
		//��Դ������ָ��
		CELLResourceMgr* _resMgr;
		//��굱ǰλ��
		int _mouseX;
		int _mouseY;
		//���ڵĴ�С
		int _width;
		int _height;
		//2d��ĻͶӰ����
		matrix4r _screenPrj;

	};

}