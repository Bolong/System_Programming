#include <stdio.h>
int main( int argc, char** argv )
{
 if( argc != 2 )
 {
  fprintf( stderr, "Usage: ./prog /some/path\n" );
  return 1;
 }
 // do something with argv[ 1 ] which contains "/some/path"
 return 0;
}
