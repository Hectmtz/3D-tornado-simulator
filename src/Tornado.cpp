#include "../include/Tornado.hpp"
#include "../include/Ply.hpp"
#include "../include/Obj.hpp"
#include "../include/Transform.hpp"
#include <armadillo>
#include <GLFW/glfw3.h>

Tornado::Tornado()
{
    
}

void Tornado::setTornado(double pos_x, double pos_y, double pos_z)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->pos_z = pos_z;
    this->torn.setObject("models/tornado2.obj", 0.5, 0.5, 0.5);
    this->torn.setMaterial(1.0, 0.9);
}

void Tornado::draw(double Ia, double Ip, arma::vec F)
{
    Transform tr;

    this->t_angle = (this->t_angle < 360.0) ? this->t_angle + 1.5 : 0.0;
    transf = tr.Ry(this->t_angle) * tr.T(-0.35, 0.0, 0.0) * tr.S(0.4, 0.4, 0.4) ;

    vector<Face> torn_faces = torn.getFaces();

    
    
    for (Face f : torn_faces)
    {
        //f.calc_normal();
        if(f.is_visible(0.0, 1.0, 0.0, transf))
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


            double I = Ia * this->torn.getKa() + (fatt * Ip * this->torn.getKd() * light);

            double r = this->torn.getR() * I;
            double g = this->torn.getG() * I;
            double b = this->torn.getB() * I;

            glColor3f(r, g, b);
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
    
}

arma::Mat<double> Tornado::trMatrix()
{
    return this->transf;
}