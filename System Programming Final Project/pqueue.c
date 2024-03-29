/** Author: Bolong Yan
    2013/12/11*/
#include "pqueue.h"

/* Util macros */
#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) ((x-1) / 2)

void pqueue_heapify(priority_queue *q, size_t idx);

int word_cmp(const void *element1, const void *element2) {
	return ((word*)element1)->str - ((word*)element2)->str;
}

int count_cmp(const void *element1, const void *element2) {
	return ((word*)element1)->count - ((word*)element2)->count;
}

int number_cmp(const void *element1, const void *element2) {
	return *(int *)element1 - *(int *)element2;
}

/**
* Allocates memory for a new Priority Queue structure .

* 'cmp' function:
*   returns 0 if d1 and d2 have the same priorities
*   returns [negative value] if d1 have a smaller priority than d2
*   returns [positive value] if d1 have a greater priority than d2
*/
priority_queue *pq_create(int (*cmp)(const void *d1, const void *d2),
                   size_t capacity) {
    priority_queue *res = NULL;
    NP_CHECK(cmp);
    res = malloc(sizeof(*res));
    NP_CHECK(res);
    res->cmp = cmp;
    res->capacity = capacity;
    /* The inner representation of data inside the queue is an array of void* */
    res->data = malloc(capacity * sizeof(*(res->data)));
    NP_CHECK(res->data);
    res->size = 0;
    return (res);
}

/**
* Returns 1 if the priority queue is empty; or 0 otherwise.
*
*/
int pq_empty(priority_queue *q) {
    if (NULL == q) {
        return(1);
    }
    if (q->size < 1) {
         /* Priority Queue is empty */
         return 1;
    }
         return 0;
}

/**
* De-allocates memory for a given Priority Queue structure .
*/
void pq_destroy(priority_queue *q) {
    if (NULL == q) {
        DEBUG("Priority Queue is already NULL. Nothing to free.");
        return;
    }
    free(q->data);
    free(q);
    q=NULL;
}

/**
* Adds a new element to the Priority Queue .
*/
void pq_insert(priority_queue *q, const void *data) {
    size_t i;
    void *tmp = NULL;
    NP_CHECK(q);
    if (q->size >= q->capacity) {
        DEBUG("Priority Queue is full. Cannot add another element .");
        return;
    }
    /* Adds element last */
    q->data[q->size] = (void*) data;
    i = q->size;
    q->size++;
    /* The new element is swapped with its parent as long as its
    precedence is higher */
    while(i > 0 && q->cmp(q->data[i], q->data[PARENT(i)]) > 0) {
        tmp = q->data[i];
        q->data[i] = q->data[PARENT(i)];
        q->data[PARENT(i)] = tmp;
        i = PARENT(i);
    }
}

/**

* Returns the element with the biggest priority from the queue .
*/
void *pq_max(priority_queue *q) {
    void *data = NULL;
    NP_CHECK(q);
    if (q->size < 1) {
         /* Priority Queue is empty */
         DEBUG("Priority Queue underflow . Cannot remove another element .");
         return NULL;
    }
    data = q->data[0];
    return (data);
}

/**
* Removes and Returns the element with the biggest priority from the queue .
*/
void *pq_remove_max(priority_queue *q) {
    void *data = NULL;
    NP_CHECK(q);
    if (q->size < 1) {
         /* Priority Queue is empty */
         DEBUG("Priority Queue underflow . Cannot remove another element .");
         return NULL;
    }
    data = q->data[0];
    q->data[0] = q->data[q->size-1];
    q->size--;
    /* Restore heap property */
    pqueue_heapify(q, 0);
    return (data);
}

/**
* Turn an "almost-heap" into a heap .
*/
void pqueue_heapify(priority_queue *q, size_t idx) {
    /* left index, right index, largest */
    void *tmp = NULL;
    size_t l_idx, r_idx, lrg_idx;
    NP_CHECK(q);

    l_idx = LEFT(idx);
    r_idx = RIGHT(idx);

    /* Left child exists, compare left child with its parent */
    if (l_idx < q->size && q->cmp(q->data[l_idx], q->data[idx]) > 0) {
        lrg_idx = l_idx;
    } else {
        lrg_idx = idx;
    }

    /* Right child exists, compare right child with the largest element */
    if (r_idx < q->size && q->cmp(q->data[r_idx], q->data[lrg_idx]) > 0) {
        lrg_idx = r_idx;
    }

    /* At this point largest element was determined */
    if (lrg_idx != idx) {
        /* Swap between the index at the largest element */
        tmp = q->data[lrg_idx];
        q->data[lrg_idx] = q->data[idx];
        q->data[idx] = tmp;
        /* Heapify again */
        pqueue_heapify(q, lrg_idx);
    }
}
