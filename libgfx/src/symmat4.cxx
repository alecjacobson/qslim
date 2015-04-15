/************************************************************************

  4X4 Symmetric Matrix class
  
  $Id: symmat4.cxx,v 1.3 2003/06/30 10:26:52 garland Exp $

 ************************************************************************/
#include <gfx/symmat4.h>

SymMat4 SymMat4::I()
{
	SymMat4 A;
	A(0,0) = A(1,1) = A(2,2) = A(3,3) = 1;
	return A;
}

Mat4 SymMat4::fullmatrix() const
{
	Mat4 temp;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			temp(i,j) = (*this) (i,j);
	return temp;
}

SymMat4 SymMat4::outer_product(const Vec4& v)
{
	SymMat4 tmp;
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			tmp(i,j)=v[i]*v[j];
	return tmp;
}

SymMat4 operator* (const SymMat4& n, const SymMat4& m)
{
	SymMat4 temp;
	for (int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			temp(i,j)=n.row(i) * m.col(j);
	return temp;
}

double invert(Mat4& m_inv, const SymMat4& m)
{
    return invert(m_inv, m.fullmatrix());
}
