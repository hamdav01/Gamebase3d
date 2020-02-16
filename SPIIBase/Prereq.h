// Prereq.h

#ifndef PREREQ_H_INCLUDED
#define PREREQ_H_INCLUDED

#include <string>
#include <vector>
#include <list>
#include <map>

// stl
typedef std::string String;
typedef std::vector<String> StringVector;

// primitives
typedef unsigned __int64 u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef u32 dword;
typedef u8 ubyte;
typedef __int64 s64;
typedef int s32;
typedef short s16;
typedef char s8;
typedef s32 word;
typedef float f32;
typedef double f64;

// internal
#include "spiiMath.h"

#define SAFE_RELEASE(x) if(x!=NULL) {x->Release();x=NULL;}
#define SAFE_DELETE(x) if(x!=NULL) {delete x;x=NULL;}
#define SAFE_DELETE_ARRAY(x) if(x!=NULL) {delete [] x;x=NULL;}

#endif // PREREQ_H_INCLUDED
