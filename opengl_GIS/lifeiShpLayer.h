#pragma once
#include "ILayer.h"
#include "shp/shapefil.h"
#include "AxisALignedBox2d.h"

namespace CELL
{
	class lifeiShpLayer : public ILayer
	{
	public:
		//�������е�Ҫ������
		arrayFeature _features;

	public:
		//����shp�ļ�
		virtual bool loadShp(const char* shpName);
		//�õ�ʸ��Ҫ�ظ���
		virtual size_t getFeatureCount();
		//�õ�ʸ��Ҫ��
		virtual IFeature* getFeature(size_t index);
		//��ͼ�����ʸ��Ҫ��
		virtual void addFeature(IFeature* feature);
		//ɾ��ʸ��Ҫ��
		virtual void removeFeature(IFeature* feature);
		//�Ƴ�����ʸ��Ҫ��
		virtual void removeAllFeatures();
		//ɾ������ʸ��Ҫ��
		virtual void destroyAllFeatures();
		//����ʸ��Ҫ�����Ʋ�ѯ
		virtual IFeature* query(const char* name);
		//���ݾ�γ�ȷ�Χ����ʸ��Ҫ��
		virtual size_t query(const CELL::aabb2dr& aabb, arrayFeature& features);
	};
}
