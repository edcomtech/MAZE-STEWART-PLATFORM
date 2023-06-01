#include <16f877a.h>
#fuses HS,NOWDT,NOPROTECT,NOPUT,NOLVP,NOBROWNOUT
#use delay(clock=20000000)
#use RS232(BAUD=9600, BITS=8, PARITY=N, XMIT=PIN_C6, RCV=PIN_C7)    
#use standard_io(B)
#include <lcd_d.c>
#include <stdio.h>

#define use_servo_1                                   
#define use_servo_2                                   
#define use_servo_3                                   

#define servo_1 PIN_E0                                
#define servo_2 PIN_E1                                
#define servo_3 PIN_E2                                

#include <servo_st.c>                                 

char dato_rx;
int pos1,pos2,pos3;
int wins=0;
short status=0;

#INT_RDA
void interrupcion_RDA(){
 
   dato_rx = getc();
   
   if(dato_rx=='j')
   {
        pos1 = getc();
        pos2 = getc();
        pos3 = getc(); 
   }

}

void main()
{
   lcd_init();
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   input(PIN_A1);
   servo_init();                                      
   servo_1_write(0);                                  
   servo_2_write(0);
   servo_3_write(0);
   delay_ms(1000);
   
   wins = read_eeprom(0); 
   
   while(true){
      
      switch(dato_rx){
      
      case 'r':
      servo_1_write(0); 
      if(dato_rx == 's')break;
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_2_write(0);
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_3_write(0);
      delay_ms(500);
      if(dato_rx == 's')break;
      
      servo_2_write(90);
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_1_write(90);
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_3_write(90);
      delay_ms(500);
      if(dato_rx == 's')break;
      
      servo_1_write(20);
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_2_write(0);
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_3_write(35);
      delay_ms(500);
      if(dato_rx == 's')break;
      
      servo_2_write(130);
      delay_ms(2000);
      if(dato_rx == 's')break;
      
      servo_1_write(90); 
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_2_write(90);
      delay_ms(500);
      if(dato_rx == 's')break;
      servo_3_write(90);
      delay_ms(500);
      if(dato_rx == 's')break;
      dato_rx = ' ';
      break;
      
      case 's':
      lcd_gotoxy(1,1);
      printf(lcd_putc,"RESETTING");
      servo_1_write(0); 
      delay_ms(500);
      servo_2_write(0);
      delay_ms(500);
      servo_3_write(0);
      delay_ms(500);
      dato_rx = ' ';
      break;
      
      case 'j':
      servo_1_write(pos1);                                 
      servo_2_write(pos2);
      servo_3_write(pos3);
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fYOU WON!");
      dato_rx = ' ';
      break;
      }
      
      if(input(PIN_A1)==0 && status==1){ 
      read_eeprom(0);
      wins+=1;
      write_eeprom(0,wins);
      printf("%u", wins);
      printf(lcd_putc,"\fYOU WON!, %u", wins);
      delay_ms(100);
      } else{
      lcd_gotoxy(1,1);
      printf(lcd_putc,"\fPLAY THE MAZE!!! \nGAMES WON: %u", wins);
      delay_ms(100);
      }
      status=input(PIN_A1);
      delay_ms(100);
      
      
   }
}
