#pragma once
#include "lifeiContext.h"
#include "CELLOpenGL.h"

namespace CELL
{
	class lifeiTextureMgr
	{
	public:
		lifeiContext&	_context;
		bool			_used[1024];
		Texture3dId		_textureId;

	public:
		lifeiTextureMgr(lifeiContext& context)
			:_context(context)
		{
			_textureId = _context._device->createTexture2dArray(256, 256, sizeof(_used), GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE);
			memset(_used, 0, sizeof(_used));
		}
		//��ʼ��
		virtual bool initialize()
		{
			return true;
		}
		//��ѯ��ȡ
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
		//�ͷ�����
		virtual void freeTexture(uint index)
		{
			_used[index] = false;
		}
		//������������
		virtual void updateTexture(uint index, const void* data)
		{
			_context._device->updateCompressTexture2dArray(0, 0, 0, index, 256, 256, GL_COMPRESSED_RGBA_S3TC_DXT1_ANGLE, 256*256*4/8, data);
		}
		//��ȡ��ǰ�Ѿ�ʹ�õ�����Ԫ����
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
		//��õ�ǰʣ�����������
		virtual uint getFreeCount()
		{
			return sizeof(_used) - getUsedCount();
		}
	};
}
