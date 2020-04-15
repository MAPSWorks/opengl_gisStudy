#pragma once
#include "lifeiContext_2.h"
#include "lifeiOpengl.h"
#include "lifeiTexture3dID.h"

namespace CELL
{
	class lifeiTextureMgr_2
	{
	public:
		lifeiContext_2&			_context;
		bool					_used[1024];
		lifeiTexture3dID		_textureId;

	public:
		lifeiTextureMgr_2(lifeiContext_2& context);
		//��ʼ��
		virtual bool initialize();
		//��ѯ��ȡ,�����-1������Ч��������lifeiquadtree����������ͷ�����
		virtual uint allocTexture();
		//�ͷ�����
		virtual void freeTexture(uint index);
		//������������
		virtual void updateTexture(uint index, const void* data);
		//��ȡ��ǰ�Ѿ�ʹ�õ�����Ԫ����
		virtual uint getUsedCount();
		//��õ�ǰʣ�����������
		virtual uint getFreeCount();
	};
}
