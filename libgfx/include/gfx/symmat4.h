#ifndef GFXSYMMAT4_INCLUDED // C++
#define GFXSYMMAT4_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif
/************************************************************************

  4X4 Symmetric Matrix class

  $Id: symmat4.h,v 1.4 2003/07/07 16:59:34 garland Exp $

 ************************************************************************/

#include "mat4.h"

class SymMat4
{
public:
    double pro[10];
    
	inline int index(int i, int j) const
    {
		if (i<=j) 
			return (10 - (4-i)*(5-i)/2 + (j-i));
		else 
			return (10 - (4-j)*(5-j)/2 + (i-j));
    }

public:
    // Standard constructors
    //
    SymMat4(double s=0.0) { *this = 0.0; }
	SymMat4(const SymMat4 &m) {*this=m;}

	
    // Descriptive interface
    //
    typedef double value_type;
    typedef Vec4 vector_type;
    typedef Mat4 inverse_type;
    static int dim() { return 4; }
	static int size() {return 10;} 


    // Access methods
    //
    double& operator()(int i, int j)       { return pro[index(i,j)]; }
    double  operator()(int i, int j) const { return pro[index(i,j)]; }

    inline Vec4 row(int i) const;
	inline Vec4 col(int i) const;
	Mat4 fullmatrix() const;
    
    operator       double*()       { return pro; }
    operator const double*()       { return pro; }
    operator const double*() const { return pro; }

    // Assignment methods
    //
    inline SymMat4& operator=(const SymMat4& m);
    inline SymMat4& operator=(double s);

    inline SymMat4& operator+=(const SymMat4& m);
    inline SymMat4& operator-=(const SymMat4& m);
    inline SymMat4& operator*=(double s);
    inline SymMat4& operator/=(double s);

    static SymMat4 I();
	static SymMat4 outer_product(const Vec4& v);
};

////////////////////////////////////////////////////////////////////////
//
// Method definitions
//
inline Vec4 SymMat4::row(int i) const
{
	return Vec4((*this)(i,0), (*this)(i,1), (*this)(i,2), (*this)(i,3));
}

inline Vec4 SymMat4::col(int j) const
{
	return Vec4((*this)(0,j), (*this)(1,j), (*this)(2,j), (*this)(3,j));
}

inline SymMat4& SymMat4::operator=(const SymMat4& m)
{
   	for(int i=0; i<size(); i++)
		pro[i] = m.pro[i];
    return *this;
}

inline SymMat4& SymMat4::operator=(double s)
{
    for(int i=0; i<size(); i++)
		pro[i] = s;
    return *this;
}

inline SymMat4& SymMat4::operator+=(const SymMat4& m)
{
    for(int i=0; i<size(); i++)
		pro[i]+=m.pro[i];
    return *this;
}

inline SymMat4& SymMat4::operator-=(const SymMat4& m)
{
    for(int i=0; i<size(); i++)
		pro[i]-=m.pro[i];
    return *this;
}

inline SymMat4& SymMat4::operator*=(double s)
{
    for(int i=0; i<size(); i++)
		pro[i] *= s;
    return *this;
}

inline SymMat4& SymMat4::operator/=(double s)
{
    for(int i=0; i<size(); i++)
		pro[i] /= s;
    return *this;
}

////////////////////////////////////////////////////////////////////////
//
// Operator definitions
//

inline SymMat4 operator+(SymMat4 n, const SymMat4& m) { n += m; return n; }
inline SymMat4 operator-(SymMat4 n, const SymMat4& m) { n -= m; return n; }

inline SymMat4 operator*(double s, SymMat4 m) { m*=s; return m; }
inline SymMat4 operator*(SymMat4 m, double s) { m*=s; return m; }
inline SymMat4 operator/(SymMat4 m, double s) { m/=s; return m; }

inline SymMat4 operator-(const SymMat4& m)
{ 	
    SymMat4 temp;
    for(int i=0; i<m.size(); i++)  temp.pro[i]= -m.pro[i];
    return temp; 
}

inline Vec4 operator*(const SymMat4& m, const Vec4& v)
	{ return Vec4(m.row(0)*v, m.row(1)*v, m.row(2)*v, m.row(3)*v); }

extern SymMat4 operator*(const SymMat4& n, const SymMat4& m);

/* no use right now
inline std::ostream &operator<<(std::ostream &out, const Mat4& M)
       { return out<<M[0]<<std::endl<<M[1]<<std::endl<<M[2]<<std::endl<<M[3]; }

inline std::istream &operator>>(std::istream &in, Mat4& M)
       { return in >> M[0] >> M[1] >> M[2] >> M[3]; }
*/

////////////////////////////////////////////////////////////////////////
//
// Misc. function definitions
//

inline double trace(const SymMat4& m) { return m(0,0)+m(1,1)+m(2,2)+m(3,3); }

inline SymMat4 transpose(const SymMat4& m) { return m; }
	
extern double invert(Mat4& m_inv, const SymMat4& m);

extern bool eigen(const SymMat4& m, Vec4& eig_vals, Vec4 eig_vecs[4]);

// GFXSYMMAT4_INCLUDED  
#endif
