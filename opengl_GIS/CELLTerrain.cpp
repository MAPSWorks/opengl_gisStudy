#include "CELLTerrain.h"
#include "lifeiResourceMgr.h"
#include "LifeiProgramLibrary.h"
#include "CELLTileTask.hpp"
#include "lifeiTimeStamp.hpp"
#include "rapidxml.hpp"
#include "CELLGIS3DPlatform.h"

namespace CELL
{
    CELLTerrain::CELLTerrain(lifeiContext& context)
        :_context(context)
        ,_textureMgr(_context)
    {
		_tileSource = 0;
		_hTileSourceDll = 0;
        _root   =   0;
        _taskSystem.setObserver(this);
        _vertex.reserve(1024*4);
        _facees.reserve(1024 * 4);
        _textureMgr.initialize();
        _counts._nodes  =   0;
        _counts._drawNodes  =   0;
        _counts._textCounts =   sizeof(_textureMgr._used);
        _counts._texFree    =   _textureMgr.getFreeCount();
        _counts._texUsed    =   _textureMgr.getUsedCount();
    }

    CELLTerrain::~CELLTerrain()
    {
        delete  _root;
    }

    void CELLTerrain::setTileSourcePath(const char* pathName)
    {
        strncpy(_path, pathName, sizeof(_path));
    }

    void CELLTerrain::initailze()
    {
        _taskSystem.start(4);
        _root = new lifeiQuadTree(this, 0, real2(-20037508, -20037508), real2(20037508, 20037508), 0, lifeiQuadTree::CHILD_LT);
    }

    void CELLTerrain::update(lifeiContext& context)
    {
        _root->update(context);
        ArrayTask   tasks;
        {
            lifeiMutex::ScopeLock lk(_mutex);
            tasks   =   _tasks;
            _tasks.clear();
        }
        for (size_t i = 0 ;i < tasks.size() ; ++ i)
        {
            CELLTileTask*   pTask   =   dynamic_cast<CELLTileTask*>(tasks[i]);
            if (pTask == 0)
            {
                delete  tasks[i];
                continue;
            }
            char    szBuf[128];
            sprintf(
                szBuf
                , "%d-%d-%d:%p"
                , pTask->_tileId._lev
                , pTask->_tileId._row
                , pTask->_tileId._col
                , pTask->_node);

            MapNode::iterator itr = _nodes.find(szBuf);
            if (itr == _nodes.end())
            {
                delete  pTask;
                continue;
            }
            else
            {
                _nodes.erase(itr);
            }
            /// 查询节点是否存在
            uint    texIndex    =   _textureMgr.allocTexture();
            pTask->_node->updateTexture(texIndex);
             
            _textureMgr.updateTexture(texIndex,pTask->_image.data());
            delete  pTask;
        }
    }

    void CELLTerrain::render(lifeiContext& context)
    {
        renderPackVertex(context);
    }

    CELL::lifeiCounts& CELLTerrain::getCounts()
    {
        return  _counts;
    }

    void CELLTerrain::renderPackVertex(lifeiContext& context)
    {
		lifeiQuadTree::ArrayNode nodes;
        _root->getAllRenderableNode(nodes);
        getCounts()._drawNodes  =   (uint)nodes.size();
        getCounts()._texUsed    =   _textureMgr.getUsedCount();
        getCounts()._texFree    =   _textureMgr.getFreeCount();

        if (nodes.empty())
        {
            return;
        }
        /// 对节点进行绘制
        lifeiTimeStamp   tm;
        /// 获取shader
        PROGRAM_P3_U3_TEXARRAY&  prg = context._resMgr->_program_P3_U3_TEXARRAY;
        
        
        calcVertexBuffer(nodes,_vertex);
        context._device->bindTextureArray(&_textureMgr._textureId);
        prg.begin();
        if (_vertex.size())
        {
            context._device->setUniformMatrix4fv(prg._mvp, 1, false, context._vp.dataPtr());
            context._device->setUniform1i(prg._texture, 0);
            context._device->attributePointer(prg._position,    3, GL_FLOAT, GL_FALSE, sizeof(P3U3), &_vertex[0].x);
            context._device->attributePointer(prg._uv,          3, GL_FLOAT, GL_FALSE, sizeof(P3U3), &_vertex[0].u);

            context._device->drawArrays(GL_TRIANGLES, 0, _vertex.size());
        }
        prg.end();

        tm.getElapsedTimeInMilliSec();
        char    szBuf[1024];

        sprintf(szBuf,"node = %d draw = %d  free = %d ,%lf ms\n"
            ,_counts._nodes
            ,_counts._drawNodes
            ,_counts._texFree
            ,tm.getElapsedTimeInMilliSec());
        OutputDebugStringA(szBuf);
    }

