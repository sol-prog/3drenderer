#include "Mesh.h"
#include "my_getline.h"
#include "array.h"
//#include "Vector.h"
//#include "Face.h"
#include <stdlib.h>
//#include <stdbool.h>


Vec3 mesh_vertices[N_MESH_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 1
    { .x = -1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y =  1, .z = -1 }, // 3
    { .x =  1, .y = -1, .z = -1 }, // 4
    { .x =  1, .y =  1, .z =  1 }, // 5
    { .x =  1, .y = -1, .z =  1 }, // 6
    { .x = -1, .y =  1, .z =  1 }, // 7
    { .x = -1, .y = -1, .z =  1 }  // 8
};

Face mesh_faces[N_MESH_FACES] = {
    // front
    { .a = 1, .b = 2, .c = 3 },
    { .a = 1, .b = 3, .c = 4 },
    // right
    { .a = 4, .b = 3, .c = 5 },
    { .a = 4, .b = 5, .c = 6 },
    // back
    { .a = 6, .b = 5, .c = 7 },
    { .a = 6, .b = 7, .c = 8 },
    // left
    { .a = 8, .b = 7, .c = 2 },
    { .a = 8, .b = 2, .c = 1 },
    // top
    { .a = 2, .b = 7, .c = 5 },
    { .a = 2, .b = 5, .c = 3 },
    // bottom
    { .a = 6, .b = 8, .c = 1 },
    { .a = 6, .b = 1, .c = 4 }
};

void ObjMeshInit(ObjMesh *mesh) {
    ARRAY_CREATE(Vec3, arr);
    mesh->vertices = arr;
    ARRAY_CREATE(Face, arr2);
    mesh->faces = arr2;
    ARRAY_CREATE(Face, arr3);
    mesh->textures = arr3;
    ARRAY_CREATE(Face, arr4);
    mesh->normals = arr4;

    mesh->has_normals = false;
    mesh->has_textures = false;
}

void ObjMeshDestroy(ObjMesh *mesh) {
    ARRAY_DESTROY(mesh->vertices);
    ARRAY_DESTROY(mesh->faces);
    ARRAY_DESTROY(mesh->textures);
    ARRAY_DESTROY(mesh->normals);
}

void parse_v_line(ObjMesh *mesh, char *line) {
    float x, y, z;
    sscanf(line, "%f%f%f", &x, &y, &z);
    ARRAY_PUSH(mesh->vertices, ((Vec3){x, y, z}));
}

void parse_f_line(ObjMesh *mesh, char *line) {
    //printf("%s", line);
    char *token;
    const char delimiters[] = "/ ";
    const int max_elements = 9;
 
    enum {no_elem = 3};
    int fi[no_elem];
    int ti[no_elem];
    int ni[no_elem];
    
    int count = 0, total = 0;
    int fi_indx = 0, ti_indx = 0, ni_indx = 0;

    token = strtok(line, delimiters);
    int type = 0;
    while (token != NULL) {
        int number = atoi(token);
        total++;
        token = strtok(NULL, delimiters);

        if(count < max_elements) {    
            if(type == 0) {
                //printf("We take out face elem %d\n", number);
                fi[fi_indx++] = number;

                if(mesh->has_textures) {
                    type = 1;
                } else if(mesh->has_normals) {
                    type = 2;
                }
                count++;
                continue;
            }
            if(type == 1) {
                //printf("We take out texture elem %d\n", number);
                ti[ti_indx++] = number;
                if(mesh->has_normals) {
                    type = 2;
                } else {
                    type = 0;
                }
                count++;
                continue;
            }
            if(type == 2) {
                //printf("We take out texture elem %d\n", number);
                ni[ni_indx++] = number;
                type = 0;
                count++;
                continue;
            }            
        }
    }

    if(count != total) {
        fprintf(stderr, "Error! I can parse only triangles!\n");
    } else {
        if(fi_indx == 3) ARRAY_PUSH(mesh->faces, ((Face){fi[0], fi[1], fi[2]}));
        if(ti_indx == 3) ARRAY_PUSH(mesh->textures, ((Face){ti[0], ti[1], ti[2]}));
        if(ni_indx == 3) ARRAY_PUSH(mesh->normals, ((Face){ni[0], ni[1], ni[2]}));
    }
}

void parse_line(ObjMesh *mesh, char *line) {
    size_t len = strlen(line);
    if(len > 3) {
        if(line[0] == 'v' && line[1] == ' ') {
            parse_v_line(mesh, line + 2);
        } else if(line[0] == 'v' && line[1] == 't') {
            if(!mesh->has_textures) mesh->has_textures = true;
        } else if(line[0] == 'v' && line[1] == 'n') {
            if(!mesh->has_normals) mesh->has_normals = true;
        } else if(line[0] == 'f' && line[1] == ' ') {
            parse_f_line(mesh, line + 2);
        }
    }
}

void load_mesh(ObjMesh *mesh, const char *fpath) {
    FILE *fp = fopen(fpath, "r");
    if(fp == NULL) {
        fprintf(stderr, "Unable to open file %s\n", fpath);
        return;
    }

    char *line = NULL;
    size_t len = 0;

    while(my_getline(&line, &len, fp) != -1) {
        parse_line(mesh, line);
    }

    fclose(fp);
    free(line);
}
