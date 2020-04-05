#include "lifeiFeaturePoint.h"
namespace CELL
{
	lifeiFeaturePoint::lifeiFeaturePoint(const char* name)
	{
		if (name)
		{
			strncmp(_name, name, sizeof(_name));
		}
		else
		{
			sprintf(_name, "%p", this);
		}
	}

	lifeiFeaturePoint::~lifeiFeaturePoint()
	{
	}

	//��ȡҪ������
	char* lifeiFeaturePoint::getName()
	{
		return _name;
	}

	//��ȡ��ĸ���
	size_t lifeiFeaturePoint::getGroupCount()
	{
		return 0;
	}

	//��ȡ������
	Group* lifeiFeaturePoint::getGroup(size_t index)
	{
		return 0;
	}

	//�õ�ʸ����Χ��
	aabb2dr lifeiFeaturePoint::getAABB()
	{
		return _aabb;
	}

	//���ص�ĸ���
	size_t lifeiFeaturePoint::getPointCount()
	{
		return _points.size();
	}

	//����ָ�������Ϣ
	real2 lifeiFeaturePoint::getPoint(size_t index)
	{
		return _points[index];
	}
}
