#pragma once
namespace CELL
{
	class CELLInput
	{
	public:
		//����������
		virtual void onLButtonDown(int x, int y) = 0;
		//����������
		virtual void onLButtonUp(int x, int y) = 0;
		//����ƶ�
		virtual void onMouseMove(int x, int y) = 0;
		//�����¼�
		virtual void onKeyDown(int key) = 0;
		//�����¼�
		virtual void onKeyUp(int key) = 0;

	};
}