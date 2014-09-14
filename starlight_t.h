/******************************************************************************
file: starlight_t.h
desc: 
 *****************************************************************************/
#pragma once

#include "xwin_t.h"		//window routines
#include "rn_t.h"		//renderer
#include "console_t.h"	//io console
#include "log_t.h"		//logging facilites


class starlight_t
{
	public:
		/*functions*/
		starlight_t( void ) {};
		~starlight_t( void ) {};
		int start( void );
		int shutdown( void );

		int assign_global_log( log_t** log );
		int run( void );

	private:
		int update_world( short* draw_flag );
		xwin_t* s_xw;
		rn_t* s_r;
		console_t* s_con;
		log_t* s_log;
};


