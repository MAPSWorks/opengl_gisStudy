#pragma once
#include "lifeiFrame.h"
#include "CELLTimestamp.hpp"
namespace CELL
{
    class CELLFrameBigMap :public lifeiFrame
    {
    public:
        CELLTimestamp   _timeStamp;
        aabb3dr         _aabb;
        real3           _basePoint;
        bool            _bLbuttonDown;
        int2            _lbuttonDown;
    public:
		CELLFrameBigMap(lifeiContext& context);

        virtual ~CELLFrameBigMap();

        /// <summary>
        /// ��������
        /// </summary>
		virtual void    update(lifeiContext& context);
        /// <summary>
        /// ��ʼ����
        /// </summary>
		virtual void    onFrameStart(lifeiContext& context);

        /// <summary>
        /// ��������
        /// </summary>
		virtual void    onFrameEnd(lifeiContext& context);


	public:
		//����������
		virtual void onLButtonDown(int x, int y);
		//����������
		virtual void onLButtonUp(int x, int y);
		//����Ҽ�����
		virtual void onRButtonDown(int x, int y);
		//����Ҽ�����
		virtual void onRButtonUp(int x, int y);
		//����м�����
		virtual void onMButtonDown(int x, int y);
		//����м�����
		virtual void onMButtonUp(int x, int y) ;
		//����ƶ��¼�
		virtual void onMouseMove(int x, int y);
		//�������¼�
		virtual void onMouseWheel(int delta);
		//���̰��������¼�
		virtual void onKeyDown(int key);
		//���̰���̧���¼�
		virtual void onKeyUp(int key);
    protected:
        /// <summary>
        /// ����������������볡���Ľ���
        /// </summary>
        bool   getPointsFromScreen(int x,int y,real3& point);

    };

}

