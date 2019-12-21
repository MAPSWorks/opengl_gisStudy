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
		typedef std::map<std::string, Texture*> mapTexture;
	public:
		//��Դ��Ŀ¼
		char*					_path;
		CELLOpenGL*				_device;
		//��Ի�����Ļ��ά����
		PROGRAM_P2_UC			_PROGRAM_P2_UC;
		PROGRAM_P3_UC			_PROGRAM_P3_UC;
		PROGRAM_P3_U2			_PROGRAM_P3_U2;

		//����2d��������
		PROGRAM_P3_U3_TEXARRAY	_program_P3_U3_TEXARRAY;
		mapTexture				_mapTexture;

	public:
		lifeiResourceMgr()
		{
			_device = 0;
		}
		~lifeiResourceMgr()
		{
		}
	public:
		Texture1d createTexture1dFromImage(const char* pathName)
		{
			Texture1d tex;
			lifeiImage image;
			if (lifeiImageLoader::loadImage(pathName, image))
			{
				switch (image._format)
				{
				case lifeiImage::FORMAT_RGB8:
					tex = _device->createTexture1d(0, GL_RGBA, image._width, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
					break;

				case lifeiImage::FORMAT_RGBA8:
					tex = _device->createTexture1d(0, GL_RGBA, image._width, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
					break;
				default:
					assert(0 != 0);
				}
			}

			return tex;
		}

		Texture2dId createTexture2dFromImage(const char* pathName)
		{
			Texture2dId tex;
			lifeiImage image;
			if (lifeiImageLoader::loadImage(pathName, image))
			{
				switch (image._format)
				{
				case lifeiImage::FORMAT_RGB8:
					tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
					break;

				case lifeiImage::FORMAT_RGBA8:
					tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
					break;
				default:
					assert(0 != 0);
				}
			}

			return tex;
		}

		Texture2dId createTexture2dFromImage(lifeiImage& image)
		{
			Texture2dId tex;
				
			switch (image._format)
			{
			case lifeiImage::FORMAT_RGB8:
				tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
				break;

			case lifeiImage::FORMAT_RGBA8:
				tex = _device->createTexure2D(0, GL_RGBA, image._width, image._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
				break;
			default:
				assert(0 != 0);
			}
			
			return tex;
		}
	public:
		void initialize(CELLOpenGL* device)
		{
			_device = device;
			_PROGRAM_P2_UC.initialize(device);
			_PROGRAM_P3_UC.initialize(device);
			_PROGRAM_P3_U2.initialize(device);
			_program_P3_U3_TEXARRAY.initialize(device);
		}
		void destroy()
		{
			_PROGRAM_P2_UC.destroy();
			_PROGRAM_P3_UC.destroy();
			_PROGRAM_P3_U2.destroy();
			_program_P3_U3_TEXARRAY.destroy();
		}
		//��ȡ������Դ
		Texture* getTexture(const char* filePathName)
		{
			mapTexture::iterator itr = _mapTexture.find(filePathName);
			if (itr == _mapTexture.end())
			{
				return 0;
			}
			else
			{
				return itr->second;
			}
		}
		//����1d������
		Texture1d* createTexture1d(const char* pName)
		{
			char szFullPath[CELL_PATH_LENGTH];
			sprintf(szFullPath, "%s/%s", _path, pName);
			Texture* pTex = getTexture(szFullPath);
			if (pTex)
			{
				return dynamic_cast<Texture1d*> (pTex);
			}
			else
			{
				Texture1d* pTex1d = new Texture1d();
				*pTex1d = createTexture1dFromImage(szFullPath);
				_mapTexture[szFullPath] = pTex1d;
				return pTex1d;
			}
		}
		//����2d������
		Texture2dId* createTexture2d(const char* pName)
		{
			char szFullPath[CELL_PATH_LENGTH];
			sprintf(szFullPath, "%s/%s", _path, pName);
			Texture* pTex = getTexture(szFullPath);
			if (pTex)
			{
				return dynamic_cast<Texture2dId*> (pTex);
			}
			else
			{
				Texture2dId* pTex1d = new Texture2dId();
				*pTex1d = createTexture2dFromImage(szFullPath);
				_mapTexture[szFullPath] = pTex1d;
				return pTex1d;
			}
		}
		//����3d������
		Texture3dId* createTexture3d(const char* pId, int w, int h, int d, int fmt)
		{
			Texture* pTex = getTexture(pId);
			if (pTex)
			{
				return dynamic_cast<Texture3dId*> (pTex);
			}
			else
			{
				Texture3dId* pTex1d = new Texture3dId();
				*pTex1d = _device->createTexture2dArray(w, h, d, fmt);
				_mapTexture[pId] = pTex1d;
				return pTex1d;
			}
		}
	};
}
