#pragma once
#include "CELLMath.hpp"
namespace CELL
{
	class GlobalMercator
	{
	protected:
		int		tileSize;			//ÿ����Ƭ�Ĵ�С
		real	initialResolution;	//��ʼ�ֱ���,ÿ���ض�Ӧ������
		real	originShift;		//��������ͶӰ�����ı߳�
	public:
		GlobalMercator()
		{
			tileSize = 256;
			initialResolution = 2 * PI * 6378137 / tileSize;
			originShift = 2 * PI * 6378137 / 2.0;
		}
		//��γ��ת����
		real2 LatLonToMeters(real lat, real lon)
		{
			//��WGS84��γ�ȵ�EPSG:900913��xy
			real mx = lon * originShift / 180.0;
			real my = log(tan((90 + lat) * PI / 360.0)) / (PI / 180.0);
			my = my * originShift / 180.0;
			return real2(mx, my);
		}
		//��ת�ɾ�γ��
		real2 MetersToLatLon(int mx, int my)
		{
			real lon = (mx / originShift) * 180.0;
			real lat = (my / originShift) * 180.0;
			lat = real(180 / PI * (2 * atan(exp(lat * PI / 180.0)) - PI / 2.0));
			return real2(lon, lat);
		}
		real resolution(int zoom)
		{
			return initialResolution / (pow(2, real(zoom)));
		}
		//����ת������
		real2 PixelsToMeters(int px, int py, int zoom)
		{
			real res = resolution(zoom);
			real mx = px * res - originShift;
			real my = py * res - originShift;
			return real2(mx, my);
		}
		//��ת��������
		int2 MetersToPixels(real mx, real my, int zoom)
		{
			real res = resolution(zoom);
			int px = int((mx + originShift) / res);
			int py = int((my + originShift) / res);
			return int2(px, py);
		}
		int2 PixelsToTile(int px, int py)
		{
			int tx = int(ceil(px / real(tileSize)) - 1);
			int ty = int(ceil(py / real(tileSize)) - 1);
			return int2(tx, ty);
		}
		int2 MetersToTile(real mx, real my, int zoom)
		{
			int2 vPt = MetersToPixels(mx, my, zoom);
			return PixelsToTile(vPt.x, vPt.y);
		}
	};
	class lifeiSpatialReference
	{
	protected:
		GlobalMercator _proj;
	public:
		lifeiSpatialReference()
		{

		}
		~lifeiSpatialReference()
		{

		}
		//������ת��Ϊx-tile key
		static int long2tilex(real lon, int z)
		{
			return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
		}
		//��γ��ת��Ϊy-tile key
		static int lat2tiley(real lat, int z)
		{
			return (int)(floor((1.0 - log(tan(lat * PI / 180.0) + 1.0 / cos(lat * PI / 180.0)) / PI) / 2.0 * pow(2.0, z)));
		}
		//����x-tile��ȡ����
		static real tilex2long(int x, int z)
		{
			return x / pow(2.0, z) * 360.0 - 180;
		}
		//����y-tile��ȡγ��
		static real tiley2lat(int y, int z)
		{
			real n = PI - 2.0 * PI * y / pow(2.0, z);
			return 180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
		}
		static real2 tile2lonlat(int x, int y, int z)
		{
			real p = pow(2.0, z);
			real n = PI - 2.0 * PI * y / p;
			real lat = 180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
			real lon = x / p * 360.0 - 180;
			return real2(lon, lat);
		}
		real2 tile2World(int x, int y, int z)
		{
			real2 lonLat = tile2lonlat(x, y, z);
			return _proj.LatLonToMeters(lonLat.x, lonLat.y);
		}
		//���ݾ�γ���뼶�𷵻���ƬKey
		static int2 getKey(unsigned level, real rLong, real rLat)
		{
			//ע�⣬���ﲻ����ʾ����Ϊ�˴����ͼ����������ͼ����ʾ��Χ���Բ���������
#if 1
			if (rLong <= -180)
			{
				rLong = -179.9;
			}
			if (rLong >= 180)
			{
				rLong = 179.9;
			}
			if (rLat < -85)
			{
				rLat = -85;
			}
			if (rLat > 85)
			{
				rLat = 85;
			}
#endif // 1
			int levelTileNumber = 0;
			levelTileNumber = 1 << 0;
			int xTile = long2tilex(rLong, level);
			int yTile = lat2tiley(rLat, level);
			return int2(xTile, yTile);
		}

	public:
		//��γ��תΪ��������
		real2 longLatToWorld(const real2& longlat)
		{
			real2 lonLatxy = longlat;
			lonLatxy.x = tmin<real>(179.9999f, longlat.x);
			lonLatxy.x = tmax<real>(-179.9999f, longlat.x);
			lonLatxy.y = tmin<real>(85.0f, longlat.y);
			lonLatxy.y = tmax<real>(-85.0f, longlat.y);
			return _proj.LatLonToMeters(longlat.y, longlat.x);

		}
		//��������ת��γ��
		real2 worldToLongLat(const real2& world)
		{
			const real worldMin = -20037504.0f * 1000;
			const real worldMax = 20037504.0f * 1000;
			real dWorldX = (real)tmin<real>(world.x, worldMax);
			dWorldX = (real)tmax<real>((real)dWorldX, worldMin);
			real dWorldY = (real)tmin<real>(world.y, worldMax);
			dWorldY = (real)tmax<real>((real)dWorldY, worldMin);
			return _proj.MetersToLatLon((int)dWorldX, (int)dWorldY);
		}
		//�õ���ǰ������tile�ĸ���
		int getTileNumber(int lev)
		{
			return (int)pow(2, real(lev));
		}
	};
	typedef lifeiSpatialReference spatialReference;
}

