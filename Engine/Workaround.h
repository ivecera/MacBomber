/*MacBomber - Copyright (C) 2006  Altay Cebe

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/* ARB_multitexture defines and prototypes from <GL/gl.h> */
#ifndef GL_ARB_MULTITEXTURE
extern "C" {
#define GL_ARB_MULTITEXTURE 1
#define GL_ACTIVE_TEXTURE_ARB 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE_ARB 0x84E1
#define GL_MAX_TEXTURE_UNITS_ARB 0x84E2
#define GL_TEXTURE0_ARB 0x84C0
#define GL_TEXTURE1_ARB 0x84C1
#define GL_TEXTURE2_ARB 0x84C2
#define GL_TEXTURE3_ARB 0x84C3
}
#endif //GL_ARB_MULTITEXTURE

// ARB_vertex_buffer_object
#ifndef GL_ARB_vertex_buffer_object
extern "C" {
#include <stdint.h>

typedef intptr_t GLintptrARB;
typedef uintptr_t GLsizeiptrARB;

extern void glBindBufferARB(GLenum target, GLuint buffer);
extern void glDeleteBuffersARB(GLsizei n, const GLuint *buffers);
extern void glGenBuffersARB(GLsizei n, GLuint *buffers);
extern GLboolean glIsBufferARB(GLuint buffer);

extern void glBufferDataARB(GLenum target, GLsizeiptrARB size,
			    const GLvoid *data, GLenum usage);
extern void glBufferSubDataARB(GLenum target, GLintptrARB offset,
			       GLsizeiptrARB size, const GLvoid *data);
extern void glGetBufferSubDataARB(GLenum target, GLintptrARB offset,
				  GLsizeiptrARB size, GLvoid *data);

extern void *glMapBufferARB(GLenum target, GLenum access);
extern GLboolean glUnmapBufferARB(GLenum target);

extern void glGetBufferParameterivARB(GLenum target, GLenum pname,
				      GLint *params);
extern void glGetBufferPointervARB(GLenum target, GLenum pname,
				   GLvoid **params);

#define GL_ARRAY_BUFFER_ARB 0x8892
#define GL_ELEMENT_ARRAY_BUFFER_ARB 0x8893

#define GL_ARRAY_BUFFER_BINDING_ARB 0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB 0x8895
#define GL_VERTEX_ARRAY_BUFFER_BINDING_ARB 0x8896
#define GL_NORMAL_ARRAY_BUFFER_BINDING_ARB 0x8897
#define GL_COLOR_ARRAY_BUFFER_BINDING_ARB 0x8898
#define GL_INDEX_ARRAY_BUFFER_BINDING_ARB 0x8899
#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB 0x889A
#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB 0x889B
#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB 0x889C
#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB 0x889D
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB 0x889E

#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB 0x889F

#define GL_STREAM_DRAW_ARB 0x88E0
#define GL_STREAM_READ_ARB 0x88E1
#define GL_STREAM_COPY_ARB 0x88E2
#define GL_STATIC_DRAW_ARB 0x88E4
#define GL_STATIC_READ_ARB 0x88E5
#define GL_STATIC_COPY_ARB 0x88E6
#define GL_DYNAMIC_DRAW_ARB 0x88E8
#define GL_DYNAMIC_READ_ARB 0x88E9
#define GL_DYNAMIC_COPY_ARB 0x88EA

#define GL_READ_ONLY_ARB 0x88B8
#define GL_WRITE_ONLY_ARB 0x88B9
#define GL_READ_WRITE_ARB 0x88BA

#define GL_BUFFER_SIZE_ARB 0x8764
#define GL_BUFFER_USAGE_ARB 0x8765
#define GL_BUFFER_ACCESS_ARB 0x88BB
#define GL_BUFFER_MAPPED_ARB 0x88BC

#define GL_BUFFER_MAP_POINTER_ARB 0x88BD
}
#endif // ARB_vertex_buffer_objects