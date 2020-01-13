#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class lifeiQuadTree;
	class lifeiCounts
	{
	public:
		uint _nodes;
		uint _drawNodes;
		uint _textCounts;
		uint _texUsed;
		uint _texFree;
	};
	class lifeiTerrainInterface
	{
	public:
		virtual ~lifeiTerrainInterface()
		{
		}
		//�ͷ�����
		virtual void releaseTexture(uint texId) = 0;
		//��������
		virtual void request(lifeiQuadTree * node) = 0;
		//�ͷ�����
		virtual void cancelRequest(lifeiQuadTree* node) = 0;
		//��ȡͳ����Ϣ
		virtual lifeiCounts& getCounts() = 0;
	};
}