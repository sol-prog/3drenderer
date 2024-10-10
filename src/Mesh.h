#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "Vector.h"
#include "Face.h"

typedef struct {
    Vec3 *vertices;
    Face *faces;
    Face *textures;
    Face *normals;
    bool has_normals;
    bool has_textures;
    bool was_init;
    size_t nr_vertices;
    size_t nr_faces;
} ObjMesh;

void ObjMeshInit(ObjMesh *mesh);
void load_mesh(ObjMesh *mesh, const char *fpath);
void ObjMeshDestroy(ObjMesh *mesh);
