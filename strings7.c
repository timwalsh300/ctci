#include <stdio.h>
#include <stdlib.h>

struct pixel {
    int red, green, blue;
};

struct ppm {
    struct pixel **image;
    int rows, columns;
};

struct ppm read_ppm(const char *filename)
{
    char buff[16];
    FILE *fp;
    int c, rgb_comp_color;
    struct ppm p;

    fp = fopen(filename, "rb");

    if (!fgets(buff, sizeof(buff), fp)) {
        perror(filename);
        exit(1);
    }

    if (buff[0] != 'P' || buff[1] != '3') {
         fprintf(stderr, "Invalid image format (must be 'P3')\n");
         exit(1);
    }

    //check for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n')
            ;
        c = getc(fp);
    }
    ungetc(c, fp);

    if (fscanf(fp, "%d %d", &p.columns, &p.rows) != 2 || p.rows != p.columns) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
         exit(1);
    }

    if (fscanf(fp, "%d", &rgb_comp_color) != 1 || rgb_comp_color != 255) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
         exit(1);
    }

    while (fgetc(fp) != '\n')
        ;

    //memory allocation for pixel data
    p.image = malloc(sizeof(struct pixel *) * p.rows);
    for (int i = 0; i < p.rows; i++) {
        p.image[i] = malloc(sizeof(struct pixel) * p.columns);
    }

    //read pixel data from file
    for (int i = 0; i < p.rows; i++) {
        for (int j = 0; j < p.columns; j++) {
            fscanf(fp, "%d %d %d", &p.image[i][j].red, &p.image[i][j].green, &p.image[i][j].blue);
        }
    }

    fclose(fp);
    return p;
}

void rotate_ppm(struct ppm *p)
{
    // transpose the image matrix in-place
    int depth = p->rows;
    struct pixel temp;
    for (int i = 0; i < depth; i++) {
        for (int j = i + 1; j < depth; j++) {
            temp = p->image[i][j];
            p->image[i][j] = p->image[j][i];
            p->image[j][i] = temp;
        }
    }

    // reverse the image matrix rows in-place
    for (int row = 0; row < depth; row++) {
        int i = 0;
        int j = depth - 1;
        while (i < j) {
            temp = p->image[row][i];
            p->image[row][i] = p->image[row][j];
            p->image[row][j] = temp;
            j--;
            i++;
        }
    }
}

void blue(struct ppm *p)
{
    for (int i = 0; i < p->rows; i++) {
        for (int j = 0; j < p->columns; j++) {
            p->image[i][j].blue = p->image[i][j].blue + 128 < 256 ? p->image[i][j].blue + 128 : 255;
        }
    }
}

void write_ppm(const char *filename, struct ppm *p)
{
    FILE *fp;
    //open file for output
    fp = fopen(filename, "wb");
    if (!fp) {
         fprintf(stderr, "Unable to open file '%s'\n", filename);
         exit(1);
    }

    //write the header file
    //image format
    fprintf(fp, "P3\n");

    //image size
    fprintf(fp, "%d %d\n", p->columns, p->rows);

    // rgb component depth
    fprintf(fp, "255\n\n");

    // pixel data
    for (int i = 0; i < p->rows; i++) {
        for (int j = 0; j < p->columns; j++) {
            fprintf(fp, "%d %d %d\t", p->image[i][j].red, p->image[i][j].green, p->image[i][j].blue);
        }
        fprintf(fp, "\n\n");
    }

    fclose(fp);
}

int main(void)
{
    struct ppm test = read_ppm("watch.ppm");
    // it's more efficient to pass pointers to my ppm struct than passing the whole ppm struct
    rotate_ppm(&test);
    blue(&test);
    write_ppm("rotated_blue_watch.ppm", &test);
}
