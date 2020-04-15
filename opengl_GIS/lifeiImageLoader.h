#pragma once
#include "lifeiImage.h"
#include "CELLDXTCompressor.h"

namespace CELL
{
	class EXPORTFUNC lifeiImageLoader
	{
	public:
		static bool loadImage(const char* fileName, CELL::lifeiImage& image);

		static bool loadImageBufferToDXT1(const void* data, int len, lifeiImage& image);
		//����png/jpg��ʽ���ݲ�ת����dxt1
		static bool loadImageToDXT1(const char* fileName, lifeiImage& image);
		//RGBA����ת����DXT1
		static bool rgbaBuffertToDXT1(const void* data, int w, int h, lifeiImage& image);
	};
}
