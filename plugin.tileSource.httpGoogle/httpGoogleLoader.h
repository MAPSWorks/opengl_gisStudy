#pragma once
#include <vector>
#include "CELLHttpClient.h"
#include "../opengl_GIS/IPluginTileManager.h"

namespace CELL
{
	class httpGoogleLoader : public IPluginTileManager
	{
	public:
		char _path[1024];
		char _ext[16];
	public:
		httpGoogleLoader();
		~httpGoogleLoader();
		//���ò���
		virtual void setParam(const char* name, const char* value);
		//��������
		virtual lifeiTask * load(lifeiTask* task);
		//ж������
		virtual void unload(lifeiTask * task);

	protected:
		//����url(http)��������
		bool getImageData(const char* url, std::vector<char>& arBuf);

	};

}

