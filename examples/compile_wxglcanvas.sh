#!/bin/bash

g++ wxglcanvas.cpp -o wxglcanvas `wx-config --cflags --libs` `pkg-config --cflags --libs gtk+-3.0 wayland-client wayland-egl egl glesv1_cm` -lwx_gtk3u_gl-2.9 libEGLX.so -DHAVE_JWZGLES -DGL_VERSION_ES_CM_1_0 -ljwzgles.so 
