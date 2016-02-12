#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

inline int randInt(int x, int y) {return rand()%(y-x+1)+x;}
inline double randFloat() {return (rand())/(RAND_MAX+1.0);}
inline bool randbool(){
    if(randInt(0,1)) return true;
    else return false;
}
inline double randomClamped() {return randFloat() - randFloat();}

#endif
