/* 
 * Copyright (C) 2021 Alyssa Rosenzweig
 * Copyright (C) 2020-2021 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "agx_state.h"
#include "compiler/nir/nir_builder.h"
#include "asahi/compiler/agx_compile.h"

void
agx_build_reload_shader(struct agx_device *dev)
{
   nir_builder b = nir_builder_init_simple_shader(MESA_SHADER_FRAGMENT,
         &agx_nir_options, "agx_reload");
   b.shader->info.internal = true;

   nir_variable *out = nir_variable_create(b.shader, nir_var_shader_out,
         glsl_vector_type(GLSL_TYPE_FLOAT, 4), "output");
   out->data.location = FRAG_RESULT_DATA0;

   nir_ssa_def *fragcoord = nir_load_frag_coord(&b);
   nir_ssa_def *coord = nir_channels(&b, fragcoord, 0x3);

   nir_tex_instr *tex = nir_tex_instr_create(b.shader, 1);
   tex->dest_type = nir_type_float32;
   tex->sampler_dim = GLSL_SAMPLER_DIM_RECT;
   tex->op = nir_texop_tex;
   tex->src[0].src_type = nir_tex_src_coord;
   tex->src[0].src = nir_src_for_ssa(coord);
   tex->coord_components = 2;
   nir_ssa_dest_init(&tex->instr, &tex->dest, 4, 32, NULL);
   nir_builder_instr_insert(&b, &tex->instr);
   nir_store_var(&b, out, &tex->dest.ssa, 0xFF);

   unsigned offset = 0;
   unsigned bo_size = 4096;

   struct agx_bo *bo = agx_bo_create(dev, bo_size, AGX_MEMORY_TYPE_SHADER);
   dev->reload.bo = bo;

   for (unsigned i = 0; i < AGX_NUM_FORMATS; ++i) {
      struct util_dynarray binary;
      util_dynarray_init(&binary, NULL);

      nir_shader *s = nir_shader_clone(NULL, b.shader);
      struct agx_shader_info info;

      struct agx_shader_key key = {
         .fs.tib_formats[0] = i
      };

      agx_compile_shader_nir(s, &key, &binary, &info);

      assert(offset + binary.size < bo_size);
      memcpy(((uint8_t *) bo->ptr.cpu) + offset, binary.data, binary.size);

      dev->reload.format[i] = bo->ptr.gpu + offset;
      offset += ALIGN_POT(binary.size, 128);

      util_dynarray_fini(&binary);
   }
}