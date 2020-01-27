#pragma once
#include "IGIS3DPlatform.h"
#include "CELLWinApp.hpp"
#include "IlifeiGISPlatform.h"

namespace CELL
{
	class CELLGIS3DPlatform : public ILifeiGISPlatform
	{
	protected:
		CREATEPARAM _createParam;
		CELLWinApp* _winApp;
	public:
		CELLGIS3DPlatform(const CREATEPARAM& param);
		~CELLGIS3DPlatform();
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
	ILifeiGISPlatform* createPlatform(const CREATEPARAM& param);
}

