#include "CR_shared.h"

static const char asset_sceneVert[] = {
#embed "CR_scene.vert" suffix(, 0)
};
static const char asset_sceneFrag[] = {
#embed "CR_scene.frag" suffix(, 0)
};

const char* const CR_asset_sceneVert = asset_sceneVert;
const char* const CR_asset_sceneFrag = asset_sceneFrag;

static const char asset_finalVert[] = {
#embed "CR_final.vert" suffix(, 0)
};
static const char asset_finalFrag[] = {
#embed "CR_final.frag" suffix(, 0)
};

const char* const CR_asset_finalVert = asset_finalVert;
const char* const CR_asset_finalFrag = asset_finalFrag;

static const Uint8 asset_defaultPng[] = {
#embed "CR_default.png"
};
const Uint8* const CR_asset_defaultPng = asset_defaultPng;
const size_t CR_asset_defaultPng_size = sizeof(asset_defaultPng);
