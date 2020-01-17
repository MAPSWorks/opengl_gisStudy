#pragma once
#include "tvec3.h"

namespace CELL
{
	template <typename T>
	class tray
	{
	protected:
		tvec3<T>	_origin;
		tvec3<T>	_direction;

	public:
		tray()
		{
			_origin = tvec3<T>(T(0), T(0), T(0));
			_direction = tvec3<T>(T(0), T(0), T(1));
		}

		//�������ߵ����
		void setOrigin(const tvec3<T>& origin)
		{
			_origin = origin;
		}

		//�������ߵ����
		const tvec3<T>& getOrigin() const
		{
			return _origin;
		}
		//�������ߵķ���
		void setDirection(const tvec3<T>& dir)
		{
			_direction = dir;
		}
		//�������ߵķ���
		const tvec3<T>& getDirection() const
		{
			return _direction;
		}
		tvec3<T> getPoint(T time) const
		{
			return tvec3<T>(_origin + (_direction * time));
		}

	};

	typedef tray<real>	Ray;
	typedef tray<float>	RayF;
}