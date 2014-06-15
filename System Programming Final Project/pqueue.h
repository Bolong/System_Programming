/** Author: Bolong Yan
    2013/12/11*/
#ifndef __PQUEUE__H__
#define __PQUEUE__H__
#include <stdio.h>
#include <stdlib.h>
/**
* Debugging macro .
*
* Checks for a NULL pointer, and prints the error message, source file and
* line via 'stderr' .
* If the check fails the program exits with error code (-1) .
*/
#define NP_CHECK(ptr) \
    { \
        if (NULL == (ptr)) { \
            fprintf(stderr, "%s:%d NULL POINTER: %s n", \
                __FILE__, __LINE__, #ptr); \
            exit(-1); \
        } \
    } \

#define DEBUG(msg) fprintf(stderr, "%s:%d %s", __FILE__, __LINE__, (msg))

/**
* Priority Queue Structure
*/
typedef struct priority_queue_s {
    /* The actual size of heap at a certain time */
    size_t size;
    /* The amount of allocated memory for the heap */
    size_t capacity;
    /* An array of (void*), the actual max-heap */
    void **data;
    /* A pointer to a comparator function, used to prioritize elements */
    int (*cmp)(const void *d1, const void *d2);
} priority_queue;

/* Word structure */
typedef struct word_s {
    char *str;
    int count;
} word;

int word_cmp(const void *element1, const void *element2);

int count_cmp(const void *element1, const void *element2);

int number_cmp(const void *element1, const void *element2);

/** Allocates memory for a new Priority Queue .
Needs a pointer to a comparator function, thus establishing priorities .
*/
priority_queue *pq_create(int (*cmp)(const void *d1, const void *d2),
                   size_t capacity);


/**Returns 1 if the priority queue is empty; or 0 otherwise.*/
int pq_empty(priority_queue *q);

/** De-allocates memory for a given Priority Queue */
void pq_destroy(priority_queue *q);

/** Add an element inside the Priority Queue */
void pq_insert(priority_queue *q, const void *data);

/** Returns the element with the greatest priority from within the Queue */
void *pq_max(priority_queue *q);

/** Removes and Returns the element with the greatest priority from within the Queue */
void *pq_remove_max(priority_queue *q);

#endif
