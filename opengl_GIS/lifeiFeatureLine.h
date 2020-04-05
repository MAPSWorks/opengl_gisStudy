#pragma once
#include "IFeatureLine.h"
#include "group.h"

namespace CELL
{
	class lifeiFeatureLine : public IFeatureLine
	{
	public:
		typedef std::vector<real2> pointArray;
		typedef std::vector<Group> groupArray;
	public:
		char _name[64];
		groupArray _groups;
		aabb2dr _aabb;
		pointArray _points;
	public:
		lifeiFeatureLine( const char* name);
		~lifeiFeatureLine();

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

