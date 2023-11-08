#include "../include/Vertex.hpp"
#include <iostream>

using namespace std;

 Vertex::Vertex(double x, double y, double z)
 {
    this -> x = x;
    this -> y = y;
    this -> z = z;
 }

Vertex Vertex ::operator+(Vertex op)
{
   return Vertex(this->x + op.x, this->y + op.y, this->z + op.z);
}

Vertex Vertex ::operator-(Vertex op)
{
   return Vertex(this->x - op.x, this->y - op.y, this->z - op.z);
}

Vertex Vertex ::operator*(double op)
{
   return Vertex(this->x * op, this->y * op, this->z * op);
}

arma::Col<double> Vertex::h()
{
   arma::Col<double> homg = {this->x, this->y, this->z, 1};
   return (homg);
}

double Vertex::getX()
{
   return this->x;
}

double Vertex::getY()
{
   return this->y;
}

double Vertex::getZ()
{
   return this->z;
}
 void Vertex::print()
{
   cout <<"(" << this -> x
   <<", " << this -> y <<
   ", " << this -> z << ")";
}

void Vertex::setVertex(double x, double y, double z)
{
   this->x = x;
   this->y = y;
   this->z = z;
}

arma::vec Vertex::vec()
{
   arma::vec v = {this->x, this->y, this->z};
   return (v);
}
