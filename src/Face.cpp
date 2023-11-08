#include <iostream>
#include "../include/Edge.hpp"
#include "../include/Face.hpp"

using namespace std;

 Face::Face(vector <Edge> edges)
 {
    this -> edges = edges;
    this->calc_normal();
 }

void Face::print()
{
    cout <<"{";
    for(Edge e: this->edges)
    {
        e.print();
        cout<< ", ";
    }
    cout<<"}";
}

vector<Edge> Face::getEdges()
{
    return this->edges;
    this->calc_normal();
}

void Face::calc_normal()
{
    arma::vec v1 = this->edges[0].getVi().vec();
    arma::vec v2 = this->edges[1].getVi().vec();
    arma::vec v3 = this->edges[2].getVi().vec();
    this->normal = arma::normalise(arma::cross(v2-v1, v3-v1));
}

bool Face::is_visible(float eye_x, float eye_y, float eye_z, arma::Mat<double> transf)
{
    arma::vec dop = {eye_x, eye_y, eye_z};
    arma::vec dop_n = arma::normalise(dop);
    //aplicar transformacion a la normal
    arma::Col<double> nhomg = {this->normal[0], this->normal[1], this->normal[2], 1};
    arma::Mat<double> nt = transf * nhomg;
    arma::vec normal_transf = {nt[0]/nt[3], nt[1]/nt[3], nt[2]/nt[3]};
    double visibiility = arma::dot(dop_n, normal_transf);
    if(visibiility < 0.0)
        {
            return(true);
        }
    return(false);
}

arma::vec Face::getNormal()
{
    return(this->normal);
}