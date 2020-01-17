#pragma once
#include "../opengl_GIS/IGIS3DPlatform.h"
namespace CELL
{
	class TMSLoader : public IPluginTileSource
	{
	public:
		char _path[1024];
		char _ext[16];
	public:
		TMSLoader();
		~TMSLoader();
		//���ò���
		virtual void setParam(const char* name, const char* value);
		//��������
		virtual lifeiTask * load(lifeiTask* task);
		//ж������
		virtual void unload(lifeiTask * task);
	};

}

