/*********************************************************************
 *  CMPSC 457 Section 001                                            *
 *  Code for Homework 1                                              *
 *  September 2, 2021                                                *
 *  Andrew Smith                                                     *
 *  azs7014                                                          *
 *********************************************************************/  

/*************************************************************************
 * First, I will explain this part ((w & 0x08) == 0) ^ ((h & 0x08) == 0);*
 * This takes the column and uses bitwise AND with 0x08(hex value) to    *
 * transform it, since 0x08 is binary 1000 only w values with a 1 in the *
 * 8s place will result in a value of 8, otherwise it will be 0, the h   *
 * or row value will have the same effect in its own bitwise operation.  *
 * This means that every 8 values will switch from a result of 8 and a   *
 * result of 0, 0 results will return true due to the ==0 and 8 will be  *
 * false.  Finally, the ^ or XOR will return a true if only 1 of the     *
 * column or row values results in a 1 in the 8s place.  This gives a    *
 * checkerboard pattern of size 8 pixels.  To change this we can change  *
 * the 0x08 to another number with a binary representation that only has *
 * one 1 in it.  Such as 0x04 for checkerboard spaces half the size or   *
 * 0x10 for twice the size, other options(0x02,0x20,0x40,etc.).          *
 * 
 * Second, the static casts to float of col.  At this point col is       *
 * either 1 or 0.  A bitwise AND will compare 0x00 or 0x11 to 1 or 0,    *
 * this comes to 00001 & 00000 or 00001 & 10001. This means the 1 value  *
 * always returns 1 for both r(since no operation is done) and b(since   *
 * 00001 and 10001 both have a 1 in the 1s place), while g always is     *
 * 0 because of the 00000 value. The 0 value for col always continues to *
 * be 0, this means the checkerboard is black(0,0,0) or magenta(1,0,1).  *
 * To change this we would need to change the bitwise & values in the    *
 * static cast, but since we are starting with a 1 or 0 we don't have a  *
 * way to set rgb values other than 0 or 255.  Since we will be          *
 * multiplying the resulting 1 or 0 with 255 prior to writing to the ppm *
 * file.
 * 
 * We multiply the 1 or 0 in the raster by 255 so that the ppm will      *
 * show the full color or not. The raster holds values between 1 and 0,  *
 * while the ppm file uses 0 to 255 to convey the same information.      *
 ************************************************************************/



//////////////////     YOUR PROGRAM GOES HERE    /////////////////////
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct RGB {
    float r;
    float g;
    float b;
};

int main(int argc, char* argv[])
{
    if(argc < 4){
        cout << "Please use the format: 'program <width> <height> <output filename>' to run this program" << endl;
    }

    char* filename = argv[3];
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    cout << width << endl;
    cout << height << endl;

    //initialization
    RGB** raster = new RGB*[height];
    for(int i = 0; i < height; i++){
        raster[i] = new RGB[width];
    }

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            int col = ((w & 0x08) == 0) ^ ((h & 0x08) == 0);
            cout << col << " " << (col & 0x00) << " " << (col & 0x10) << " " << endl;
            raster[h][w].r = static_cast<float>(col);
            raster[h][w].g = static_cast<float>(col & 0x00);
            raster[h][w].b = static_cast<float>(col & 0x11);
        }
        cout << endl;
    }

    ofstream ppmFile;
    ppmFile.open(filename);
    int tf = 255;
    
    if(!ppmFile){
        cout << "File creation failed, please try again." << endl;
    }else {
		cout << "File created/opened successfully!" << endl;
		ppmFile << "P3" << endl << width << " " << height << endl << "255" << endl;
		
        for(int r = height-1; r >= 0; r--){
            for(int c = 0; c < width; c++){
                ppmFile << (tf * raster[r][c].r) << " " << (tf * raster[r][c].g) << " " << (tf * raster[r][c].b) << " ";
            }
            ppmFile << endl;
        }
        cout << "File written successfully!" << endl;
        
        
        ppmFile.close();
        cout << "File closed." << endl;
	}


    //Free space used by raster
    for(int i=0;i<height;i++)    //delete inner arrays
      delete [] raster[i]; 
    delete [] raster;

    cout << "Memory cleaned up.";
    return 0;
}

