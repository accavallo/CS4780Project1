//
//  blow.h
//  Proj1
//
//  Created by Tony on 7/2/16.
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//

#ifndef blow_h
#define blow_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int parray[];
extern unsigned int sbox0[];
extern unsigned int sbox1[];
extern unsigned int sbox2[];
extern unsigned int sbox3[];

struct lAndR {
    unsigned int l;
    unsigned int r;
};
void shifty(char **, int );
void print(char *);
struct lAndR* magicHappens(unsigned, unsigned, int);

unsigned int sBoxStuffHappens(unsigned int);
void splitKey(unsigned long);

#endif /* blow_h */
