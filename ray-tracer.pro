TEMPLATE = app

TARGET  = ray-tracer

CONFIG *= qt opengl release
CONFIG += c++11

QT     *= opengl xml
QMAKE_CXXFLAGS += -std=c++11

HEADERS = Viewer.h PointVector.h Color.h Sphere.h GraphicalObject.h Light.h \
          Material.h PointLight.h Image2D.h Image2DWriter.h Renderer.h Ray.h \
          Background.h CustomBackground.h PeriodicPlane.hpp
          
SOURCES = Viewer.cpp ray-tracer.cpp Sphere.cpp

#INCLUDEPATH *= /usr/include
LIBS *= -L/usr/lib/x86_64-linux-gnu -lQGLViewer-qt5
