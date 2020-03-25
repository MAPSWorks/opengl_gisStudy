#pragma once
#include "lifeiFrame_2.h"
#include "lifeiOpengl.h"
#include "lifeiTimeStamp.hpp"
#include "lifeiTerrain_2.h"
#include "lifeiContext_2.h"

namespace CELL
{
	class lifeiFrameBigMap_2 : public lifeiFrame_2
	{
		lifeiTimeStamp		_timeStamp;
		real3				_basePoint;
		bool				_bLbuttonDown;
		int2				_lbuttonDown;
		lifeiTerrain_2		_terrain;
		bool				_bMbuttonDown;
		int2				_mButtonDown;

	public:
		lifeiFrameBigMap_2(lifeiContext_2& context);
		virtual ~lifeiFrameBigMap_2();

		//���س���
		virtual bool loadScene(const char* fileName);
		//��������
		virtual void update(lifeiContext_2& context);
		//��ʼ����
		virtual void onFrameStart(lifeiContext_2& context);
		//��������
		virtual void onFrameEnd(lifeiContext_2& context);
		//����������
		virtual void onLButtonUp(int x, int y);
		virtual void onLButtonDown(int x, int y);
		//����Ҽ�
		virtual void onRButtonUp(int x, int y);
		virtual void onRButtonDown(int x, int y);
		//�м�
		virtual void onMButtonUp(int x, int y);
		virtual void onMButtonDown(int x, int y);
		//����ƶ��¼�
		virtual void onMouseMove(int x, int y);
		//�������¼�
		virtual void onMouseWheel(int delta);

		//�����¼�
		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);

	protected:
		//����������������볡���Ľ���
		//bool getPointsFromScreen(int x, int y, real3& point);
		//ƽ�Ƴ���
		void moveScene(const real3& worldPickup, const int2& ofScreen);

	};
}