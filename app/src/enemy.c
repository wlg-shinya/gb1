#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdlib.h>
#include <rand.h>

#include "bullet.h"
#include "enemy.h"
#include "fore.h"
#include "game.h"
#include "graphics.h"
#include "kirai.h"
#include "player.h"
#include "ui.h"
#include "utils.h"

uint8_t ef[MAX_ET], ex[MAX_ET], ey[MAX_ET];
uint8_t rnd_enemy;

void init_enemy(void)
{
  uint8_t i;

  for( i=0; i<MAX_ET; i++ ) {
    ef[i] = 0;
    ex[i] = 0;
    ey[i] = 0;
    set_sprite_tile( i*2+DEF_ES0, DEF_SP );
    set_sprite_tile( i*2+DEF_ES1, DEF_SP );
    move_sprite( i*2+DEF_ES0, ex[i], ey[i] );
    move_sprite( i*2+DEF_ES1, ex[i], ey[i] );
  }
}

void enemys(void)
{
  uint8_t i, j;

  for( i=0; i<MAX_ET; i++ ) {
    if( ef[i] == 1 ) {
      /* move right to left */
      ex[i]--;
      if( (pl>0)&&(ey[i]<SPEED_EY) )  ex[i]--;
      if( ex[i] <= MIN_EX ) {
        ef[i] = 0;
        set_sprite_tile( i*2+DEF_ES0, DEF_SP );
        set_sprite_tile( i*2+DEF_ES1, DEF_SP );
      } else {
        /* new */
        if( ex[i]<MIN_SX*8+13 ) {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0 );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1 );
        } else if( ex[i]<MIN_SX*8+20 ) {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0 );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1+(ex[i]-MIN_SX*8-13) );
        } else if( ex[i]<MIN_SX*8+28 ) {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0+(ex[i]-MIN_SX*8-20) );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1+8 );
        } else if( ex[i]<MAX_SX*8+13 ) {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0+8 );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1+8 );
        } else if( ex[i]<MAX_SX*8+20 ) {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0+8 );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1+(ex[i]-MAX_SX*8-12)+7 );
        } else if( ex[i]<MAX_SX*8+28 ) {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0+(ex[i]-MAX_SX*8-20)+8 );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1 );
        } else {
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0 );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1 );
        }
        /* new */
        move_sprite( i*2+DEF_ES0, ex[i]-SUB_EX0, ey[i] );
        move_sprite( i*2+DEF_ES1, ex[i]-SUB_EX1, ey[i] );
        /* check bomb */
        for( j=0; j<MAX_TT; j++ ) {
          if( tf[j] != 0 ) {
            if( (ty[j]>ey[i]-2)&&(ty[j]<ey[i]+2) ) {
              if( (tx[j]>(ex[i]-SUB_EX0-5))&&(tx[j]<(ex[i]-SUB_EX1+5)) ) {
                /* hit */
                tf[j] = 0; tx[j] = j*4+DEF_TX; ty[j] = DEF_TY;
                set_sprite_tile( j+DEF_TS, tf[j]+DEF_TC );
                set_sprite_attrb( j+DEF_TS, foreCGB[tf[j]+DEF_TC] );
                move_sprite( j+DEF_TS, tx[j], ty[j] );
                ef[i] = 3;
                set_sprite_tile( i*2+DEF_ES0, ef[i]*2+DEF_BC1 );
                set_sprite_attrb( i*2+DEF_ES0, foreCGB[ef[i]*2+DEF_BC1] );
                set_sprite_tile( i*2+DEF_ES1, ef[i]*2+DEF_BC2 );
                set_sprite_attrb( i*2+DEF_ES1, foreCGB[ef[i]*2+DEF_BC2] );
              }
            }
          }
        }
        if( make_rnd(rnd_kirai) == 0 ) {
          if( ((ex[i]-SUB_EX0)>MIN_PX)&&((ex[i]-SUB_EX0)<MAX_PX) ) {
            if( kf[i] == 0 ) {
              /* shot kirai */
              kf[i] = 1;
              kx[i] = ex[i]-SUB_EX0+4;
              ky[i] = ey[i]-4;
            } else if( kf[i+1] == 0 ) {
              /* shot kirai */
              kf[i+1] = 1;
              kx[i+1] = ex[i]-SUB_EX0+4;
              ky[i+1] = ey[i]-4;
            } else if( kf[i+2] == 0 ) {
              /* shot kirai */
              kf[i+2] = 1;
              kx[i+2] = ex[i]-SUB_EX0+4;
              ky[i+2] = ey[i]-4;
            }
          }
        }
      }
    } else if( ef[i] == 2 ) {
      /* move left to right */
      ex[i]++;
      if( (pl>0)&&(ey[i]<SPEED_EY) )  ex[i]++;
      if( ex[i] >= MAX_EX ) {
        ef[i] = 0;
        set_sprite_tile( i*2+DEF_ES0, DEF_SP );
        set_sprite_tile( i*2+DEF_ES1, DEF_SP );
      } else {
        /* new */
        if( i==9 ) {
          if( ex[i]<MIN_SX*8+13 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0 );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1 );
          } else if( ex[i]<MIN_SX*8+20 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0 );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1+(ex[i]-MIN_SX*8-13) );
          } else if( ex[i]<MIN_SX*8+28 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0+(ex[i]-MIN_SX*8-20) );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1+8 );
          } else if( ex[i]<MAX_SX*8+13 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0+8 );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1+8 );
          } else if( ex[i]<MAX_SX*8+20 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0+8 );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1+(ex[i]-MAX_SX*8-12)+7 );
          } else if( ex[i]<MAX_SX*8+28 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0+(ex[i]-MAX_SX*8-20)+8 );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1 );
          } else {
            set_sprite_tile( i*2+DEF_ES0, DEF_XEC0 );
            set_sprite_tile( i*2+DEF_ES1, DEF_XEC1 );
          }
        } else {
          if( ex[i]<MIN_SX*8+13 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0 );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1 );
          } else if( ex[i]<MIN_SX*8+20 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0 );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1+(ex[i]-MIN_SX*8-13) );
          } else if( ex[i]<MIN_SX*8+28 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0+(ex[i]-MIN_SX*8-20) );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1+8 );
          } else if( ex[i]<MAX_SX*8+13 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0+8 );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1+8 );
          } else if( ex[i]<MAX_SX*8+20 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0+8 );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1+(ex[i]-MAX_SX*8-12)+7 );
          } else if( ex[i]<MAX_SX*8+28 ) {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0+(ex[i]-MAX_SX*8-20)+8 );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1 );
          } else {
            set_sprite_tile( i*2+DEF_ES0, DEF_2EC0 );
            set_sprite_tile( i*2+DEF_ES1, DEF_2EC1 );
          }
        }
        /* new */
        move_sprite( i*2+DEF_ES0, ex[i]-SUB_EX0, ey[i] );
        move_sprite( i*2+DEF_ES1, ex[i]-SUB_EX1, ey[i] );
        /* check bomb */
        for( j=0; j<MAX_TT; j++ ) {
          if( tf[j] != 0 ) {
            if( (ty[j]>ey[i]-2)&&(ty[j]<ey[i]+2) ) {
              if( (tx[j]>(ex[i]-SUB_EX0-5))&&(tx[j]<(ex[i]-SUB_EX1+5)) ) {
                /* hit */
                tf[j] = 0; tx[j] = j*4+DEF_TX; ty[j] = DEF_TY;
                set_sprite_tile( j+DEF_TS, tf[j]+DEF_TC );
                set_sprite_attrb( j+DEF_TS, foreCGB[tf[j]+DEF_TC] );
                move_sprite( j+DEF_TS, tx[j], ty[j] );
                ef[i] = 3;
                set_sprite_tile( i*2+DEF_ES0, ef[i]*2+DEF_BC1 );
                set_sprite_attrb( i*2+DEF_ES0, foreCGB[ef[i]*2+DEF_BC1] );
                set_sprite_tile( i*2+DEF_ES1, ef[i]*2+DEF_BC2 );
                set_sprite_attrb( i*2+DEF_ES1, foreCGB[ef[i]*2+DEF_BC2] );
              }
            }
          }
        }
        if( make_rnd(rnd_kirai) == 0 ) {
          if( ((ex[i]-SUB_EX0)>MIN_PX)&&((ex[i]-SUB_EX0)<MAX_PX) ) {
            if( kf[i] == 0 ) {
              /* shot kirai */
              kf[i] = 1;
              kx[i] = ex[i]-SUB_EX0+4;
              ky[i] = ey[i]-4;
            } else if( kf[i+1] == 0 ) {
              /* shot kirai */
              kf[i+1] = 1;
              kx[i+1] = ex[i]-SUB_EX0+4;
              ky[i+1] = ey[i]-4;
            } else if( kf[i+2] == 0 ) {
              /* shot kirai */
              kf[i+2] = 1;
              kx[i+2] = ex[i]-SUB_EX0+4;
              ky[i+2] = ey[i]-4;
            }
          }
        }
      }
    } else if( ef[i] >= 3 ) {
      if( ef[i] > 4 ) {
        ef[i] = 0;
        set_sprite_tile( i*2+DEF_ES0, DEF_SP );
        set_sprite_tile( i*2+DEF_ES1, DEF_SP );
        if( i == 9 ) {
          ps += 100; show_score( ps ); pp++;
          set_level( pl-1 );
        } else {
          ps += (i+1); show_score( ps ); pp++;
        }
      } else {
        set_sprite_tile( i*2+DEF_ES0, ef[i]*2+DEF_BC1 );
        set_sprite_attrb( i*2+DEF_ES0, foreCGB[ef[i]*2+DEF_BC1] );
        set_sprite_tile( i*2+DEF_ES1, ef[i]*2+DEF_BC2 );
        set_sprite_attrb( i*2+DEF_ES1, foreCGB[ef[i]*2+DEF_BC2] );
        ef[i]++;
      }
    } else if( i == 9 ) {
      if( pp > 20 ) {
        pp = 0;
        pl++; show_level( pl );
        /* X */
        ey[i] = i*DEF_EH+DEF_EY;
        ef[i] = i%2+1;
        ex[i] = MIN_EX;
        set_sprite_tile( i*2+DEF_ES0, DEF_XEC0 );
        set_sprite_attrb( i*2+DEF_ES0, foreCGB[DEF_XEC0] );
        set_sprite_tile( i*2+DEF_ES1, DEF_XEC1 );
        set_sprite_attrb( i*2+DEF_ES1, foreCGB[DEF_XEC1] );
        move_sprite( i*2+DEF_ES0, ex[i]-SUB_EX0, ey[i] );
        move_sprite( i*2+DEF_ES1, ex[i]-SUB_EX1, ey[i] );
      }
    } else if( make_rnd(rnd_enemy) == 0 ) {
      if( !((pl<4)&&(i==0)) ) {
        /* create */
        ey[i] = i*DEF_EH+DEF_EY;
        ef[i] = i%2+1;
        if( ef[i] == 1 ) {
          ex[i] = MAX_EX;
          set_sprite_tile( i*2+DEF_ES0, DEF_1EC0 );
          set_sprite_attrb( i*2+DEF_ES0, foreCGB[DEF_1EC0] );
          set_sprite_tile( i*2+DEF_ES1, DEF_1EC1 );
          set_sprite_attrb( i*2+DEF_ES1, foreCGB[DEF_1EC1] );
        } else {
          ex[i] = MIN_EX;
          set_sprite_tile( i*2+DEF_ES0, DEF_2EC0 );
          set_sprite_attrb( i*2+DEF_ES0, foreCGB[DEF_2EC0] );
          set_sprite_tile( i*2+DEF_ES1, DEF_2EC1 );
          set_sprite_attrb( i*2+DEF_ES1, foreCGB[DEF_2EC1] );
        }
        move_sprite( i*2+DEF_ES0, ex[i]-SUB_EX0, ey[i] );
        move_sprite( i*2+DEF_ES1, ex[i]-SUB_EX1, ey[i] );
      }
    }
  }
}
