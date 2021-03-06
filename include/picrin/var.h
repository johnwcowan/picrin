/**
 * See Copyright Notice in picrin.h
 */

#ifndef PICRIN_VAR_H__
#define PICRIN_VAR_H__

#if defined(__cplusplus)
extern "C" {
#endif

struct pic_var {
  PIC_OBJECT_HEADER
  pic_value value;
  struct pic_proc *conv;
};

#define pic_var_p(o) (pic_type(o) == PIC_TT_VAR)
#define pic_var_ptr(o) ((struct pic_var *)pic_ptr(o))

struct pic_var *pic_var_new(pic_state *, pic_value, struct pic_proc *);

struct pic_proc *pic_wrap_var(pic_state *, struct pic_var *);
struct pic_var *pic_unwrap_var(pic_state *, struct pic_proc *);

pic_value pic_var_ref(pic_state *, struct pic_var *);
void pic_var_set(pic_state *, struct pic_var *, pic_value);
void pic_var_set_force(pic_state *, struct pic_var *, pic_value);

#if defined(__cplusplus)
}
#endif

#endif
