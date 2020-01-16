#pragma once
#include "CELLMath.hpp"
#include "lifeiObject.h"
#include "lifeiContext.h"
#include "lifeiTerrainInterface.h"
#include "lifeiTileId.h"
#include "AxisALignedBox.h"

namespace CELL
{
	class lifeiQuadTree : public  lifeiObject
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
			FLAG_HAS_IMAGE	= 1 << 0,
			FLAG_HAS_CULL	= 1 << 1,
			FLAG_RENDER		= 1 << 2,
		};
	public:
		typedef std::vector<lifeiQuadTree*> ArrayNode;
	public:
		lifeiTerrainInterface* _terrain;
		//��Ӧ��Ƭid
		 lifeiTileId _tileID;
		//���ݱ�־
		uint	_flag;
		//�������귶Χ
		real2 _vStart;
		real2 _vEnd;

		float2 _uvStart;
		float2 _uvEnd;
		//��Ӧ��Ƭ�ķ�Χ���������꣩
		aabb3dr _aabb;
		//λ��
		ChildID _cornerID;
		//��ǰ��Ƭ�ĸ��ڵ�
		lifeiQuadTree * _parent;
		//����ID
		uint			_textureID;
		//��ǰ��Ƭ�ĺ��ӽڵ�����
		lifeiQuadTree * _childs[4];
	public:
		lifeiQuadTree( 
			lifeiTerrainInterface * pInterface,
			lifeiQuadTree* parent, 
			const real2 vStart, 
			const real2 vEnd,
			int level,
			ChildID corner);
		~lifeiQuadTree();
		//��ȡ�ɼ��ڵ�
		virtual void getAllRenderableNode(ArrayNode& nodes);
		//���½ڵ�
		void update(lifeiContext& context);
		//�ж��Ƿ����ӽڵ㣨ĿǰֻҪ�ж�һ�����ɣ���Ϊһͬ��ӣ�һͬ���٣�
		bool hasChild();
		//�ж��Ƿ����ͼ��
		bool hasImage();
		//�ж��Ƿ���ڱ�־
		bool hasFlag(uint flag)
		{
			return (_flag & flag) ? true : false;
		}
		bool hasNoFlag(uint flag)
		{
			return !hasFlag(flag);
		}
		//�������ݵ���
		virtual void updateTexture(unsigned texID);
	};
}

