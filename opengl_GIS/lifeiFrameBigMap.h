/*
#pragma once
#include "lifeiFrame.h"
#include "lifeiOpengl.h"
#include "lifeiTimeStamp.hpp"
#include "CELLTerrain.h"
#include "lifeiContext.h"

namespace CELL
{
	class lifeiFrameBigMap : public lifeiFrame
	{
		lifeiTimeStamp		_timeStamp;
		real3				_basePoint;
		bool				_bLbuttonDown;
		int2				_lbuttonDown;
		CELLTerrain			_terrain;
		bool				_bMbuttonDown;
		int2				_mButtonDown;

	public:
		lifeiFrameBigMap(lifeiContext& context);
		virtual ~lifeiFrameBigMap();

		//���س���
		virtual bool loadScene(const char* fileName);
		//��������
		virtual void update(lifeiContext& context);
		//��ʼ����
		virtual void onFrameStart(lifeiContext& context);
		//��������
		virtual void onFrameEnd(lifeiContext& context);

		//����������
		virtual void onLButtonUp(int x, int y);
		//�Ҽ�
		virtual void onRButtonDown(int x, int y);
		virtual void onRButtonUp(int x, int y);
		//�м�
		virtual void onMButtonDown(int x, int y);
		virtual void onMButtonUp(int x, int y);

		//����ƶ��¼�
		virtual void onMouseMove(int x, int y);
		//�������¼�
		virtual void onMouseWheel(int delta);
		//�����¼�
		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);
		
	protected:
		//����������������볡���Ľ���
		bool getPointsFromScreen(int x, int y, real3& point);
		//ƽ�Ƴ���
		void moveScene(const real3& worldPickup, const int2& ofScreen);
		
	};
}
*/