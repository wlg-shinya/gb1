#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdint.h>

#include "bkg.h"
#include "fore.h"
#include "game.h"
#include "graphics.h"

const uint16_t bkg_p[] =
{
  bkgCGBPal0c0,bkgCGBPal0c1,bkgCGBPal0c2,bkgCGBPal0c3,
  bkgCGBPal1c0,bkgCGBPal1c1,bkgCGBPal1c2,bkgCGBPal1c3,
  bkgCGBPal2c0,bkgCGBPal2c1,bkgCGBPal2c2,bkgCGBPal2c3,
  bkgCGBPal3c0,bkgCGBPal3c1,bkgCGBPal3c2,bkgCGBPal3c3,
  bkgCGBPal4c0,bkgCGBPal4c1,bkgCGBPal4c2,bkgCGBPal4c3,
  bkgCGBPal5c0,bkgCGBPal5c1,bkgCGBPal5c2,bkgCGBPal5c3,
  bkgCGBPal6c0,bkgCGBPal6c1,bkgCGBPal6c2,bkgCGBPal6c3,
  bkgCGBPal7c0,bkgCGBPal7c1,bkgCGBPal7c2,bkgCGBPal7c3
};

const uint16_t obj_p[] =
{
  foreCGBPal0c0,foreCGBPal0c1,foreCGBPal0c2,foreCGBPal0c3,
  foreCGBPal1c0,foreCGBPal1c1,foreCGBPal1c2,foreCGBPal1c3,
  foreCGBPal2c0,foreCGBPal2c1,foreCGBPal2c2,foreCGBPal2c3,
  foreCGBPal3c0,foreCGBPal3c1,foreCGBPal3c2,foreCGBPal3c3,
  foreCGBPal4c0,foreCGBPal4c1,foreCGBPal4c2,foreCGBPal4c3,
  foreCGBPal5c0,foreCGBPal5c1,foreCGBPal5c2,foreCGBPal5c3,
  foreCGBPal6c0,foreCGBPal6c1,foreCGBPal6c2,foreCGBPal6c3,
  foreCGBPal7c0,foreCGBPal7c1,foreCGBPal7c2,foreCGBPal7c3
};

unsigned char msg_tile[64];

void init_graphics(void)
{
  uint8_t n;

  if(DEVICE_SUPPORTS_COLOR) {
    /* Transfer color palette */
    set_bkg_palette( BKGF_CGB_PAL0, 1, &bkg_p[0] );
    set_bkg_palette( BKGF_CGB_PAL1, 1, &bkg_p[4] );
    set_bkg_palette( BKGF_CGB_PAL2, 1, &bkg_p[8] );
    set_bkg_palette( BKGF_CGB_PAL3, 1, &bkg_p[12] );
    set_bkg_palette( BKGF_CGB_PAL4, 1, &bkg_p[16] );
    set_bkg_palette( BKGF_CGB_PAL5, 1, &bkg_p[20] );
    set_bkg_palette( BKGF_CGB_PAL6, 1, &bkg_p[24] );
    set_bkg_palette( BKGF_CGB_PAL7, 1, &bkg_p[28] );
    
    set_sprite_palette( OAMF_CGB_PAL0, 1, &obj_p[0] );
    set_sprite_palette( OAMF_CGB_PAL1, 1, &obj_p[4] );
    set_sprite_palette( OAMF_CGB_PAL2, 1, &obj_p[8] );
    set_sprite_palette( OAMF_CGB_PAL3, 1, &obj_p[12] );
    set_sprite_palette( OAMF_CGB_PAL4, 1, &obj_p[16] );
    set_sprite_palette( OAMF_CGB_PAL5, 1, &obj_p[20] );
    set_sprite_palette( OAMF_CGB_PAL6, 1, &obj_p[24] );
    set_sprite_palette( OAMF_CGB_PAL7, 1, &obj_p[28] );

    /* set attributes */
    set_bkg_attr( 0, 0, 20, 18, (unsigned char *)bkg_c );
    set_bkg_tiles( 0, 0, 20, 18, (unsigned char *)bkg_c );
  } else {
    set_bkg_tiles( 0, 0, 20, 18, (unsigned char *)bkg_m );
  }

  set_bkg_data( 0, 96, bkg );

  SHOW_BKG;
  SPRITES_8x8;
  set_sprite_data( 0, 128, fore );
  SHOW_SPRITES;
  
  for( n=0; n<40; n++ ) {
    set_sprite_tile( n, DEF_SP );
    move_sprite( n, 0, 0 );
  }
}

void set_sprite_attrb( uint8_t nb, uint8_t tile )
{
  if(DEVICE_SUPPORTS_COLOR) {
    set_sprite_prop( nb, tile );
  }
}

void set_bkg_attr( uint8_t x, uint8_t y, uint8_t sx, uint8_t sy, unsigned char *d )
{
  uint8_t xx, yy;

  VBK_REG = VBK_ATTRIBUTES;	/* select palette bank */
  for( yy=0; yy<sy; yy++ ) {
    for( xx=0; xx<sx; xx++ ) {
      msg_tile[xx] = bkgCGB[(unsigned int)*d];
      d++;
    }
    set_bkg_tiles( x, y+yy, sx, 1, msg_tile );
  }
  VBK_REG = VBK_TILES;		/* select data bank */
}