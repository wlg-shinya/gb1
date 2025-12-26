#ifndef GAME_H
#define GAME_H

#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#define MIN_SX		5U		/* min x (char) */
#define MAX_SX		(20U-MIN_SX)    /* max x (char) */
#define MIN_SY		5U		/* min y (char) */
#define MAX_SY		(MIN_SY+13U)	/* max y (char) */
#define DEF_SP		30U		/* sprite null char code */	

extern uint8_t k_right, k_left;
extern uint8_t pl;
extern uint16_t pw;
extern uint16_t ps;
extern uint8_t pp;

#endif