#pragma once
#ifdef ENGINE_API_EXP
#define ENGINE_API_EXP	declspec(dllexport)
#else
#define ENGINE_API_EXP	declspec(dllimport)
#endif
#include <Windows.h>

namespace CELL
{
	class IGIS3DPlatform
	{
	public:
		//��ʼ��ƽ̨
		virtual bool initialize(HWND hWnd) = 0;
		//����
		virtual void unInitialize() = 0;
	};

	struct CREATEPARAM
	{
		//�����ھ��
		HWND _hWnd;
	};
	//ʵ����
	__declspec(dllexport) IGIS3DPlatform * createPlatform(const CREATEPARAM& param);
}