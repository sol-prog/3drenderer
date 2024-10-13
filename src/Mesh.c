#include "Mesh.h"
#include "my_getline.h"
#include "array.h"
#include <stdlib.h>

void ObjMeshInit(ObjMesh *mesh) {
    ARRAY_CREATE(Vec3, arr);
    mesh->vertices = arr;
    ARRAY_CREATE(Face, arr2);
    mesh->faces_indices = arr2;
    ARRAY_CREATE(Face, arr3);
    mesh->textures_indices = arr3;
    ARRAY_CREATE(Face, arr4);
    mesh->normals_indices = arr4;
    ARRAY_CREATE(Vec2, arr5);
    mesh->vtextures = arr5;
    ARRAY_CREATE(Vec3, arr6);
    mesh->vnormals = arr6;


    mesh->has_normals = false;
    mesh->has_textures = false;
    mesh->was_init = true;
    mesh->nr_vertices = 0;
    mesh->nr_faces = 0;
}

void ObjMeshDestroy(ObjMesh *mesh) {
    if(!mesh->was_init) return;

    ARRAY_DESTROY(mesh->vertices);
    ARRAY_DESTROY(mesh->faces_indices);
    ARRAY_DESTROY(mesh->textures_indices);
    ARRAY_DESTROY(mesh->normals_indices);
    ARRAY_DESTROY(mesh->vtextures);
    ARRAY_DESTROY(mesh->vnormals);
}

void parse_v_line(ObjMesh *mesh, char *line) {
    float x, y, z;
    sscanf(line, "%f%f%f", &x, &y, &z);
    ARRAY_PUSH(mesh->vertices, ((Vec3){x, y, z}));
}

void parse_vn_line(ObjMesh *mesh, char *line) {
    float nx, ny, nz;
    sscanf(line, "%f%f%f", &nx, &ny, &nz);
    ARRAY_PUSH(mesh->vnormals, ((Vec3){nx, ny, nz}));
}

void parse_vt_line(ObjMesh *mesh, char *line) {
    float tx, ty;
    sscanf(line, "%f%f", &tx, &ty);
    ARRAY_PUSH(mesh->vtextures, ((Vec2){tx, ty}));
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
        if(fi_indx == 3) ARRAY_PUSH(mesh->faces_indices, ((Face){fi[0], fi[1], fi[2]}));
        if(ti_indx == 3) ARRAY_PUSH(mesh->textures_indices, ((Face){ti[0], ti[1], ti[2]}));
        if(ni_indx == 3) ARRAY_PUSH(mesh->normals_indices, ((Face){ni[0], ni[1], ni[2]}));
    }
}

void parse_line(ObjMesh *mesh, char *line) {
    size_t len = strlen(line);
    if(len > 3) {
        if(line[0] == 'v' && line[1] == ' ') {
            parse_v_line(mesh, line + 2);
        } else if(line[0] == 'v' && line[1] == 't') {
            if(!mesh->has_textures) mesh->has_textures = true;
            parse_vt_line(mesh, line + 2);
        } else if(line[0] == 'v' && line[1] == 'n') {
            if(!mesh->has_normals) mesh->has_normals = true;
            parse_vn_line(mesh, line + 2);
        } else if(line[0] == 'f' && line[1] == ' ') {
            parse_f_line(mesh, line + 2);
        }
    }
}

void load_mesh(ObjMesh *mesh, const char *fpath) {
    if(mesh->was_init == false) {
        fprintf(stderr, "Error! ObjMesh was not intialized - we abort the loading sequence!\n");
        return;
    }

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

    mesh->nr_vertices = ARRAY_SIZE(mesh->vertices);
    mesh->nr_faces = ARRAY_SIZE(mesh->faces_indices);
}

/*
// gcc -std=c17 -Wall -Wextra -pedantic -g -fsanitize=address,undefined my_getline.c Vector.c Mesh.c -lm
int main(void) {
    ObjMesh mesh;
    ObjMeshInit(&mesh);
    load_mesh(&mesh, "../assets/cube.obj");
    Vec3 camera_pos = {0, 0, -5};

    for(size_t i = 0; i < mesh.nr_faces; ++i) {
        printf("Face %zd\n", i + 1);
        printf("A = %d\n", mesh.faces_indices[i].a);
        printf("B = %d\n", mesh.faces_indices[i].b);
        printf("C = %d\n", mesh.faces_indices[i].c);
        
        Vec3 ptA = mesh.vertices[mesh.faces_indices[i].a - 1];
        Vec3 ptB = mesh.vertices[mesh.faces_indices[i].b - 1];
        Vec3 ptC = mesh.vertices[mesh.faces_indices[i].c - 1];
        
        // Calculate the normal vector N
        Vec3 AB = vec3_sub(ptB, ptA);
        Vec3 AC = vec3_sub(ptC, ptA);
        Vec3 N = vec3_cross(AB, AC);
        printf("Nx = %f, Ny = %f, Nz = %f\n", N.x, N.y, N.z);
        
        Vec3 AO = vec3_sub(camera_pos, ptA);

        float AO_N = vec3_dot(AO, N);
        printf("dot prod = %f\n", AO_N);
        puts("");
    }
    ObjMeshDestroy(&mesh);
}
*/