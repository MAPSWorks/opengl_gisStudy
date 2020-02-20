#include "lifeiQuadTree_2.h"
#include "lifeiSpatialReference.h"

namespace CELL
{
	lifeiQuadTree_2::lifeiQuadTree_2(lifeiTerrainInterface_2 * pInterface, lifeiQuadTree_2 * parent, const real2 vStart, const real2 vEnd, int level, ChildID corner)
	{
		_aabb.setExtents(vStart.x, 0, vStart.y, vEnd.x, 0, vEnd.y);
		real3 vXCenter = _aabb.getCenter();
		lifeiSpatialReference spr;
		real2 vWorld = spr.worldToLongLat(real2(vXCenter.x, vXCenter.z));
		int2 vTileID = spr.getKey(level, vWorld.x, vWorld.y);
		_tileID._lev = level;
		_tileID._col = vTileID.x;
		_tileID._row = vTileID.y;
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
		_terrain->getCounts()._nodes++;
		_flag = 0;
		_flag &= ~FLAG_HAS_IMAGE;
		//���Ĳ����ڵ����û�и��ڵ㣬˵����ǰ�Ĳ����ڵ�Ϊ���ڵ㣬Ҫ���ȡ���ڵ�
		if (NULL == parent)
		{
			_terrain->request(this);
			return;
		}

		//�����С�����ĵ�
		float2 vHalf = (_parent->_uvEnd - _parent->_uvStart) * 0.5f;
		float2 vCenter = (_parent->_uvStart + _parent->_uvEnd) * 0.5f;
		_textureID = _parent->_textureID;
		switch (corner)
		{
		case CELL::lifeiQuadTree_2::CHILD_LT:
			_uvStart = float2(vCenter.x - vHalf.x, vCenter.y);
			_uvEnd = float2(vCenter.x, vCenter.y + vHalf.y);
			break;

		case CELL::lifeiQuadTree_2::CHILD_RT:
			_uvStart = float2(vCenter.x, vCenter.y);
			_uvEnd = float2(vCenter.x + vHalf.x , vCenter.y + vHalf.y);
			break;

		case CELL::lifeiQuadTree_2::CHILD_LB:
			_uvStart = float2(vCenter.x - vHalf.x, vCenter.y - vHalf.y);
			_uvEnd = float2(vCenter.x, vCenter.y);
			break;

		case CELL::lifeiQuadTree_2::CHILD_RB:
			_uvStart = float2(vCenter.x, vCenter.y - vHalf.y);
			_uvEnd = float2(vCenter.x + vHalf.x, vCenter.y);
			break;
		default:
			break;
		}

		if (_parent->hasFlag(FLAG_HAS_IMAGE))
		{
			_flag |= FLAG_RENDER;
		}

		//������Ǹ��ڵ㣬�򿴿��Ƿ������������������ɣ����ø��ڵ������
		_textureID = _parent->_textureID;
		_terrain->request(this);
	}

	lifeiQuadTree_2::~lifeiQuadTree_2()
	{
		_terrain->cancelRequest(this);
		_terrain->getCounts()._nodes--;
		if (_textureID != -1 && _flag & FLAG_HAS_IMAGE )
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

	void lifeiQuadTree_2::getAllRenderableNode(arrayNode & nodes)
	{
		if (hasChild())
		{
			_childs[0]->getAllRenderableNode(nodes);
			_childs[1]->getAllRenderableNode(nodes);
			_childs[2]->getAllRenderableNode(nodes);
			_childs[3]->getAllRenderableNode(nodes);
		}
		else
		{
			if (hasFlag(FLAG_RENDER))
			{
				nodes.push_back(this);
			}
		}
	}

	void lifeiQuadTree_2::update(lifeiContext & context)
	{
		//�жϰ�Χ���Ƿ������������׶�ཻ
		CELL::real minX = _aabb._minimum.x;
		CELL::real maxX = _aabb._maximum.x;
		CELL::real minY = _aabb._minimum.y;
		CELL::real maxY = _aabb._maximum.y;
		CELL::real minZ = _aabb._minimum.z;
		CELL::real maxZ = _aabb._maximum.z;

		bool bIntersect = context._frustum.cubeInFrustum(minX, maxX, minY, maxY, minZ, maxZ);
		if ( bIntersect)
		{
			_flag &= ~FLAG_HAS_CULL;
		}
		else
		{
			_flag |= FLAG_HAS_CULL;
		}

		//�����Χ�����ĵ��������λ��,
		lifeiCamera& camera = context._camera;
		real3 vCenter = _aabb.getCenter();
		real3 vSize = _aabb.getSize();

		real fSize = vSize.x;
		real dis = CELL::length(vCenter - camera._eye);
		//��Ƭ��С/���룬���������ѷ�
		bool bHasChild = this->hasChild();
		if (dis / fSize < 3.0 && hasNoFlag(FLAG_HAS_CULL))
		{
			if (!bHasChild && hasImage())
			{
				vSize = _aabb.getHalfSize();
				_childs[CHILD_LT] = new lifeiQuadTree_2(
					_terrain,
					this,
					real2(vCenter.x - vSize.x, vCenter.z),
					real2(vCenter.x, vCenter.z + vSize.z),
					_tileID._lev + 1,
					CHILD_LT
					);
				_childs[CHILD_RT] = new lifeiQuadTree_2(
					_terrain,
					this,
					real2(vCenter.x, vCenter.z),
					real2(vCenter.x + vSize.x, vCenter.z + vSize.z),
					_tileID._lev + 1,
					CHILD_RT
				);
				_childs[CHILD_LB] = new lifeiQuadTree_2(
					_terrain,
					this,
					real2(vCenter.x - vSize.x, vCenter.z - vSize.z),
					real2(vCenter.x, vCenter.z ),
					_tileID._lev + 1,
					CHILD_LB
				);

				_childs[CHILD_RB] = new lifeiQuadTree_2(
					_terrain,
					this,
					real2(vCenter.x , vCenter.z - vSize.z),
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
					if (_childs[i] && hasNoFlag(FLAG_HAS_CULL))
					{
						_childs[i]->update(context);
					}
					else
					{
						_flag &= FLAG_RENDER;
					}
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

	bool lifeiQuadTree_2::hasChild()
	{
		return _childs[0] ? true : false;
	}

	bool lifeiQuadTree_2::hasImage()
	{
		return (_flag & FLAG_HAS_IMAGE) ? true : false;
	}

	bool lifeiQuadTree_2::hasFlag(uint flag)
	{
		return (_flag & flag) ? true : false;
	}

	bool lifeiQuadTree_2::hasNoFlag(uint flag)
	{
		return !hasFlag(flag);
	}

	void lifeiQuadTree_2::updateTexture(unsigned texID)
	{
		_textureID = texID;
		_flag |= FLAG_HAS_IMAGE;
		_flag |= FLAG_RENDER;
		_uvStart = float2(0, 0);
		_uvEnd = float2(1.0f, 1.0f);
	}

}
