#pragma once
#include "lifeiImage.h"
#include "CELLDXTCompressor.h"
#include "IGIS3DPlatform.h"

namespace CELL
{
	class EXPORTFUNC lifeiImageLoader
	{
	public:
		static bool loadImage(const char* fileName, CELL::lifeiImage& image);
		//����png/jpg��ʽ���ݲ�ת����dxt1
		static bool loadImageToDXT1(const char* fileName, lifeiImage& image);
	};
}
