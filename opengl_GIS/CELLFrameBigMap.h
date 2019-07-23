#pragma once
#include "CELLFrame.hpp"
#include "CELLTimestamp.hpp"
namespace CELL
{
    class CELLFrameBigMap :public CELLFrame
    {
    public:
        CELLTimestamp   _timeStamp;
        aabb3dr         _aabb;
        real3           _basePoint;
        bool            _bLbuttonDown;
        int2            _lbuttonDown;
    public:
        CELLFrameBigMap(CELLContext& context);

        virtual ~CELLFrameBigMap();

        /// <summary>
        /// 更新数据
        /// </summary>
        virtual void    update(CELLContext& context);
        /// <summary>
        /// 开始绘制
        /// </summary>
        virtual void    onFrameStart(CELLContext& context);

        /// <summary>
        /// 结束绘制
        /// </summary>
        virtual void    onFrameEnd(CELLContext& context);

        /// <summary>
        /// 鼠标左键按下
        /// </summary>
        virtual void    onLButtonDown(int x, int y);
        /// <summary>
        /// 鼠标左键提起
        /// </summary>
        virtual void    onLButtonUp(int x, int y);
        /// <summary>
        /// 鼠标移动事件
        /// </summary>
        virtual void    onMouseMove(int x, int y);

        /// <summary>
        /// 鼠标滚轮事件
        /// </summary>
        virtual void    onMouseWheel(int delta);
        /// <summary>
        /// 键盘事件
        /// </summary>
        virtual void    onKeyDown(int key);
        /// <summary>
        /// 键盘事件
        /// </summary>
        virtual void    onKeyUp(int key);
    protected:
        /// <summary>
        /// 返回鼠标点击出射线与场景的交点
        /// </summary>
        bool   getPointsFromScreen(int x,int y,real3& point);

    };

}

