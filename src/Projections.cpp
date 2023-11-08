#include "../include/Projections.hpp"

Projections::Projections()
{

}

void Projections::mper()
{
    Vertex v1(3, 7, 10);
    Vertex v2(3, 7, 20);

    double d = 5.0;

    arma::Mat<double> Mper = {  {1,0,0,0},
                                {0,1,0,0},
                                {0,0,1,0},
                                {0,0,1/d,0}};

    arma::Mat<double> v1p = Mper * v1.h();
    arma::Mat<double> v2p = Mper * v2.h();

    cout << "(" << v1p(0,0)/v1p(3,0) << ","
         <<v1p(1,0)/v1p(3,0) << ","
         <<v1p(2,0)/v1p(3,0) <<")"<< endl;
    cout<< " "<< endl;
    cout << "(" << v2p(0,0)/v2p(3,0) <<","
    << v2p(1,0)/v2p(3,0) <<","
    << v2p(2,0)/v2p(3,0) <<")"<< endl;
}

void Projections::mperp()
{
    Vertex v1(3, 7, 10);
    Vertex v2(3, 7, 20);

    double d = 8.0;

    arma::Mat<double> Mperp = {  {1,0,0,0},
                                {0,1,0,0},
                                {0,0,0,0},
                                {0,0,1/d,1}};

    arma::Mat<double> v1p = Mperp * v1.h();
    arma::Mat<double> v2p = Mperp * v2.h();

    cout << "(" << v1p(0,0)/v1p(3,0) << ","
         <<v1p(1,0)/v1p(3,0) << ","
         <<v1p(2,0)/v1p(3,0) <<")"<< endl;
    cout<< " "<< endl;
    cout << "(" << v2p(0,0)/v2p(3,0) <<","
    << v2p(1,0)/v2p(3,0) <<","
    << v2p(2,0)/v2p(3,0) <<")"<< endl;
}


void Projections::mort()
{
    Vertex v1(3, 7, 10);
    Vertex v2(3, 7, 20);

    double d = INFINITY;

    arma::Mat<double> Mort = {  {1,0,0,0},
                                {0,1,0,0},
                                {0,0,0,0},
                                {0,0,0,1}};

    arma::Mat<double> v1p = Mort * v1.h();
    arma::Mat<double> v2p = Mort * v2.h();

    cout << "(" << v1p(0,0)/v1p(3,0) << ","
         <<v1p(1,0)/v1p(3,0) << ","
         <<v1p(2,0)/v1p(3,0) <<")"<< endl;
    cout<< " "<< endl;
    cout << "(" << v2p(0,0)/v2p(3,0) <<","
    << v2p(1,0)/v2p(3,0) <<","
    << v2p(2,0)/v2p(3,0) <<")"<< endl;
}

/*arma::<double> Mgeneral(double Zp, double Q, double dx, double dz)
{
    arma::Mat<double> Mg = {    {1,0,-(dx/dz),Zp*(dx/dz)},
                                {0,1,-(dz/dx),Zp*(dz/dx)},
                                {0,0,-Zp(Q*dz),(pow(Zp, 2)/(Q*dz))+Zp},
                                {0,0,-1/(Q*dz), (Zp/(Q*dz))+1}};
    return (Mg);
}*/