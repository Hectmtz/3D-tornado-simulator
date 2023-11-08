#ifndef BALL_H
#define BALL_H

#pragma once

#include "Ply.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Face.hpp" 
#include "Obj.hpp"
#include <armadillo>

class Ball
 {
    private:
        double pos_x, pos_y, pos_z;
        arma::Mat<double> transf;
        double b_angle;
    public:
        Ball();
        void draw(arma::Mat<double> matrix, double Ia, double Ip, arma::vec F);
        void setBall(double pos_x, double pos_y, double pos_z, double r, double g, double b);
        Ply box_1;
        double getX();
        double getY();
        double getZ();
 };

#endif
