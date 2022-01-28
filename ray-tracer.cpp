#include <qapplication.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Viewer.h"
#include "Scene.h"
#include "Sphere.h"
#include "Material.h"
#include "PointLight.h"
#include "PeriodicPlane.hpp"

using namespace std;
using namespace rt;

int main(int argc, char **argv) {
    // Read command lines arguments.
    QApplication application(argc, argv);

    // Creates a 3D scene
    Scene scene;

    // Light
    Light *light = new PointLight(GL_LIGHT1, Point4(-10, -4, 2, 1), Color(1.0, 1.0, 1.0));
    scene.addLight(light);

    // Objects
    Sphere *sphere1 = new Sphere(Point3(5, 5, 5), 5.0, Material::whitePlastic());
    Sphere *sphere2 = new Sphere(Point3(0, 0, 2), 2.0, Material::mirror());
    Sphere *sphere3 = new Sphere(Point3(10, 0, 2), 2.0, Material::glass());
    Sphere *sphere4 = new Sphere(Point3(20, 5, 5), 5.0, Material::redPlastic());
    Sphere *sphere5 = new Sphere(Point3(5, 20, 5), 5.0, Material::bronze());
    Sphere *sphere6 = new Sphere(Point3(20, 20, 5), 5.0, Material::emerald());

    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addObject(sphere4);
    scene.addObject(sphere5);
    scene.addObject(sphere6);

    PeriodicPlane *plane = new PeriodicPlane(Point3(0, 0, 0), Vector3(5, 0, 0), Vector3(0, 5, 0),
                                             Material::redPlastic(), Material::emerald(), 0.05f);
    scene.addObject(plane);

    // Instantiate the viewer.
    Viewer viewer;

    // Give a name
    viewer.setWindowTitle("Ray-tracer preview");

    // Sets the scene
    viewer.setScene(scene);

    // Make the viewer window visible on screen.
    viewer.show();
    // Run main loop.
    application.exec();

    return 0;
}
