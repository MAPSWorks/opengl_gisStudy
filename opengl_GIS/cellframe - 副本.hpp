#pragma once

#include    "lifeiContext.h"
#include "lifeiInput.h"
namespace   CELL
{

    class   CELLFrame :public lifeiInput
    {
    public:
		lifeiContext&    _context;
    public:
        CELLFrame(lifeiContext& context)
            :_context(context)
        {}
        virtual ~CELLFrame()
        {}
        /// <summary>
        /// ��������
        /// </summary>
        virtual void    update(lifeiContext& context) = 0;
        /// <summary>
        /// ��ʼ����
        /// </summary>
        virtual void    onFrameStart(lifeiContext& context)  =   0;

        /// <summary>
        /// ��������
        /// </summary>
        virtual void    onFrameEnd(lifeiContext& context)  =   0;
    };
}