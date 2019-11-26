#include "lifeiQuadTree.h"
#include "lifeiSpatialReference.h"

namespace CELL
{
	lifeiQuadTree::lifeiQuadTree(
		lifeiTerrainInterface* pInterface,
		lifeiQuadTree* parent,
		const real2 vStart,
		const real2 vEnd,
		int level,
		ChildID corner)
	{
		lifeiSpatialReference spr;
		_aabb.setExtents(vStart.x, 0, vStart.y, vEnd.x, 0, vEnd.y);
		real3 vXCenter = _aabb.getCenter();
		real2 vlatLon = spr.worldToLongLat(real2(vXCenter.x, vXCenter.z));
		int2 vTileID = spr.getKey(level, vlatLon.x, vlatLon.y);
		_tileID._lev = level;
		_tileID._col = vTileID.x;
		_tileID._row = vTileID.y;
		_cornerID = corner;
		_parent = parent;
		_vStart = vStart;
		_vEnd = vEnd;
		for (int i = 0; i < 4; i++)
		{
			_childs[i] = 0;
		}
		_terrain = pInterface;			
		_uvStart = float2(0, 0);
		_uvEnd = float2(1.0f, 1.0f);

		_flag = 0;
		_flag &= ~FLAG_HAS_IMAGE;
		if (NULL == _parent)
		{
			_textureID = _terrain->createTexture(_tileID);
			if (-1 != _textureID)
			{
				_flag |= FLAG_HAS_IMAGE;
			}
			return;
		}
		//�����С�����ĵ�
		float2 vHalf = (_parent-> _uvEnd - _parent-> _uvStart) * 0.5f;
		float2 vCenter = (_parent-> _uvStart + _parent-> _uvEnd) * 0.5f;
		_textureID = _parent->_textureID;
		switch (corner)
		{
		case CELL::lifeiQuadTree::CHILD_LT:
			_uvStart = float2(vCenter.x - vHalf.x, vCenter.y);
			_uvEnd = float2(vCenter.x, vCenter.y + vHalf.y);
			break;
		case CELL::lifeiQuadTree::CHILD_RT:
			_uvStart = float2(vCenter.x, vCenter.y);
			_uvEnd = float2(vCenter.x + vHalf.x, vCenter.y + vHalf.y);
			break;
		case CELL::lifeiQuadTree::CHILD_LB:
			_uvStart = float2(vCenter.x - vHalf.x, vCenter.y - vHalf.y);
			_uvEnd = float2(vCenter.x, vCenter.y );
			break;
		case CELL::lifeiQuadTree::CHILD_RB:
			_uvStart = float2(vCenter.x , vCenter.y - vCenter.y);
			_uvEnd = float2(vCenter.x + vHalf.x, vCenter.y);
			break;
		default:
			break;
		}
		//����Ǹ��ڵ㣬���޸��ڵ㣩,������Ǹ��ڵ㣬�򿴿��Ƿ������������������ɣ����ø��ڵ������
		_textureID = _parent->_textureID;
		_terrain->request(this);


	}

	lifeiQuadTree::~lifeiQuadTree()
	{
		_terrain->cancelRequest(this);
		if (_textureID != -1 && _flag & FLAG_HAS_IMAGE)
		{
			_terrain->releaseTexture(_textureID);
		}
		for (int i = 0; i < 4; i++)
		{
			if (_childs[i])
			{
				delete _childs[i];
			}
		}
	}

	void lifeiQuadTree::getAllRenderableNode(ArrayNode & nodes)
	{
		bool bHasChild = this->hasChild();
		if (false == bHasChild)
		{
			nodes.push_back(this);
			return;
		}
		//�ݹ��ж��Ƿ���Խڵ��Ƿ�����ӽڵ�
		for (int i = 0; i < 4; i++)
		{
			_childs[i]->getAllRenderableNode(nodes);
		}

	}
	//���ݾ�������Ĳ����ָ�
	void lifeiQuadTree::update(lifeiContext & context)
	{
		lifeiCamera& camera = context._camera;
		real3 vCenter = _aabb.getCenter();
		real3 vSize = _aabb.getSize();
		
		real fSize = vSize.x;
		real dis = CELL::length(vCenter - camera._eye);
		//��Ƭ��С/���룬���������ѷ�

		bool bHasChild = this->hasChild();
		if (dis / fSize < 3 )
		{
			if (!bHasChild && hasImage())
			{
				vSize = _aabb.getHalfSize();
				_childs[CHILD_LT] = new lifeiQuadTree(
					_terrain,
					this,
					real2(vCenter.x - vSize.x, vCenter.z),
					real2(vCenter.x, vCenter.z + vSize.z),
					_tileID._lev + 1,
					CHILD_LT
				);
				_childs[CHILD_RT] = new lifeiQuadTree(
					_terrain,
					this,
					real2(vCenter.x , vCenter.z),
					real2(vCenter.x + vSize.x, vCenter.z + vSize.z),
					_tileID._lev + 1,
					CHILD_RT
				);

				_childs[CHILD_LB] = new lifeiQuadTree(
					_terrain,
					this,
					real2(vCenter.x - vSize.x, vCenter.z - vSize.z),
					real2(vCenter.x, vCenter.z),
					_tileID._lev + 1,
					CHILD_LB
				);

				_childs[CHILD_RB] = new lifeiQuadTree(
					_terrain,
					this,
					real2(vCenter.x, vCenter.z - vSize.z),
					real2(vCenter.x + vSize.x, vCenter.z),
					_tileID._lev + 1,
					CHILD_RB
				);
			}
			else
			{
			//�ݹ��ӽڵ��Ƿ���Էָ�
				for (int i = 0; i < 4; i++)
				{
					if (NULL == _childs[i])
					{
						continue;
					}
					_childs[i]->update(context);
				}
			}

		}
		else
		{
			//�ջ��ӽڵ�
			for (int i = 0; i < 4; i++)
			{
				if (NULL == _childs[i])
				{
					continue;
				}
				delete _childs[i];
				_childs[i] = NULL;
			}
		}

	}

	bool lifeiQuadTree::hasChild()
	{
		return _childs[0] ? true : false;
	}

	bool lifeiQuadTree::hasImage()
	{
		return (_flag & FLAG_HAS_IMAGE) ? true : false;
	}

	void lifeiQuadTree::updateTexture(unsigned texID)
	{
		_textureID = texID;
		_flag |= FLAG_HAS_IMAGE;
		_uvStart = float2(0, 0);
		_uvEnd = float2(1.0f, 1.0f);		
	}

}
