
#pragma once
#include <Windows.h>
#include "export.h"

namespace CELL
{

	struct CREATEPARAM
	{
		//�����ھ��
		HWND _hWnd;
	};

	class ILifeiGISPlatform
	{
	public:
		//��ʼ��ƽ̨
		virtual bool initialize() = 0;
		//����
		virtual void unInitialize() = 0;
		//�¼���Ӧ
		virtual LRESULT inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam) = 0;
		//����
		virtual bool loadScene(const char* sceneFile) = 0;
	};

	//ʵ����
	ENGINE_API ILifeiGISPlatform * createPlatform(const CREATEPARAM& param);
	
}