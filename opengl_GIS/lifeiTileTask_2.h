#pragma once
#include "lifeiTask_2.h"
#include "lifeiImage.h"
#include "lifeiTileId.h"

namespace CELL
{
	class lifeiQuadTree_2;
	class lifeiTileTask_2 : public lifeiTask_2 //��ǰҪ�������Ƭ�����ݣ��������ԣ�
	{
	public:
		lifeiQuadTree_2*	_node;
		lifeiTileId		_tileId;
		lifeiImage		_image;
	};
}