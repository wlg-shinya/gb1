#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "fore.h"
#include "game.h"
#include "graphics.h"
#include "kirai.h"
#include "player.h"

uint8_t kf[MAX_KT], kx[MAX_KT], ky[MAX_KT];
uint8_t rnd_kirai;

void init_kirai(void)
{
  uint8_t i;

  for( i=0; i<MAX_KT; i++ ) {
    kf[i] = 0;
    kx[i] = DEF_KX;
    ky[i] = DEF_KY;
    set_sprite_tile( i+DEF_KS, DEF_SP );
    move_sprite( i+DEF_KS, kx[i], ky[i] );
  }
}

void kirai(void)
{
  uint8_t i;

  for( i=0; i<MAX_KT; i++ ) {
    if( kf[i] != 0 ) {
      ky[i]--;
      if( kf[i] >=3 ) {
        kf[i]++;
        if( (kx[i]>(px-5))&&(kx[i]<(px+12)) ) {
          if( pf < 2 ) {
            /* out!! */
            pf = 2;
          }
        }
        if( kf[i] >= 6 ) {
          kf[i] = 0; kx[i] = DEF_KX; ky[i] = DEF_KY;
        }
      } else if( ky[i] <= MIN_KY ) {
        kf[i] = 3;
      } else {
        kf[i] = 3-kf[i];
      }
      set_sprite_tile( i+DEF_KS, kf[i]+DEF_KC );
      set_sprite_attrb( i+DEF_KS, foreCGB[kf[i]+DEF_KC] );
      move_sprite( i+DEF_KS, kx[i], ky[i] );
    }
  }
}