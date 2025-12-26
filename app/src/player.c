#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdlib.h>
#include <rand.h>

#include "bullet.h"
#include "enemy.h"
#include "fore.h"
#include "graphics.h"
#include "kirai.h"
#include "player.h"
#include "ui.h"

uint8_t pf;
uint8_t px;

void init_player(void)
{
  pf = 0; px = DEF_PX;
  set_sprite_tile( 0, 0 );
  set_sprite_attrb( 0, foreCGB[0] );
  move_sprite( 0, px, DEF_PY );
  set_sprite_tile( 1, 1 );
  set_sprite_attrb( 1, foreCGB[1] );
  move_sprite( 1, px+8, DEF_PY );
}

void player(void)
{
  uint8_t key;
  uint8_t i;
  uint16_t seed;

  key = joypad();
  /* pause */
  if( key & J_START ) {
    if( pf == DEF_PF ) {
      /* Initialize the random number generator */
      seed = DIV_REG;
      waitpadup();
      seed |= ((uint16_t)DIV_REG << 8);
      initarand(seed);
      hide_msg();
      init_score();
      init_player();
      init_tama();
      init_enemy();
      init_kirai();
      delay( 500 );
    } else {
      show_pause();
      waitpadup();
      key = joypad();
      while( !(key & J_START) ) {
        key = joypad();
        if( key & J_DOWN ) {
          if(pl > 0)
            pl--;
          show_level( pl );
          waitpadup();
        } else if( key & J_UP ) {
          if(pl < 8)
            pl++;
          show_level( pl );
          waitpadup();
        } else if( key & J_LEFT ) {
          while( joypad() & J_LEFT ) {
            if(pw > 0)
              pw--;
            show_score( pw );
            delay( 250 );
          }
          show_score( ps );
        } else if( key & J_RIGHT ) {
          while( joypad() & J_RIGHT ) {
            if(pw < 99)
              pw++;
            show_score( pw );
            delay( 250 );
          }
          show_score( ps );
        } else if( key & J_SELECT ) {
          i = k_right;
          k_right = k_left;
          k_left  = i;
          waitpadup();
        }
      }
      waitpadup();
      hide_msg();
      delay( 500 );
    }
    return;
  }

  /* dead */
  if( pf > 1 ) {
    if( pf < DEF_PF ) {
      set_sprite_tile( 0, pf*2+DEF_PC0 );
      set_sprite_attrb( 0, foreCGB[pf*2+DEF_PC0] );
      set_sprite_tile( 1, pf*2+DEF_PC1 );
      set_sprite_attrb( 1, foreCGB[pf*2+DEF_PC1] );
      pf++;
    } else {
      set_sprite_tile( 0, DEF_SP );
      set_sprite_tile( 1, DEF_SP );
      show_gover();
    }
    return;
  }

  /* move */
  if( (key&J_LEFT)&&(px>MIN_PX) ) {
    px--;
    move_sprite( 0, px, DEF_PY ); move_sprite( 1, px+8, DEF_PY );
  } else if( (key&J_RIGHT)&&(px<MAX_PX) ) {
    px++;
    move_sprite( 0, px, DEF_PY ); move_sprite( 1, px+8, DEF_PY );
  }
  /* shot */
  if( key & k_left ) {  /* change J_B to J_A */
    if( pf == 0 ) {
      pf = 1;
      for( i=0; i<MAX_TT; i++ ) {
        if( tf[i] == 0 ) {
          tf[i] = 1; tx[i] = px-4; ty[i] = DEF_PY;
          break;
        }
      }
    }
  } else if( key & k_right ) {  /* change J_A to J_B */
    if( pf == 0 ) {
      pf = 1;
      for( i=0; i<MAX_TT; i++ ) {
        if( tf[i] == 0 ) {
          tf[i] = 1; tx[i] = px+12; ty[i] = DEF_PY;
          break;
        }
      }
    }
  } else if( pf == 1 ) {
    pf = 0;
  }
}