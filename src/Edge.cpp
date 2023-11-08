#include "../include/Edge.hpp"
#include <iostream>

using namespace std;

Edge::Edge(Vertex vi, Vertex vf)
 {
    this->v1 = vi;
    this->v2 = vf;
 }

void Edge::print()
{
    this->v1.print();
    cout << " - ";
    this->v2.print();
}

Vertex Edge::getVi()
{
    return this->v1;
}

Vertex Edge::getVf()
{
    return this->v2;
}