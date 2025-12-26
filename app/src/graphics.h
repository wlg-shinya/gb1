#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

extern const uint16_t bkg_p[];
extern const uint16_t obj_p[];

void init_graphics( void );
void set_sprite_attrb( uint8_t nb, uint8_t tile );
void set_bkg_attr( uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, unsigned char *d );

#endif