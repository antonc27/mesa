/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2008  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef FBOBJECT_H
#define FBOBJECT_H

#include "glheader.h"
#include <stdbool.h>

struct gl_context;
struct gl_texture_object;


/**
 * Is the given FBO a user-created FBO?
 */
static inline GLboolean
_mesa_is_user_fbo(const struct gl_framebuffer *fb)
{
   return fb->Name != 0;
}


/**
 * Is the given FBO a window system FBO (like an X window)?
 */
static inline GLboolean
_mesa_is_winsys_fbo(const struct gl_framebuffer *fb)
{
   return fb->Name == 0;
}



extern struct gl_framebuffer *
_mesa_get_incomplete_framebuffer(void);

extern struct gl_renderbuffer *
_mesa_lookup_renderbuffer(struct gl_context *ctx, GLuint id);

extern struct gl_renderbuffer *
_mesa_lookup_renderbuffer_err(struct gl_context *ctx, GLuint id,
                              const char *func);

extern struct gl_framebuffer *
_mesa_lookup_framebuffer(struct gl_context *ctx, GLuint id);

extern struct gl_framebuffer *
_mesa_lookup_framebuffer_err(struct gl_context *ctx, GLuint id,
                             const char *func);

struct gl_framebuffer *
_mesa_lookup_framebuffer_dsa(struct gl_context *ctx, GLuint id,
                             const char* func);


void
_mesa_update_texture_renderbuffer(struct gl_context *ctx,
                                  struct gl_framebuffer *fb,
                                  struct gl_renderbuffer_attachment *att);

extern void
_mesa_framebuffer_renderbuffer(struct gl_context *ctx,
                               struct gl_framebuffer *fb,
                               GLenum attachment,
                               struct gl_renderbuffer *rb);

extern void
_mesa_renderbuffer_storage(struct gl_context *ctx, struct gl_renderbuffer *rb,
                           GLenum internalFormat, GLsizei width,
                           GLsizei height, GLsizei samples,
                           GLsizei storageSamples);

extern void
_mesa_validate_framebuffer(struct gl_context *ctx, struct gl_framebuffer *fb);

extern GLboolean
_mesa_has_depthstencil_combined(const struct gl_framebuffer *fb);

extern void
_mesa_test_framebuffer_completeness(struct gl_context *ctx,
                                    struct gl_framebuffer *fb);

extern GLboolean
_mesa_is_legal_color_format(const struct gl_context *ctx, GLenum baseFormat);

extern GLenum
_mesa_base_fbo_format(const struct gl_context *ctx, GLenum internalFormat);

extern bool
_mesa_detach_renderbuffer(struct gl_context *ctx,
                          struct gl_framebuffer *fb,
                          const void *att);

extern struct gl_renderbuffer_attachment *
_mesa_get_and_validate_attachment(struct gl_context *ctx,
                                  struct gl_framebuffer *fb,
                                  GLenum attachment, const char *caller);

extern void
_mesa_framebuffer_texture(struct gl_context *ctx, struct gl_framebuffer *fb,
                          GLenum attachment,
                          struct gl_renderbuffer_attachment *att,
                          struct gl_texture_object *texObj, GLenum textarget,
                          GLint level, GLsizei samples,
                          GLuint layer, GLboolean layered);

extern GLenum
_mesa_check_framebuffer_status(struct gl_context *ctx,
                               struct gl_framebuffer *fb);

extern void
_mesa_bind_framebuffers(struct gl_context *ctx,
                        struct gl_framebuffer *newDrawFb,
                        struct gl_framebuffer *newReadFb);

