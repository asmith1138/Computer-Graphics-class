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
//using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 4){
        std::cout << "Please use the format: 'program <width> <height> <output filename>' to run this program" << std::endl;
    }

    std::string filename = argv[3];
    int width = static_cast<int>(*argv[1]);
    int height = static_cast<int>(*argv[2]);

    return 0;
}

struct RGB {
    float r;
    float g;
    float b;
};