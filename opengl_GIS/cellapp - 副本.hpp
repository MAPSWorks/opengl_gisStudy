#pragma once

#include "lifeiPlatform.h"
#include "lifeiFrame.h"

namespace CELL
{
    class   CELLApp
    {
    public:

        /// �������ں���
        virtual bool        createWindow(int width,int height,INSTANCE hInst)  =   0;
        /// <summary>
        /// �������
        /// </summary>
        virtual lifeiFrame*  createFrame()   =   0;
        ///  ��ں���
        virtual void        main(int argc,char** argv)  =   0;
    };
}
