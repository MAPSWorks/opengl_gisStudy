#pragma once
#include "IFeaturePoint.h"
#include "group.h"

namespace CELL
{
	class lifeiFeaturePoint : public IFeaturePoint
	{
	public:
		typedef std::vector<real2> pointArray;
	public:
		char _name[64];
		aabb2dr _aabb;
		pointArray _points;
	public:
		lifeiFeaturePoint(const char* name);
		~lifeiFeaturePoint();

		//��ȡҪ������
		virtual char* getName();
		//�õ�ʸ����Χ��
		virtual aabb2dr getAABB();
		//���ص�ĸ���
		virtual size_t getPointCount();
		//����ָ�������Ϣ
		virtual real2 getPoint(size_t index);
		//��ȡ��ĸ���
		virtual size_t getGroupCount();
		//��ȡ������
		virtual Group* getGroup( size_t index);
	};

}

