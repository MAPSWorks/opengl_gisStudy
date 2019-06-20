#pragma once

namespace CELL
{
    class   CELLInput
    {
    public:
        /// <summary>
        /// ����������
        /// </summary>
        virtual void    onLButtonDown(int x,int y)  =   0;
        /// <summary>
        /// ����������
        /// </summary>
        virtual void    onLButtonUp(int x, int y) = 0;
        /// <summary>
        /// ����ƶ��¼�
        /// </summary>
        virtual void    onMouseMove(int x,int y)    =   0;

        /// <summary>
        /// ����ƶ��¼�
        /// </summary>
        virtual void    onMouseWheel(int delta) = 0;
        /// <summary>
        /// �����¼�
        /// </summary>
        virtual void    onKeyDown(int key)  =   0;
        /// <summary>
        /// �����¼�
        /// </summary>
        virtual void    onKeyUp(int key)    =   0;

    };
}
