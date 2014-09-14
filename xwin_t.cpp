/******************************************************************************
file: xwin_t.cpp
desc: 
 *****************************************************************************/

#include "xwin_t.h"			//
#include "common.h"			//
#include "rn_t.h"			//for renderer
#include "log_t.h"			//global logger
#include <X11/X.h>			//x stuff
#include <X11/Xlib.h>		//	"
#include <GL/glew.h>		//extension enumerator
#include <GL/glx.h>			//for xvisualinfo
#include <GL/gl.h>			//more gl stuff
#include <string.h>			//memcpy

using std::endl;

extern log_t* g_log;

/******************************************************************************
func: 
desc: 
 *****************************************************************************/
int xwin_t::start( void )
{
	int retv = ERR_OK;

	x_root_win = new Window;
	x_win = new Window;
	x_set_attribs = new XSetWindowAttributes;
	x_attribs = new XWindowAttributes;
	x_event = new XEvent;
	x_cmap = new Colormap;
	x_glcon = new GLXContext;

	if( !( x_root_win &&
				x_win &&
				x_set_attribs &&
				x_attribs &&
				x_event ) )
	{
		retv = ERR_MEM;
		goto out;
	}

	x_x_pos = DEF_X_POS;
	x_y_pos = DEF_Y_POS;
	x_width = DEF_WIDTH;
	x_height = DEF_HEIGHT;

	memcpy( x_gl_attribs,
			( GLint[5] ){
			GLX_RGBA,
			GLX_DEPTH_SIZE,
			COLOR_DEPTH,
			GLX_DOUBLEBUFFER,
			0 },
			sizeof(GLint) * 5 );

	if( ( retv = make_window( x_x_pos, x_y_pos, x_width, x_height ) )
			!= ERR_OK )
		goto out;

out:
	return retv;
}


/******************************************************************************
func: 
desc: 
 *****************************************************************************/
int xwin_t::shutdown( void )
{
	/*xlib*/
	XUnmapWindow( x_disp, *x_win );
	glXMakeCurrent( x_disp, None, NULL );
	glXDestroyContext( x_disp, *x_glcon );
	XFreeColormap( x_disp, *x_cmap );
	XDestroyWindow( x_disp, *x_win );
	XCloseDisplay( x_disp );

	/*gl*/
	if( x_vis_info ) XFree( x_vis_info );
	if( x_glcon ) delete x_glcon;
	if( x_cmap ) delete x_cmap;
	if( x_event ) delete x_event;
	if( x_attribs ) delete x_attribs;
	if( x_set_attribs ) delete x_set_attribs;
	if( x_win ) delete x_win;
	if( x_root_win ) delete x_root_win;

	return ERR_OK;
}


/******************************************************************************
func: 
desc: 
 *****************************************************************************/
int xwin_t::handle_events( rn_t* r, short* draw_flag )
{
	int retv = ERR_OK;

	/*check for pending events*/
	while( XPending( x_disp ) )
	{
		XNextEvent( x_disp, x_event );
		switch( x_event->type )
		{
			/*update the window where we need to*/
			case Expose:
				*draw_flag = true;
				break;

				/*handle key presses*/
			case KeyPress:
				g_log->w( MSG_INFO, "key %u\n", x_event->xkey.keycode );
				if( x_event->xkey.keycode == 24 )
					retv = ERR_QUIT;
				break;

			default:
				break;
		}
	}

	return retv;
}


/******************************************************************************
func: 
desc: draw the window
 *****************************************************************************/
int xwin_t::draw_window( rn_t* r )
{
	/*draw the window*/
	XGetWindowAttributes( x_disp, *x_win, x_attribs );
	glViewport( 0, 0, x_attribs->width, x_attribs->height );
	r->draw();
	glXSwapBuffers( x_disp, *x_win );

	return ERR_OK;
}


/******************************************************************************
func: 
desc: 
 *****************************************************************************/
int xwin_t::make_window( int x, int y, unsigned w, unsigned h )
{
	int retv = ERR_OK;

	if( !( x_disp = XOpenDisplay( NULL ) ) )
	{
		retv = ERR_DISPLAY;
		goto out;
	}

	*x_root_win = DefaultRootWindow( x_disp );

	/*get a visual mode*/
	if( !( x_vis_info = glXChooseVisual( x_disp, 0, x_gl_attribs ) ) )
	{
		retv = ERR_NO_VISUAL;
		goto out;
	}

	g_log->w( MSG_INFO, "found visual %u\n", x_vis_info->visualid );

	/*create the colormap*/
	*x_cmap = XCreateColormap(
			x_disp,
			*x_root_win,
			x_vis_info->visual,
			AllocNone );

	x_set_attribs->colormap = *x_cmap;
	x_set_attribs->event_mask = ExposureMask | KeyPressMask;

	/*create the window*/
	*x_win = XCreateWindow(
			x_disp,
			*x_root_win,
			x_x_pos,
			x_y_pos,
			x_width,
			x_height,
			0,
			x_vis_info->depth,
			InputOutput,
			x_vis_info->visual,
			( CWColormap | CWEventMask ),
			x_set_attribs );

	XMapWindow( x_disp, *x_win );
	XStoreName( x_disp, *x_win, WIN_NAME );

	/*create the gl context*/
	*x_glcon = glXCreateContext( x_disp, x_vis_info, NULL, GL_TRUE );
	glXMakeCurrent( x_disp, *x_win, *x_glcon );

	g_log->w( MSG_INFO, "gl version is %s\n", glGetString( GL_VERSION ) );

out:
	return retv;
}


