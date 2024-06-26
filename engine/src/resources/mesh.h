#pragma once

#include "resource_types.h"

CAPI b8 mesh_load_from_resource(const char* resource_name, mesh* out_mesh);

CAPI void mesh_unload(mesh* m);
