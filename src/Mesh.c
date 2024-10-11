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
        } else if(line[0] == 'v' && line[1] == 'n') {
            if(!mesh->has_normals) mesh->has_normals = true;
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
