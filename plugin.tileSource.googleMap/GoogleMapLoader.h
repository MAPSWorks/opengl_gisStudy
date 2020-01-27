#pragma once
#include "../opengl_GIS/IPluginTileManager.h"
namespace CELL
{
	class GoogleMapLoader : public IPluginTileManager
	{
	public:
		char _path[1024];
		char _ext[16];
	public:
		GoogleMapLoader();
		~GoogleMapLoader();
		//���ò���
		virtual void setParam(const char* name, const char* value);
		//��������
		virtual lifeiTask * load(lifeiTask* task);
		//ж������
		virtual void unload(lifeiTask * task);
	};

}

