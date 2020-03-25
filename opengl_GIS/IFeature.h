#pragma once
#include "tvec2.h"
#include "AxisALignedBox.h"
namespace CELL
{
	class Group;
	//ʸ��Ҫ����Ϣ
	class IFeature
	{
	public:
		virtual ~IFeature() {}

		//��ȡҪ������
		virtual char* getName() = 0;

		//�õ�ʸ����Χ��
		virtual aabb2dr getAABB() = 0;
		//���ص�ĸ���
		virtual size_t getPointCount() = 0;
		//����ָ�������Ϣ
		virtual real2 getPoint(size_t index) = 0;
		//��ȡ��ĸ���
		virtual size_t getGroupCount() = 0;
		//��ȡ������
		virtual Group* getGroup() = 0;
	};

}