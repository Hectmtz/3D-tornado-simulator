#ifndef TORNADO_H
#define TORNADO_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Face.hpp" 
#include "Obj.hpp"
#include "Ply.hpp"

class Tornado
 {
    private:
        double pos_x, pos_y, pos_z;
        double t_angle = 0;
        arma::Mat<double> transf;
    public:
        Tornado();
        void setTornado(double pos_x, double pos_y, double pos_z);
        void draw(double Ia, double Ip, arma::vec F);
        arma::Mat<double> trMatrix();
        Obj torn;
 };

#endif