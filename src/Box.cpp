#include "../include/Tornado.hpp"
#include "../include/Ply.hpp"
#include "../include/Obj.hpp"
#include "../include/Box.hpp"
#include "../include/Transform.hpp"
#include <armadillo>
#include <GLFW/glfw3.h>

using namespace std;

Box::Box()
{

}

void Box::setBox(double pos_x, double pos_y, double pos_z, double r, double g, double b)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_z = pos_z;
    this->r = r;
    this->g = g;
    this->b = b;
    this->box_1.setObject("models/cube.ply", r, g, b);
    this->b_angle = 0;
    this->box_1.setMaterial(1.5, 2.0);
}

void Box::draw(arma::Mat<double> matrix, double Ia, double Ip, arma::vec F)
{
    Transform tr;
    b_angle = (b_angle < 360.0) ? b_angle + 2.0 : 0.0;
    this->transf = tr.T(-0.9, -0.5, 0.0) * matrix ;

    vector<Face> box_1_faces =  box_1.getFaces();
    
    for (Face f : box_1_faces)
    {
        arma::vec v = f.getEdges()[0].getVi().vec();
        arma::vec L = F - v;
        double dL = sqrt(powf(L[0],2) + powf(L[1],2) + powf(L[2],2));
        L = L / dL;
        double fatt = 1 / powf(dL, 2);

        arma::vec LNormalise = arma::normalise(L);
            //aplicar transformacion a la normal
        arma::Col<double> nhomg = {f.getNormal()[0], f.getNormal()[1], f.getNormal()[2], 1};
        arma::Mat<double> nt = transf * nhomg;
        arma::vec normal_transf = {nt[0]/nt[3], nt[1]/nt[3], nt[2]/nt[3]};
        double light = arma::dot(LNormalise, normal_transf);


        double I = Ia * this->box_1.getKa() + (fatt * Ip * this->box_1.getKd() * light);

        double r = this->box_1.getR() * I;
        double g = this->box_1.getG() * I;
        double b = this->box_1.getB() * I;

        glColor3f(this->r, this->g, this->b);
        glBegin(GL_POLYGON);
        // Recorrer las aristas de la cara
        for (Edge e : f.getEdges())
        {
            // Dibujar la cara....
            arma::Col<double> vp = transf * e.getVi().h();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
        arma::Col<double> vp = transf * f.getEdges().back().getVf().h();
        glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        glEnd();
    }
    
}

double Box::getX()
{
    return (this->pos_x);
}

double Box::getY()
{
    return (this->pos_y);
}

double Box::getZ()
{
    return (this->pos_z);
}
