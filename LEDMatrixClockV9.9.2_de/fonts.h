// Sonderzeichen und Umlaute (Font: font[])
char IL  = '~' + 1; // Zeichen für InnenLuftfeuchte
char IT  = '~' + 2; // Zeichen für InnenTemperatur
char AL  = '~' + 3; // Zeichen für AußenLuftfeuchte
char AT  = '~' + 4; // Zeichen für AußenTemperatur
char IL2 = '~' + 5; // Zeichen für InnenLuftfeuchte für > 99
char IT2 = '~' + 6; // Zeichen für InnenTemperatur für Minusgrade
char AT2 = '~' + 7; // Zeichen für AußenTemperatur für Minusgrade
char SM  = '~' + 8; // Zeichen - kurzes Minus für Minusgrade bei Innen- und AußenTemperatur
char Face = '~' + 21; // Ein Gesicht Zeichen
char Hart = '~' + 22; // Ein Herz Zeichen
char   AU = '~' + 23; // Pfeil nach oben Zeichen
char   AD = '~' + 24; // Pfeil nach unten Zeichen
char  deg = '~' + 25; // ° Grad Zeichen
char  uue = '~' + 26; // ü Zeichen
char  uoe = '~' + 27; // ö Zeichen
char  uae = '~' + 28; // ä Zeichen
char  uss = '~' + 29; // ß Zeichen
char  uAe = '~' + 30; // Ä Zeichen
char  uOe = '~' + 31; // Ö Zeichen
char  uUe = '~' + 32; // Ü Zeichen

const uint8_t dig6x8[] PROGMEM = { 7,
0x06, 0x7E, 0xFF, 0x81, 0x81, 0xFF, 0x7E,
0x06, 0x00, 0x82, 0xFF, 0xFF, 0x80, 0x00,
0x06, 0xC2, 0xE3, 0xB1, 0x99, 0x8F, 0x86,
0x06, 0x42, 0xC3, 0x89, 0x89, 0xFF, 0x76,
0x06, 0x38, 0x3C, 0x26, 0x23, 0xFF, 0xFF,
0x06, 0x4F, 0xCF, 0x89, 0x89, 0xF9, 0x71,
0x06, 0x7E, 0xFF, 0x89, 0x89, 0xFB, 0x72,
0x06, 0x01, 0x01, 0xF1, 0xF9, 0x0F, 0x07,
0x06, 0x76, 0xFF, 0x89, 0x89, 0xFF, 0x76,
0x06, 0x4E, 0xDF, 0x91, 0x91, 0xFF, 0x7E,
6, 0,0,0,0,0,0
};

