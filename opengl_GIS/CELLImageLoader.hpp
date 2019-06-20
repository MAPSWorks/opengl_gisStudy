#pragma once

#include "CELLImage.hpp"


namespace CELL
{
    class   CELLImageLoader
    {
    public:
        /// <summary>
        /// �����ļ�����ͼ����Ϣ
        /// </summary>
        static  CELLImage*  load(const char* fileName);
        static  bool        loadImage( const char* fileName,CELL::CELLImage& image );
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgb
        /// </summary>
        static  RgbBuffer*  loadRgb_256X256(const char* fileName);
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  RgbaBuffer* loadRgba_256X256(const char* fileName);
 
        /// <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgb
        /// </summary>
        static  bool        loadImageToRgb( const char* fileName,CELLImage& image );
        // <summary>
        /// ����png/jpg��ʽ���ݲ�ת����Rgba
        /// </summary>
        static  bool        loadImageToRgba( const char* fileName,CELLImage& image );
       

    };
}