#ifndef PLY_H
#define PLY_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Face.hpp" 
#include <fstream>
#include <sstream>
#include "Models.hpp"

using namespace std;

class Ply : public Models
{
    private:
        int numVertex;
        int numFaces;
        int contVertex;
        void load();
    public:
        Ply();
        void setObject(string file, double r, double g, double b);
};

#endif