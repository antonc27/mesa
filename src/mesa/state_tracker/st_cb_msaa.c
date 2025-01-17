/**************************************************************************
 *
 * Copyright 2013 Red Hat
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#include "main/bufferobj.h"

#include "main/framebuffer.h"

#include "state_tracker/st_cb_msaa.h"
#include "state_tracker/st_context.h"
#include "state_tracker/st_atom.h"
#include "state_tracker/st_cb_fbo.h"

#include "pipe/p_context.h"


void
st_GetSamplePosition(struct gl_context *ctx,
                     struct gl_framebuffer *fb,
                     GLuint index,
                     GLfloat *outPos)
{
   struct st_context *st = st_context(ctx);

   st_validate_state(st, ST_PIPELINE_UPDATE_FRAMEBUFFER);

   if (st->pipe->get_sample_position)
      st->pipe->get_sample_position(st->pipe,
                                    _mesa_geometric_samples(fb),
                                    index, outPos);
   else
      outPos[0] = outPos[1] = 0.5f;
}


void
st_GetProgrammableSampleCaps(struct gl_context *ctx, const struct gl_framebuffer *fb,
                             GLuint *outBits, GLuint *outWidth, GLuint *outHeight)
{
   struct st_context *st = st_context(ctx);
   struct pipe_screen *screen = st->screen;

   st_validate_state(st, ST_PIPELINE_UPDATE_FRAMEBUFFER);

   *outBits = 4;
   *outWidth = 1;
   *outHeight = 1;

   if (ctx->Extensions.ARB_sample_locations)
      screen->get_sample_pixel_grid(screen, st->state.fb_num_samples,
                                    outWidth, outHeight);

   /* We could handle this better in some circumstances,
    * but it's not really an issue */
   if (*outWidth > MAX_SAMPLE_LOCATION_GRID_SIZE ||
       *outHeight > MAX_SAMPLE_LOCATION_GRID_SIZE) {
      *outWidth = 1;
      *outHeight = 1;
   }
}
