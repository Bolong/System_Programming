/** Author: Bolong Yan
    2013/12/11*/

#include "pqueue.h"
/** Test Function */
int main( ) {
	int i;
	word word1, word2, word3;
	word1.str = "One";
	word1.count = 100;
	word2.str = "Two";
	word2.count = 50;
	word3.str = "Three";
	word3.count = 20;
	// Create a priority queue that uses a word comparator
	priority_queue* pq1 = pq_create(word_cmp, 3 );
	pq_insert(pq1, &word1);
	pq_insert(pq1, &word2);
	pq_insert(pq1, &word3);
	printf("Test Case #1:\n");
	while(!pq_empty(pq1))
	{
	printf("%s\n", ((word*) pq_remove_max(pq1))->str);
	}
	// Create a priority queue that uses a count comparator
	priority_queue* pq2 = pq_create(count_cmp, 3);
	pq_insert(pq2, &word1);
	pq_insert(pq2, &word2);
	pq_insert(pq2, &word3);
	printf( "Test Case #2:\n" );
	while(!pq_empty(pq2))
	{
	printf("%s\n", ((word*) pq_remove_max(pq2))->str);
	}
	// Create a priority queue that uses a number comparator
	priority_queue* pq3 = pq_create(number_cmp, 5);
	for( i = 1; i <= 5; i++ )
	{
	int* number = (int*) malloc(sizeof(int));
	*number = i;
	pq_insert( pq3, number );
	}
	printf( "Test Case #3:\n" );
	printf( "%d\n", *( ( int* ) pq_max( pq3 ) ) );
	while( ! pq_empty( pq3 ) )
	{
	printf( "%d\n", *( ( int* ) pq_remove_max( pq3 ) ) );
	}
	pq_destroy( pq1 );
	pq_destroy( pq2 );
	pq_destroy( pq3 );
	return 0;
}
