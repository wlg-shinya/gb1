#include <gb/gb.h>
#include <stdint.h>

#include "enemy.h"
#include "game.h"
#include "kirai.h"
#include "player.h"
#include "ui.h"

const unsigned char * const msg_1up   = "1UP";
const unsigned char * const msg_lv    = "LV";
const unsigned char * const msg_gover = "GAMEOVER";
const unsigned char * const msg_pause = " PAUSE! ";
const unsigned char * const msg_start = "        ";

void init_ui(void)
{
  set_bkg_tiles(  0, 0, 3, 1, (unsigned char *)msg_1up );
  set_bkg_tiles( 16, 0, 2, 1, (unsigned char *)msg_lv );
}

void init_score(void)
{
  ps = 0;
  show_score( ps );
  pp = 0; pl = 0;
  show_level( pl );
}

void show_score( uint16_t s )
{
  uint16_t m;
  uint8_t i, n, f;
  unsigned char score[6];

  f = 0; m = 10000;
  for( i=0; i<5; i++ ) {
    n = s/m; s = s%m; m = m/10;
    if( (n==0)&&(f==0) ) {
      score[i] = 0x20;      /* ' ' */
    } else {
      f = 1;
      score[i] = 0x30+n;    /* '0' - '9' */
    }
  }
  score[5] = 0x30;      /* '0' */
  set_bkg_tiles( 4, 0, 6, 1, score );
}

void set_level( uint8_t i )
{
  /* level */
  if( i < 9 ) {
    rnd_enemy = 100-(i*12); /* 1% - */
    rnd_kirai = 50-(i*6);   /* 2% - */
  } else {
    rnd_enemy = 0;      /* 100 % */
    rnd_kirai = 0;      /* 100 % */
  }
}

void show_level( uint8_t i )
{
  unsigned char level[2];

  if( i < 9 ) {
    level[0] = 0x31+i;
  } else {
    level[0] = 0x41+i-9;
  }
  set_bkg_tiles( 19, 0, 1, 1, level );
  set_level( i );
}

void show_gover(void)
{
  set_bkg_tiles(  6, 9, 8, 1, (unsigned char *)msg_gover );
  pf = DEF_PF;
}

void show_pause(void)
{
  set_bkg_tiles(  6, 9, 8, 1, (unsigned char *)msg_pause );
}

void hide_msg(void)
{
  set_bkg_tiles(  6, 9, 8, 1, (unsigned char *)msg_start );
}