extern GLboolean GLAPIENTRY
_mesa_IsRenderbuffer(GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_BindRenderbuffer(GLenum target, GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_BindRenderbufferEXT(GLenum target, GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_DeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers);

void GLAPIENTRY
_mesa_GenRenderbuffers_no_error(GLsizei n, GLuint *renderbuffers);

extern void GLAPIENTRY
_mesa_GenRenderbuffers(GLsizei n, GLuint *renderbuffers);

void GLAPIENTRY
_mesa_CreateRenderbuffers_no_error(GLsizei n, GLuint *renderbuffers);

extern void GLAPIENTRY
_mesa_CreateRenderbuffers(GLsizei n, GLuint *renderbuffers);

extern void GLAPIENTRY
_mesa_RenderbufferStorage(GLenum target, GLenum internalformat,
                             GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_RenderbufferStorageMultisample(GLenum target, GLsizei samples,
                                     GLenum internalformat,
                                     GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_RenderbufferStorageMultisampleAdvancedAMD(
      GLenum target, GLsizei samples, GLsizei storageSamples,
      GLenum internalFormat, GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat,
                               GLsizei width, GLsizei height);
extern void GLAPIENTRY
_mesa_NamedRenderbufferStorageEXT(GLuint renderbuffer, GLenum internalformat,
                                  GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples,
                                          GLenum internalformat,
                                          GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_NamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer, GLsizei samples,
                                             GLenum internalformat,
                                             GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_NamedRenderbufferStorageMultisampleAdvancedAMD(
      GLuint renderbuffer, GLsizei samples, GLsizei storageSamples,
      GLenum internalformat, GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_EGLImageTargetRenderbufferStorageOES(GLenum target, GLeglImageOES image);

extern void GLAPIENTRY
_mesa_GetRenderbufferParameteriv(GLenum target, GLenum pname,
                                    GLint *params);

void GLAPIENTRY
_mesa_GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname,
                                      GLint *params);

extern GLboolean GLAPIENTRY
_mesa_IsFramebuffer(GLuint framebuffer);

extern void GLAPIENTRY
_mesa_BindFramebuffer(GLenum target, GLuint framebuffer);

extern void GLAPIENTRY
_mesa_BindFramebufferEXT(GLenum target, GLuint framebuffer);

extern void GLAPIENTRY
_mesa_DeleteFramebuffers(GLsizei n, const GLuint *framebuffers);

extern void GLAPIENTRY
_mesa_GenFramebuffers(GLsizei n, GLuint *framebuffers);

extern void GLAPIENTRY
_mesa_CreateFramebuffers(GLsizei n, GLuint *framebuffers);

GLenum GLAPIENTRY
_mesa_CheckFramebufferStatus_no_error(GLenum target);

extern GLenum GLAPIENTRY
_mesa_CheckFramebufferStatus(GLenum target);

extern GLenum GLAPIENTRY
_mesa_CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target);

extern GLenum GLAPIENTRY
_mesa_CheckNamedFramebufferStatusEXT(GLuint framebuffer, GLenum target);

extern void GLAPIENTRY
_mesa_FramebufferTexture1D_no_error(GLenum target, GLenum attachment,
                                    GLenum textarget, GLuint texture,
                                    GLint level);
extern void GLAPIENTRY
_mesa_FramebufferTexture1D(GLenum target, GLenum attachment,
                              GLenum textarget, GLuint texture, GLint level);

extern void GLAPIENTRY
_mesa_FramebufferTexture2D_no_error(GLenum target, GLenum attachment,
                                    GLenum textarget, GLuint texture,
                                    GLint level);
extern void GLAPIENTRY
_mesa_FramebufferTexture2D(GLenum target, GLenum attachment,
                              GLenum textarget, GLuint texture, GLint level);

void GLAPIENTRY
_mesa_FramebufferTexture2DMultisampleEXT(GLenum target, GLenum attachment,
                                         GLenum textarget, GLuint texture,
                                         GLint level, GLsizei samples);

extern void GLAPIENTRY
_mesa_FramebufferTexture3D_no_error(GLenum target, GLenum attachment,
                                    GLenum textarget, GLuint texture,
                                    GLint level, GLint layer);
extern void GLAPIENTRY
_mesa_FramebufferTexture3D(GLenum target, GLenum attachment,
                              GLenum textarget, GLuint texture,
                              GLint level, GLint layer);

extern void GLAPIENTRY
_mesa_FramebufferTextureLayer_no_error(GLenum target, GLenum attachment,
                                       GLuint texture, GLint level,
                                       GLint layer);
extern void GLAPIENTRY
_mesa_FramebufferTextureLayer(GLenum target, GLenum attachment,
                                 GLuint texture, GLint level, GLint layer);

extern void GLAPIENTRY
_mesa_NamedFramebufferTextureLayer_no_error(GLuint framebuffer,
                                            GLenum attachment,
                                            GLuint texture, GLint level,
                                            GLint layer);
extern void GLAPIENTRY
_mesa_NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment,
                                   GLuint texture, GLint level, GLint layer);

extern void GLAPIENTRY
_mesa_FramebufferTexture_no_error(GLenum target, GLenum attachment,
                                  GLuint texture, GLint level);
extern void GLAPIENTRY
_mesa_FramebufferTexture(GLenum target, GLenum attachment,
                         GLuint texture, GLint level);

extern void GLAPIENTRY
_mesa_NamedFramebufferTexture_no_error(GLuint framebuffer, GLenum attachment,
                                       GLuint texture, GLint level);
extern void GLAPIENTRY
_mesa_NamedFramebufferTexture(GLuint framebuffer, GLenum attachment,
                              GLuint texture, GLint level);

extern void GLAPIENTRY
_mesa_NamedFramebufferRenderbufferEXT(GLuint framebuffer, GLenum attachment,
                                      GLenum renderbuffertarget,
                                      GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_NamedFramebufferTexture1DEXT(GLuint framebuffer, GLenum attachment,
                                   GLenum textarget, GLuint texture, GLint level);

extern void GLAPIENTRY
_mesa_NamedFramebufferTexture2DEXT(GLuint framebuffer, GLenum attachment,
                                   GLenum textarget, GLuint texture, GLint level);

extern void GLAPIENTRY
_mesa_NamedFramebufferTexture3DEXT(GLuint framebuffer, GLenum attachment,
                                   GLenum textarget, GLuint texture,
                                   GLint level, GLint zoffset);

void GLAPIENTRY
_mesa_FramebufferRenderbuffer_no_error(GLenum target, GLenum attachment,
                                       GLenum renderbuffertarget,
                                       GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_FramebufferRenderbuffer(GLenum target, GLenum attachment,
                                 GLenum renderbuffertarget,
                                 GLuint renderbuffer);

void GLAPIENTRY
_mesa_NamedFramebufferRenderbuffer_no_error(GLuint framebuffer,
                                            GLenum attachment,
                                            GLenum renderbuffertarget,
                                            GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment,
                                   GLenum renderbuffertarget,
                                   GLuint renderbuffer);

extern void GLAPIENTRY
_mesa_GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment,
                                          GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer,
                                               GLenum attachment,
                                               GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer,
                                                  GLenum attachment,
                                                  GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_NamedFramebufferParameteri(GLuint framebuffer, GLenum pname,
                                 GLint param);

extern void GLAPIENTRY
_mesa_NamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname,
                                    GLint param);

extern void GLAPIENTRY
_mesa_GetNamedRenderbufferParameterivEXT(GLuint renderbuffer, GLenum pname,
                                         GLint *params);

extern void GLAPIENTRY
_mesa_GetFramebufferParameterivEXT(GLuint framebuffer, GLenum pname,
                                   GLint *param);

extern void GLAPIENTRY
_mesa_GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname,
                                     GLint *param);

extern void GLAPIENTRY
_mesa_GetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname,
                                        GLint *param);

void GLAPIENTRY
_mesa_InvalidateSubFramebuffer_no_error(GLenum target, GLsizei numAttachments,
                                        const GLenum *attachments, GLint x,
                                        GLint y, GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments,
                               const GLenum *attachments, GLint x, GLint y,
                               GLsizei width, GLsizei height);

extern void GLAPIENTRY
_mesa_InvalidateNamedFramebufferSubData(GLuint framebuffer,
                                        GLsizei numAttachments,
                                        const GLenum *attachments,
                                        GLint x, GLint y,
                                        GLsizei width, GLsizei height);
void GLAPIENTRY
_mesa_InvalidateFramebuffer_no_error(GLenum target, GLsizei numAttachments,
                                     const GLenum *attachments);

extern void GLAPIENTRY
_mesa_InvalidateFramebuffer(GLenum target, GLsizei numAttachments,
                            const GLenum *attachments);

extern void GLAPIENTRY
_mesa_InvalidateNamedFramebufferData(GLuint framebuffer,
                                     GLsizei numAttachments,
                                     const GLenum *attachments);

extern void GLAPIENTRY
_mesa_DiscardFramebufferEXT(GLenum target, GLsizei numAttachments,
                            const GLenum *attachments);

extern void GLAPIENTRY
_mesa_FramebufferParameteri(GLenum target, GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_FramebufferParameteriMESA(GLenum target, GLenum pname, GLint param);

extern void GLAPIENTRY
_mesa_GetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_GetFramebufferParameterivMESA(GLenum target, GLenum pname, GLint *params);

extern void GLAPIENTRY
_mesa_FramebufferSampleLocationsfvARB(GLenum target, GLuint start,
                                      GLsizei count, const GLfloat *v);

extern void GLAPIENTRY
_mesa_NamedFramebufferSampleLocationsfvARB(GLuint framebuffer, GLuint start,
                                           GLsizei count, const GLfloat *v);

extern void GLAPIENTRY
_mesa_FramebufferSampleLocationsfvARB_no_error(GLenum target, GLuint start,
                                               GLsizei count, const GLfloat *v);

extern void GLAPIENTRY
_mesa_NamedFramebufferSampleLocationsfvARB_no_error(GLuint framebuffer,
                                                    GLuint start, GLsizei count,
                                                    const GLfloat *v);

extern void GLAPIENTRY
_mesa_EvaluateDepthValuesARB(void);

#endif /* FBOBJECT_H */
