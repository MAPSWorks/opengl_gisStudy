#pragma once
#include "lifeiContext.h"
#include "CELLOpenGL.h"
#include "lifeiTexture3dID.h"

namespace CELL
{
	class lifeiTextureMgr
	{
	public:
		lifeiContext&			_context;
		bool					_used[1024];
		lifeiTexture3dID		_textureId;

	public:
		lifeiTextureMgr(lifeiContext& context)
			:_context(context)
		{
			_textureId = _context._device->createTexture2dArray(256, 256, sizeof(_used), GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE);
			memset(_used, 0, sizeof(_used));
		}
		//初始化
		virtual bool initialize()
		{
			return true;
		}
		//查询获取
		virtual uint allocTexture()
		{
			for (uint i = 0; i < sizeof(_used); i++)
			{
				if (!_used[i])
				{
					_used[i] = true;
					return i;
				}
			}
			return -1;
		}
		//释放纹理
		virtual void freeTexture(uint index)
		{
			_used[index] = false;
		}
		//更新纹理数据
		virtual void updateTexture(uint index, const void* data)
		{
			_context._device->updateCompressTexture2dArray(0, 0, 0, index, 256, 256, GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE, 256*256*4/8, data);
		}
		//获取当前已经使用的纹理单元个数
		virtual uint getUsedCount()
		{
			uint cnt = 0;
			for (uint i = 0; i < sizeof(_used); i++)
			{
				if (_used[i])
				{
					++cnt;
				}
			}
			return cnt;
		}
		//获得当前剩余的纹理数量
		virtual uint getFreeCount()
		{
			return sizeof(_used) - getUsedCount();
		}
	};
}
