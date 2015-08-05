

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>

#include <math.h>
#include <assert.h>

using namespace std;

struct KItem {

    friend bool operator<(const KItem & lhs, const KItem & rhs) {
        return lhs.ratio < rhs.ratio;
    }

    friend bool operator==(const KItem & lhs, const KItem & rhs) {
        return lhs.ratio == rhs.ratio;
    }

    friend ostream & operator<<(ostream & out, const KItem & item) {
        if(out)
            out << "[" << item.idx << "] "
                << item.val << " " << item.wght
                << " (" << item.ratio << ")";
        
        return out;
    }

    friend istream & operator>>(istream & in, KItem & item) {
        if(in) {
            in >> item.val >> item.wght;
            assert(item.wght > 0);
            item.ratio = (double)item.val / item.wght;
        }
        return in;
    }
    
    KItem(int idx_, int val_ = 0, int wght_ = 1) {
        assert(wght_ > 0);
        
        this->idx = idx_;
        this->val = val_;
        this->wght = wght_;
        this->ratio = (double)val_ / wght_;
    }

    int get_value() const {
        return this->val;
    }

    int get_weight() const {
        return this->wght;
    }

    double get_ratio() const {
        return this->ratio;
    }
    
private:
    
    int idx;
    int val;
    int wght;
    double ratio;    
};

#if 0
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
#endif

/**
 * Precalculate optimal value i.e. most idealistic solution
 * take all items until fill in and split the last item if needed
 */
int precalc(const vector<KItem> & items, const int K) {
    vector<KItem>::const_iterator it = items.begin();
    int value = 0;
    int capacity = K;
    int i = 0;
    
    for(; i < items.size() && capacity >= items[i].get_weight(); i++) {
        value += items[i].get_value();
        capacity -= items[i].get_weight();
    }

    if(capacity > 0) {
        // we can not pack the last item
        // but most likelly we can pack part of it
        double r = (double)capacity / items[i].get_weight();
        value += floor(capacity * items[i].get_ratio());
    }

    return value;
}


/*
 * oblicz ile maksymalna wartosc jezeli dalaczymy wszystkie mozliwe elementy
 */
int get_bound(const vector<KItem> & items, int idx, int cap) {

}


static bool verbose = true;
int main(int argc, char * argv[]) {
    ifstream in(argv[1]);

    int N, K, V = 0; // V is sum of all values
    vector<KItem> items;

    in >> N >> K;

    for(int i = 0; i < N; i++) {
        KItem item(i);
        in >> item;
        items.push_back( item );
        V += item.gwt_value();
    }

    sort(items.begin(), items.end());
    reverse(items.begin(), items.end());
    
    copy(items.begin(), items.end(), ostream_iterator<KItem>(cout, "\n"));

    return 0;
}
