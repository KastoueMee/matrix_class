#ifndef TP2_HPP_INCLUDED
#define TP2_HPP_INCLUDED

#include"matricecarree.hpp"
#include <cmath>

matricecarree assemblage_matrice_1(int const& n);
matricecarree assemblage_matrice_2(int const& n);
matricecarree assemblage_matrice_3(int const& n, std::vector<double> const& soleil, std::vector<double> const& temperature);

double fonction_1(double const& x, int const& choix);
double sol_exacte_1(double const& x);

void question1();
void question2();


void application1();
void application2();


#endif