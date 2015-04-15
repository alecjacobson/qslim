#include <gfx/gfx.h>
#include <gfx/symmat3.h>

using namespace std;

SymMat3 SymMat3::I()
{
    SymMat3 A;
    A(0,0) = A(1,1) = A(2,2) = 1;
    return A;
}

Mat3 SymMat3::fullmatrix() const
{
    Mat3 A;

    for(int i=0; i<A.dim(); i++)
	for(int j=0; j<A.dim(); j++)
	    A(i, j) = (*this)(i,j);

    return A;
}

SymMat3 operator*(const SymMat3& n, const SymMat3& m)
{
    SymMat3 A;
    for(int i=0; i<3; i++)  for(int j=i; j<3; j++)
	    A(i,j) = n.row(i)*m.col(j);
    return A;
}

ostream &operator<<(std::ostream &out, const SymMat3& M)
{
    for(int i=0; i<M.dim(); i++)
    {
	for(int j=0; j<M.dim(); j++)
	    out << M(i, j) << " ";
	out << endl;
    }

    return out;
}

SymMat3 SymMat3::outer_product(const Vec3& v)
{
    SymMat3 A;

    for(int i=0; i<A.dim(); i++)
	for(int j=i; j<A.dim(); j++)
	    A(i, j) = v[i]*v[j];

    return A;
}

double invert(Mat3& m_inv, const SymMat3& m)
{
    return invert(m_inv, m.fullmatrix());
}
