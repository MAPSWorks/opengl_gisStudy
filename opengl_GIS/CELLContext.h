#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class CELLResouceMgr;
	class CELLOpenGL;
	class CELLContext
	{
	public:
		CELLOpenGL * _device;
		//��Դ������ָ��
		CELLResouceMgr* _resMgr;
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