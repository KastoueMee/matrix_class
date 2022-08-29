#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED  

#include"utils_vecteur_matrice.hpp"
#include<cassert>
#include <sstream>

class matrice {

protected:
	int size1;
	int size2;
	std::vector<double>* matrix;

public:
	matrice(); // constructeur par defaut
	matrice(int, int);
	matrice(const matrice&); // operateur de copie
	~matrice() { delete[]matrix; };

	matrice& operator=(const matrice&);
	matrice operator+(const matrice&);
	matrice operator-(const matrice&);
	matrice operator*(const matrice&);
	matrice operator*(const double&);
	std::vector<double> operator*(const std::vector<double>&);

	bool set_coefficient(int const& i, int const& j, double const& x);
	bool set_coefficient(int const& i, std::vector<double> const& x);
	std::vector<double> colonne(int const& j);

	int dim1() { return size1; }
	int dim2() { return size2; }

	matrice transpose();
	std::vector<double> operator[](int const& i);
	double operator()(int const& i, int const& j);


	void ecrire_matrice(std::string const&);

	friend std::vector<double> operator*(std::vector<double> const& v, matrice const& m);
	friend std::istream& operator>>(std::istream& in, matrice& m);
	friend std::ostream& operator<<(std::ostream& os, const matrice& m);
};

matrice lire_matrice(std::string const& nom_fichier);

#endif 