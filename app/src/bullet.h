#ifndef BULLET_H
#define BULLET_H

#include <gb/gb.h>
#include <stdint.h>
#include "game.h"
#include "player.h"

#define MAX_TT		6U		/* number */
#define DEF_TS		2U		/* sprite tile id */
#define DEF_TC		2U		/* sprite data id */
#define DEF_TX		(80U-6U)	/* bomb x pos (dot) */
#define DEF_TY		(DEF_PY-14U)	/* bomb y pos (dot) */
#define MAX_TY		(MAX_SY*8U)	/* max y pos (dot) */

extern uint8_t tf[MAX_TT];
extern uint8_t tx[MAX_TT];
extern uint8_t ty[MAX_TT];

void init_tama( void );
void bombs( void );

#endif