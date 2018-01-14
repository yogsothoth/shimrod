/*
 * Magick++-no-warn.h
 * Wrapper for Magick++.h to inhibit warnings
 */

#ifndef MAGICKNOWARN_H
#define MAGICKNOWARN_H

// turn off warnings for ImageMagick
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#include <Magick++.h>
#pragma clang diagnostic pop



#endif // MAGICKNOWARN_H
