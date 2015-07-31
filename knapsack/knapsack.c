

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct kitem_st {

    int idx;
    int val;
    int wght;
    double ratio;

    struct kitem_st * next;
} kitem_t;

int kitem_cmp(const void *a, const void *b) 
{
    const kitem_t * left = (kitem_t*)a;
    const kitem_t * right = (kitem_t*)b;

    if(left->ratio > right->ratio)
        return -1;
    else if(left->ratio < right->ratio)
        return 1;

    return 0;
}

kitem_t * kitem_create(int idx, int val, int wght) {
    kitem_t * ret = (kitem_t*)malloc(sizeof(kitem_t));

    assert(wght > 0);
    
    ret->idx = idx;
    ret->val = val;
    ret->wght = wght;
    ret->ratio = (double)val / wght;

    ret->next = NULL;
    
    return ret;
}

void kitem_free( kitem_t * item ) {
    assert(item != NULL);
    free(item);
}

typedef 
struct {
    kitem_t * head;
    kitem_t * tail;
    size_t  size;
} klist_t;


klist_t * klist_create() {
    klist_t * ret = (klist_t*)malloc(sizeof(klist_t));
    ret->head = NULL;
    ret->tail = NULL;
    ret->size = 0;
    
    return ret;
}

void klist_delete( klist_t * list ) {
    kitem_t * n;

    assert(list != NULL);
    while( list->head != NULL ) {
        n = list->head->next;
        kitem_free( list->head );
        list->head = n;
    }
       
}


size_t klist_size( const klist_t * list ) {
    return ((list != NULL) ? list->size : 0);
}

klist_t * klist_add( klist_t * list, kitem_t * item ) {
    kitem_t * tmp;
    
    assert( list != NULL );
    assert( item != NULL );
    
    item->next = list->head;
    list->head = item;
    list->size += 1;
    
    return list;
}

typedef 
struct {
    kitem_t * data;
    int       capacity;
    int       size;
} kprob_t;

kprob_t * kprob_create(int capacity, int size) {
    kprob_t * ret = (kprob_t*)malloc(sizeof(kprob_t));
    
    assert(capacity > 0 && size > 0);
    
    ret->capacity = capacity;
    ret->size = size;
    ret->data = (kitem_t*)malloc(sizeof(kitem_t) * ret->size);

    assert(ret->data != NULL);
    
    return ret;
}

void kprob_delete( kprob_t * p ) {
    assert( p != NULL );
    free( p->data );
    free( p );
}


void kprob_sort(kprob_t * prob) {
    assert(prob != NULL);
    qsort(prob->data, prob->size, sizeof(kitem_t), kitem_cmp);
    
}

kprob_t * read_data(const char * file_name) {
    kprob_t * ret = NULL;
    kitem_t * tmp = 0;
    FILE * in = fopen(file_name, "r");
    int v, w, i = 0;
    
    
    fscanf(in, "%d %d", &v, &w);

    ret = kprob_create(w, v);
    
    while( fscanf(in, "%d %d", &v, &w) != EOF ) {
        assert( w > 0 );
        ret->data[i].idx = i;
        ret->data[i].val = v;
        ret->data[i].wght = w;
        ret->data[i].ratio = (double) v / w;
        i++;
    }

    fclose( in );
    
    return ret;
}

void print_data(kprob_t * data, bool verbose) {
    kitem_t * it = NULL;
    int i;
    
    assert(data != NULL);
    fprintf(stderr, "%d %d\n", data->size, data->capacity);

    for(i = 0; i < data->size; i++) {
        if(verbose) fprintf(stderr, "%d: ", data->data[i].idx);
        fprintf(stderr, "%d %d ", data->data[i].val, data->data[i].wght);
        if(verbose) fprintf(stderr, " (%lf)", data->data[i].ratio);
        fprintf(stderr, "\n");
    }
}


static bool verbose = true;
int main(int argc, char * argv[]) {

    kprob_t * data;
    
    data = read_data(argv[1]);
    
    fprintf(stderr, "Read %ld items\n", data->size);
    print_data( data, verbose );
    
    kprob_sort( data );
    print_data( data, verbose );
    
    kprob_delete( data );
    
    return EXIT_SUCCESS;
}
