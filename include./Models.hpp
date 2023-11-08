#ifndef MODELS_H
#define MODELS_H

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "Face.hpp" 
#include <fstream>
#include <sstream>
#include "Transform.hpp"

using namespace std;


class Models
 {
    private:
        
    public:
        vector<Vertex> bezier(Vertex p1, Vertex p2, Vertex p3, Vertex p4, double dt);
        void hermite(Vertex p1, Vertex p4, Vertex r1, Vertex r4, double dt);
        void lines(Vertex vi, Vertex vf, double dt);
        vector<Face> getFaces();
        vector<Edge> getEdges();
        virtual void load() = 0;
        virtual void setObject(string file, double r, double g, double b) = 0;
        void setMaterial(double ka, double kd);
        double getR();
        double getG();
        double getB();
        double getMaterial();
        double getKd();
        double getKa();
    protected:
        vector<Vertex> vertices;
        vector<Face> faces;
        vector<Edge> edges;
        string file;
        vector<string> split(const string& str, const string& delim);
        double r, g, b;
        double ka;
        double kd;
 };

#endif