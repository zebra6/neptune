/******************************************************************************
file: console_t.h
desc: top level implementation of the 2d drawing routines
  *****************************************************************************/
#pragma once
#include "xwin_t.h"				//xwin for the fonts
#include <GL/glx.h>				//GLuint
#include <string>				//stl string				
#include <iostream>				//endl
#include <ostream>				//stream manipulators

#define FONT_NAME "fixed"		//name of the font to load

using std::string;
using std::endl;
using std::ostream;

class console_t
{
	public:
		/*functions*/
		console_t( void ) {};
		~console_t( void ) {};

		int start( void );
		int shutdown( void );
		int w( string msg );
		int w( string* msg );
		int w( const char* msg, ... );
		int w( char* msg, ... );
		
	private:
		/*functions*/
		int write( string* s );
		
		/*attributes*/
		GLuint c_font_base;
};

/*operators
  console_t& operator << ( console_t& lhs, string& rhs );
console_t& operator << ( console_t& lhs, const char* rhs );
console_t& operator << ( console_t& lhs, ostream& (*f)( ostream& ) );*/

