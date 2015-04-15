/************************************************************************

  Test various vector math facilities provided by libgfx.

  by Michael Garland, 2000.
  
  $Id: t-vec.cxx,v 1.5 2002/03/12 19:49:12 garland Exp $

 ************************************************************************/

#include <gfx/gfx.h>

#include <gfx/vec2.h>
#include <gfx/vec3.h>
#include <gfx/vec4.h>
#include <gfx/intvec.h>

using namespace std;

void test_intvec()
{
    cout << "Testing IntVec types" << endl;

    class Normal : public IntVec<short, SHRT_MAX, 3>
    {
    public:
	Normal(const Vec3& v) { (*this) = v; }

	Vec3 unpack() const { return Vec3((*this)[0],(*this)[1],(*this)[2]); }
	void pack(const Vec3& v)
	    { set(0, v[0]); set(1, v[1]); set(2, v[2]); }

	Normal& operator=(const Vec3& v) { pack(v); return *this; }
    };

    Normal n = Vec3(1.0, 0.4, -1.0);
    cout << "  n = " << n.unpack() << endl;

    n.set(0, -1.0);  n.set(1, 0.4);  n.set(2, 1);
    cout << "  n = " << n[0] << " " << n[1] << " " << n[2] << endl;


    typedef IntVec3<unsigned char, UCHAR_MAX> byteColor;
    byteColor rgb(0.8, 0.2, 0.2);
    cout << "  rgb = " << rgb.unpack() << endl;
}

template<class Vec>
void test_vector()
{
    Vec u = 0;
    Vec v = 0;

    u[0] = 1;
    v[1] = 1;

    Vec x = u * 2.0;
    Vec y = v / 2.0;

    cout << "  x = " << x << endl;
    cout << "  y = " << y << endl;
}

main()
{
    cout << "+ Testing class Vec2" << endl;
    test_vector<Vec2>();

    cout << "+ Testing class Vec3" << endl;
    test_vector<Vec3>();

    cout << "+ Testing class Vec4" << endl;
    test_vector<Vec4>();

    test_intvec();

    return 0;
}
