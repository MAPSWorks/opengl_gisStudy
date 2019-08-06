#pragma once

#include "lifeiPlatform.h"

namespace CELL
{
	class lifeiOpenGL;
	class Texture
	{
	public:
		enum 
		{
			TEXTURE_NONE,
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D,
		};
	public:
		unsigned	_texture;
		unsigned	_texType;

	public:
		Texture(unsigned type = TEXTURE_NONE) :
			_texture(0xFFFFFFFF),
			_texType(type)
		{

		}

		virtual ~Texture()
		{
		}
	};

	class Texture1d : public Texture
	{
	public:
		unsigned _width;
	public:
		Texture1d() : Texture(TEXTURE_1D)
		{
			_width = 0;
		}
		virtual ~Texture1d()
		{

		}
	};

	class Texture2dId : public Texture
	{
	public:
		unsigned _width;
		unsigned _height;
	public:
		Texture2dId() : Texture2dId(TEXTURE_2D)
		{
			_width = 0;
			_height = 0;
		}
		virtual ~Texture2dId()
		{

		}
	};


	class Texture3dId : public Texture
	{
	public:
		unsigned _width;
		unsigned _height;
		unsigned _depth;
	public:
		Texture3dId() : Texture(TEXTURE_3D)
		{
			_width = 0;
			_height = 0;
			_depth = 0;
		}
		virtual ~Texture3dId()
		{

		}
	};

	class lifeiProgram
	{
	public:
		typedef GLint	attribute;
		typedef GLint	uniform;
	public:
		enum ShaderType
		{
			SHADER_NONE		= 0,
			SHADER_VERTEX	= 1,
			SHADER_FRAGMENT	= 2,
			SHADER_TES		= 3,
			SHADER_TCS		= 4,
			SHADER_GEM		= 5,
			SHADER_COMPUTE	= 6,
		};

	public:
		friend lifeiOpenGL;
	public:
		GLint		_vHandle;
		GLint		_pHandle;
		GLint		_program;
		lifeiOpenGL	* _device;

	public:
		lifeiProgram();
		virtual ~lifeiProgram();

		//��ʼ��
		virtual bool initialize(lifeiOpenGL * device);
		virtual void destroy();
		//ʹ��shader
		virtual void begin();
		//����
		virtual void end();
		//����shader����
		virtual GLuint createShader(const char* source, int type);
		//��shader������program
		virtual bool attachShader(GLuint shader);
		virtual bool linkProgram();
		//�������ƻ�ȡuniform
		virtual GLuint getUniform(const char* name);
		//�������ƻ�ȡattribute
		virtual GLuint getAttribute(const char* name);

	};
	class lifeiContext;
	class vertexBufferId
	{
		unsigned	_bufferId;
		unsigned	_bufferSize;
		unsigned	_accessType;
		void *		_user;
		vertexBufferId()
		{
			_bufferId = unsigned(-1);
			_bufferSize = 0;
			_accessType = 0;
			_user = 0;
		}
	};

	class IndexBufferId
	{
	public:
		enum DataType
		{
			DT_UINT8	= 0,
			DT_UINT16	= 1,
			DT_UINT32	= 2,
		};
		unsigned	_bufferId;
		unsigned	_bufferSize;
		unsigned	_accessType;
		unsigned	_elmentCnt;
		short		_elementType;
		short		_primitive;

	public:
		IndexBufferId()
		{
			_bufferId = unsigned(-1);
			_bufferSize = 0;
			_accessType = 0;
			_elementType = 0;
			_primitive = 0;
			_elmentCnt = 0;

		}

	};

	class FrameBufferId
	{
	public:
		unsigned	_width;
		unsigned	_height;
		unsigned	_FBOID;
		unsigned	_RBOID;
		FrameBufferId()
		{
			_width = 0;
			_height = 0;
			_FBOID = 0;
			_RBOID = 0;
		}
	};

	class lifeiOpenGL
	{
	public:
		//���㻺����
		char _vertexBuf[1024 * 1024 * 8];
		//����������
		char _indexBuf[11024 * 1024];
	public:
		lifeiOpenGL();
		virtual ~lifeiOpenGL();
		static void initialize();
		//��պ���
		static void clearColor(float r, float g, float b, float a);
		static void clear(unsigned mask);
		static void setViewPort(int x, int y, int width, int height);
		//����1d������
		static Texture1d	createTexture1d(
			int level,
			int intFmt,
			int width,
			int border,
			int srcFmt,
			int type,
			const void* data
			);

		//����2d����
		static Texture2dId	createTexture2d(
			int level,
			int intFmt,
			int width,
			int height,
			int border,
			int srcFmt,
			int type,
			const void* data
			);
		static Texture2dId	createCompressTexture2d(
							int level,
							int intFmt,
							int width,
							int height,
							int border,
							int size,
							const void* data
							);
		static void	updateCompressedTexSubImage2d(
			GLint level,
			GLint xoffset,
			GLint yoffset,
			GLsizei width,
			GLsizei height,
			GLenum	format,
			GLsizei	imageSize,
			const GLvoid* data
			);

		static void updateTexture2D(
			int level,
			int xOffset,
			int yOffset,
			int width,
			int height,
			int srcFormat,
			int srcType,
			const void* data
			);

		//��������
		static void bindTexture2D(const Texture2dId* textureID, unsigned stage = 0);

		//����������
		static void destroyTexture2D(Texture2dId& id);
		static Texture3dId createTexture2dArray(int width, int height, int layers, unsigned fmt);
		static void destroyTexture2dArray(Texture3dId& id);
		static void updateTexture2dArray(
										int level,
										int xOffset,
										int yOffset,
										int layer,
										int width,
										int height,
										int srcFormat,
										int srcType,
										const void* data
										);
		static void updateCompressTexture2dArray(
										int level,
										int xOffset,
										int yOffset,
										int layer,
										int width,
										int height,
										int srcFormat,
										int size,
										const void* data
										);
		static void bindTextureArray(const Texture3dId* textureID, unsigned stage = 0);
		static void bindTexture3D(const Texture3dId* textureID, unsigned stage = 0);

		//�������㻺����
		static vertexBufferId createVertexBuffer(unsigned size, unsigned acc, const void * data);
		//�������ݺ���
		static void setVertexBuffer(unsigned size, unsigned acc, const void* data);
		//�������ݺ���
		static void updateVertexBuffer(unsigned offset, unsigned size, const void* data);
		//ʹ�û���������
		static void bindVertexBuffer(const vertexBufferId* id);
		//���ٻ���������
		static void destroyVertexBuffer(vertexBufferId& id);
		//�������㻺����
		static IndexBufferId createIndexBuffer(unsigned size, unsigned acc, short type, const void* data);
		static void setIndexBuffer(unsigned size, unsigned acc, const void* data);
		static void updateIndexBuffer(unsigned offset, unsigned size, const void* data);
		static void bindIndexBuffer(const IndexBufferId* id);
		static void destroyIndexBuffer(IndexBufferId& id);
		static void bindIndirectBuffer(unsigned bufId);
		
		//����һ����Ⱦ������������
		static FrameBufferId createFrameBuffer(int width, int height);
		static void resizeFrameBuffer(FrameBufferId bufferID, int width, int height);
		//ɾ��һ����Ⱦ����
		static void destroyFrameBuffer(FrameBufferId& frameBuffer);

	};
}