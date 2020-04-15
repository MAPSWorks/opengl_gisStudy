#pragma once
#include "../opengl_GIS/IPluginTileManager.h"
#include "../opengl_GIS/lifeiTask_2.h"
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
		virtual lifeiTask_2 * load(lifeiTask_2* task);
		//ж������
		virtual void unload(lifeiTask_2 * task);
	};

}

