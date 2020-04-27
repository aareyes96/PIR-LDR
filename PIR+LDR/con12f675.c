#include <12F675.h>
#device ADC=10

#FUSES NOWDT       //No Watch Dog Timer
#fuses INTRC_IO    //Internal RC Osc, no CLKOUT
#fuses PUT         //Power Up Timer
#fuses NOMCLR      //Master Clear pin used for I/O
#fuses BROWNOUT    //Reset when brownout detected
#fuses PROTECT     //Code protected from reads

#use delay(internal=4MHz)
#use FIXED_IO( A_outputs=PIN_A4,PIN_A0 )
#use rs232(baud=9600,parity=N,xmit=PIN_A0,rcv=PIN_A1,bits=8,stream=PORT1)

#define SETPOINT  512

int16 a=0,b=0;

int1 flag=0;

void main()
{
   port_A_pullups(0x20);
   setup_adc_ports(4);
   setup_adc(ADC_CLOCK_INTERNAL);
   set_adc_channel(2);
   output_bit(PIN_A4,0);
   delay_ms(1);   
   
   while(1)
   {
      a=read_adc();
      b=input(PIN_A5);
      printf("%lu  %lu\r\n",a,b);
      
     if(a >= SETPOINT) flag=1;
     else flag=0;
     
      if( flag==1 && b==1 )
      while(b) { output_bit(PIN_A4,1); b=input(PIN_A5); }
   
     else
         output_bit(PIN_A4,0);
         
      delay_ms(500);
   }

}
