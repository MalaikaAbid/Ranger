#include <pic.h>
#include "Lab3_Config.h"
#include "Lab3_SPI.h"
#include "Lab3_SD.h"
#include "Functions_Globals.h"


void main(void) {

   // Set the system clock speed to 32MHz and wait for the ready flag.
   OSCCON = 0xF4;
   while(OSCSTATbits.HFIOFR == 0);

   //Initialize all required peripherals.
   SPI_Init();
   SD_Init();
    
   DAC5CON0 = 0xA0; //1010 0000
    
   TRISCbits.TRISC0 = 0; //set RC0 to be DAC output instead of RA2 (DAC5OUT1)
   
   TRISA = 0x0F; //set pins RA0-RA3 to inputs, set pins RA4 to RA7 as outputs
   
  
   ANSELAbits.ANSA0 = 0;
   ANSELAbits.ANSA1 = 0;
   ANSELAbits.ANSA2 = 0;
   ANSELAbits.ANSA3 = 0;
    
   Lab2_ConfigureTimer2(63);
   
   //how many bytes are we at in one block 
   int countBytes = 0;  

   //address of which block we are on
   char countBlock3 = 0;  
   char countBlock2 = 0;
   char countBlock1 = 0;
   char countBlock0 = 0;

   bool SongIsPlaying = false; 

    while(1)
    {
        //If song is not playing, check the button.
        //If the user input a song, set the addresses
        if(SongIsPlaying == false)
        {
            char check = buttonPress();
            //Button combination 65 is the atrium
            if (check == 65)
            {
                countBlock3 = atrium.start3;
                countBlock2 = atrium.start2;
                countBlock1 = atrium.start1;
                countBlock0 = atrium.start0;
                End3=atrium.end3;
                End2=atrium.end2;
                End1=atrium.end1;
                End0=atrium.end0;
                
                SongIsPlaying = true;
                
            } //end if buttonpress = 65
            
            if (check == 66)
             {  countBlock3 = eng60.start3;
                countBlock2 = eng60.start2;
                countBlock1 = eng60.start1;
                countBlock0 = eng60.start0;
                End3=eng60.end3;
                End2=eng60.end2;
                End1=eng60.end1;
                End0=eng60.end0;
                
                SongIsPlaying = true;
                
            } //end if buttonpress = 66
            
            if (check == 67){
                countBlock3 = enc70.start3;
                countBlock2 = enc70.start2;
                countBlock1 = enc70.start1;
                countBlock0 = enc70.start0;
                End3=enc70.end3;
                End2=enc70.end2;
                End1=enc70.end1;
                End0=enc70.end0;
                
                SongIsPlaying = true;
                
        
                
            } //end if buttonpress = 66
             
            if (check == 68){
                countBlock3 = enggLounge.start3;
                countBlock2 = enggLounge.start2;
                countBlock1 = enggLounge.start1;
                countBlock0 = enggLounge.start0;
                End3=enggLounge.end3;
                End2=enggLounge.end2;
                End1=enggLounge.end1;
                End0=enggLounge.end0;
                
                
                SongIsPlaying = true;
                
            } //end if buttonpress = 68
           
            
            if(check==2){ 
                countBlock3 = rm201.start3;
                countBlock2 = rm201.start2;
                countBlock1 = rm201.start1;
                countBlock0 = rm201.start0;
                End3=rm201.end3;
                End2=rm201.end2;
                End1=rm201.end1;
                End0=rm201.end0;

                SongIsPlaying = true;

                }
            
            if(check==1){
                countBlock3 = socialStairs.start3;
                countBlock2 = socialStairs.start2;
                countBlock1 = socialStairs.start1;
                countBlock0 = socialStairs.start0;
                End3=socialStairs.end3;
                End2=socialStairs.end2;
                End1=socialStairs.end1;
                End0=socialStairs.end0;

                SongIsPlaying = true;

                }
            
               if(check==3){
                countBlock3 = rm007.start3;
                countBlock2 = rm007.start2;
                countBlock1 = rm007.start1;
                countBlock0 = rm007.start0;
                End3=rm007.end3;
                End2=rm007.end2;
                End1=rm007.end1;
                End0=rm007.end0;

                SongIsPlaying = true;

                }
            
            if(check==5){
                
                countBlock3 = stopm.start3;
                countBlock2 = stopm.start2;
                countBlock1 = stopm.start1;
                countBlock0 = stopm.start0;
                End3=stopm.end3;
                End2=stopm.end2;
                End1=stopm.end1;
                End0=stopm.end0;

                SongIsPlaying = true;

                }
                
   
        } // end if songisplaying = false
        else //Songisplaying is true
        {
            //check if we are at the first byte in the block
            if (countBytes == 0) 
            {
                //send the command to start reading from the SD card
                SD_ReadBlock(countBlock3,countBlock2,countBlock1,countBlock0);  
            }
        
            //grab a value from the SPI
            char x = SPI_Read();
            //convert char value to short
            short y = x;
            //write the value from the SPI to the DAC
            Lab2_WriteDAQ(y);


            //go to the next byte in the block 
            countBytes++; 
            //check if we've reached the end of a 512 block of bytes        
            if (countBytes == 512){
                    //send a few reads to waste time 
                    SPI_Read();                                                            
                    SPI_Read();                                                            
                    SPI_Read();   
                    //ensure that we are starting the next block at byte 0
                    countBytes = 0;

                    //go to the next block of bytes    
                    INCREMENT_BLOCK(countBlock3,countBlock2,countBlock1,countBlock0);
                    //are we at the last block?
                    
                    if (countBlock3 == End3 && countBlock2 == End2 && countBlock1== End1 && countBlock0 == End0){
                        
                        SongIsPlaying = false;
                        
                    }
                        
                        
                    
            }
        } // end if songIsPlaying == true
        
        while(!PIR1bits.TMR2IF);
        
        PIR1bits.TMR2IF = 0;
        
        
     
    } //End of while(1)    
          
      
    return;    
}
      
    

