#include "fixedpoint.hpp"

#include <avr/pgmspace.h>
//#include <Arduino.h>
//#include "log.hpp"

const PROGMEM unsigned int ATAN_0_512_4[] = {0, 3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 58, 62, 66, 70, 73, 77, 81, 84, 88, 91, 95, 98, 102, 105, 108, 112, 115, 118, 121, 125, 128, 131, 134, 137, 140, 143, 145, 148, 151, 154, 156, 159, 162, 164, 167, 169, 172, 174, 177, 179, 181, 184, 186, 188, 190, 192, 194, 196, 199, 201, 203, 205, 206, 208, 210, 212, 214, 216, 217, 219, 221, 222, 224, 226, 227, 229, 230, 232, 233, 235, 236, 238, 239, 241, 242, 243, 245, 246, 247, 249, 250, 251, 252, 254, 255, 256, 257, 258, 259, 260, 261, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 273, 274, 275, 276, 277, 278, 279, 280, 280, 281, 282};
const PROGMEM unsigned int ATAN_512_2048_16[] = {283, 286, 289, 292, 295, 297, 300, 302, 304, 306, 308, 310, 312, 314, 316, 318, 319, 321, 322, 324, 325, 327, 328, 329, 330, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 342, 343, 344, 345, 346, 346, 347, 348, 349, 349, 350, 350, 351, 352, 352, 353, 353, 354, 355, 355, 356, 356, 357, 357, 358, 358, 358, 359, 359, 360, 360, 361, 361, 361, 362, 362, 363, 363, 363, 364, 364, 364, 365, 365, 365, 366, 366, 366, 367, 367, 367, 367, 368, 368, 368, 369, 369, 369, 369, 370};
const PROGMEM unsigned int ATAN_2048_16384_512[] = {370, 376, 380, 383, 386, 387, 389, 390, 391, 392, 392, 393, 394, 394, 395, 395, 395, 396, 396, 396, 396, 397, 397, 397, 397, 397, 397, 397};


fixed atan(fixed x) {
    int value = x.getValue();
    if (value < 0) {
        value = -value;
    }
    if (value < 80) {
        return x;
    }
    unsigned int out;
    if (value < 512) {
        out = pgm_read_word_near(ATAN_0_512_4 + value / 4);
    } else if (value < 2048) {
        out = pgm_read_word_near(ATAN_512_2048_16 + (value - 512) / 16);
    } else if (value < 16384) {
        out = pgm_read_word_near(ATAN_2048_16384_512 + (value - 2048) / 512);
    } else {
        out = 402;
    }
    return (x > 0) ? fixed(out) : -fixed(out);
}
