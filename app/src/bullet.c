#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "bullet.h"
#include "fore.h"
#include "game.h"
#include "graphics.h"
#include "player.h"

uint8_t tf[MAX_TT];
uint8_t tx[MAX_TT], ty[MAX_TT];

void init_tama(void)
{
  uint8_t i;

  for( i=0; i<MAX_TT; i++ ) {
    tf[i] = 0;
    tx[i] = i*4+DEF_TX;
    ty[i] = DEF_TY;
    set_sprite_tile( i+DEF_TS, tf[i]+DEF_TC );
    set_sprite_attrb( i+DEF_TS, foreCGB[tf[i]+DEF_TC] );
    move_sprite( i+DEF_TS, tx[i], ty[i] );
  }
}

void bombs(void)
{
   uint8_t i;

   for( i=0; i<MAX_TT; i++ ) {
    if( tf[i] != 0 ) {
      ty[i]++;
      if( ty[i] > MAX_TY ) {
        tf[i] = 0; tx[i] = i*4+DEF_TX; ty[i] = DEF_TY;
      } else {
        tf[i] = 3-tf[i];
      }
      set_sprite_tile( i+DEF_TS, tf[i]+DEF_TC );
      set_sprite_attrb( i+DEF_TS, foreCGB[tf[i]+DEF_TC] );
      move_sprite( i+DEF_TS, tx[i], ty[i] );
    }
  }
}