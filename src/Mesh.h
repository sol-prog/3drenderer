#pragma once

#include <stdbool.h>
#include "Vector.h"
#include "Face.h"


#define N_MESH_VERTICES 8
extern Vec3 mesh_vertices[N_MESH_VERTICES];

#define N_MESH_FACES 12 // 6 x 2 cube faces
extern Face mesh_faces[N_MESH_FACES];

typedef struct {
    Vec3 *vertices;
    Face *faces;
    Face *textures;
    Face *normals;
    bool has_normals;
    bool has_textures;
} ObjMesh;

void load_mesh(ObjMesh *mesh, const char *fpath);
void ObjMeshInit(ObjMesh *mesh);
void ObjMeshDestroy(ObjMesh *mesh);
