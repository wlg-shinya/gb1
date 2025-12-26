#ifndef UI_H
#define UI_H

#include <gb/gb.h>
#include <stdint.h>

void init_ui( void );
void init_score( void );
void show_score( uint16_t s );
void set_level( uint8_t i );
void show_level( uint8_t i );
void show_gover( void );
void show_pause( void );
void hide_msg( void );

#endif