#ifndef PERIODIC_PLANE_HPP
#define PERIODIC_PLANE_HPP

#include "./GraphicalObject.h"

namespace rt {

    struct PeriodicPlane : public GraphicalObject {
        Point3 c;
        Vector3 u, v;
        Material band_m, main_m;
        Real w;

        /// Creates a periodic infinite plane passing through c and
        /// tangent to u and v. Then w defines the width of the
        /// band around (0,0) and its period to put material band_m,
        /// otherwise main_m is used.
        PeriodicPlane(Point3 c, Vector3 u, Vector3 v, Material main_m, Material band_m, Real w)
                : c(c), u(u), v(v), main_m(main_m), band_m(band_m), w(w) {};

        /// Etant donné un point p dans le plan, retourne ses coordonnées x et y selon u et v.
        void coordinates(Point3 p, Real &x, Real &y) {
            x = u[0] + v[0] + p[0];
            y = u[1] + v[1] + p[1];
        }

        void init(Viewer & /* viewer */) {}

        void draw(Viewer &viewer) override {
            // Création d'un rectangle avec 2 triangles

            glBegin(GL_TRIANGLES);
            glColor4fv(main_m.ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, main_m.diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, main_m.specular);
            glMaterialf(GL_FRONT, GL_SHININESS, main_m.shinyness);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 1000, 0);
            glVertex3f(1000, 0, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
            glColor4fv(main_m.ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, main_m.diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, main_m.specular);
            glMaterialf(GL_FRONT, GL_SHININESS, main_m.shinyness);
            glVertex3f(1000, 1000, 0);
            glVertex3f(0, 1000, 0);
            glVertex3f(1000, 0, 0);
            glEnd();
        }

        Vector3 getNormal(Point3 p) {
            return p + u.cross(v);
        }

        Material getMaterial(Point3 p) {
            Real x, y;
            coordinates(p, x, y);
            int x_rounded = (int) x;
            int y_rounded = (int) y;
            Real x_diff = x - x_rounded;
            Real y_diff = y - y_rounded;
            if (x_diff < 0) x_diff *= -1.0f;
            if (y_diff < 0) y_diff *= -1.0f;
            return x_diff < w || y_diff < w ? band_m : main_m;
        }

        Real rayIntersection(const Ray &ray, Point3 &p) {
            Real t;
            Vector3 N = this->getNormal(c) / this->getNormal(c).norm();
            Vector3 W = ray.direction / ray.direction.norm();
            Real wn = W.dot(N);
            Vector3 n0w0 = c - ray.origin;

            if (wn == 0.0f) {
                if (N.dot(n0w0) == 0) {
                    t = 0;
                    p = ray.origin + W * t;
                    return -1.0f;
                } else {
                    return 1.0f;
                }
            } else {
                t = N.dot(n0w0) / wn;
                p = ray.origin + W * t;
            }
            return t >= 0 ? -1.0f : 1.0f;
        }
    };
}

#endif