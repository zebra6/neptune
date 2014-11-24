/******************************************************************************
file: common.h
desc: 
 *****************************************************************************/
#pragma once

#include "error.h"
#include <assert.h>

#define GL_NULL 0
#define MAX_FNAME 256
#define MAX_PATH 1024
#define MAX_STR_LEN 2048
#define MID_STR_LEN 128
//#define ASSERT_OVERRIDE false
#define SHOW_DBG_TIME false
#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

//int com_assert( int value );		//override built-in assert
//int com_array_count( void ar[] );	//size of an array

