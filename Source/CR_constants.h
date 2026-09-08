#if !defined __CR_CONSTANTS_H__
#define __CR_CONSTANTS_H__

#include "CR_common.h"

constexpr int CR_WIDTH = 640;
constexpr int CR_HEIGHT = 360;
constexpr float CR_ASPECT = (float)CR_WIDTH / (float)CR_HEIGHT;

constexpr int CR_MASTER_TEX_WIDTH = 1024;
constexpr int CR_MASTER_TEX_HEIGHT = 1024;

constexpr int CR_MAX_SPRITES = 1024;
constexpr int CR_MAX_VERTICES = CR_MAX_SPRITES * 4;
constexpr int CR_MAX_INDICES = CR_MAX_SPRITES * 6;

#endif /* __CR_CONSTANTS_H__ */
