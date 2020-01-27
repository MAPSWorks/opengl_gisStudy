#pragma once

#include    "lifeiQuadTree.h"
#include    "lifeiContext.h"
#include    "lifeiTerrainInterface.h"
#include    "lifeiTaskSystem.h"
#include    "lifeiTextureMgr.h"

namespace   CELL
{
	class IPluginTileManager;
    class CELLTerrain 
        :public lifeiObject
        ,public lifeiTerrainInterface
        ,public lifeiTaskObserver
    {
    public:
        struct  P3U3
        {
            float x, y, z;
            float u, v, w;
        };

        struct  FaceIndex
        {
            short   x,y,z;
        };
    public:
        typedef std::vector<lifeiTask*>  ArrayTask;
        typedef std::map<std::string,lifeiQuadTree*>     MapNode;
        typedef std::vector<P3U3>                       ArrayVertex;
        typedef std::vector<FaceIndex>                  ArrayFace;
    public:
		lifeiQuadTree*   _root;
        lifeiContext&    _context;
        lifeiTaskSystem  _taskSystem;
        ArrayTask       _tasks;
        lifeiMutex       _mutex;
        MapNode         _nodes;
        ArrayVertex     _vertex;
        ArrayFace       _facees;
        lifeiTextureMgr  _textureMgr;
        lifeiCounts          _counts;

		IPluginTileManager * _tileSourcePlugin;
		HMODULE				_hTileSourceDll;
    public:
        CELLTerrain(lifeiContext& context);
        ~CELLTerrain();

		//���س���
		virtual bool loadScene(const char* fileName);
        /// <summary>
        /// �����ڵ�
        /// </summary>
        virtual void    initailze();
        /// <summary>
        /// ���½ӿ�
        /// </summary>
        virtual void    update(lifeiContext& context);
        /// <summary>
        /// ����
        /// </summary>
        virtual void    render(lifeiContext& context);
        /// <summary>
       /// ��ȡͳ����Ϣ
       /// </summary>

        virtual lifeiCounts& getCounts();
        /// <summary>
        /// ���Ʒ�ʽ1,�������ݴ��
        /// </summary>
        virtual void    renderPackVertex(lifeiContext& context);

    public:
        /// <summary>
        /// �ͷ�����
        /// </summary>
        virtual void    request(lifeiQuadTree* node);
        /// <summary>
        /// �ͷ�����
        /// </summary>
        virtual void    cancelRequest(lifeiQuadTree* node);

        /// <summary>
        /// �ͷ�����
        /// </summary>
        virtual void    releaseTexture(uint texId);   
    public:
        /// <summary>
        /// ����ȡ��֪ͨ
        /// </summary>
        virtual void    onTaskCancel(lifeiTask* task);
        /// <summary>
        /// �������֪ͨ
        /// </summary>
        virtual void    onTaskExe(lifeiTask* task);
        /// <summary>
        /// �������֪ͨ
        /// </summary>
        virtual void    onTaskFinish(lifeiTask* task);
    protected:
        void    calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes,ArrayVertex& vertx);

		IPluginTileManager * createTileSourceDLL(const char* dllFileName);
    };
}


