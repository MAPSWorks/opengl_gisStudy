
#pragma once

#include "CELLWinApp.hpp"
#include "IGISPlatform.h"

namespace CELL
{
	class lifeiGIS3DPlatform : public IGISPlatform
	{
	protected:
		CREATEPARAM		_createParam;
		CELLWinApp		* _winApp;

	public:
		lifeiGIS3DPlatform(const CREATEPARAM& param);
		~lifeiGIS3DPlatform();

	public:
		//��ʼ��ƽ̨
		virtual bool initialize();
		//����
		virtual void unInitialize();
		//�¼���Ӧ
		virtual LRESULT inputEvent(HWND hWnd, UINT msgId, WPARAM wParam, LPARAM lParam);
		//����
		virtual bool loadScene(const char* sceneFile);
	};

	IGISPlatform * createPlatform(const CREATEPARAM& param);
}