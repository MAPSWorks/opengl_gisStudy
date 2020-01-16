#pragma once
#ifdef ENGINE_API_EXP
#define ENGINE_API	declspec(dllexport)
#else
#define ENGINE_API	declspec(dllimport)
#endif

#define EXPORTFUNC	_declspec(dllexport)
#define IMPORTFUNC	_declspec(dllimport)

#include <Windows.h>

namespace CELL
{
	class CELLTask;
	class IPluginTileSource;
	class IGIS3DPlatform;
	class IPlugin
	{
	public:
	};

	#define CREATE_TILESOURCE	"createTileSource"
	typedef IPluginTileSource* (*CREATETILESOURCEFUNC)(IGIS3DPlatform*);

	class IPluginTileSource : public IPlugin
	{
	public:
		//���ò���
		virtual void setParam(const char* name, const char* value) = 0;
		//��������
		virtual CELLTask * load(CELLTask* task) = 0;
		//ж������
		virtual void unload(CELLTask * task) = 0;
	};
	class IGIS3DPlatform
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

	struct CREATEPARAM
	{
		//�����ھ��
		HWND _hWnd;
	};
	//ʵ����
	__declspec(dllexport) IGIS3DPlatform * createPlatform(const CREATEPARAM& param);
}