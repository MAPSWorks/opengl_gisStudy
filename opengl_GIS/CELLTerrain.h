#pragma once

#include    "lifeiQuadTree.h"
#include    "lifeiContext.h"
#include    "lifeiTerrainInterface.h"
#include    "CELLTaskSystem.hpp"
#include    "CELLTextureMgr.hpp"
namespace   CELL
{
    class CELLTerrain 
        :public lifeiObject
        ,public lifeiTerrainInterface
        ,public CELLTaskObserver
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
        typedef std::vector<CELLTask*>  ArrayTask;
        typedef std::map<std::string,lifeiQuadTree*>     MapNode;
        typedef std::vector<P3U3>                       ArrayVertex;
        typedef std::vector<FaceIndex>                  ArrayFace;
    public:
		lifeiQuadTree*   _root;
        lifeiContext&    _context;
        char            _path[CELL_PATH_LENGTH];
        CELLTaskSystem  _taskSystem;
        ArrayTask       _tasks;
        lifeiMutex       _mutex;
        MapNode         _nodes;
        ArrayVertex     _vertex;
        ArrayFace       _facees;
        CELLTextureMgr  _textureMgr;
        lifeiCounts          _counts;
    public:
        CELLTerrain(lifeiContext& context);
        ~CELLTerrain();
        /// <summary>
        /// ָ������Դ
        /// </summary>
        virtual void    setTileSourcePath(const char* pathName);

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
        /// ��������
        /// </summary>
        virtual uint    createTexture(const TileId& id);
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
        virtual void    onTaskCancel(CELLTask* task);
        /// <summary>
        /// �������֪ͨ
        /// </summary>
        virtual void    onTaskExe(CELLTask* task);
        /// <summary>
        /// �������֪ͨ
        /// </summary>
        virtual void    onTaskFinish(CELLTask* task);
    protected:
        void    calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes,ArrayVertex& vertx);
        void    calcIndex(lifeiQuadTree::ArrayNode& nodes);
    };
}


