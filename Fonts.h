#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

//Font storage
#define CHAR_LINE	0x80
#define LEFT_ARROW	0x82
#define RIGHT_ARROW 0x83
#define BACK_SPACE  0x85
#define CASE_CHAR	0x84
#define RETURN_MENU 0x86

extern const uint8_t ADAFont[];
extern const uint8_t HFont1[];

#ifdef __cplusplus
}
#endif
#endif
