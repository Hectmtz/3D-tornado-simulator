#ifndef PROJECTIONS_H
#define PROJECTIONS_H

#pragma once

#include <iostream>
#include <stdlib.h>
#include <armadillo>
#include "Vertex.hpp"


using namespace std;

class Projections
{
    public:
        Projections();
        void mper();
        void mort();
        void mperp();
        arma::Mat<double> Mgeneral(double zp, double Q, double dx, double dz);
    private:
};

#endif