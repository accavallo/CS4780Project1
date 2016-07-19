//
//  main.c
//  Proj1
//
//  Created by Tony on 6/28/16.
//  Copyright © 2016 Anthony Cavallo. All rights reserved.
//  This program uses the Blowfish encryption algorithm to encrypt a message from stdin with a key as one of the command-line inputs.

#include "blow.h"

int main(int argc, const char * argv[]) {
    
    unsigned long key = strtol(argv[1], NULL, 16);
//    printf("The key is %lu\n", key);
    
    splitKey(key);
    
    unsigned long count = 0;
    
    char *msg;// = "This is a test.\nIt is not a very good test.\nBut a test nontheless.\n";
    int i = 0;

    msg = malloc(sizeof(char *));
    
    char words[1024];
    while((fgets(words,1024,stdin)) != NULL) {
//        printf("%lu\n", strlen(words));
        //Since we don't know how big the message actually is, we just keep reallocating memory to msg for the current size plus whatever is coming in next.
        msg = realloc(msg, strlen(msg) + strlen(words));
        //After which we concatenate the previous message with what just came in from stdin.
        strcat(msg, words);
        i++;
    }
    
    unsigned int L = 0, R = 0;
    
//    printf("L = %u\tR = %u\tstrlen(msg) = %lu\n", L, R, strlen(msg));
//    printf("%lu\n", (strlen(msg) % 8));
    //We have to get an accurate count of how big the message is. That way, we can extend the count to pad the message with 0's to the next byte.
    if(strlen(msg) % 8 == 0) {
        count = strlen(msg);
    } else {
        count = strlen(msg) / 8 + 1;
        count *= 8;
    }
    
//    printf("count = %lu\n", count);
    //With this for loop, we iterate through the entire message, along with any additional bytes up to the next mod 8 if necessary to ensure that we are packing with zeroes.
    int index = 0;
    for(i = 0; i < count; i++) {
        if(i < strlen(msg)) {
//            printf("index = %i\n", index);
            if(index < 4) {
//                printf("Byte: %x\tShifted: %x\n", msg[i], msg[i] << 8);
                L = L | msg[i];
                if(index != 3)
                    L <<= 8;
            } else {
//                printf("Byte: %x\tShifted: %x\n", msg[i], msg[i] << 8);
                R = R | msg[i];
                if(index != 7)
                    R <<= 8;
            }
            index++;
            if(index >= 8) {
//                printf("L = %x\n", L);
//                printf("R = %x\n", R);
                index = 0;
                
                magicHappens(L, R, 1);
                L = 0; R = 0;
            }
        } else {
            if(index < 4)
                L <<= 8 * (4 - index);
            R <<= 8 * (8 - index);
            magicHappens(L, R, 1);
            
            break;
        }
    }
    
    //print(msg);
    free(msg);  //Don't forget to free memory with char stars
    
    return 0;
}

//Useless leftover method I didn't feel like deleting. It's just too pretty.
void print(char * msg) {
    int i;
    for(i = 0; i < strlen(msg); i++) {
        printf("%c", msg[i]);
    }
}
