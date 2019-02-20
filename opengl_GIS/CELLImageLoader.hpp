#pragma once
#include "CELLImage.hpp"

namespace CELL
{
	class CELLImageLoader
	{
	public:
		//�����ļ�����ͼ����Ϣ
		static CELLImage* load(const char* fileName);
		static bool loadImage(const char* fileName, CELL::CELLImage& image);
		//����png/jpg��ʽ���ݲ�ת����rgb
		static RgbBuffer* loadRgb_256x256(const char* fileName);
		//����png/jpg��ʽ���ݲ�ת����rgba
		static RgbaBuffer* loadRgba_256x256(const char* fileName);
		//����png/jpg��ʽ���ݲ�ת����rgb
		static bool loadImageToRgb(const char* fileName, CELLImage& image);
		//����png/jpg��ʽ���ݲ�ת����rgba
		static bool loadImageToRgba(const char* fileName, CELLImage& image);
	};
}