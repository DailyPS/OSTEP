#include <stdio.h>
#include <stdlib.h>

struct vector {
  int * data;
  int sz;
  int cap;
};

void vector_insert(struct vector * v, int val)
{
  if (v->sz == v->cap)
  {
    v->cap = v->cap * 2;
    v->data = (int *) realloc(v->data, sizeof(int) * v->cap);
  }

  (v->data)[v->sz] = val;
  v->sz++;
}

void vector_delete(struct vector * v)
{
  v->sz--;
  (v->data)[v->sz] = 0;

  if (v->sz == (v->cap / 4))
  {
    v->cap = v->cap / 2;
    v->data = (int *) realloc(v->data, sizeof(int) * v->cap);
  }
}

void vector_free(struct vector * v)
{
  free(v->data);
  v->sz = 0;
  v->cap = 0;
}