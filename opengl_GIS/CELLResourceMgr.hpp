#pragma once
#include "CELLProgramLibrary.hpp"

namespace CELL
{
	class CELLResourceMgr
	{
	public:
		//��Ի�����Ļ��ά����
		Program_p2_uc _program_p2_UC;
	public:
		CELLResourceMgr()
		{

		}
		~CELLResourceMgr()
		{

		}

	public:
		void initialize(CELLOpenGL * device)
		{
			_program_p2_UC.initialize(device);
		}
		void destroy()
		{
			_program_p2_UC.destroy();
		}
	};

}