#pragma once

#include    "CELLQuadTree.h"
#include    "CELLContext.hpp"
#include    "CELLTerrainInterface.hpp"
#include    "CELLTaskSystem.hpp"
#include    "CELLTextureMgr.hpp"
namespace   CELL
{
    class CELLTerrain 
        :public CELLObject
        ,public CELLTerrainInterface
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
        typedef std::map<std::string,CELLQuadTree*>     MapNode;
        typedef std::vector<P3U3>                       ArrayVertex;
        typedef std::vector<FaceIndex>                  ArrayFace;
    public:
        CELLQuadTree*   _root;
        CELLContext&    _context;
        char            _path[CELL_PATH_LENGHT];
        CELLTaskSystem  _taskSystem;
        ArrayTask       _tasks;
        CELLMutex       _mutex;
        MapNode         _nodes;
        ArrayVertex     _vertex;
        ArrayFace       _facees;
        CELLTextureMgr  _textureMgr;
        Counts          _counts;
    public:
        CELLTerrain(CELLContext& context);
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
        virtual void    update(CELLContext& context);
        /// <summary>
        /// ����
        /// </summary>
        virtual void    render(CELLContext& context);
        /// <summary>
       /// ��ȡͳ����Ϣ
       /// </summary>

        virtual Counts& getCounts();
        /// <summary>
        /// ���Ʒ�ʽ1,�������ݴ��
        /// </summary>
        virtual void    renderPackVertex(CELLContext& context);

    public:
        /// <summary>
        /// ��������
        /// </summary>
        virtual uint    createTexture(const TileId& id);
        /// <summary>
        /// �ͷ�����
        /// </summary>
        virtual void    request(CELLQuadTree* node);
        /// <summary>
        /// �ͷ�����
        /// </summary>
        virtual void    cancelRequest(CELLQuadTree* node);

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
        void    calcVertexBuffer(CELLQuadTree::ArrayNode& nodes,ArrayVertex& vertx);
        void    calcIndex(CELLQuadTree::ArrayNode& nodes);
    };
}


