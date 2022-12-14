#ifndef MATRICECARREE_HPP_INCLUDED
#define MATRICECARREE_HPP_INCLUDED

#include"utils_vecteur_matrice.hpp"
#include"matrix.hpp"
#include<cassert>
#include<cmath> // sqrt()

class matricecarree : public matrice
{
public:
    matricecarree(int n) : matrice(n, n) {};

    matricecarree transpose();
    matricecarree operator*(const double&);

    matricecarree chol();
    matricecarree lu(std::vector<int>& piv);
    std::vector<double> solvelu(std::vector<double> const& b, std::vector<int>& piv);

    std::vector<double> forward(std::vector<double> const& b);
    std::vector<double> backward(std::vector<double> const& b);
    std::vector<double> solvechol(std::vector<double> const& b);
};

#endif