#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>   
#include <stddef.h>   
#include <stdbool.h>  

#ifndef NULL
#define NULL ((void *)0)
#endif
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;

typedef uint64 pde_t;

#endif 
