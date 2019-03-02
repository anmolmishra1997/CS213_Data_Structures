#include <cstdio>
#include <math.h>
#include <iostream>
#include <math.h>
#include "bitmap_image.hpp"
using namespace std;


void biaspixel(bitmap_image&);
void scale(bitmap_image&);

void biaspixel(bitmap_image& img)
{
	unsigned char red, green, blue;
	unsigned char redcandidate = 0, greencandidate = 0, bluecandidate = 0;
	int redcount = 0, greencount =0, bluecount =0;
	int finalredcount = 0, finalgreencount =0, finalbluecount =0;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(img);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         if ( red == redcandidate)
         	redcount+=1;
         else
         	redcount-=1;
         if ( redcount <=0)
         {
         	redcount =1;
         	redcandidate = red;
         }
         if ( green == greencandidate)
         	greencount+=1;
         else
         	greencount-=1;
         if ( greencount <=0)
         {
         	greencount =1;
         	greencandidate = green;
         }
         if ( blue == bluecandidate)
         	bluecount+=1;
         else
         	bluecount-=1;
         if ( bluecount <=0)
         {
         	bluecount =1;
         	bluecandidate = blue;
         }
      }
   }
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         if ( red == redcandidate)
         	finalredcount+=1;
         if ( green == greencandidate)
         	finalgreencount+=1;
         if ( blue == bluecandidate)
         	finalbluecount+=1;
      }
   }
   if ( finalredcount > width*height)
   {
   	for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         if ( red!= redcandidate)
         	new_image.set_pixel(x,y,0,green,blue);
      }
   }
   }
   if ( finalbluecount > width*height)
   {
   	for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         if ( blue!= bluecandidate)
         	new_image.set_pixel(x,y,red,green,0);
      }
   }
   }
   if ( finalgreencount > width*height)
   {
   	for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         if ( green!= greencandidate)
         	new_image.set_pixel(x,y,red,0,blue);
      }
   }
   }
   new_image.save_image("output.bmp");
}
void scale(bitmap_image& img)
{
   unsigned char red, green, blue;
   img.get_pixel(0,0,red,green,blue);
   unsigned char maxred =red,maxgreen = green,maxblue = blue,minred =red,mingreen = green,minblue = blue;
   const unsigned int height = img.height();
   const unsigned int width  = img.width();
   bitmap_image new_image(width, height);
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         maxred = max(red, maxred);
         maxblue = max(blue, maxblue);
         maxgreen = max(green, maxgreen);
         minred = min(red, minred);
         minblue = min(blue, minblue);
         mingreen = min(green, mingreen);
      }
   }
   for (size_t y =0; y<height; y++)
   {
      for (size_t x=0; x<width; x++)
      {
         img.get_pixel(x,y,red,green,blue);
         unsigned char newred = (red-minred) * 255.0/(maxred-minred);
         unsigned char newgreen = (green-mingreen) * 255.0/(maxgreen-mingreen);
         unsigned char newblue = (blue-minblue) * 255.0/(maxblue-minblue);
         new_image.set_pixel(x,y,newred,newgreen,newblue);
      }
   }
   new_image.save_image("scaled.bmp");
}

int main()
{
   string img;
   img = "input2.bmp" ;

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
   
   // for each of the 3 colors zero-out all pixels other than pixels biased with value.
   biaspixel(image);

   // scale image intensities to 0 to 255
   scale(image);

   return 0;
}


