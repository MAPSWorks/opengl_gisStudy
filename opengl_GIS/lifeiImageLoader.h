#pragma once
#include "lifeiImage.h"
#include "CELLDXTCompressor.h"
#include "IGIS3DPlatform.h"

namespace CELL
{
	class EXPORTFUNC lifeiImageLoader
	{
	public:
		//�����ļ�����ͼ����Ϣ
		static lifeiImage* load(const char* fileName);
		static bool loadImage(const char* fileName, CELL::lifeiImage& image);
		//����png/jpg��ʽ���ݲ�ת��rgb
		static RgbBuffer* loadRgb_256X256(const char* fileName);
		//����png/jpg��ʽ���ݲ�ת����rgba
		static RgbaBuffer* loadRgba_256X256(const char* fileName);
		//����png/jpg��ʽ���ݲ�ת����rgb
		static bool loadImageToRGB(const char* fileName, lifeiImage& image);
		//����png/jpg��ʽ���ݲ�ת����rgba
		static bool loadImageToRGBA(const char* fileName, lifeiImage& image);
		//����png/jpg��ʽ���ݲ�ת����dxt1
		static bool loadImageToDXT1(const char* fileName, lifeiImage& image);
		//����png/jpg��ʽ���ݲ�ת����dxt5
		static bool loadImageToDXT5(const char* fileName, lifeiImage& image);
		

	};
}
