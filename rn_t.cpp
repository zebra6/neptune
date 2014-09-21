/******************************************************************************
file: rn_t.cpp
desc: 
 *****************************************************************************/
#include "rn_t.h"			//
#include "common.h"			//
#include "fs_t.h"			//filesystem
#include "log_t.h"			//for logging
#include <GL/glew.h>		//extension enumerator
#include <GL/gl.h>			//gl types
#include <math.h>			//fmodf, fcosf, fsinf
#include <vector>			//stl vector
#include <algorithm>		//stl for each
#include <string>			//stl string

using std::vector;
using std::string;
using std::for_each;

extern log_t* g_log;

const float vtx_data[] =
{
	0.25f,  0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,

	0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,

	0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,

	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,

	0.25f,  0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,

	0.25f,  0.25f, -1.25f, 1.0f,
	0.25f,  0.25f, -2.75f, 1.0f,
	0.25f, -0.25f, -2.75f, 1.0f,

	0.25f,  0.25f, -2.75f, 1.0f,
	0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,

	0.25f,  0.25f, -2.75f, 1.0f,
	-0.25f,  0.25f, -1.25f, 1.0f,
	-0.25f,  0.25f, -2.75f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,
	0.25f, -0.25f, -1.25f, 1.0f,

	0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -2.75f, 1.0f,
	-0.25f, -0.25f, -1.25f, 1.0f,




	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,
	0.8f, 0.8f, 0.8f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,

	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
};


/******************************************************************************
func:
desc: start the renderer 
 *****************************************************************************/
int rn_t::start( void )
{
	int retv = ERR_OK;
	GLenum gl_err = glewInit();

	/*start glew*/
	if( gl_err != GLEW_OK )
	{
		g_log->w( MSG_FATAL, "error starting glew (%s)\n",
				glewGetErrorString( gl_err ) );
		retv = ERR_GLEW;
		goto out;
	}

	g_log->w( MSG_INFO, "glew version %s started successfully\n",
			glewGetString( GLEW_VERSION ) );

	/*setup the shaders*/
	if( ( retv = load_all_shaders() ) != ERR_OK )
		goto out;

	if( ( retv = create_sh_program() ) != ERR_OK )
		goto out;

	/*initialze shaders*/
	initialize_shaders();

	delete_all_shaders();

	/*initialize the vertex data*/
	init_vtx_b();

	/*set desired gl state*/
	set_gl_state();

out:
	return retv;
}


/******************************************************************************
func:
desc: draw the scene
 *****************************************************************************/
int rn_t::draw( void )
{
	unsigned color_data = sizeof( vtx_data ) / 2;
	static GLfloat offx = 0.0;
	static GLfloat offy = 0.0;

	glClearColor( BG_COLOR );
	glClear( GL_COLOR_BUFFER_BIT );
	glUseProgram( r_sh_program );

	glUniform2f( glGetUniformLocation( r_sh_program, "offset" ), offx, offy );

	glBindBuffer( GL_ARRAY_BUFFER, r_pos_bobj );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer(
			0,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			0 );
	glVertexAttribPointer(
			1,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)color_data );
	glDrawArrays( GL_TRIANGLES, 0, 36 );
	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glUseProgram( 0 );

	offx += 0.03f;
	offy += 0.01f;

	if( offx > 1.0f )
		offx = -1.0f;
	if( offy > 1.0f )
		offy = -1.0f;

	return ERR_OK;
}


/******************************************************************************
func:
desc: 
 *****************************************************************************/
int rn_t::shutdown( void )
{
	/*shut down*/
	glDeleteProgram( r_sh_program );
	return ERR_OK;
}


/******************************************************************************
func:
desc: 
 *****************************************************************************/
int rn_t::load_all_shaders( void )
{
	int retv = ERR_OK;
	GLuint sh_num = 0;
	fs_t f;
	vector<string> files;
	vector<string>::iterator i = files.begin();
	string current_shader = "";

	/*get all vertex the files*/
	f.get_all_files_in_dir( VTX_SHADER_DIR, &files );

	/*compile all the vertex shaders*/
	for( i = files.begin(); i != files.end(); i ++ )
	{
		current_shader = "";
		f.read_file_to_string( *i, &current_shader );
		if( ( retv = compile_shader(
						&sh_num,
						GL_VERTEX_SHADER,
						(char*)current_shader.c_str(),
						*i ) ) != ERR_OK )
			goto out;

		r_shader_list.push_back( sh_num );
	}

	g_log->w( MSG_INFO, "found %u vertex shaders\n", files.size() );

	files.clear();

	/*do the same for the fragment shaders*/
	f.get_all_files_in_dir( FRAG_SHADER_DIR, &files );

	for( i = files.begin(); i != files.end(); i ++ )
	{
		current_shader = "";
		f.read_file_to_string( *i, &current_shader );
		if( ( retv = compile_shader(
						&sh_num,
						GL_FRAGMENT_SHADER,
						(char*)current_shader.c_str(),
						*i ) ) != ERR_OK )
			goto out;

		r_shader_list.push_back( sh_num );
	}

	g_log->w( MSG_INFO, "found %u fragment shaders\n", files.size() );

out:
	return retv;
}


/******************************************************************************
func: compile_shader
desc: compile an individual shader for opengl
 *****************************************************************************/
