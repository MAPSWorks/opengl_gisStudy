#pragma once

#include    "CELLMath.hpp"

namespace   CELL
{
    class   GlobalMercator
    {
    protected:
        int     tileSize ;
        real    initialResolution;
        real    originShift;

    public:
        GlobalMercator()
        {
            tileSize            =   256;
            initialResolution   =   2 * PI * 6378137 / tileSize;  
            originShift         =   2 * PI * 6378137 / 2.0;
        }

        real2     LatLonToMeters(real lat, real lon )
        {
            //"Converts given lat/lon in WGS84 Datum to XY in Spherical Mercator EPSG:900913" 
            real    mx  = lon * originShift / 180.0 ;
            real    my  = log( tan((90 + lat) *PI / 360.0 )) / (PI / 180.0);
                    my  = my * originShift / 180.0;
            return real2(mx, my);
        }

        real2     MetersToLatLon(int mx,int my )
        {
            real    lon =   (mx / originShift) * 180.0;
            real    lat =   (my / originShift) * 180.0;
                    lat =   real(180 / PI * (2 * atan( exp( lat * PI / 180.0)) - PI / 2.0));
            return  real2(lon,lat);
        }

        real     resolution(int zoom )
        {
            //  return (2 * math.pi * 6378137) / (self.tileSize * 2**zoom)
            return  initialResolution / (pow(2,real(zoom))); 
        }
        real2     PixelsToMeters(int px, int py, int zoom)
        {
            real    res =   resolution( zoom );
            real    mx  =   px * res - originShift;
            real    my  =   py * res - originShift;
            return  real2(mx,my);
        }
        int2    MetersToPixels(real mx, real my, int zoom)
        {
            real    res =   resolution( zoom );
            int     px  =   int((mx + originShift) / res) ;
            int     py  =   int((my + originShift) / res);
            return  int2(px,py);
        }

        int2    PixelsToTile(int px, int py)
        {
            int tx = int( ceil( px / real(tileSize) ) - 1 );
            int ty = int( ceil( py / real(tileSize) ) - 1 );
            return  int2(tx,ty);
        }

        int2 MetersToTile(real mx, real my, int zoom)
        {
            int2 vPt = MetersToPixels( mx, my, zoom);
            return PixelsToTile(vPt.x,vPt.y) ;
        }
        int2    LongLatToTile(real dLon,real dLat,int zoom)
        {
            real2 vMeter  =   LatLonToMeters(dLat,dLon);

            return  MetersToTile(vMeter.x,vMeter.y,zoom);
        }

    };

    class   CELLSpatialReference
    {
    protected:
        GlobalMercator  _proj;
    public:

        CELLSpatialReference(void)
        {
        
        }

        ~CELLSpatialReference(void)
        {
        }
        /**
        *   ������ת��Ϊx-tile key
        */
        static  int     long2tilex(real lon, int z) 
        { 
            return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z))); 
        }
        /**
        *   ��γ��ת��Ϊy-tile key
        */
        static  int     lat2tiley(real lat, int z)
        { 
            return  (int)(floor((1.0 - log( tan(lat * PI/180.0) + 1.0 / cos(lat * PI/180.0)) / PI) / 2.0 * pow(2.0, z)));   
        }
        /**
        *   ���� x-tile ��ȡ����
        */
        static  real  tilex2long(int x, int z) 
        {
            return x / pow(2.0, z) * 360.0 - 180;
        }
        /**
        *   ���� y-tile ��ȡγ��
        */
        static  real  tiley2lat(int y, int z) 
        {
            real n = PI - 2.0 * PI * y / pow(2.0, z);
            return 180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
        }

        static  real2  tile2lonlat(int x,int y, int z) 
        {
            real    p   =   pow(2.0, z);
            real    n   =   PI - 2.0 * PI * y / p;
            real    lat =   180.0 / PI * atan(0.5 * (exp(n) - exp(-n)));
            real    lon =   x / p * 360.0 - 180;
            return  real2(lon,lat);
        }
        real2   tile2World(int x,int y, int z)
        {
            real2   lonLat  =   tile2lonlat(x,y,z);
            return  _proj.LatLonToMeters(lonLat.x,lonLat.y);
        }
        /**
        *   ���ݾ�γ���뼶�𷵻���ƬKey
        */
        static  int2    getKey(unsigned level, real rLong,real rLat)
        {
            //! ע�⣬���ﲻ����ʾ����Ϊ�˴����ͼ����������ͼ����ʾ��Χ���Բ���������
            #if 1
            if (rLong <= -180)
            {
                rLong   =   -179.9;
            }
            if (rLong >= 180)
            {
                rLong   =   179.9;
            }
            if (rLat < -85)
            {
                rLat   =   -85;
            }
            if (rLat > 85)
            {
                rLat   =   85;
            }
            #endif
            int levelTileNumber =   0;
            levelTileNumber =   1<<level;

            int    xTile   =    long2tilex(rLong,level);

            int    yTile   =    lat2tiley(rLat,level); 

            return  int2(xTile,yTile);
        }
    public:
        /**
        *   ��γ��ת��Ϊ��������
        */
        real2   longLatToWorld(const real2& longLatx)
        {

            //return  longLatx;
            real2   longLat =   longLatx;
            longLat.x   =   tmin<real>(179.9999f,longLatx.x);
            longLat.x   =   tmax<real>(-179.9999f,longLat.x);

            longLat.y   =   tmin<real>(85.0f,longLatx.y);
            longLat.y   =   tmax<real>(-85.0f,longLat.y);

            return  _proj.LatLonToMeters(longLatx.y,longLatx.x);
        }

        /**
        *   ��������ת��Ϊ��γ��
        */
        real2   worldToLongLat(const real2& world)
        {
            const   real      worldMin = -20037504.0f * 1000;
            const   real      worldMax = 20037504.0f * 1000;
            real    dWordX  = (real)tmin<real>(world.x, worldMax);
                    dWordX  = (real)tmax<real>((real)dWordX, worldMin);

            real    dWordY  = (real)tmin<real>(world.y, worldMax);
                    dWordY  = (real)tmax<real>((real)dWordY, worldMin);
            return  _proj.MetersToLatLon((int)dWordX, (int)dWordY);
        }

        /**
        *   �õ���ǰ������tile�ĸ���
        */
        int     getTileNumber(int lev)
        {
            return  (int)pow(2,real(lev));
        }
    };
    typedef CELLSpatialReference	SpatialReference;

}