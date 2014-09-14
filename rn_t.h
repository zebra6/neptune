/******************************************************************************
file: rn_t.h
desc: 
 *****************************************************************************/
#pragma once

#include <GL/glew.h>		//extension enumerator (has to be here for link)
#include <GL/gl.h>			//gl types
#include <vector>			//stl vector
#include <string>

#define BG_COLOR 0.0f, 0.0f, 0.0f, 0.0f
#define VTX_SHADER_DIR "shader/vertex/"
#define FRAG_SHADER_DIR "shader/fragment/"

using std::vector;
using std::string;

class rn_t
{
	public:
		/*functions*/
		rn_t( void ) {};
		~rn_t( void ) {};

		int start( void );
		int draw( void );
		int shutdown( void );

		int update_offsets( float* x_offset, float* y_offset );
		int adj_vtx_data( float x_offset, float y_offset );

	private:
		/*functions*/
		int load_all_shaders( void );
		int compile_shader( GLuint* sh_num,
				GLenum sh_type,
				char* sh_file,
				string sh_file_name );
		int create_sh_program( void );
		int delete_all_shaders( void );
		int init_vtx_b( void );
		int set_gl_state( void );

		/*attribs*/
		vector<GLuint> r_shader_list;
		GLuint r_sh_program;

		GLuint r_pos_bobj;
		GLuint r_vtx_array_obj;
};


