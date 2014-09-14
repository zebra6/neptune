/******************************************************************************
file: console_t.cpp
desc: for writing 2d text to the screen
 *****************************************************************************/

#include "console_t.h"			//
#include "common.h"				//
#include "xwin_t.h"				//xwin for the fonts
#include "log_t.h"				//global log
#include <GL/glx.h>				//glxusefont
#include <iostream>				//cout, end
#include <string>				//stl string
#include <stdio.h>				//c-style print functions
#include <string.h>				//strcat
//#include <ostream>				//stream manipulators
//#include <sstream>				//ss for stream maipulator conversions

using std::cout;
using std::endl;
using std::string;
//using std::ostream;
//using std::stringstream;

extern log_t* g_log;

/******************************************************************************
func: start the console and load the appropriate fonts
desc:
 *****************************************************************************/
int console_t::start( void )
{
	g_log->w( MSG_INFO, "console started\n" );
	return ERR_OK;
}


/******************************************************************************
func: wrapper for writing a string to the console
desc:
 *****************************************************************************/
int console_t::w( string s )
{
	return write( &s );
}


/******************************************************************************
func: wrapper for writing a string to the console
desc:
 *****************************************************************************/
int console_t::w( string* s )
{
	return write( s );
}


/******************************************************************************
func: wrapper for writing a string to the console
desc:
 *****************************************************************************/
int console_t::w( const char* msg, ... )
{
	int retv = ERR_OK;
	char b[MAX_STR_LEN]	= { '\0' };
	string str = "";
	va_list argp;

	/*no parameters*/
	if( !msg )
		goto out;

	/*convert the message*/
	va_start( argp, msg );
	vsnprintf( b, MAX_STR_LEN, msg, argp );
	va_end( argp );
	b[MAX_STR_LEN - 1] = '\0';
	str = b;

	write( &str );

out:
	return retv;
}


/******************************************************************************
func: wrapper for writing a string to the console
desc:
 *****************************************************************************/
int console_t::w( char* msg, ... )
{
	int retv = ERR_OK;
	char b[MAX_STR_LEN]	= { '\0' };
	string str = "";
	va_list argp;

	/*no parameters*/
	if( !msg )
		goto out;

	/*convert the message*/
	va_start( argp, msg );
	vsnprintf( b, MAX_STR_LEN, msg, argp );
	va_end( argp );
	b[MAX_STR_LEN - 1] = '\0';
	str = b;

	write( &str );

out:
	return retv;
}


/******************************************************************************
func: wrapper for writing a string to the console
desc:
 *****************************************************************************/
int console_t::write( string* s )
{
	cout << *s;
	return ERR_OK;
}

/*
console_t& operator << ( console_t& lhs, string& rhs )
{
	if( (void*)&lhs == (void*)&rhs )
		goto out;

	lhs.w( &rhs );

out:
	return lhs;
}


console_t& operator << ( console_t& lhs, const char* rhs )
{
	if( (void*)&lhs == (void*)&rhs )
		goto out;

	lhs.w( (char*)rhs );

out:
	return lhs;
}


console_t& operator << ( console_t& lhs, ostream& (*rhs)( ostream& ) )
{
	if( (void*)&lhs == (void*)&rhs )
		goto out;

	lhs.w( "\n" );

out:
	return lhs;
}
*/


