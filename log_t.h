/******************************************************************************
file: log_t.h
desc: 
 *****************************************************************************/
#pragma once

#include "console_t.h"		//for console writing
#include <string>			//stl string
#include <ostream>			//string manipulators

using std::string;
using std::ostream;

/*enums for where the output should go*/
typedef enum
{
	DST_NONE,
	DST_COUT,
	DST_STDERR,				//not implemented
	DST_CONSOLE,
	DST_FILE,				//not implemented
	DST_CONSOLE_AND_FILE,	//	"
} E_LOG_DESTINATION;

/*enum for the log message types*/
typedef enum
{
	MSG_UNK,
	MSG_INFO,
	MSG_WARN,
	MSG_FATAL
} E_MSG_TYPE;


class log_t
{
	public:
		/*functions*/
		log_t( void ) {};
		~log_t( void ) {};
		int start( void );
		int shutdown( void );

		/*compound methods*/
		int select_output( E_LOG_DESTINATION d );
		int set_min_info_level( E_MSG_TYPE min );
		int w( E_MSG_TYPE type, string msg );
		int w( E_MSG_TYPE type, string* msg );
		int w( E_MSG_TYPE type, const char* msg, ... );
		int w( E_MSG_TYPE type, char* msg, ... );
		int w( string msg );
		int w( string* msg );
		int w( const char* msg, ... );
		int w( char* msg, ... );


		/*basic methods*/
		void set_current_console( console_t* con ) { l_con = con; };
		void set_lmmode( E_MSG_TYPE type ) { l_mmode = type; };


	private:
		/*functions*/
		int write_str( E_MSG_TYPE type, string* msg );
		int msg_type_to_str( string* dst, E_MSG_TYPE type );

		/*attribs*/
		E_LOG_DESTINATION l_dst;
		E_MSG_TYPE l_min_info_level;
		E_MSG_TYPE l_mmode;
		console_t* l_con;
};

