#include"utils_vecteur_matrice.hpp"

std::vector<double> lire_vecteur(std::string nom_fichier)
{
	std::vector<double> vecteur;
	std::ifstream fichier{ nom_fichier };
	std::string phrase{ " " };

	//Récupère la ligne du fichier
	std::getline(fichier, phrase);

	std::string nombre_str;
	for (auto it : phrase)
	{
		if (it == ',')
		{
			vecteur.push_back(std::stod(nombre_str));
			nombre_str = "";
		}
		else if (it != ' ')
		{
			nombre_str += it;
		}
	}
	//On oublie pas le dernier !
	vecteur.push_back(std::stod(nombre_str));

	return vecteur;
}

void ecrire_vecteur(std::string nom_fichier, const std::vector<double>& vecteur)
{
	std::ofstream fichier{ nom_fichier, std::ios::app };

	for (auto it{ std::begin(vecteur) }; it != std::end(vecteur); ++it)
	{
		fichier << *it;
		if (it != (vecteur.end() - 1))
		{
			fichier << ", ";
		}
	}
}

