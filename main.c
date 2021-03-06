/*
 * main.c
 *
 * Created: 8/24/2016 6:12:14 PM
 *  Author: Benjamin Nold
 */ 

 #include "globalInclude.h"
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include "keyScannerMidi.h"
 #include "serial.h"
 #include "circularQueue.h"



 //This is the transmitter ISR
  ISR(USART0_UDRE_vect)
  {
	  //do something here

	  if(isEmpty(&serialOutQueue)==0){
		  //data is empty, so stop the interrupt
		  TX0_INTERRUPT_OFF; //will this work?
		  
	  }else
	  UDR0 = dequeue(&serialOutQueue);
  }


 ISR(USART2_UDRE_vect)
 {
	 //do something here

	 if(isEmpty(&midiOutQueue)==0){
		 //data is empty, so stop the interrupt
		 TX2_INTERRUPT_OFF; //will this work?
		 
	 }else
	 UDR2 = dequeue(&midiOutQueue);
 }


 int main(void)
 {
 /**
 * PORT A, C, and K are used for the manuals
 * PORT L, B and some pins from G are used for the pedals
 */
 
 //----------Keys---------
  //PA7 = 29-> PA0 = 22
  DDRA = 0b00000000;//set as inputs
  //PC = 37 -> PC0 = 30
  DDRC = 0b00000000; //set as inputs
  DDRK = 0b11111111; //set as outputs
  //----------Pedals-----------
  DDRL = 0x00; 
  DDRB = 0x00;
  DDRG = 0x03;
  
  /* Initiate MIDI */
  //midi is 31250
  //Serial.begin(115200);
  //Serial.begin(31250);
  USART0_Init(MIDI_BAUD_PRESCALE);
  USART2_Init(MIDI_BAUD_PRESCALE);
 


  /* Initiate Message Buffer */
  //midiMessageBuffer.init(100);
  setupQueue(&serialOutQueue);
  setupQueue(&midiOutQueue);
  sei();

  while(1){

  //enqueue(&serialOutQueue, 'h');
  //TX0_INTERRUPT_ON;


  // put your main code here, to run repeatedly:
  readManuals();
  //testPedals();
  readPedals();
  //  PORTL = 0x08;
  //  binaryCharPrint(PINC);
  //  binaryCharPrint(debounce(PINC, 1));
  //  Serial.println("%");
  //-----------------------

  /* Convert to interrupt based */
  //while(midiMessageBuffer.getSize() >0){
	  //Serial.write(midiMessageBuffer.get());
  //}
  
  _delay_ms(5);
 
  }

 }