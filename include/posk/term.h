#define MAX_WIDTH    80
#define MAX_HEIGHT   25

#define POSK_GRAY_TEXT    0x8
#define POSK_WHITE_TXT    0x7
#define POSK_BLUE_TXT     0x9
#define POSK_ORNG_TXT     0x6
#define POSK_PURP_TXT     0x5
#define POSK_RED_TXT      0x4
#define POSK_GAY_TXT      0x3
#define POSK_GREEN_TXT    0x2
#define POSK_BLCK_TXT     0x0

#define POSK_BLUE_BG      0x10
#define POSK_GREEN_BG     0x20
#define POSK_GAY_BG       0x30
#define POSK_RED_BG       0x40
#define POSK_PURP_BG      0x50
#define POSK_ORNG_BG      0x60
#define POSK_WHITE_BG     0x70
#define POSK_GRAY_BG      0x80

#define POSK_CURS_X _POSK_CURS_X
#define POSK_CURS_Y _POSK_CURS_Y

int _POSK_CURS_X;
int _POSK_CURS_Y;

void          posk_clear_screen( int c );
void          posk_print_char_tl( char c );
void          posk_print_char( int x, int y, char c );
void          posk_print_line( char * c );
void          posk_clear_line( int l );
