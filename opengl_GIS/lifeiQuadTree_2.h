#pragma once

#include "lifeiObject_2.h"
#include "lifeiContext_2.h"
#include "lifeiTerrainInterface_2.h"
#include "lifeiTileId.h"
#include "AxisALignedBox.h"

namespace CELL
{
	class lifeiQuadTree_2 : public lifeiObject_2
	{
	public:
		enum ChildID
		{
			CHILD_LT,
			CHILD_RT,
			CHILD_LB,
			CHILD_RB,
		};
		enum  
		{
			FLAG_HAS_IMAGE = 1 << 0,
			FLAG_HAS_CULL = 1 << 1,
			FLAG_RENDER	= 1 << 2,	
		};

	public:
		typedef std::vector<lifeiQuadTree_2*> arrayNode;

	public:
		lifeiTerrainInterface_2* _terrain;
		//��Ӧ��ƬID
		lifeiTileId	_tileID;
		//���ݱ�־
		uint _flag;
		//�������귶Χ
		real2	_startXY;
		real2	_endXY;

		//��ά����������ڸ��ڵ��uv���꣨���ڵ���ʼUV��0��0������ֹUV��1��1����
		float2	_uvStart;
		float2	_uvEnd;

		//��Ӧ��Ƭ�ķ�Χ(�������꣩
		aabb3dr	_aabb;
		//��ǰ��Ƭ�ĸ��ڵ�
		lifeiQuadTree_2 * _parent;
		//����ID
		uint	_textureID;
		//��ǰ��Ƭ�ĺ��ӽڵ�����
		lifeiQuadTree_2* _childs[4];

	public:
		lifeiQuadTree_2(lifeiTerrainInterface_2* pInterface,
			lifeiQuadTree_2* parent,
			const real2	startXY,
			const real2 endXY,
			int level,
			ChildID corner
		);
		~lifeiQuadTree_2();
		//��ȡ�ɼ��ڵ�
		virtual void getAllRenderableNode(arrayNode& nodes);
		//���½ڵ�,���ݾ�������Ĳ����ָ�
		void update(lifeiContext_2& context);
		//�ж��Ƿ����ӽڵ㣨ĿǰֻҪ�ж�һ�����ɣ���Ϊһͬ��ӣ�һͬ����)
		bool hasChild();
		//�ж��Ƿ����ͼ��
		bool hasImage();
		//�ж��Ƿ���ڱ�־
		bool hasFlag(uint flag);
		//�ж��Ƿ�û�б�־
		bool hasNoFlag(uint flag);
		//�������ݵ���
		virtual void updateTexture(unsigned texID);

	};
}
