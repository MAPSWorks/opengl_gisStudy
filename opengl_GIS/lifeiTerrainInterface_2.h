#pragma once
namespace CELL
{
	class lifeiQuadTree_2;
	class lifeiCounts
	{
	public:
		unsigned int		_nodes;
		unsigned int		_drawNodes;
		unsigned int		_texCounts;
		unsigned int		_texUsed;
		unsigned int		_texFree;
	};

	class lifeiTerrainInterface_2
	{
	public:
		virtual ~lifeiTerrainInterface_2()
		{}

		//�ͷ�����
		virtual void releaseTexture(unsigned int texID) = 0;
		//��������
		virtual void request(lifeiQuadTree_2* node) = 0;
		//ȡ������
		virtual void cancelRequest(lifeiQuadTree_2* node) = 0;
		//��ȡͳ����Ϣ
		virtual lifeiCounts& getCounts() = 0;
	};
}