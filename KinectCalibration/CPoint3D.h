//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*           CPoint3D.h                                                 */
/************************************************************************/

#ifndef  __CPOINT3D_H__
#define  __CPOINT3D_H__

typedef class POINT3D 
{
public:	
	POINT3D();
	~POINT3D();
	POINT3D operator + (const POINT3D &point3d);
	POINT3D operator - (const POINT3D &point3d);
	POINT3D operator / (const int &sum);
	POINT3D operator * (const int &sum);
	POINT3D operator += (const POINT3D &point3d);
	POINT3D operator -= (const POINT3D &point3d);
	POINT3D operator /= (const int &sum);	
	POINT3D operator *= (const int &sum);	
public:
	float x;
	float y;
	float z;
	BYTE   w;// w = 0    无用
	         //   = 1    有用			
}Point3D;

typedef class POINT7D : public POINT3D
{
public :
	POINT7D();
	~POINT7D();
	POINT7D operator =(const POINT3D &point3d);
public:
	//float nx;
	//float ny;
	//float nz;
	int r;
	int g;
	int b;
} Point7D;

struct POINT6D
{
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
};

struct MyPoint
{
	int i;//行
	int j;//列
	float x;
	float y;
	float z;
	float gray;
};

double Distance(const POINT3D &p1 , const POINT3D &p2);

#endif 