int rn_t::compile_shader( GLuint* sh_num,
		GLenum sh_type,
		char* sh_file,
		string sh_file_name )
{
	int retv = ERR_OK;
	GLuint shader = glCreateShader( sh_type );
	GLint status = 0;
	GLint log_length = 0;
	GLchar* shader_err_log = NULL;
	assert( sh_num && sh_file && shader );

	/*compile the shader*/
	glShaderSource( shader, 1, (const char**)&sh_file, NULL );
	glCompileShader( shader );

	/*check for errors*/
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
	if( status == GL_FALSE )
	{
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &log_length );
		shader_err_log = new GLchar[log_length + 1];
		glGetShaderInfoLog( shader, log_length, NULL, shader_err_log );

		g_log->w ( MSG_FATAL,
				"error compiling shader %s (",
				sh_file_name.c_str() );

		switch( sh_type )
		{
			case GL_VERTEX_SHADER: g_log->w( "vertex" ); break;
			case GL_GEOMETRY_SHADER: g_log->w( "geometry" ); break;
			case GL_FRAGMENT_SHADER: g_log->w( "fragment" ); break;
			default: g_log->w( "unknown" ); break;
		}

		g_log->w( ")\n\n%s", shader_err_log );
		delete[] shader_err_log;
		shader_err_log = NULL;
		retv = ERR_SHADER_COMPILE;
		goto out;
	}

out:
	*sh_num = shader;
	return retv;
}


/******************************************************************************
func:
desc: 
 *****************************************************************************/
int rn_t::create_sh_program( void )
{
	int retv = ERR_OK;
	GLint glerr = 0;
	GLint glerr_len = 0;
	GLchar* glerr_log = NULL;
	vector<GLuint>::iterator i = r_shader_list.begin();

	r_sh_program = glCreateProgram();

	/*attach all the shaders to the program*/
	while( i != r_shader_list.end() )
	{
		glAttachShader( r_sh_program, *i );
		i++;
	}

	/*link it*/
	glLinkProgram( r_sh_program );

	/*check for errors*/
	glGetProgramiv( r_sh_program, GL_LINK_STATUS, &glerr );
	if( glerr == GL_FALSE )
	{
		glGetProgramiv( r_sh_program, GL_INFO_LOG_LENGTH, &glerr_len );
		glerr_log = new GLchar[glerr_len + 1];
		glGetProgramInfoLog( r_sh_program, glerr_len, NULL, glerr_log );
		g_log->w( "shader linker failure: %s\n", glerr_log );
		delete[] glerr_log;
		glerr_log = NULL;
		retv = ERR_SHADER_LINK;
	}

	/*detach the shaders*/
	for( i = r_shader_list.begin(); i != r_shader_list.end(); i++ )
		glDetachShader( r_sh_program, *i );

	return retv;
}


/******************************************************************************
func:
desc: 
 *****************************************************************************/
int rn_t::delete_all_shaders( void )
{
	for_each( r_shader_list.begin(), r_shader_list.end(), glDeleteShader );
	return ERR_OK;
}


/******************************************************************************
func:
desc: 
 *****************************************************************************/
int rn_t::init_vtx_b( void )
{
	/*bind the buffers to the gfx card*/
	glGenBuffers( 1, &r_pos_bobj );
	glBindBuffer( GL_ARRAY_BUFFER, r_pos_bobj );
	glBufferData(
			GL_ARRAY_BUFFER,
			sizeof(vtx_data),
			vtx_data,
			GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	/*???*/
	glGenVertexArrays( 1, &r_vtx_array_obj );
	glBindVertexArray( r_vtx_array_obj );

	return ERR_OK;
}


/******************************************************************************
func:
desc: update the vertex buffer offsets, move to engine
 *****************************************************************************/
int rn_t::update_offsets( float* x_offset, float* y_offset )
{
	/*	float duration = 5.0f;
		float scale = ( 3.14159f * 2.0f ) / duration;
		float et = (float)( ( clock() * 1000 ) / CLOCKS_PER_SEC );
		float time_index = fmodf( et, duration );

	 *x_offset = cosf( time_index * scale ) * 0.5f;
	 *y_offset = sinf( time_index * scale ) * 0.5f;*/

	return ERR_OK;
}


/******************************************************************************
func: update the vertex data with the new offsets
desc:
 *****************************************************************************/
int rn_t::adj_vtx_data( float x_offset, float y_offset )
{
	/*	int i = 0;

		float vtx_data[] =
		{
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.366f, 0.0f, 1.0f,
		-0.5f, -0.366f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		};

		for( i = 0; i < sizeof(vtx_data) / sizeof(vtx_data[0] ); i += 4 )
		{
		vtx_data[i] += x_offset;
		vtx_data[i+1] += y_offset;
		}

		glBindBuffer( GL_ARRAY_BUFFER, r_pos_bobj );
		glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vtx_data), vtx_data );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );*/

	return ERR_OK;
}


/******************************************************************************
func: setup the gl state machine
desc:
 *****************************************************************************/
int rn_t::set_gl_state( void )
{
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );
	glFrontFace( GL_CW );

	return ERR_OK;
}


/******************************************************************************
func: setup any initial uniforms for the shaders
desc:
 *****************************************************************************/
int rn_t::initialize_shaders( void )
{
	glUseProgram( r_sh_program );
	
	/*assign the shader inputs*/
	glUniform2f( glGetUniformLocation( r_sh_program, "offset" ), 0.5f, 0.5f );
	glUniform1f( glGetUniformLocation( r_sh_program, "f_scale" ), 1.0f );
	glUniform1f( glGetUniformLocation( r_sh_program, "zNear" ), 1.0f );
	glUniform1f( glGetUniformLocation( r_sh_program, "zFar" ), 3.0f );
	glUseProgram( 0 );

	return ERR_OK;
}
