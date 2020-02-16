#pragma once

#include "lifeiTask_2.h"
#include "lifeiImage.h"
#include "lifeiTileId.h"

namespace CELL
{
	class lifeiQuadTree;
	class lifeiTileTask : public lifeiTask_2 //Ӧ���ǵ�ǰҪ�������Ƭ������
	{
	public:
		lifeiQuadTree * _node;
		lifeiTileId		_tileId;
		lifeiImage		_image;
	};
}
