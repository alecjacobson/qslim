/************************************************************************

  The images produced by this test are checkboard gradients.  They
  ramp from black in the upper left corner to full color in the lower
  right corner.

  by Michael Garland, 1999.
  
  $Id: t-img.cxx,v 1.2 2000/08/19 03:37:26 garland Exp $

 ************************************************************************/

#include <gfx/gfx.h>
#include <gfx/raster.h>

static
void grayscale_test()
{
    ByteRaster img(256, 256, 1);

    int i, j, c;

    for(i=0; i<img.height(); i++) for(j=0; j<img.width(); j++)
    {
	c = ((((i&0x8)==0)^((j&0x8))==0))*(i+j)/2;
	img.pixel(j,i)[0] = c;
    }
    
    write_pnm_image("chex1.pgm", img);
    write_tiff_image("chex1.tif", img);
    write_png_image("chex1.png", img);
    write_jpeg_image("chex1.jpg", img);

    ByteRaster *pgm = read_pnm_image("chex1.pgm");
    ByteRaster *tif = read_tiff_image("chex1.tif");
    ByteRaster *png = read_png_image("chex1.png");
    ByteRaster *jpg = read_jpeg_image("chex1.jpg");

    if( pgm )  write_pnm_image("chex1-dup.pgm", *pgm);
    if( tif )  write_tiff_image("chex1-dup.tif", *tif);
    if( png )  write_png_image("chex1-dup.png", *png);
    if( jpg )  write_jpeg_image("chex1-dup.jpg", *jpg);
}

static
void rgb_test()
{
    ByteRaster img(256, 256, 3);

    int i, j, c;

    for(i=0; i<img.height(); i++) for(j=0; j<img.width(); j++)
    {
	c = ((((i&0x8)==0)^((j&0x8))==0))*(i+j)/2;
	img.pixel(j,i)[0] = c;
	img.pixel(j,i)[1] = c/2;
	img.pixel(j,i)[2] = c/4;
    }

    write_pnm_image("chex3.ppm", img);
    write_tiff_image("chex3.tif", img);
    write_png_image("chex3.png", img);
    write_jpeg_image("chex3.jpg", img);

    ByteRaster *ppm = read_pnm_image("chex3.ppm");
    ByteRaster *tif = read_tiff_image("chex3.tif");
    ByteRaster *png = read_png_image("chex3.png");
    ByteRaster *jpg = read_jpeg_image("chex3.jpg");

    if( ppm )  write_pnm_image("chex3-dup.ppm", *ppm);
    if( tif )  write_tiff_image("chex3-dup.tif", *tif);
    if( png )  write_png_image("chex3-dup.png", *png);
    if( jpg )  write_jpeg_image("chex3-dup.jpg", *jpg);
}

main()
{
    grayscale_test();
    rgb_test();

    return 0;
}
