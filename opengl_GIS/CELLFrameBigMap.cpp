#include    "stdafx.h"

#include    "lifeiPlatform.h"
#include    "CELLFrameBigMap.h"
#include    "CELLOpenGL.h"
#include    "lifeiContext.h"
#include    "CELLResourceMgr.hpp"
#include    "LifeiProgramLibrary.h"


namespace CELL
{

	CELLFrameBigMap::CELLFrameBigMap(lifeiContext& context)
        :lifeiFrame(context)
        ,_bLbuttonDown(false)
    {
        context._camera.setEye(real3(0,0,-10));
        context._camera.setTarget(real3(0,0,0));
        context._camera.calcDir();

        context._camera.setUp(real3(0,1,0));
        context._camera.setRight(real3(1,0,0));

		Texture2dId* pTex = _context._resMgr->createTextue2d("image/1.jpg");
		if (pTex)
		{
			_textureId = *pTex;
		}

    }

    CELLFrameBigMap::~CELLFrameBigMap()
    {
    }

	void CELLFrameBigMap::update(lifeiContext&)
    {
        _context._device->setViewPort(0,0,_context._width,_context._height);
        _context._screenPrj =   CELL::ortho<real>(0.0f,(real)_context._width,(real)_context._height,0,-1000.0f,1000.0f);

        _context._camera.setViewSize(real2(_context._width,_context._height));

        _context._camera.perspective(45.0,real(_context._width)/real(_context._height),0.1,1000.0);

        _context._camera.update();
        _context._mvp   =   _context._camera._matProj * _context._camera._matView * _context._camera._matWorld ;
        _context._vp    =   _context._camera._matProj * _context._camera._matView;
        
        _context._timePerFrame  =   _timeStamp.getElapsedSecond();
        _timeStamp.update();

        if (_context._keyState[VK_UP])
        {
            _context._camera.moveFront(_context._timePerFrame);
        }
        if (_context._keyState[VK_DOWN])
        {
            _context._camera.moveBack(_context._timePerFrame);
        }
        if (_context._keyState[VK_LEFT])
        {
            _context._camera.moveLeft(_context._timePerFrame);
        }
        if (_context._keyState[VK_RIGHT])
        {
            _context._camera.moveRight(_context._timePerFrame);
        }
    }

	void CELLFrameBigMap::onFrameStart(lifeiContext& context)
    {
        context._device->clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        context._device->clearColor(0, 0, 0, 1);
        context._device->disableRenderState(GL_CULL_FACE);

		struct P3U2
		{
			float _x, _y, _z;
			float _u, _v;
			P3U2(float x, float y, float z, float u, float v)
			{
				_x = x;
				_y = y;
				_z = z;
				_u = u;
				_v = v;
			}
		};
        /// 顶点数据
		P3U2  vPlane[6] =
		{
			P3U2(-10.0f, -3.0f, +10.0f, 0, 1),
			P3U2(+10.0f, -3.0f, +10.0f,1,1),
			P3U2(+10.0f, -3.0f, -10.0f,1,0),

			P3U2(-10.0f, -3.0f, +10.0f, 0, 1),
			P3U2(+10.0f, -3.0f, -10.0f, 1, 0),
			P3U2(-10.0f, -3.0f, -10.0f, 0, 0),
        };

        _aabb.setExtents(real3(-10,-3.0,-10),real3(10,-3.0,10));

        Rgba    color(255,0,0,255);
		_context._device->bindTexture2D(&_textureId, 0);
        /// 获取shader
        PROGRAM_P3_U2&  prg =   context._resMgr->_PROGRAM_P3_U2;
        prg.begin();
        {
            context._device->setUniformMatrix4fv(prg._mvp,1,false,context._vp.dataPtr());
			context._device->setUniform1i(prg._texture, 0);

			context._device->attributePointer(prg._position, 3, GL_FLOAT, GL_FALSE, sizeof(P3U2), &vPlane[0]._x);
			context._device->attributePointer(prg._uv, 2, GL_FLOAT, GL_FALSE, sizeof(P3U2), &vPlane[0]._u);

            context._device->drawArrays(GL_TRIANGLES,0,6);

        }
        prg.end();

    }

	void CELLFrameBigMap::onFrameEnd(lifeiContext& context)
    {
    }

    void CELLFrameBigMap::onLButtonDown(int x, int y)
    {
        getPointsFromScreen(x,y,_basePoint);
        _bLbuttonDown   =   true;
        _lbuttonDown    =   int2(x,y);
    }

    void CELLFrameBigMap::onLButtonUp(int x, int y)
    {
        _bLbuttonDown   =   false;
    }

	void CELLFrameBigMap::onRButtonDown(int x, int y)
	{
	}

	void CELLFrameBigMap::onRButtonUp(int x, int y)
	{
	}

	void CELLFrameBigMap::onMButtonDown(int x, int y)
	{
	}

	void CELLFrameBigMap::onMButtonUp(int x, int y)
	{
	}
    void CELLFrameBigMap::onMouseMove(int x, int y)
    {
        if (!_bLbuttonDown)
        {
            return;
        }
        int2    curPoint(x,y);
        int2    offset  =   curPoint - _lbuttonDown;
        _lbuttonDown    =   curPoint;
        _context._camera.roteteViewYByCenter(offset.x,_basePoint);
		_context._camera.roteteViewXByCenter(offset.y, _basePoint);
    }

    void CELLFrameBigMap::onMouseWheel(int delta)
    {
        double  persent =   1;
        if (delta > 0)
        {
            persent =   0.9;
        }
        else
        {
            persent =   1.1;
        }
        _context._camera.scaleCameraByPos(_basePoint,persent);
    }

    void CELLFrameBigMap::onKeyDown(int key)
    {
        _context._keyState[key] =  1; 
    }

    void CELLFrameBigMap::onKeyUp(int key)
    {
        _context._keyState[key] =   0;
    }

    bool CELLFrameBigMap::getPointsFromScreen(int x, int y, real3& point)
    {
        CELL::Ray   ray     =   _context._camera.createRayFromScreen(x, y);

		real t, u, v;
		bool res = CELL::intersectTriangle<real>(
					ray.getOrigin(),
					ray.getDirection(),
					real3(-10.0f, -3.0f, +10.0f),
					real3(+10.0f, -3.0f, +10.0f),
					real3(+10.0f, -3.0f, -10.0f),
					&t,
					&u,
					&v
					);
		if (! res)
		{
			res = CELL::intersectTriangle<real>(
				ray.getOrigin(),
				ray.getDirection(),
				real3(-10.0f, -3.0f, +10.0f),
				real3(+10.0f, -3.0f, -10.0f),
				real3(-10.0f, -3.0f, -10.0f),
				&t,
				&u,
				&v
				);
		}
		if (res)
		{
			point = ray.getPoint(t);
		}
        return  res;
    }

}

