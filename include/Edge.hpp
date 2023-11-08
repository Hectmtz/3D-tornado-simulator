#ifndef EDGE_H
#define EDGE_H

#pragma once

#include "Vertex.hpp"

class Edge
 {
    private:
        Vertex v1, v2;
    public:
        Edge(Vertex vi, Vertex vf);
        void print();
        Vertex getVi();
        Vertex getVf();
 };

#endif