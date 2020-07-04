//Jason Nguyen 
//CSCI 2400
//Sandesh
//Performance Lab

/* Original
#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;


  for(int col = 1; col < (input -> width) - 1; col = col + 1) {
    for(int row = 1; row < (input -> height) - 1 ; row = row + 1) {
      for(int plane = 0; plane < 3; plane++) {

	output -> color[plane][row][col] = 0;

	for (int j = 0; j < filter -> getSize(); j++) {
	  for (int i = 0; i < filter -> getSize(); i++) {	
	    output -> color[plane][row][col]
	      = output -> color[plane][row][col]
	      + (input -> color[plane][row + i - 1][col + j - 1] 
		 * filter -> get(i, j) );
	  }
	}
	
	output -> color[plane][row][col] = 	
	  output -> color[plane][row][col] / filter -> getDivisor();

	if ( output -> color[plane][row][col]  < 0 ) {
	  output -> color[plane][row][col] = 0;
	}

	if ( output -> color[plane][row][col]  > 255 ) { 
	  output -> color[plane][row][col] = 255;
	}
      }
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}



*/ 


#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"
#include <omp.h>

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);

double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int main(int argc, char **argv)
{

    if ( argc < 2) {
        fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
    }

  //
  // Convert to C++ strings to simplify manipulation
  //
    string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
    string filterOutputName = filtername;
    string::size_type loc = filterOutputName.find(".filter");
    if (loc != string::npos) {
        //
        // Remove the ".filter" name, which should occur on all the provided filters
        //
        filterOutputName = filtername.substr(0, loc);
    }

    Filter *filter = readFilter(filtername);

    double sum = 0.0;
    int samples = 0;

    for (int inNum = 2; inNum < argc; inNum++) {
        string inputFilename = argv[inNum];
        string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
        struct cs1300bmp *input = new struct cs1300bmp;
        struct cs1300bmp *output = new struct cs1300bmp;
        int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

        if( ok ) {
          double sample = applyFilter(filter, input, output);
          sum += sample;
          samples++;
          cs1300bmp_writefile((char *) outputFilename.c_str(), output);
        }
        delete input;
        delete output;
    }
    fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);
}


struct Filter *readFilter(string filename)
{
    ifstream input(filename.c_str());

    //move declarations outside of loop
    int size = 0; 
    int div;
    int value;
    if (! input.bad()) 
    {
        input >> size;
        Filter *filter = new Filter(size);
        input >> div;
        filter -> setDivisor(div);
      
        for (int i=0; i < size; i++) 
        {
            for (int j=0; j < size; j++) 
            {
                input >> value;
                filter -> set(i,j,value);
            }
        }
  
    return filter;
    }
    
    else 
    {
        cerr << "Bad input in readFilter:" << filename << endl;
        exit(-1);
    }
    
}
   

double applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output){

  long long cycStart, cycStop;

  cycStart = rdtscll();

  output -> width = input -> width;
  output -> height = input -> height;


  //for(int col = 1; col < (input -> width) - 1; col = col + 1) {
  //  for(int row = 1; row < (input -> height) - 1 ; row = row + 1) {
   //   for(int plane = 0; plane < 3; plane++) {
    
    int H_ = (input -> height) - 1;
    int W_ = (input -> width) - 1;       
    int Fsize = filter -> getDivisor();
    int plane = 0;
    int row;
    int col;
    
    
    //hard codes the pixels of a 3x3 grid
    unsigned int pix1,pix2,pix3,pix4,pix5,pix6,pix7,pix8,pix9;
    pix1 = filter -> get(0,0);
    pix2 = filter -> get(0,1);
    pix3 = filter -> get(0,2);
    pix4 = filter -> get(1,0);
    pix5 = filter -> get(1,1);
    pix6 = filter -> get(1,2);
    pix7 = filter -> get(2,0);
    pix8 = filter -> get(2,1);
    pix9 = filter -> get(2,2);
    
    unsigned int loopOutput;
    
    
    #pragma omp parallel for    
    for(plane = 0; plane < 3; ++plane) {
        for(row = 1; row < H_ ; ++row) {
            for(col = 1; col < W_; ++col) {
              loopOutput = 0;
              loopOutput = (input -> color[plane][row-1][col] * pix2);   //loops through 3 items instead of 5
              loopOutput += (input -> color[plane][row-1][col-1] * pix1);
              loopOutput += (input -> color[plane][row-1][col+1] * pix3);
              
              loopOutput += (input -> color[plane][row][col] * pix5);
              loopOutput += (input -> color[plane][row][col-1] * pix4);
              loopOutput += (input -> color[plane][row][col+1] * pix6);
             
              loopOutput += (input -> color[plane][row+1][col] * pix8);
              loopOutput += (input -> color[plane][row+1][col-1] * pix7);
              loopOutput += (input -> color[plane][row+1][col+1] * pix9);
                      
                
              output -> color[plane][row][col] = loopOutput;
	
              if(Fsize > 1)
              {
                output -> color[plane][row][col] = output -> color[plane][row][col] / Fsize;
              }
              else if ( output -> color[plane][row][col]  < 0 ) 
              {
                  output -> color[plane][row][col] = 0;
              }

              else if ( output -> color[plane][row][col]  > 255 ) 
              { 
                  output -> color[plane][row][col] = 255;
              }
            }
         }
       }

      cycStop = rdtscll();
      double diff = cycStop - cycStart;
      double diffPerPixel = diff / (output -> width * output -> height);
      fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
          diff, diff / (output -> width * output -> height));
      return diffPerPixel;
}