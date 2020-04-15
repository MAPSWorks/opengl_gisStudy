#pragma once
#include <vector>
#include "../opengl_GIS/IPluginTileManager.h"
#include "../opengl_GIS/lifeiTileId.h"
#include "../opengl_GIS/lifeiMutex_2.h"
#include "../opengl_GIS/lifeiTask_2.h"

namespace CELL
{
#define KEY_ROW				"row"
#define KEY_REVERSEROW		"rrow"
#define KEY_COL				"col"
#define KEY_REVERSECOL		"rcol"
#define KEY_LEVEL			"lev"
	class tileSoureUserDraw : public IPluginTileManager
	{
	public:
		char _path[1024];
		char _ext[16];
		char _arg0[128];  //ռλ��
		char _arg1[128];
		char _arg2[128];

		HBITMAP _hBitMap;
		HDC _hMemDC;
		void * _pRGBA;
		lifeiMutex_2 _mutex;
	public:
		tileSoureUserDraw();
		~tileSoureUserDraw();
		//���ò���
		virtual void setParam(const char* name, const char* value);
		//��������
		virtual lifeiTask_2 * load(lifeiTask_2* task);
		//ж������
		virtual void unload(lifeiTask_2 * task);

	protected:
		//�ж��Ƿ����������ݣ���http
		bool isHttp(const char* url)
		{
			char szBuf[6];
			strncpy(szBuf, url, 5);
			return _stricmp(url, "http:") == 0 ? true : false;
		}

		int getArg( const char* arg, const lifeiTileId& id);
	};

}

