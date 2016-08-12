//
//  encryption.c
//  Proj1
//
//  Created by Tony on 7/10/16.
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//

#include "blow.h"

//We collect the pieces from the key, or message, so we can change around the next entry.
unsigned int sBoxStuffHappens(unsigned int R) {
    
    unsigned a = 0, b = 0, c = 0, d = 0;
    
    a = R >> 24;    // Collect the left-most 8 bits of the hex number
    b = R << 8;     //Collect the middle-left 8 bits of the hex number
    b >>= 24;
    c = R << 16;    //Collect the middle-right 8 bits of the hex number
    c >>= 24;
    d = R << 24;    //Collect the right-most 8 bits of the hex number
    d >>= 24;
    
//    printf("%u\t%u\t%u\t%u\n", a, b, c, d);
    
    return ((sbox0[a] + sbox1[b]) ^ sbox2[c]) + sbox3[d];
}

//All that these for loops do, all six of them, is rearrange a bunch of stuff a lot of times, all in the name of encryption. This is before anything actually gets XOR'd with the message.
void splitKey(unsigned long key) {
    unsigned long lKey, rKey;
    
    lKey = key >> 32;
    rKey = key << 32;
    rKey >>= 32;
    
//    printf("lKey = %lu\trKey = %lu\n", lKey, rKey);
    int i = 0;
    for (; i < 18; i++) {
        if (i % 2 == 0) {
            parray[i] ^= lKey;
        } else {
            parray[i] ^= rKey;
        }
    }
    
    unsigned int L = 0, R = 0;
    struct lAndR *nums = malloc(sizeof(struct lAndR));
    
    //for loop 18 for parray
    for(i = 0; i < 18; i+=2) {
        nums = magicHappens(L, R, 0);
        L = nums->l; R = nums->r;
        parray[i] = L; parray[i+1] = R;
//        printf("End iteration %i: L = %x\tR = %x\n", i, L, R);
    }
    
    //for loop 256 for sbox0
    for(i = 0; i < 256; i+=2) {
        nums = magicHappens(L, R, 0);
        L = nums->l; R = nums->r;
        sbox0[i] = L; sbox0[i+1] = R;
    }
    
    //for loop 256 for sbox1
    for(i = 0; i < 256; i+=2) {
        nums = magicHappens(L, R, 0);
        L = nums->l; R = nums->r;
        sbox1[i] = L; sbox1[i+1] = R;
    }
    
    //for loop 256 for sbox2
    for(i = 0; i < 256; i+=2) {
        nums = magicHappens(L, R, 0);
        L = nums->l; R = nums->r;
        sbox2[i] = L; sbox2[i+1] = R;
    }
    
    //for loop 256 for sbox3
    for(i = 0; i < 256; i+=2) {
        nums = magicHappens(L, R, 0);
        L = nums->l; R = nums->r;
        sbox3[i] = L; sbox3[i+1] = R;
    }
}

//We XOR a couple things with the integers sent. Whether this is the key splitting for the parray and sboxes or the message itself, both go through this process.
struct lAndR * magicHappens(unsigned L, unsigned R, int printStuff) {
    unsigned prevL, prevR;
    struct lAndR *nums = malloc(sizeof(struct lAndR));
    
    int i = 0;
    for (; i < 16; i++) {
        prevL = L;
        prevR = R;
        
        R = L ^ parray[i];
        L = sBoxStuffHappens(R) ^ prevR;
    }
    prevR = R;
    prevL = L;
    
    L = prevR ^ parray[17];
    R = prevL ^ parray[16];
    
    nums->l = L;
    nums->r = R;
    
    if(printStuff == 1)
        printf("%x%x\n", L, R);
//    printf("%x %x\n", nums->l, nums->r);
    
    return nums;
}