const uint8_t font[] PROGMEM = {7,
2, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, B01011111, B00000000, B00000000, B00000000, B00000000, B00000000, // !
3, B00000011, B00000000, B00000011, B00000000, B00000000, B00000000, // "
5, B00010100, B00111110, B00010100, B00111110, B00010100, B00000000, // #
4, B00100100, B01101010, B00101011, B00010010, B00000000, B00000000, // $
5, B01100011, B00010011, B00001000, B01100100, B01100011, B00000000, // %
5, B00110110, B01001001, B01010110, B00100000, B01010000, B00000000, // &
1, B00000011, B00000000, B00000000, B00000000, B00000000, B00000000, // '
3, B00011100, B00100010, B01000001, B00000000, B00000000, B00000000, // (
3, B01000001, B00100010, B00011100, B00000000, B00000000, B00000000, // )
5, B00101000, B00011000, B00001110, B00011000, B00101000, B00000000, // *
5, B00001000, B00001000, B00111110, B00001000, B00001000, B00000000, // +
2, B10110000, B01110000, B00000000, B00000000, B00000000, B00000000, // ,
4, B00001000, B00001000, B00001000, B00001000, B00000000, B00000000, // -
1, B01000000, B00000000, B00000000, B00000000, B00000000, B00000000, // .
3, B01100000, B00011100, B00000011, B00000000, B00000000, B00000000, // /
4, B00111110, B01000001, B01000001, B00111110, B00000000, B00000000, // 0
3, B01000010, B01111111, B01000000, B00000000, B00000000, B00000000, // 1
4, B01100010, B01010001, B01001001, B01000110, B00000000, B00000000, // 2
4, B00100010, B01000001, B01001001, B00110110, B00000000, B00000000, // 3
4, B00011000, B00010100, B00010010, B01111111, B00000000, B00000000, // 4
4, B00100111, B01000101, B01000101, B00111001, B00000000, B00000000, // 5
4, B00111110, B01001001, B01001001, B00110010, B00000000, B00000000, // 6
4, B01100001, B00010001, B00001001, B00000111, B00000000, B00000000, // 7
4, B00110110, B01001001, B01001001, B00110110, B00000000, B00000000, // 8
4, B00100110, B01001001, B01001001, B00111110, B00000000, B00000000, // 9
1, B01000100, B00000000, B00000000, B00000000, B00000000, B00000000, // :
2, B10000000, B01010000, B00000000, B00000000, B00000000, B00000000, // ;
3, B00010000, B00101000, B01000100, B00000000, B00000000, B00000000, // <
3, B00010100, B00010100, B00010100, B00000000, B00000000, B00000000, // =
3, B01000100, B00101000, B00010000, B00000000, B00000000, B00000000, // >
4, B00000010, B01011001, B00001001, B00000110, B00000000, B00000000, // ?
5, B00111110, B01001001, B01010101, B01011101, B00001110, B00000000, // @
4, B01111110, B00010001, B00010001, B01111110, B00000000, B00000000, // A
4, B01111111, B01001001, B01001001, B00110110, B00000000, B00000000, // B
4, B00111110, B01000001, B01000001, B00100010, B00000000, B00000000, // C
4, B01111111, B01000001, B01000001, B00111110, B00000000, B00000000, // D
4, B01111111, B01001001, B01001001, B01000001, B00000000, B00000000, // E
4, B01111111, B00001001, B00001001, B00000001, B00000000, B00000000, // F
4, B00111110, B01000001, B01001001, B01111010, B00000000, B00000000, // G
4, B01111111, B00001000, B00001000, B01111111, B00000000, B00000000, // H
3, B01000001, B01111111, B01000001, B00000000, B00000000, B00000000, // I
4, B00110000, B01000000, B01000001, B00111111, B00000000, B00000000, // J
4, B01111111, B00001000, B00010100, B01100011, B00000000, B00000000, // K
4, B01111111, B01000000, B01000000, B01000000, B00000000, B00000000, // L
5, B01111111, B00000010, B00001100, B00000010, B01111111, B00000000, // M
5, B01111111, B00000100, B00001000, B00010000, B01111111, B00000000, // N
4, B00111110, B01000001, B01000001, B00111110, B00000000, B00000000, // O
4, B01111111, B00001001, B00001001, B00000110, B00000000, B00000000, // P
4, B00111110, B01000001, B01000001, B10111110, B00000000, B00000000, // Q
4, B01111111, B00001001, B00001001, B01110110, B00000000, B00000000, // R
4, B00100110, B01001001, B01001001, B00110010, B00000000, B00000000, // S
5, B00000001, B00000001, B01111111, B00000001, B00000001, B00000000, // T
4, B00111111, B01000000, B01000000, B00111111, B00000000, B00000000, // U
5, B00001111, B00110000, B01000000, B00110000, B00001111, B00000000, // V
5, B00111111, B01000000, B00111000, B01000000, B00111111, B00000000, // W
5, B01100011, B00010100, B00001000, B00010100, B01100011, B00000000, // X
5, B00000111, B00001000, B01110000, B00001000, B00000111, B00000000, // Y
4, B01100001, B01010001, B01001001, B01000111, B00000000, B00000000, // Z
2, B01111111, B01000001, B00000000, B00000000, B00000000, B00000000, // [
4, B00000001, B00000110, B00011000, B01100000, B00000000, B00000000, // \ backslash
2, B01000001, B01111111, B00000000, B00000000, B00000000, B00000000, // ]
3, B00000010, B00000001, B00000010, B00000000, B00000000, B00000000, // hat
4, B01000000, B01000000, B01000000, B01000000, B00000000, B00000000, // _
2, B00000001, B00000010, B00000000, B00000000, B00000000, B00000000, // `
4, B00100000, B01010100, B01010100, B01111000, B00000000, B00000000, // a
4, B01111111, B01000100, B01000100, B00111000, B00000000, B00000000, // b
4, B00111000, B01000100, B01000100, B00101000, B00000000, B00000000, // c
4, B00111000, B01000100, B01000100, B01111111, B00000000, B00000000, // d
4, B00111000, B01010100, B01010100, B00011000, B00000000, B00000000, // e
3, B00000100, B01111110, B00000101, B00000000, B00000000, B00000000, // f
4, B10011000, B10100100, B10100100, B01111000, B00000000, B00000000, // g
4, B01111111, B00000100, B00000100, B01111000, B00000000, B00000000, // h
3, B01000100, B01111101, B01000000, B00000000, B00000000, B00000000, // i
4, B01000000, B10000000, B10000100, B01111101, B00000000, B00000000, // j
4, B01111111, B00010000, B00101000, B01000100, B00000000, B00000000, // k
3, B01000001, B01111111, B01000000, B00000000, B00000000, B00000000, // l
5, B01111100, B00000100, B01111100, B00000100, B01111000, B00000000, // m
4, B01111100, B00000100, B00000100, B01111000, B00000000, B00000000, // n
4, B00111000, B01000100, B01000100, B00111000, B00000000, B00000000, // o
4, B11111100, B00100100, B00100100, B00011000, B00000000, B00000000, // p
4, B00011000, B00100100, B00100100, B11111100, B00000000, B00000000, // q
4, B01111100, B00001000, B00000100, B00000100, B00000000, B00000000, // r
4, B01001000, B01010100, B01010100, B00100100, B00000000, B00000000, // s
3, B00000100, B00111111, B01000100, B00000000, B00000000, B00000000, // t
4, B00111100, B01000000, B01000000, B00111100, B00000000, B00000000, // u
5, B00011100, B00100000, B01000000, B00100000, B00011100, B00000000, // v
5, B00111100, B01000000, B00111100, B01000000, B00111100, B00000000, // w
5, B01000100, B00101000, B00010000, B00101000, B01000100, B00000000, // x
4, B10011100, B10100000, B10100000, B01111100, B00000000, B00000000, // y
3, B01100100, B01010100, B01001100, B00000000, B00000000, B00000000, // z
3, B00001000, B00110110, B01000001, B00000000, B00000000, B00000000, // {
1, B01111111, B00000000, B00000000, B00000000, B00000000, B00000000, // |
3, B01000001, B00110110, B00001000, B00000000, B00000000, B00000000, // }
4, B00001000, B00000100, B00001000, B00000100, B00000000, B00000000, // ~

6, B00001001, B00001111, B00001001, B11110000, B10000000, B10000000, // IL = InnenLuftfeuchte
6, B00001001, B00001111, B00001001, B00010000, B11110000, B00010000, // IT = InnenTemperatur
5, B00001110, B00000101, B11110101, B10001110, B10000000, B00000000, // AL = AußenLuftfeuchte
6, B00001110, B00000101, B00000101, B00011110, B11110000, B00010000, // AT = AußenTemperatur
5, B00001001, B00001111, B11111001, B10000000, B10000000, B00000000, // IL = InnenLuftfeuchte für > 99
6, B00000000, B00001001, B00001111, B00011001, B11110000, B00010000, // IT = InnenTemperatur für Minusgrade
5, B00001110, B00000101, B00011110, B11110000, B00010000, B00000000, // AT = AußenTemperatur für Minusgrade
3, B00001000, B00001000, B00001000, B00000000, B00000000, B00000000, // -  = kurzes Minus für Innen- und AußenTemperatur
// 5, B00100000, B01010100, B01010100, B11111000, B10000000, B00000000, // a
// 4, B00111000, B01000100, B01000110, B00101001, B00000000, B00000000, // c
// 4, B00111000, B01010100, B11010100, B10011000, B00000000, B00000000, // e
// 3, B01010001, B01111111, B01000100, B00000000, B00000000, B00000000, // l
// 4, B01111100, B00000100, B00000110, B01111001, B00000000, B00000000, // n
// 4, B00111000, B01000100, B01000110, B00111001, B00000000, B00000000, // o
// 4, B01001000, B01010100, B01010110, B00100101, B00000000, B00000000, // s
// 3, B01100100, B01010110, B01001101, B00000000, B00000000, B00000000, // z
3, B01100100, B01010101, B01001100, B00000000, B00000000, B00000000, // z
5, B01111110, B00010001, B00010001, B11111110, B10000000, B00000000, // A
4, B00111100, B01000010, B01000011, B00100101, B00000000, B00000000, // C
5, B01111111, B01001001, B01001001, B11000001, B10000000, B00000000, // E
4, B01111111, B01001000, B01000100, B01000000, B00000000, B00000000, // L
5, B01111110, B00000100, B00001010, B00010001, B01111110, B00000000, // N
4, B00111100, B01000110, B01000011, B00111100, B00000000, B00000000, // O
4, B00100100, B01001010, B01001011, B00110000, B00000000, B00000000, // S
4, B01100010, B01010110, B01001011, B01000110, B00000000, B00000000, // Z
4, B01101001, B01011001, B01001101, B01001011, B00000000, B00000000, // Z

5, B00111110, B01010101, B01100001, B01010101, B00111110, B00000000, // :)
5, B00111110, B01100101, B01010001, B01100101, B00111110, B00000000, // :(
5, B00111110, B01000101, B01010001, B01000101, B00111110, B00000000, // :o
5, 0x06, 0x1F, 0x7E, 0x1F, 0x06, 0x00,  // heart
5, 0x04, 0x02, 0x7F, 0x02, 0x04, 0x00,  // arrow up
5, 0x10, 0x20, 0x7F, 0x20, 0x10, 0x00,  // arrow down
3, B00000010, B00000101, B00000010, B00000000, B00000000, B00000000, // deg
4, B00111010, B01000000, B01000000, B00111010, B00000000, B00000000, // ü
4, B00110010, B01001000, B01001000, B00110010, B00000000, B00000000, // ö
4, B00100010, B01010100, B01010100, B01111010, B00000000, B00000000, // ä
3, B11111110, B00101010, B00011100, B00000000, B00000000, B00000000, // ß
5, B01111101, B00010010, B00010010, B00010010, B01111101, B00000000, // Ä
5, B00111101, B01000010, B01000010, B01000010, B00111101, B00000000, // Ö
5, B00111101, B01000000, B01000000, B01000000, B00111101, B00000000, // Ü 
};

