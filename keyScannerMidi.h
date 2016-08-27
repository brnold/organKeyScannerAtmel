/*
 * keyScannerMidi.h
 *
 * Created: 8/26/2016 5:56:00 PM
 *  Author: Benjamin Nold
 */ 


#ifndef KEYSCANNERMIDI_H_
#define KEYSCANNERMIDI_H_

#define _NOTEON 0x90
#define _NOTEOFF 0x80
#define _DEFAULTVELOCITY 0x69

void readManuals(void);
void readPedals(void);
void testPedals(void);
void parseLeft(char changedBits, char thePort, char offset, char channel);
void midiCommandToQueue(char channel, char cmd, char pitch);
void parseRight(unsigned char changedBits, char thePort, char offset, char channel);
void binaryCharPrint(char theNumber);
void binaryIntPrint(int theNumber);
unsigned char debounce(unsigned char currentbits, char number);



#endif /* KEYSCANNERMIDI_H_ */