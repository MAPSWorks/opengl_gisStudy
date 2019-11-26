#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class lifeiQuadTree;
	class lifeiTerrainInterface
	{
	public:
		virtual ~lifeiTerrainInterface()
		{
		}
		//��������
		virtual uint createTexture(const TileId& id) = 0;
		//�ͷ�����
		virtual void releaseTexture(uint texId) = 0;
		//��������
		virtual void request(lifeiQuadTree * node) = 0;
		//�ͷ�����
		virtual void cancelRequest(lifeiQuadTree* node) = 0;
	};
}