#include "CR_shared.h"

static const char asset_finalVert[] = {
#embed "CR_final.vert" suffix(, 0)
};
static const char asset_finalFrag[] = {
#embed "CR_final.frag" suffix(, 0)
};

const char* const CR_asset_finalVert = asset_finalVert;
const char* const CR_asset_finalFrag = asset_finalFrag;
