/******************************************************************************
file: error.h
desc: error codes
 ******************************************************************************/

#define ERR_OK 0				//no error
#define ERR_GEN 1				//
#define ERR_MEM 2				//out of memory
#define ERR_DISPLAY 3			//xlib couldn't make a display
#define ERR_NO_VISUAL 4			//xlib couldn't get a visual
#define ERR_GLEW 5				//glew couldn't get extensions
#define ERR_SHADER_COMPILE 6	//opengl failed to compile the shader program
#define ERR_SHADER_LINK 7		//opengl failed to link the shader program
#define ERR_OPENING_DIR 8		//filesystem failed to open directory
#define ERR_STAT 9				//filesystem stat() failed
#define ERR_QUIT 10				//user exited
#define ERR_NO_FONT 11			//couldn't find a font requested
#define ERR_WIN_SIZE 12			//window position was invalid

