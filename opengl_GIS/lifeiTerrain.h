#pragma once

#include "lifeiQuadTree.h"
#include "lifeiContext.h"
#include "lifeiTerrainInterface.h"
#include "lifeiTaskSystem.h"
#include "lifeiTextureMgr.h"

namespace CELL
{
	class IPluginTileManager;

	class lifeiTerrain : public lifeiObject, public lifeiTerrainInterface, public lifeiTaskObserver
	{
	public:
		struct P3U3
		{
			float x, y, z;
			float u, v, w;
		};

		struct FaceIndex
		{
			short x, y, z;
		};
	public:
		typedef std::vector<lifeiTask*>							arrayTask;
		typedef std::map<std::string, lifeiQuadTree*>			mapNode;
		typedef std::vector<P3U3>								arrayVertex;
		typedef std::vector<FaceIndex>							arrayFace;

	public:
		lifeiQuadTree*											_root;
		lifeiContext&											_context;
		lifeiTaskSystem											_taskSystem;
		arrayTask												_tasks;
		lifeiMutex												_mutex;
		mapNode													_nodes;
		arrayVertex												_vertex;
		arrayFace												_faces;
		lifeiTextureMgr											_textureMgr;
		lifeiCounts												_counts;

		IPluginTileManager	*									_tileSourcePlugin;
		HMODULE													_hTileSourceDll;

	public:
		lifeiTerrain(lifeiContext& context);
		~lifeiTerrain();

		//���س���
		virtual bool loadScene(const char* fileName);
		//�����ڵ�
		virtual void initialize();
		//���½ӿ�
		virtual void update(lifeiContext& context);
		//����
		virtual void render(lifeiContext& context);
		//��ȡͳ����Ϣ
		virtual lifeiCounts& getCounts();

		//���Ʒ�ʽ1���������ݴ��
		virtual void renderPackVertex(lifeiContext& context);

	public:
		virtual void request(lifeiQuadTree* node);
		virtual void cancelRequest(lifeiQuadTree* node);
		//�ͷ�����
		virtual void releaseTexture(uint texId);

	public:
		//����ȡ��֪ͨ
		virtual void onTaskCancel(lifeiTask* task);
		//����ִ��֪ͨ
		virtual void onTaskExe(lifeiTask* task);
		//�������֪ͨ
		virtual void onTaskFinish(lifeiTask* task);

	protected:
		void calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes, arrayVertex& vertex);

		IPluginTileManager* createTileSourceDLL(const char* dllFileName);


	};

}