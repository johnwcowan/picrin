/**
 * See Copyright Notice in picrin.h
 */

#include <stdio.h>

#include "picrin.h"
#include "picrin/port.h"
#include "xfile/xfile.h"

static pic_value
generic_open_file(pic_state *pic, const char *fname, char *mode, short flags)
{
  struct pic_port *port;
  XFILE *file;

  file = xfopen(fname, mode);
  if (! file) {
    pic_error(pic, "could not open file");
  }

  port = (struct pic_port *)pic_obj_alloc(pic, sizeof(struct pic_port), PIC_TT_PORT);
  port->file = file;
  port->flags = flags;
  port->status = PIC_PORT_OPEN;

  return pic_obj_value(port);
}

pic_value
pic_file_open_input_file(pic_state *pic)
{
  static const short flags = PIC_PORT_IN | PIC_PORT_TEXT;
  char *fname;
  size_t size;

  pic_get_args(pic, "s", &fname, &size);

  return generic_open_file(pic, fname, "r", flags);
}

pic_value
pic_file_open_input_binary_file(pic_state *pic)
{
  static const short flags = PIC_PORT_IN | PIC_PORT_BINARY;
  char *fname;
  size_t size;

  pic_get_args(pic, "s", &fname, &size);

  return generic_open_file(pic, fname, "rb", flags);
}

pic_value
pic_file_open_output_file(pic_state *pic)
{
  static const short flags = PIC_PORT_OUT | PIC_PORT_TEXT;
  char *fname;
  size_t size;

  pic_get_args(pic, "s", &fname, &size);

  return generic_open_file(pic, fname, "w", flags);
}

pic_value
pic_file_open_output_binary_file(pic_state *pic)
{
  static const short flags = PIC_PORT_OUT | PIC_PORT_BINARY;
  char *fname;
  size_t size;

  pic_get_args(pic, "s", &fname, &size);

  return generic_open_file(pic, fname, "wb", flags);
}

pic_value
pic_file_exists_p(pic_state *pic)
{
  char *fname;
  size_t size;
  FILE *fp;

  pic_get_args(pic, "s", &fname, &size);

  fp = fopen(fname, "r");
  if (fp) {
    fclose(fp);
    return pic_true_value();
  } else {
    return pic_false_value();
  }
}

pic_value
pic_file_delete(pic_state *pic)
{
  char *fname;
  size_t size;

  pic_get_args(pic, "s", &fname, &size);

  if (remove(fname) != 0) {
    pic_error(pic, "file cannot be deleted");
  }
  return pic_none_value();
}

void
pic_init_file(pic_state *pic)
{
  pic_deflibrary ("(scheme file)") {
    pic_defun(pic, "open-input-file", pic_file_open_input_file);
    pic_defun(pic, "open-input-binary-file", pic_file_open_input_binary_file);
    pic_defun(pic, "open-output-file", pic_file_open_output_file);
    pic_defun(pic, "open-output-binary-file", pic_file_open_output_binary_file);
    pic_defun(pic, "file-exists?", pic_file_exists_p);
    pic_defun(pic, "delete-file", pic_file_delete);
  }
}
