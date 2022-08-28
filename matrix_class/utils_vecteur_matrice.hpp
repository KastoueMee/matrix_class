#ifndef UTILS_VECTEUR_MATRICE_HPP_INCLUDED
#define UTILS_VECTEUR_MATRICE_HPP_INCLUDED  

#include<iostream>
#include<vector>
#include<string>

template <typename T>
std::istream& operator>>(std::istream& os, std::vector<T>& vecteur);
template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vecteur);

template <typename T>
std::vector<T> operator*(T const& lambda, std::vector<T> const& a);
template <typename T>
std::vector<T> operator+(std::vector<T> const& a, std::vector<T> const& b);
template <typename T>
std::vector<T> operator-(std::vector<T> const& a, std::vector<T> const& b);
template <typename T>
T operator*(std::vector<T> const& a, std::vector<T> const& b);



template <typename T>
T norme_infinie(std::vector<T> const& a);
template <typename T>
T norme_l1(std::vector<T> const& a);
template <typename T>
T norme_euclidienne(std::vector<T> const& a);
template <typename T>
T norme_l2(std::vector<T> const& a);


std::vector<double> lire_vecteur(std::string nom_fichier);
void ecrire_vecteur(std::string nom_fichier, const std::vector<double>& vecteur);

#include "utils_vecteur_matrice.tpp"
#endif 