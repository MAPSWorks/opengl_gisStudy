#pragma once
#include "../opengl_GIS/IGIS3DPlatform.h"
namespace CELL
{
	class GoogleMapLoader : public IPluginTileSource
	{
	public:
		GoogleMapLoader();
		~GoogleMapLoader();
		//���ò���
		virtual void setParam(const char* name, const char* value);
		//��������
		virtual CELLTask * load(CELLTask* task);
		//ж������
		virtual void unload(CELLTask * task);
	};

}

