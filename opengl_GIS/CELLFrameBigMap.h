#pragma once
#include "CELLFrame.h"
#include "CELLTimestamp.hpp"
#include "CELLMath.hpp"
namespace CELL
{
	struct Vertex
	{
		float3 _pos;
		Rgba4Byte _color;
		float3 _nor;
	};
	class CELLFrameBigMap : public CELLFrame
	{
	public:
		float _rot;
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
		AxisAlignedBox<T> calcAabb(const tvec3<T>* pPos, uint nCount, uint stride )
		{
			char * pData = (char*)pPos;
			tvec3<T>* pCur = (tvec3<T>*)pPos;
			AxisAlignedBox<T> aabb;
			aabb._minimum.x = FLT_MAX;
			aabb._minimum.y = FLT_MAX;
			aabb._minimum.z = FLT_MAX;
			aabb._maximum.x = -FLT_MAX;
			aabb._maximum.y = -FLT_MAX;
			aabb._maximum.z = -FLT_MAX;
			aabb._extent = AxisAlignedBox<T>::EXTENT_FINITE;

			for (uint i = 0; i < nCount; i++)
			{
				pData += stride;
				pCur = (tvec3<T>*) pCur;
				aabb._minimum.x = MIN(aabb._minimum.x, pCur[i].x);
				aabb._minimum.y = MIN(aabb._minimum.y, pCur[i].y);
				aabb._minimum.z = MIN(aabb._minimum.z, pCur[i].z);
				aabb._maximum.x = MAX(aabb._maximum.x, pCur[i].x);
				aabb._maximum.y = MAX(aabb._maximum.x, pCur[i].y);
				aabb._maximum.z = MAX(aabb._maximum.x, pCur[i].z);
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

