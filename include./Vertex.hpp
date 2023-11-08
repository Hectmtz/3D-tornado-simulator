#ifndef VERTEX_H
#define VERTEX_H

#pragma once

#include <armadillo>

class Vertex
{
    private:
        double x, y, z;
    public:
        Vertex(){};
        Vertex(double x, double y, double z);
        Vertex operator+(Vertex op);
        Vertex operator-(Vertex op);
        Vertex operator*(double op);
        arma::Col<double> h();
        void print();
        double getX();
        double getY();
        double getZ();
        void setVertex(double x, double y, double z);
        arma::vec vec();
};
 

#endif