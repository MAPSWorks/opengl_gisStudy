#pragma once
namespace CELL
{
	class CELLTask
	{
	public:
		CELLTask()
		{

		}
		virtual ~CELLTask()
		{

		}
	};
	class CELLTaskSystem
	{
	public:
		//�������ӿ�
		virtual void addTask(CELLTask * task)
		{

		}
	};
}
