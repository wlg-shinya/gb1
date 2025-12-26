#ifndef ENEMY_H
#define ENEMY_H

#include <gb/gb.h>
#include <stdint.h>
#include "game.h"
#include "player.h"
#include "bullet.h"

#define MAX_ET		10U		/* number */
#define DEF_ES0		(DEF_TS+MAX_TT) /* sprite tile id */
#define DEF_ES1		(DEF_ES0+1U)
#define DEF_1EC0	32U
#define DEF_1EC1	48U
#define DEF_2EC0	64U
#define DEF_2EC1	80U
#define DEF_XEC0	96U		/* sprite data(X) id */
#define DEF_XEC1	112U		/* sprite data(X) id */
#define DEF_EY		(DEF_PY+12U)
#define DEF_EH		10U
#define SUB_EX0		20U
#define SUB_EX1		(SUB_EX0-8U)
#define MIN_EX		(SUB_EX0-16U)
#define MAX_EX		(SUB_EX0+180U)
#define SPEED_EY	(DEF_EY+DEF_EH*3U)
#define DEF_BC1		4U
#define DEF_BC2		5U

extern uint8_t ef[MAX_ET], ex[MAX_ET], ey[MAX_ET];
extern uint8_t rnd_enemy; 

void init_enemy( void );
void enemys( void );

#endif