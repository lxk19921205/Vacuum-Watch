#include "load_picture.h"

CLoadPic::CLoadPic()
{
	this->Init();
}

CLoadPic::~CLoadPic()
{
	free(m_pixelDate);
}

void CLoadPic::Init()
{
	m_wide = 0;
	m_height = 0;
	m_pixelDate = NULL;
	m_pixelLength = 0;
}

bool CLoadPic::LoadPic(const char* load)
{
	//打开文件并读取像素
	FILE * readf;
	readf = fopen(load, "rb" );
	if ( readf == NULL )
	{
//		printf( "打开文件失败\n \a" );
		return false;
	}
	fseek( readf, 0x0012, SEEK_SET );
	fread( &m_wide, sizeof( m_wide ), 1, readf );
	fread( &m_height, sizeof( m_height ), 1, readf );

	//计算像素数据大小(+填补)
	m_pixelLength = m_wide * 3;
	while((m_pixelLength % 4) != 0 )
	{
		//pixelLength = pixelLength + 4 - ( pixelLength % 4 );
		m_pixelLength++;
	}
	m_pixelLength = m_pixelLength * m_height;
	m_pixelDate = ( GLubyte * )malloc( m_pixelLength );
	if ( m_pixelDate == NULL )
	{
//		printf( "\a为像素申请内存空间失败" );
		return false;
	}
	fseek( readf, 54, SEEK_SET );
	fread( m_pixelDate, m_pixelLength, 1, readf );
	fclose( readf );
	return true;
}

bool CLoadPic::AdjustPic(GLint new_wide, GLint new_height, GLint new_posx, GLint new_posy)
{
	//转换图片大小
	m_pixelLength = new_wide * 3;

	while((m_pixelLength % 4) != 0 )
	{
		//pixelLength = pixelLength + 4 - ( pixelLength % 4 );
		m_pixelLength++;
	}
	m_pixelLength = m_pixelLength * new_height;
	GLubyte *new_pixelDate = ( GLubyte * )malloc( m_pixelLength );
	if ( m_pixelDate == NULL )
	{
		printf( "\a为像素申请内存空间失败" );
		return false;
	}
	gluScaleImage(GL_RGB, m_wide, m_height, GL_UNSIGNED_BYTE, m_pixelDate, new_wide, new_height, GL_UNSIGNED_BYTE, new_pixelDate);
	free(m_pixelDate);
	m_pixelDate = new_pixelDate;
	m_wide = new_wide;
    m_height = new_height;
	m_posx = new_posx;
	m_posy = new_posy;
	return true;
}

void CLoadPic::Render()
{
	glRasterPos2i(m_posx, m_posy);
	glDrawPixels( m_wide, m_height, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pixelDate );
}