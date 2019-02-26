#pragma once
#include "CELLFrame.h"
#include "CELLTimestamp.hpp"
#include "CELLMath.hpp"
namespace CELL
{
	class CELLFrameBigMap : public CELLFrame
	{
	public:
		float3 _min;
		double3 _max;
	public:
		CELLTimestamp _timeStamp;
	public:
		CELLFrameBigMap(CELLContext& context);
		virtual ~CELLFrameBigMap();
	public:
		//��ʼ����
		virtual void onFrameStart(CELLContext& context);
		//��������
		virtual void onFrameEnd(CELLContext& context);
		//��������
		virtual void update(CELLContext& context);
		//����������
		virtual void onLButtonDown(int x, int y);
		//����������
		virtual void onLButtonUp(int x, int y);
		//����ƶ�
		virtual void onMouseMove(int x, int y);
		//�������¼�
		virtual void onMouseWheel(int delta);
		//�����¼�
		virtual void onKeyDown(int key);
		//�����¼�
		virtual void onKeyUp(int key);
		//�����Χ������
		template< class T>
		AxisAlignedBox<T> calcAabb(const tvec3<T>* pPos, uint nCount)
		{
			AxisAlignedBox<T> aabb;
			aabb._minimum.x = FLT_MAX;
			aabb._minimum.y = FLT_MAX;
			aabb._minimum.z = FLT_MAX;
			aabb._maximum.x = -FLT_MAX;
			aabb._maximum.y = -FLT_MAX;
			aabb._maximum.z = -FLT_MAX;
			aabb._extent = AxisAlignedBox<T>::EXTENT_FINITE;

			for (int i = 1; i < nCount; i++)
			{
				aabb._minimum.x = MIN(aabb._minimum.x, pPos[i].x);
				aabb._minimum.y = MIN(aabb._minimum.y, pPos[i].y);
				aabb._minimum.z = MIN(aabb._minimum.z, pPos[i].z);
				aabb._maximum.x = MAX(aabb._maximum.x, pPos[i].x);
				aabb._maximum.y = MAX(aabb._maximum.x, pPos[i].y);
				aabb._maximum.z = MAX(aabb._maximum.x, pPos[i].z);
			}
			return aabb;
		}
		//�����Χ������
		template< class T>
		tvec4<T> calcSphere(const tvec3<T>* pPos, uint nCount)
		{
			//�ȼ����Χ��
			AxisAlignedBox<T> aabb = calcAabb(pPos, nCount);
			tvec3<T> center = aabb.getCenter();
			T radius = aabb.getHalfSize();
			return tvec4<T>(center.x, center.y, center.z, radius);
		}

	};
}

