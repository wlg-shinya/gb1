/********************************************************************
 * Color Deep Scan                                                  *
 * by                                                              *
 * Mr. N.U. of TeamKNOx                                             *
 ********************************************************************/

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>
#include <stdlib.h>
#include <rand.h>

#include "bkg.h"
#include "bullet.h"
#include "enemy.h"
#include "fore.h"
#include "game.h"
#include "graphics.h"
#include "kirai.h"
#include "player.h"
#include "ui.h"
#include "utils.h"

uint8_t pp, pl;
uint16_t pw;
uint16_t ps;
uint8_t k_right, k_left;

void main(void)
{
  disable_interrupts();
  DISPLAY_OFF;

  initarand(((uint16_t)DIV_REG << 8));

  init_graphics();
  pw = 50;
  init_score();
  init_ui();

  init_player();
  init_tama();
  init_enemy();
  init_kirai();
  show_gover();
  k_right = J_A;
  k_left = J_B;
  DISPLAY_ON;
  enable_interrupts();

  while(1) {
    delay( pw );
    player();
    bombs();
    enemys();
    kirai();
  }
}