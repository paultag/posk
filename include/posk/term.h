#define MAX_WIDTH    80
#define MAX_HEIGHT   25
#define WHITE_TXT    0x07

#define POSK_CURS_X _POSK_CURS_X
#define POSK_CURS_Y _POSK_CURS_Y

void          posk_clear_screen();
void          posk_print_char_tl( char c );
void          posk_print_char( int x, int y, char c );
