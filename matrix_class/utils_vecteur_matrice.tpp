#include<fstream>
#include<stdexcept>
#include<cmath>        // abs, sqrt


//Surcharge de l'opérateur >> pour entrer un vecteur
template <typename T>
std::istream& operator>>(std::istream& os, std::vector<T>& vecteur)
{
	T nombre = 0;
	std::cout << "Entrez les composantes du vecteur en appuyant sur \"Espace \" "
		<< "pour chacune des composantes. Appuyez sur une lettre pour arreter  : ";
	while (os >> nombre)
	{
		std::cout << "Continuez : ";
		vecteur.push_back(nombre);
	}
	return os;
}

//Surcharge de l'opérateur << pour afficher un vecteur
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vecteur)
{
	os << "[";
	for (auto it{ std::begin(vecteur) }; it != std::end(vecteur); ++it)
	{
		os << *it;
		if (it != (vecteur.end() - 1))
		{
			os << ", ";
		}
	}
	os << "]\n";
	return os;
}

//Produit scalaire par un vecteur
template <typename T>
std::vector<T> operator*(T const& lambda, std::vector<T> const& a)
{
	if (a.empty())
	{
		throw std::runtime_error("Le vecteur est vide !");
	}

	auto produit = a;
	for (int i{ 0 }; i < std::size(a); ++i)
	{
		produit[i] = a[i] * lambda;
	}
	return produit;
}

//Somme de deux vecteurs
template <typename T>
std::vector<T> operator+(std::vector<T> const& a, std::vector<T> const& b)
{
	if (a.empty() || b.empty())
	{
		throw std::runtime_error("Un vecteur est vide !");
	}
	if (std::size(a) != std::size(b))
	{
		throw std::runtime_error("Les vecteurs ne sont pas de meme dimension.");
	}

	std::vector<T> somme;
	for (int i{ 0 }; i < std::size(a); ++i)
	{
		somme.push_back(a[i] + b[i]);
	}
	return somme;


}

//Différence de deux vecteurs 
template <typename T>
std::vector<T> operator-(std::vector<T> const& a, std::vector<T> const& b)
{
	T scalaire{ -1 }; //Pour que -1 soit du type T
	return (a + (scalaire * b));
}


//Produit scalaire de deux vecteurs 
template <typename T>
T operator*(std::vector<T> const& a, std::vector<T> const& b)
{

	if (a.empty() || b.empty())
	{
		throw std::runtime_error("Un vecteur est vide !");
	}
	if (std::size(a) != std::size(b))
	{
		throw std::runtime_error("Les vecteurs ne sont pas de meme dimension.");
	}

	T produit{ 0 };
	for (int i{ 0 }; i < std::size(a); ++i)
	{
		produit += a[i] * b[i];
	}
	return produit;
}

template <typename T>
T norme_infinie(std::vector<T> const& a)
{
	if (a.empty())
	{
		throw std::runtime_error("Le vecteur est vide !");
	}

	T max = std::abs(a[0]);
	for (int i{ 0 }; i < std::size(a); ++i)
	{
		if (std::abs(a[i]) > max)
		{
			max = std::abs(a[i]);
		}
	}
	return max;
}

template <typename T>
T norme_l1(std::vector<T> const& a)
{
	if (a.empty())
	{
		throw std::runtime_error("Le vecteur est vide !");
	}

	T norme = 0;
	for (auto it : a)
	{
		norme += std::abs(it);
	}
	return norme;
}

template <typename T>
T norme_euclidienne(std::vector<T> const& a)
{
	if (a.empty())
	{
		throw std::runtime_error("Le vecteur est vide !");
	}

	T norme = 0;
	for (auto it : a)
	{
		norme += std::abs(it) * std::abs(it);
	}
	return sqrt(norme);
}

template <typename T>
T norme_l2(std::vector<T> const& a)
{
	if (a.empty())
	{
		throw std::runtime_error("Le vecteur est vide !");
	}

	T norme = 0;
	for (auto it : a)
	{
		norme += std::abs(it) * std::abs(it);
	}
	return sqrt(norme/std::size(a));
}

