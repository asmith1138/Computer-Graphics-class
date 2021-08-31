/*********************************************************************
 *  CMPSC 457 Section 001                                            *
 *  Code for Homework 1                                              *
 *  September 2, 2021                                                *
 *  Andrew Smith                                                     *
 *  azs7014                                                          *
 *********************************************************************/  

/*********************************************************************
 *                                                                   *
 *                                                                   *
 *     Put your answer to the written part of assignment here        *
 *                                                                   *
 *                                                                   *
 *********************************************************************/



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
            raster[h][w].r = static_cast<float>(col);
            raster[h][w].g = static_cast<float>(col & 0x00);
            raster[h][w].b = static_cast<float>(col & 0x11);
        }
    }

    ofstream ppmFile;
    ppmFile.open(filename);
    int tf = 255;
    
    if(!ppmFile){
        cout << "File creation failed, please try again." << endl;
    }else {
		cout << "File created/opened successfully!" << endl;
		ppmFile << "P3" << endl << width << " " << height << endl << "255" << endl;
		
        for(int r = 0; r < height; r++){
            for(int c = 0; c < width; c++){
                ppmFile << tf*raster[r][c].r << " " << tf*raster[r][c].g << " " << tf*raster[r][c].b << " ";
            }
            ppmFile << endl;
        }
        cout << "File written successfully!" << endl;
        
        
        ppmFile.close();
	}


    //Free space used by raster
    for(int i=0;i<height;i++)    //delete inner arrays
      delete [] raster[i]; 
    delete [] raster;
    return 0;
}

