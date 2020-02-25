#pragma once
#include "lifeiMathUtil.h"
#include "tvec2.h"

namespace CELL
{
	class GlobalMercator_2
	{
	protected:
		int		_tileSize;			//ÿ����Ƭ�Ĵ�С
		real	_initialResolution;	//��ʼ�ֱ��ʣ�ÿ���ض�Ӧ������
		real	_originShift;		//��������ͶӰ�����ı߳�

	public:
		GlobalMercator_2()
		{
			_tileSize = 256;
			_initialResolution = 2 * PI * 6378137 / _tileSize;
			_originShift = 2 * PI * 6378137 / 2.0;
		}
		//��γ��ת������
		real2 LatLonToMeters(real lat, real lon)
		{
			//��WGS84��γ��ת��EPSG:900913��xy
			real mx = lon * _originShift / 180.0;
			real my = log(tan((90 + lat) * PI / 360.0)) / (PI / 180.0);
			my = my * _originShift / 180.0;
			return real2(mx, my);
		}

		//��ת���ɾ�γ��
		real2 MetersToLatLon(int mx, int my)
		{
			real lon = (mx / _originShift) * 180.0f;
			real lat = (my / _originShift) * 180.0f;
			lat = real(180 / PI * (2 * atan(exp(lat * PI / 180.0)) - PI / 2.0));
			return real2(lon, lat);
		}

		real resolution(int zoom)
		{
			return _initialResolution / (pow(2, real(zoom)));
		}
		//����ת������
		real2 PixelsToMeters(int px, int py, int zoom)
		{
			real res = resolution(zoom);
			real mx = px * res - _originShift;
			real my = py * res - _originShift;
			return real2(mx, my);
		}

		//��ת��������
		int2 MetersToPixels(real mx, real my, int zoom)
		{
			real res = resolution(zoom);

		}
	};
}