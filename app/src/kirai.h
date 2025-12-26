#ifndef KIRAI_H
#define KIRAI_H

#include <gb/gb.h>
#include <stdint.h>
#include "game.h"
#include "player.h"
#include "enemy.h"

#define MAX_KT		12U
#define DEF_KS		(DEF_ES0+MAX_ET*2U)	/* sprite tile id */
#define DEF_KC		4U		/* sprite data id */
#define DEF_KX		0U		/* bomb x pos (default_dot) */
#define DEF_KY		0U		/* bomb y pos (default_dot) */
#define MIN_KY		(DEF_PY+1U)	/* min y pos (dot) */

extern uint8_t kf[MAX_KT], kx[MAX_KT], ky[MAX_KT];
extern uint8_t rnd_kirai;

void init_kirai( void );
void kirai( void );

#endif