    uint CELLTerrain::createTexture(const TileId& id)
    {
        char    szPathName[CELL_PATH_LENGTH];
        sprintf(szPathName,"%s/L%02d/%06d-%06d.jpg",_path,id._lev + 1,id._row,id._col);
        Texture2dId texId = _context._resMgr->createTexture2dFromImage(szPathName);
        return  texId._texture;
    }
    void CELLTerrain::request(lifeiQuadTree* node)
    {
        CELLTileTask*   pTask   =   new CELLTileTask();
        pTask->_node    =   node;
        pTask->_tileId  =   node->_tileID ;
        _taskSystem.addTask(pTask);

        char    szBuf[128];
        sprintf(
            szBuf
            ,"%d-%d-%d:%p"
            ,pTask->_tileId._lev
            ,pTask->_tileId._row
            ,pTask->_tileId._col
            ,pTask->_node);
        if (_nodes.find(szBuf) != _nodes.end())
        {
            return;
        }
        _nodes[szBuf]   =   node;
    }

    void CELLTerrain::cancelRequest(lifeiQuadTree* node)
    {
        char    szBuf[128];
        sprintf(
            szBuf
            , "%d-%d-%d:%p"
            , node->_tileID._lev
            , node->_tileID._row
            , node->_tileID._col
            , node);
        MapNode::iterator itr = _nodes.find(szBuf);
        if (itr != _nodes.end())
        {
            _nodes.erase(itr);
        }
    }

    void CELLTerrain::releaseTexture(uint texId)
    {
        _textureMgr.freeTexture(texId);
    }

    void CELLTerrain::onTaskCancel(CELLTask* task)
    {
        delete  task;
    }

    void CELLTerrain::onTaskExe(CELLTask* task)
    {
        CELLTileTask*   pTask   =   dynamic_cast<CELLTileTask*>(task);
        if (pTask == 0)
        {
            return;
        }
		if (_tileSource == 0)
		{
			delete task;
			return;
		}
		if (_tileSource->load(task) == 0)
		{
			delete task;
			return;
		}

		lifeiMutex::ScopeLock lk(_mutex);
		_tasks.push_back(pTask);
#if 0
        char    szPathName[CELL_PATH_LENGTH];
        sprintf(szPathName, "%s/L%02d/%06d-%06d.jpg", _path, pTask->_tileId._lev + 1, pTask->_tileId._row, pTask->_tileId._col);
        if(lifeiImageLoader::loadImageToDXT1(szPathName, pTask->_image))
        {
            lifeiMutex::ScopeLock lk(_mutex);
            _tasks.push_back(pTask);
        }
        else
        {
            delete  task;
        }
#endif
    }

    void CELLTerrain::onTaskFinish(CELLTask* task)
    {
    }

	bool CELLTerrain::loadScene(const char * fileName)
	{
		rapidxml::xml_document<> doc;
		FILE* file = fopen(fileName, "rb");
		if (0 == file)
		{
			return false;
		}

		fseek(file, 0, SEEK_END);
		size_t nSize = ftell(file);
		fseek(file, 0, SEEK_SET);
		char * pBuf = new char[nSize + 1];
		memset(pBuf, 0, nSize + 1);
		fread(pBuf, nSize, 1, file);
		pBuf[nSize] = '\0';
		fclose(file);

		try
		{
			do
			{
				doc.parse<0>(pBuf);
				rapidxml::xml_node<> * pRoot = doc.first_node();
				rapidxml::xml_node<> * pImageSource = pRoot->first_node();
				if (0 == pImageSource)
				{
					break;
				}
				rapidxml::xml_attribute<>* pDll = pImageSource->first_attribute("loader");
				if (0 == pDll)
				{
					break;
				}
				_tileSource = createTileSource(pDll->value());
				if (0 == _tileSource)
				{
					break;
				}
				rapidxml::xml_attribute<>* pAttr = pImageSource->first_attribute();
				for (; pAttr; pAttr = pAttr->next_attribute())
				{
					_tileSource->setParam(pAttr->name(), pAttr->value());
				}

			} while (false);
		}
		catch (...)
		{

		}
		delete[] pBuf;
		return false;
	}

 

