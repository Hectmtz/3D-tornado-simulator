#ifndef FACE_H
#define FACE_H

#pragma once

#include <vector>
#include "Edge.hpp"

using namespace std;


class Face
 {
    private:
        vector<Edge> edges;
        arma::vec normal;
        
    public:
        Face(vector<Edge> edges);
        void print();
        vector<Edge> getEdges();
        bool is_visible(float eye_x, float eye_y, float eye_z, arma::Mat<double> transf);
        void calc_normal();
        arma::vec getNormal();
 };

#endif