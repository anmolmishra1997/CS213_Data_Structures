#include <cstdio>
#include <math.h>
#include <iostream>
#include <math.h>
#include "bitmap_image.hpp"
using namespace std;

void hflip(bitmap_image&);
void vflip(bitmap_image&);
void rotate(bitmap_image&,float);
void rotateright(bitmap_image&);
void vmirror(bitmap_image&);
void fourinone(bitmap_image&);
void translate(bitmap_image&,int,int); //Shift the image by x pixels to the Right and y pixels below
void wraparound(bitmap_image&,int,int);

void hflip(bitmap_image& img)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(width-x-1,y,red,green,blue);
      }
   }
   new_image.save_image("hflip.bmp");
}

void vflip(bitmap_image& img)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(x,height-y-1,red,green,blue);
      }
   }
   new_image.save_image("vflip.bmp");
}

void rotate(bitmap_image& img,float angle)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   int xnew,ynew,X,Y;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         xnew = x - width/2;
         ynew = y - height/2;
         X = width/2 + xnew * cos(angle) - ynew * sin(angle);
         Y = height/2 + xnew * sin(angle) + ynew * cos(angle);
         if ( X>=0 && X<width && Y>=0 && Y<height)
            new_image.set_pixel(X,Y,red,green,blue);
      }
   }
   new_image.save_image("rotated.bmp");
}

void rotateright(bitmap_image& img)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(height, width);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(height-y-1,x,red,green,blue);
      }
   }
   new_image.save_image("rotateright.bmp");
}

void translate(bitmap_image& img,int right,int down)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height-down; y++)
   {
      for (size_t x=0; x<width-right; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(x+right,y+down,red,green,blue);
      }
   }
   new_image.save_image("translated.bmp");
}

void wraparound(bitmap_image& img,int right,int down)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel((x+right)%width,(y+down)%height,red,green,blue);
      }
   }
   new_image.save_image("wrappedaround.bmp");
}

void vmirror(bitmap_image& img)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width/2; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(x,y,red,green,blue);
         new_image.set_pixel(width-x-1,y,red,green,blue);
      }
   }
   new_image.save_image("vmirror.bmp");
}

void fourinone(bitmap_image& img)
{
   unsigned char red;
   unsigned char green;
   unsigned char blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         new_image.set_pixel(x/2,y/2,red,green,blue);
         new_image.set_pixel(x/2 + width/2,y/2,red,green,blue);
         new_image.set_pixel(x/2,y/2 +height/2,red,green,blue);
         new_image.set_pixel(x/2+width/2,y/2 +height/2,red,green,blue);
      }
   }
   new_image.save_image("4in1.bmp");
}

int main()
{
   string img;
   float theta;
   float cost,sint;
   img = "input.bmp" ;
   theta = 0.45;
   cost=cos(theta);
   sint=sin(theta);

   bitmap_image image(img);

   if (!image)
   {
       printf("Error - Failed to open: input.bmp\n");
       return 1;
   }

   unsigned char red;
   unsigned char green;
   unsigned char blue;

   const unsigned int height = image.height();
   const unsigned int width  = image.width();

   bitmap_image new_image(width,height);


/* The following commmented code is for illustration of how to use 
 * the bitmap API for accessing and manipulating images.
 *
   // each image is represented as a set of pixels (height and width) 
   // with intensity levels of three colors/channels red, green, blue
   
   // create new 'blank' image with all pixel intensity values 
   // set at 0 for all colors (Note this image is complete black!)
   bitmap_image new_image(width,height);  
   
   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
         // get the red,green,blue intensity levels for pixel x,y
	 // intensity values vary from 0 to 255
         image.get_pixel(x,y,red,green,blue); 

	 // set intensity values for each channel for pixel x,y 
	 new_image.set_pixel(x,y,red,green,blue); 
      }
   }

   // save new image to a file black.bmp
   new_image.save_image("black.bmp"); 
   
   // print image statistics 
   printf("Image width and height: %d and %d\n", width, height);

   // create new image based on an existing image
   //bitmap_image new_image(image);  // create new_image, same as image!
   //new_image.save_image("output.bmp");  // saves  new_image as output.bmp
   */
   
   // call to functions for each type of operation
   hflip(image);
   vflip(image);
   rotate(image, theta);
   rotateright(image);
   vmirror(image);
   fourinone(image);

   //shift the image by 40 pixels to the right and 50 pixels down.
   translate(image,40, 50); 

   wraparound(image,40, 50);

   return 0;
}

