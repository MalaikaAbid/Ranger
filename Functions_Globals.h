#ifndef FUNCTIONS_GLOBALS_H
#define FUNCTIONS_GLOBALS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic.h>

/* ---------------------------- Global Variables ---------------------------- */
struct Audio {
        char start3;
        char start2;
        char start1;
        char start0;
        
        char end3;
        char end2;
        char end1;
        char end0;
    };
    
    
struct Audio atrium = {0, 0, 0, 0, 0, 0, 1, 92}; //A
struct Audio eng60 = {0, 0, 1, 93, 0, 0, 3, 70}; //B
struct Audio enc70 = {0, 0, 3, 71, 0, 0, 5, 61 }; //C
struct Audio enggLounge = {0, 0, 5, 62, 0, 0, 6, 93 }; //D
struct Audio socialStairs = {0, 0, 6, 94, 0, 0, 7, 203}; //1
struct Audio rm201 = {0, 0, 7, 204, 0, 0, 9, 63}; //2
struct Audio rm007 = {0, 0, 9, 64, 0, 0, 11, 106}; //3
struct Audio stopm = {0,0,11, 107, 0, 0, 11, 205}; //5



char Start3;
char Start2;
char Start1;
char Start0;

char End3;
char End2;
char End1;
char End0;



/* -------------------------- Function Prototypes --------------------------- */
void Lab2_ConfigureTimer2(char TimerPeriod_us);
void Lab2_WriteDAQ(short WriteValue);
char buttonPress(void);


/* ------------------ #define based Function Declarations ------------------- */

//the following essentially checks if we have reached the address for the
//last byte in the file
//sets the address back to zero so that we can start the file over
#define CHECK_END_OF_FILE(block3,block2,block1,block0,End3, End2, End1, End0){             \
    if (block3==0 && block2==0 && block1==End1 && block0==End0)          \
    {                                                               \
        block3=0;                                                   \
        block2=0;                                                   \
        block1=0;                                                   \
        block0=0;                                                   \
    }                                                               \
}
    
//checks if we have reached the last byte in the block
//then increments to the next block of bytes
#define INCREMENT_BLOCK(Block3,Block2,Block1,Block0){               \
    if (++Block0 == 0){                                             \
        if (++Block1 == 0){                                         \
            if (++Block2 == 0){                                     \
                Block3++;                                           \
            }                                                       \
        }                                                           \
    }                                                               \
}


#endif	/* FUNCTIONS_GLOBALS_H */