const uint8_t clockfont[] PROGMEM = {9,
8, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
0, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, // space
8, B00000000, B01111110, B11111111, B10000001, B10000001, B11111111, B01111110, B00000000, // 0
8, B00000000, B00000000, B10000010, B11111111, B11111111, B10000000, B00000000, B00000000, // 1
8, B00000000, B11000010, B11100011, B10110001, B10011001, B10001111, B10000110, B00000000, // 2
8, B00000000, B01000010, B11000011, B10001001, B10001001, B11111111, B01110110, B00000000, // 3
8, B00000000, B00111000, B00111100, B00100110, B00100011, B11111111, B11111111, B00000000, // 4
8, B00000000, B01001111, B11001111, B10001001, B10001001, B11111001, B01110001, B00000000, // 5
8, B00000000, B01111110, B11111111, B10001001, B10001001, B11111011, B01110010, B00000000, // 6
8, B00000000, B00000001, B00000001, B11110001, B11111001, B00001111, B00000111, B00000000, // 7
8, B00000000, B01110110, B11111111, B10001001, B10001001, B11111111, B01110110, B00000000, // 8
8, B00000000, B01001110, B11011111, B10010001, B10010001, B11111111, B01111110, B00000000, // 9
8, B11111100, B01110010, B11110011, B01111111, B11110011, B01110010, B11111100, B00000000, // Ghost
8, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, // Full Display ON
};