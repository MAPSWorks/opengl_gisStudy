#pragma once
namespace CELL
{
	class lifeiInput_2
	{
	public:
		//����������
		virtual void onLButtonDown(int x, int y) = 0;
		//����������
		virtual void onLButtonUp(int x, int y) = 0;
		//����Ҽ�����
		virtual void onRButtonDown(int x, int y) = 0;
		//����Ҽ�����
		virtual void onRButtonUp(int x, int y) = 0;
		//����м�����
		virtual void onMButtonDown(int x, int y) = 0;
		//����м�����
		virtual void onMButtonUp(int x, int y) = 0;
		//����ƶ��¼�
		virtual void onMouseMove(int x, int y) = 0;
		//�������¼�
		virtual void onMouseWheel(int delta) = 0;
		//���̰��������¼�
		virtual void onKeyDown(int key) = 0;
		//���̰���̧���¼�
		virtual void onKeyUp(int key) = 0;
	};
}
