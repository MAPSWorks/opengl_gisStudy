
#pragma once

#include <Windows.h>
#include "IPlugin.h"

namespace CELL
{
	class IGISPlatform;
	class lifeiTask_2;

#define CREATE_TILESOURCEDLL		"createTileSourceDLL"
	
	class IPluginTileManager : public IPlugin
	{
	public:
		//���ò���
		virtual void setParam(const char* name, const char* value) = 0;
		//��������
		virtual lifeiTask_2* load(lifeiTask_2* task) = 0;
		//ж������
		virtual void unload(lifeiTask_2 * task) = 0;

	};
	

	typedef IPluginTileManager *  (*CREATETILESOURCEFUNC)(IGISPlatform*);
	

}
