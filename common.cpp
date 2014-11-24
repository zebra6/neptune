/******************************************************************************
file: common.cpp
desc: 
 *****************************************************************************/
#include "common.h"		//
#include <assert.h>		//assert override



/******************************************************************************
func:
desc: override the default assert handler
 *****************************************************************************/
/*int com_assert( int value )
{
	short hold = true;

	if( !ASSERT_OVERRIDE )
		assert( value );
	else
	{
		cout << "engine asserted, holding..." << endl;
		while( hold ) {};
	}

	return ERR_OK;
}*/


/******************************************************************************
func:
desc: get an array count	
 *****************************************************************************/
/*int com_array_count( void ar[] )
{
	assert( ar );
	return ( sizeof( ar ) / ( sizeof( ar[0] ); 
}*/
