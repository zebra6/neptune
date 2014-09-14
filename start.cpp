/******************************************************************************
file: start.cpp
desc: 
 *****************************************************************************/
#include "common.h"
#include "starlight_t.h"
#include "log_t.h"

starlight_t* g_world = NULL;
log_t* g_log = NULL;

/******************************************************************************
func: entry_t( void )
desc: 
 *****************************************************************************/
int main( int argc, char** argv )
{
	starlight_t* s = new starlight_t;
	assert( s );
	s->start();
	g_world = s;
	s->run();
	s->shutdown();
	delete( s );
	return 0;
}

