/******************************************************************************
file: starlight_t.cpp
desc: 
 *****************************************************************************/
#include "starlight_t.h"	//
#include "common.h"			//common includes
#include "xwin_t.h"			//window
#include "rn_t.h"			//renderer
#include "console_t.h"		//io console
#include "log_t.h"			//logging facilities

extern log_t* g_log;

/******************************************************************************
func: start engine
desc:
 *****************************************************************************/
int starlight_t::start( void )
{
	int retv = ERR_OK;
	s_log = new log_t;
	s_xw = new xwin_t;
	s_r = new rn_t;
	s_con = new console_t;

	assert( s_log && s_xw && s_r && s_con );

	/*order is important in startup routines*/
	s_log->start();
	assign_global_log( &g_log );
	s_xw->start();
	s_r->start();
	s_con->start();

	/*console is started now so change log to internal logging*/
	g_log->select_output( DST_CONSOLE );

out:
	return retv;
}


/******************************************************************************
func: shut everything down
desc:
 *****************************************************************************/
int starlight_t::shutdown( void )
{
	/*shut down*/
	s_xw->shutdown();

	delete s_r;
	delete s_xw;

	delete s_con;
	delete s_log;

	return ERR_OK;
}


/******************************************************************************
func: set the global error log pointer
desc:
 *****************************************************************************/
int starlight_t::assign_global_log( log_t** log )
{
	assert( log );
	(*log) = s_log;
	return ERR_OK;
}


/******************************************************************************
func: run the engine
desc:
 *****************************************************************************/
int starlight_t::run( void )
{
	int retv = ERR_OK;
	short draw = false;

	while( retv == ERR_OK )
	{
		/*reset flags*/
		draw = false;

		/*get the events and find out if we need to draw*/
		retv = s_xw->handle_events( s_r, &draw );

		/*update the world*/
		update_world( &draw );

		/*draw if necessary*/
		if( draw )
			s_xw->draw_window( s_r );
	}

	return retv;
}


/******************************************************************************
func: update all the objects positions in the world
desc:
 *****************************************************************************/
int starlight_t::update_world( short* draw_flag )
{
	int retv = ERR_OK;
	*draw_flag = true;

	return ERR_OK;
}

