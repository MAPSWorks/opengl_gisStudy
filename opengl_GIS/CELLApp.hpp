#pragma once

namespace CELL
{
    class   CELLApp
    {
    public:

        /// �������ں���
        virtual bool    createWindow(int width,int height,HINSTANCE hInst)  =   0;
        ///  ��ں���
        virtual void    main(int argc,char** argv)  =   0;
    };
}