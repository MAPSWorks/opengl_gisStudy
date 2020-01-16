#pragma once
#include "LifeiProgramLibrary.h"

namespace CELL
{
	class lifeiShaderManager
	{
	public:
		//����2d��������
		PROGRAM_P3_U3_TEXARRAY	_program_P3_U3_TEXARRAY;

	public:
		lifeiShaderManager()
		{
		}
		~lifeiShaderManager()
		{
		}

	public:
		void initialize(CELLOpenGL* device)
		{
			_program_P3_U3_TEXARRAY.initialize(device);
		}
		void destroy()
		{
			_program_P3_U3_TEXARRAY.destroy();
		}

	};
}
