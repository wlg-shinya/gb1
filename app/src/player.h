#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

#define MIN_PX		(MIN_SX*8U+8U)	/* min x (dot) */
#define MAX_PX		(MAX_SX*8U-8U)	/* max x (dot) */
#define DEF_PX		80U		        /* ship x pos (dot) */
#define DEF_PY		(MIN_SY*8U)	    /* ship y pos (dot) */
#define DEF_PC0		14U
#define DEF_PC1		15U
#define DEF_PF		8U

extern uint8_t pf;
extern uint8_t px;

void init_player( void );
void player( void );

#endif