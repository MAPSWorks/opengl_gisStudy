#include "lifeiFeatureLine.h"

namespace CELL
{
	lifeiFeatureLine::lifeiFeatureLine(const char* name)
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

	lifeiFeatureLine::~lifeiFeatureLine()
	{
	}

	//��ȡҪ������
	char* lifeiFeatureLine::getName()
	{
		return _name;
	}

	//��ȡ��ĸ���
	size_t lifeiFeatureLine::getGroupCount()
	{
		return _groups.size();
	}

	//��ȡ������
	Group* lifeiFeatureLine::getGroup(size_t index)
	{
		return &_groups[index];
	}

	//�õ�ʸ����Χ��
	aabb2dr lifeiFeatureLine::getAABB()
	{
		return _aabb;
	}

	//���ص�ĸ���
	size_t lifeiFeatureLine::getPointCount()
	{
		return _points.size();
	}

	//����ָ�������Ϣ
	real2 lifeiFeatureLine::getPoint(size_t index)
	{
		return _points[index];
	}
}
