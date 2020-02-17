#pragma once
namespace CELL
{
	class lifeiQuadTree;
	class lifeiCounts
	{
	public:
		unsigned int		_nodes;
		unsigned int		_drawNodes;
		unsigned int		_textCounts;
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
		virtual void request(lifeiQuadTree* node) = 0;
		//ȡ������
		virtual void cancelRequest(lifeiQuadTree* node) = 0;
		//��ȡͳ����Ϣ
		virtual lifeiCounts& getCounts() = 0;
	};
}