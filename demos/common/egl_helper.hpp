#pragma once

#ifdef __WIN32
 #define EGL_HELPER_DISABLED
#endif

#include <iostream>
#include <SDL.h>
#include <fastuidraw/util/util.hpp>
#include <fastuidraw/util/reference_counted.hpp>
#include <fastuidraw/util/api_callback.hpp>
#include "stream_holder.hpp"

struct wl_egl_window;

class egl_helper:
  public fastuidraw::reference_counted<egl_helper>::non_concurrent
{
public:

  class params
  {
  public:
    params(void):
      m_msaa(0)
    {}

    int m_red_bits, m_green_bits, m_blue_bits, m_alpha_bits;
    int m_depth_bits, m_stencil_bits;

    // 0 means no MSAA, all other values are enabled and number samples
    int m_msaa;

    int m_gles_major_version;
    int m_gles_minor_version;
  };

  egl_helper(const fastuidraw::reference_counted_ptr<StreamHolder> &str,
             const params &P, SDL_Window *w);
  ~egl_helper();

  void
  make_current(void);

  void
  swap_buffers(void);

  static
  void*
  egl_get_proc(fastuidraw::c_string name);

  void
  print_info(std::ostream &dst);

private:
  void *m_ctx;
  void *m_surface;
  void *m_dpy;
  struct wl_egl_window *m_wl_window;
  fastuidraw::reference_counted_ptr<fastuidraw::APICallbackSet::CallBack> m_logger;
};
