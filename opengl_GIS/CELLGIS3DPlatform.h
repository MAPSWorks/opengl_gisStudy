#pragma once
#include "IGIS3DPlatform.h"
#include "CELLWinApp.hpp"

namespace CELL
{
	class CELLGIS3DPlatform : public IGIS3DPlatform
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
	};
	IGIS3DPlatform* createPlatform(const CREATEPARAM& param);
}

