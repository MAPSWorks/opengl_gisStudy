#pragma once

#include    "lifeiQuadTree.h"
#include	"lifeiObject.h"
#include    "lifeiContext.h"
#include    "lifeiTerrainInterface.h"
#include	"CELLTaskSystem.hpp"
#include	"CELLTask.hpp"
namespace   CELL
{
    class CELLTerrain 
        :public lifeiObject
        ,public lifeiTerrainInterface
		,public CELLTaskObserver
    {
	public:
		typedef std::vector<CELLTask*> ArrayTask;
		typedef std::map<std::string, lifeiQuadTree*> MapNode;
    public:
        lifeiQuadTree*  _root;
		lifeiContext&   _context;
        char            _path[CELL_PATH_LENGTH];
		CELLTaskSystem	_taskSystem;
		ArrayTask		_tasks;
		lifeiMutex		_mutex;
		MapNode		_nodes;
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
        virtual void    initialize();
        /// <summary>
        /// ���½ӿ�
        /// </summary>
        virtual void    update(lifeiContext& context);
        /// <summary>
        /// ����
        /// </summary>
        virtual void    render(lifeiContext& context);
    public:
        /// <summary>
        /// ��������
        /// </summary>
        virtual uint    createTexture(const TileId& id);
        /// <summary>
        /// �ͷ�����
        /// </summary>
        virtual void    releaseTexture(uint texId);
		virtual void	cancelRequest(lifeiQuadTree* node);
	public:		
		//����ִ��֪ͨ
		virtual void onTaskEXE(CELLTask* task);
		//�������֪ͨ
		virtual void onTaskFinish(CELLTask* task);
		//����ȡ��֪ͨ
		virtual void onTaskCancel(CELLTask* task);
		//��������
		virtual void request(lifeiQuadTree * node);
    };
}


