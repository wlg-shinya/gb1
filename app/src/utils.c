#include <gb/gb.h>
#include <stdint.h>
#include <rand.h>

#include "utils.h"

uint8_t make_rnd( uint8_t i )
{
  return( arand()%(i+1) );
}