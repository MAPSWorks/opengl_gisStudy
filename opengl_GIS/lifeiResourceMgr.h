#pragma once
#include "LifeiProgramLibrary.h"
#include "lifeiImage.h"
#include "lifeiImageLoader.h"
#include <map>

namespace CELL
{
	class lifeiResourceMgr
	{
	public:
		//��Դ��Ŀ¼
		char*					_path;
		CELLOpenGL*				_device;

		//����2d��������
		PROGRAM_P3_U3_TEXARRAY	_program_P3_U3_TEXARRAY;

	public:
		lifeiResourceMgr()
		{
			_device = 0;
		}
		~lifeiResourceMgr()
		{
		}

	public:
		void initialize(CELLOpenGL* device)
		{
			_device = device;
			_program_P3_U3_TEXARRAY.initialize(device);
		}
		void destroy()
		{
			_program_P3_U3_TEXARRAY.destroy();
		}

	};
}
