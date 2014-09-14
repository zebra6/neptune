/******************************************************************************
file: log_t.c
desc: error logging facilities
 *****************************************************************************/
#include "log_t.h"			//
#include "common.h"			//
#include "console_t.h"		//for console writing functions
#include <string>			//stl string
#include <stdarg.h>			//va_start, end
#include <time.h>			//for time functions
#include <iostream>			//cout, endl
#include <stdio.h>			//c-style print functions
#include <string.h>			//strcat
#include <ostream>			//string manipulators

using std::string;
using std::cout;
using std::endl;
using std::ostream;


/******************************************************************************
func: start up the logging facilities
desc:
 *****************************************************************************/
int log_t::start( void )
{
	select_output( DST_COUT );
	set_min_info_level( MSG_UNK );
	set_lmmode( MSG_UNK );

	w( MSG_INFO, "logging facilities started\n" );

	return ERR_OK;
}


/******************************************************************************
func:
desc: shut down the logging facilities
 *****************************************************************************/
int log_t::shutdown( void )
{
	select_output( DST_COUT );
	w( MSG_INFO, "logging facilities halted\n" );
	return ERR_OK;
}


/******************************************************************************
func:
desc:
 *****************************************************************************/
int log_t::select_output( E_LOG_DESTINATION d )
{
	l_dst = d;
	return ERR_OK;
}


/******************************************************************************
func:
desc:
 *****************************************************************************/
int log_t::set_min_info_level( E_MSG_TYPE min )
{
	l_min_info_level = min;
	return ERR_OK;
}


/******************************************************************************
func: generic log write function
desc:
 *****************************************************************************/
int log_t::w( E_MSG_TYPE type, string msg )
{
	write_str( type, &msg );
	return ERR_OK;
}


/******************************************************************************
func: generic log write function
desc:
 *****************************************************************************/
int log_t::w( E_MSG_TYPE type, string* msg )
{
	/*no parameters*/
	if( !msg )
		goto out;

	write_str( type, msg );

out:
	return ERR_OK;
}


/******************************************************************************
func: log write function for c-style strings
desc:
 *****************************************************************************/
int log_t::w( E_MSG_TYPE type, const char* msg, ... )
{
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

	write_str( type, &str );

out:
	return ERR_OK;
}


/******************************************************************************
func: log write function for c-style strings
desc:
 *****************************************************************************/
int log_t::w( E_MSG_TYPE type, char* msg, ... )
{
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

	write_str( type, &str );

out:
	return ERR_OK;
}


/******************************************************************************
func: generic log write function
desc:
 *****************************************************************************/
int log_t::w( string msg )
{
	write_str( l_mmode, &msg );
	return ERR_OK;
}


/******************************************************************************
func: generic log write function
desc:
 *****************************************************************************/
int log_t::w( string* msg )
{
	/*no parameters*/
	if( !msg )
		goto out;

	write_str( l_mmode, msg );

out:
	return ERR_OK;
}


/******************************************************************************
func: log write function for c-style strings
desc:
 *****************************************************************************/
int log_t::w( const char* msg, ... )
{
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

	write_str( l_mmode, &str );

out:
	return ERR_OK;
}


/******************************************************************************
func: log write function for c-style strings
desc:
 *****************************************************************************/
int log_t::w( char* msg, ... )
{
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

	write_str( l_mmode, &str );

out:
	return ERR_OK;
}


/******************************************************************************
func: here we do the actual writing to the desired source
desc:
 *****************************************************************************/
int log_t::write_str( E_MSG_TYPE type, string* msg )
{
	time_t now = 0;
	char b[MID_STR_LEN] = { '\0' };
	struct tm ts = { 0 };
	string to_write = "";
	string str_type = "";

	/*shotrcut*/
	if( l_dst == DST_NONE )
		goto out;

	/*get the date/time*/
	if( SHOW_DBG_TIME )
	{
		now = time( 0 );
		ts = *localtime( &now );
		strftime( b, sizeof(b), "%m-%d-%Y %X", &ts );
		strcat( b, " " );
	}

	if( type >= l_min_info_level )
	{
		switch( l_dst )
		{
			case DST_NONE:
				break;

			case DST_COUT:
				msg_type_to_str( &str_type, type );
				cout << "[" << str_type << "] " << b;
				cout << *msg;
				break;

			case DST_CONSOLE:
				str_type = "[";
				msg_type_to_str( &str_type, type );
				str_type += "] ";
				str_type += b;
				str_type += *msg;
				l_con->w( &str_type );
				break;

			case DST_FILE:
				break;

			case DST_CONSOLE_AND_FILE:
				break;

			default:
				break;
		}
	}

out:
	return ERR_OK;
}


/******************************************************************************
func:
desc: convert an enum type to the correct string
 *****************************************************************************/
int log_t::msg_type_to_str( string* dst, E_MSG_TYPE type )
{
	assert( dst );
	switch( type )
	{
		case MSG_UNK:
			*dst += "unknown";
			break;
		case MSG_INFO:
			*dst += "info";
			break;
		case MSG_WARN:
			*dst += "warning";
			break;
		case MSG_FATAL:
			*dst += "fatal";
			break;
		default:
			*dst += "invalid";
			break;
	}

	return ERR_OK;
}

