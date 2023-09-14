// Laura Toma
//
#ifndef __grid_h
#define __grid_h

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


typedef struct _grid {
  unsigned int     ncols;
  unsigned int     nrows;
  float* data;
  
  float   xllcorner;
  float   yllcorner;
  float   cellsize;
  float   nodata_value;
  
  float   min_value;
  float   max_value;
} Grid;


typedef struct gridpoint {
    unsigned int r, c;
} GridPoint;


static inline int inside_grid(const Grid* grid, int r, int c) {
    return r >= 0 && r < grid->nrows && c >= 0 && c < grid->ncols;
}


static inline float grid_get(const Grid* grid, int r, int c) {
    return grid->data[r * grid->ncols + c];
}


static inline bool  grid_is_nodata(Grid* grid, int r, int c) {
  return grid->nodata_value == grid_get(grid, r, c);
}


static inline void grid_set(Grid* grid, int r, int c, const float val) {
     grid->data[r * grid->ncols + c] = val;
     if (val != grid->nodata_value) {
       grid->min_value = fmin(val, grid->min_value);
       grid->max_value = fmax(val, grid->max_value);
     }
}

//set (r,c) to be nodata 
static inline void  grid_set_nodata(Grid* grid, int r, int c) {
  grid->data[r * grid->ncols + c] = grid->nodata_value; 
} 


//read  from file 
Grid* grid_read(FILE* in_file);


Grid* grid_init_from(Grid* grid);

//write to file 
void  grid_write(FILE* out_file, Grid* grid);

//free space 
void  grid_free(Grid* grid);


#endif