    void CELLTerrain::calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes, ArrayVertex& vertx)
    {
        vertx.resize(nodes.size() * 6);
        P3U3*   vPlane  =   &vertx.front();
        for (size_t i = 0 ;i < nodes.size() ; ++ i)
        {
            lifeiQuadTree*   pNode   =   nodes[i];
            real2           vStart  =   pNode->_vStart;
            real2           vEnd    =   pNode->_vEnd;

            float2          uvStart =   pNode->_uvStart;
            float2          uvEnd   =   pNode->_uvEnd;
            vPlane[0].x     =   vStart.x;
            vPlane[0].y     =   0;
            vPlane[0].z     =   vEnd.y;

            vPlane[0].u     =   uvStart.x;
            vPlane[0].v     =   uvEnd.y;
            vPlane[0].w     =   pNode->_textureID;

            vPlane[1].x     =   vEnd.x;
            vPlane[1].y     =   0;
            vPlane[1].z     =   vEnd.y;

            vPlane[1].u     =   uvEnd.x;
            vPlane[1].v     =   uvEnd.y;
            vPlane[1].w     =   pNode->_textureID;

            vPlane[2].x     =   vEnd.x;
            vPlane[2].y     =   0;
            vPlane[2].z     =   vStart.y;
            vPlane[2].u     =   uvEnd.x;
            vPlane[2].v     =   uvStart.y;
            vPlane[2].w     =   pNode->_textureID;

            vPlane[3].x     =   vStart.x;
            vPlane[3].y     =   0;
            vPlane[3].z     =   vEnd.y;

            vPlane[3].u     =   uvStart.x;
            vPlane[3].v     =   uvEnd.y;
            vPlane[3].w     =   pNode->_textureID;

            vPlane[4].x     =   vEnd.x;
            vPlane[4].y     =   0;
            vPlane[4].z     =   vStart.y;
            vPlane[4].u     =   uvEnd.x;
            vPlane[4].v     =   uvStart.y;
            vPlane[4].w     =   pNode->_textureID;

            vPlane[5].x     =   vStart.x;
            vPlane[5].y     =   0;
            vPlane[5].z     =   vStart.y;

            vPlane[5].u     =   uvStart.x;
            vPlane[5].v     =   uvStart.y;
            vPlane[5].w     =   pNode->_textureID;

            vPlane          +=  6;
        }

    }

    void CELLTerrain::calcIndex(lifeiQuadTree::ArrayNode& nodes)
    {
        _vertex.resize(nodes.size() * 4);
        _facees.resize(nodes.size() * 2);
        P3U3*   vPlane  =   &_vertex.front();
        for (size_t i = 0 ;i < nodes.size() ; ++ i)
        {
			lifeiQuadTree*   pNode   =   nodes[i];
            real2           vStart  =   pNode->_vStart;
            real2           vEnd    =   pNode->_vEnd;

            float2          uvStart =   pNode->_uvStart;
            float2          uvEnd   =   pNode->_uvEnd;
            vPlane[0].x     =   vStart.x;
            vPlane[0].y     =   0;
            vPlane[0].z     =   vEnd.y;

            vPlane[0].u     =   uvStart.x;
            vPlane[0].v     =   uvEnd.y;

            vPlane[1].x     =   vEnd.x;
            vPlane[1].y     =   0;
            vPlane[1].z     =   vEnd.y;

            vPlane[1].u     =   uvEnd.x;
            vPlane[1].v     =   uvEnd.y;

            vPlane[2].x     =   vEnd.x;
            vPlane[2].y     =   0;
            vPlane[2].z     =   vStart.y;
            vPlane[2].u     =   uvEnd.x;
            vPlane[2].v     =   uvStart.y;

            vPlane[3].x     =   vStart.x;
            vPlane[3].y     =   0;
            vPlane[3].z     =   vStart.y;
                 
            vPlane[3].u     =   uvStart.x;
            vPlane[3].v     =   uvStart.y;

            vPlane          +=  4;
            short   id      =   short(i) * 4;
            FaceIndex   index0  =   {id,id + 1,id + 2};
            FaceIndex   index1  =   {id,id + 2,id + 3};
            _facees[i*2 + 0]    =   index0;
            _facees[i*2 + 1]    =   index1;
        }
    }


	IPluginTileSource * CELLTerrain::createTileSource(const char * dllFileName)
	{
		HMODULE hDll = LoadLibraryA(dllFileName);
		if (0 == hDll)
		{
			return NULL;
		}
		CREATETILESOURCEFUNC func = (CREATETILESOURCEFUNC)GetProcAddress(hDll, CREATE_TILESOURCE);
		if (NULL == func)
		{
			CloseHandle(hDll);
			return NULL;
		}
		_hTileSourceDll = hDll;
		return func(0);
	}


}

