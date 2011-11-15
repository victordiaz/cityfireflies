#include "perfectPixelsRescale.h"

//-------------------------------------------

perfectPixelsRescale::perfectPixelsRescale()
{
    newPixels = NULL;
}

//-------------------------------------------

perfectPixelsRescale::~perfectPixelsRescale()
{
    delete [] newPixels;
}

//-------------------------------------------

void perfectPixelsRescale::setSize(int _pixelSizeX,int _pixelSizeY, int _width, int _height)
{
	// Deallocate memory
	if( newPixels!=NULL ) delete [] newPixels;
	if( img.width>0 ) img.clear();
    // New size allocation
    pixelSizeX = _pixelSizeX;
    pixelSizeY = _pixelSizeY;
    width = _width;
    height = _height;
    totalPixel = (width*pixelSizeX)*(height*pixelSizeY)*3;
    newPixels = new unsigned char[totalPixel];
    // Equation for optimization (RGB pixel rescale)
    p1 = width*3;
    p2 = width*pixelSizeX*3;
    p3 = pixelSizeX*3;
	img.allocate(width*pixelSizeX, height*pixelSizeY, OF_IMAGE_COLOR );
}

//-------------------------------------------

void perfectPixelsRescale::resample(unsigned char* pixels) 
{
    for(int h=0; h<height;h++)
    {
        for(int w=0; w<width; w++)
        {
            int pixelId = (h*p1)+(p1- (w*3));
            unsigned char pixelRColor = pixels[pixelId];
            unsigned char pixelGColor = pixels[pixelId+1];
            unsigned char pixelBColor = pixels[pixelId+2];

            int p4 = h*pixelSizeY;

            for(int y=0; y<pixelSizeY; y++)
            {
                for(int x=0; x<pixelSizeX; x++)
                {
                   newPixels[ totalPixel-((((p4)+y)*(p2))+((w)*p3)+(x*3)) ]    = pixelRColor;
                   newPixels[ totalPixel-((((p4)+y)*(p2))+((w)*p3)+(x*3)) +1 ] = pixelGColor;
                   newPixels[ totalPixel-((((p4)+y)*(p2))+((w)*p3)+(x*3)) +2 ] = pixelBColor;
                }
            }
        }
    }
}

//-------------------------------------------

void perfectPixelsRescale::draw(int x, int y, bool alignCenter)
{
    ofPushMatrix();
    if(alignCenter)ofTranslate( (ofGetWidth()/2) - (width*pixelSizeX)/2, (ofGetHeight()/2) - (height*pixelSizeY)/2 );
    ofSetColor(255,255,255);
    img.setFromPixels(newPixels, width*pixelSizeX, height*pixelSizeY, OF_IMAGE_COLOR);
    img.update();
    img.draw(0,0);
    ofPopMatrix();
}

//-------------------------------------------

unsigned char* perfectPixelsRescale::getPixels()
{
	return newPixels;
}

//-------------------------------------------

ofImage perfectPixelsRescale::getImage()
{
    img.setFromPixels(newPixels, width*pixelSizeX, height*pixelSizeY, OF_IMAGE_COLOR);
    img.update();
	return img;
}

//-------------------------------------------

int perfectPixelsRescale::getPixelSizeX()
{
    return pixelSizeX;
}

//-------------------------------------------

int perfectPixelsRescale::getPixelSizeY()
{
    return pixelSizeY;
}

//-------------------------------------------

int perfectPixelsRescale::getWidth()
{
    return width;
}

//-------------------------------------------

int perfectPixelsRescale::getHeight()
{
    return height;
}

//-------------------------------------------

