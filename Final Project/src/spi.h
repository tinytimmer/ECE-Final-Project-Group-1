#ifndef SPI_H
#define SPI_H

void SPI_MASTER_Init();
void write_execute(unsigned char CMD, unsigned char data);
void write_dogFace();
void write_bigDog();
void write_medDog();
void write_smallDog();
void write_arrow();
void write_arrowInverted();
void write_arrowFlashing(unsigned int num);
void display_8x8();

#endif