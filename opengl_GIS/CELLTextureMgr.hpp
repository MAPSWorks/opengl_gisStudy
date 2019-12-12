#pragma once
#include "lifeiContext.h"
#include "CELLOpenGL.h"

namespace CELL
{
	class CELLTextureMgr
	{
	public:
		lifeiContext& _context;
		bool _used[1024];
		Texture3dId _textureId;
	public:
		CELLTextureMgr(lifeiContext& context)
			:_context(context)
		{
			_textureId = _context._device->createTexture2dArray(256, 256, sizeof(_used), GL_RGB8);
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
			_context._device->updateTexture2dArray(0, 0, 0, index, 256, 256, GL_RGB, GL_UNSIGNALED, data);
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