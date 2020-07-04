// Original Code 
/*
#include "Filter.h"
#include <iostream>

Filter::Filter(int _dim)
{
  divisor = 1;
  dim = _dim;
  data = new int[dim * dim];
}

int Filter::get(int r, int c)
{
  return data[ r * dim + c ];
}

void Filter::set(int r, int c, int value)
{
  data[ r * dim + c ] = value;
}

int Filter::getDivisor()
{
  return divisor;
}

void Filter::setDivisor(int value)
{
  divisor = value;
}

int Filter::getSize()
{
  return dim;
}

void Filter::info()
{
    //Unrolled the heck out of this loop
    cout << "Filter is.." << endl;
    cout << get(0,0) << " ";
    cout << get(0,1) << " ";
    cout << get(0,2) << " ";
    cout << get(1,0) << " ";
    cout << get(1,1) << " ";
    cout << get(1,2) << " ";
    cout << get(2,0) << " ";
    cout << get(2,1) << " ";
    cout << get(2,2) << " ";

    cout << endl;
}
*/


/*
#include "Filter.h"
#include <iostream>

Filter::Filter(int div){   //hardcoding values in for variables so that the computer would not have to deal with transfering variables.
  divisor = div;
  dim = 3;
  data = new int[9];
}

int Filter::get(int r){   //same as above
  return data[r];
}

void Filter::set(int r, int value){   //same as above
  data[r] = value;
}

int Filter::getDivisor(){
  return divisor;
}

int Filter::getSize(){
  return 3;
}

void Filter::info(){
    cout << "Filter is.." << endl;
    cout << get(0) << " ";
    cout << get(1) << " ";
    cout << get(2) << " ";
    cout << get(3) << " ";
    cout << get(4) << " ";
    cout << get(5) << " ";
    cout << get(6) << " ";
    cout << get(7) << " ";
    cout << get(8) << " ";

    cout << endl;

}

*/

#include "Filter.h"
#include <iostream>

Filter::Filter(int div)
{
  divisor = div;
  dim = 3;
  data = new int[9];
}

int Filter::get(int r, int c)
{
  return data[ r * dim + c ];
}

void Filter::set(int r, int c, int value)
{
  data[ r * dim + c ] = value;
}

int Filter::getDivisor()
{
  return divisor;
}

void Filter::setDivisor(int value)
{
  divisor = value;
}

int Filter::getSize()
{
  return 3;
}

void Filter::info()
{
    //Unrolled the heck out of this loop
    cout << "Filter is.." << endl;
    cout << get(0,0) << " ";
    cout << get(0,1) << " ";
    cout << get(0,2) << " ";
    cout << get(1,0) << " ";
    cout << get(1,1) << " ";
    cout << get(1,2) << " ";
    cout << get(2,0) << " ";
    cout << get(2,1) << " ";
    cout << get(2,2) << " ";

    cout << endl;
}