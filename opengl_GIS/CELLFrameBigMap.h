#pragma once
#include "lifeiFrame.h"
#include "lifeiTimeStamp.hpp"
#include "CELLOpenGL.h"
#include "CELLTerrain.h"
#include "lifeiContext.h"
namespace CELL
{
    class CELLFrameBigMap :public lifeiFrame
    {
    public:
        lifeiTimeStamp  _timeStamp;
        aabb3dr         _aabb;
        real3           _basePoint;
        bool            _bLbuttonDown;
        int2            _lbuttonDown;
        Texture2dId     _textureId;
        CELLTerrain     _terrain;
		bool			_bMbuttonDown;
		int2			_mButtonDown;
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

        /// <summary>
        /// ����������
        /// </summary>
        virtual void    onLButtonDown(int x, int y);
        /// <summary>
        /// ����������
        /// </summary>
        virtual void    onLButtonUp(int x, int y);
		//�Ҽ�
		virtual void onRButtonDown(int x, int y);
		virtual void onRButtonUp(int x, int y);
		//�м�
		virtual void onMButtonDown(int x, int y);
		virtual void onMButtonUp(int x, int y);

        /// <summary>
        /// ����ƶ��¼�
        /// </summary>
        virtual void    onMouseMove(int x, int y);

        /// <summary>
        /// �������¼�
        /// </summary>
        virtual void    onMouseWheel(int delta);
        /// <summary>
        /// �����¼�
        /// </summary>
        virtual void    onKeyDown(int key);
        /// <summary>
        /// �����¼�
        /// </summary>
        virtual void    onKeyUp(int key);
    protected:
        /// <summary>
        /// ����������������볡���Ľ���
        /// </summary>
        bool   getPointsFromScreen(int x,int y,real3& point);
		//ƽ�Ƴ���
		void moveScene(const real3& worldPickup, const int2& ofScreen);

    };

}

