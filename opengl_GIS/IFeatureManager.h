#pragma once
#include <vector>
#include "AxisALignedBox.h"
//ʸ��ͼ��
namespace CELL
{
	class IFeature;
	typedef std::vector<IFeature*> arrayFeature;
	class ILayer
	{
	public:
		//�õ�ʸ��Ҫ�ظ���
		virtual size_t getFeatureCount() = 0;
		//�õ�ʸ��Ҫ��
		virtual IFeature* getFeature(size_t index) = 0;
		//��ͼ�����ʸ��Ҫ��
		virtual void addFeature(IFeature* feature) = 0;
		//ɾ��ʸ��Ҫ��
		virtual void removeFeature( IFeature* feature) = 0;
		//�Ƴ�����ʸ��Ҫ��
		virtual void removeAllFeatures() = 0;
		//ɾ������ʸ��Ҫ��
		virtual void destroyAllFeatures() = 0;
		//����ʸ��Ҫ�����Ʋ�ѯ
		virtual IFeature* query(const char* name) = 0;
		//���ݾ�γ�ȷ�Χ����ʸ��Ҫ��
		virtual size_t query(const CELL::aabb3dr& aabb, arrayFeature& features) = 0;
	};

}

