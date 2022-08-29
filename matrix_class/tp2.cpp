#include"tp2.hpp"

matricecarree assemblage_matrice_1(int const& n)
{
	matricecarree A(n);
	double pi = 3.14159265358979323846;
	double h = pi / (n + 1);
	double hh = 1 / (h * h * h * h);

	for (int i = 0; i < n - 1; ++i)
	{
		A.set_coefficient(i, i, 6.0);
		A.set_coefficient(i, i+1, -4);
		A.set_coefficient(i+1, i, -4);
	}

	A.set_coefficient(0, 0, 7.0);
	A.set_coefficient(n-1, n-1, 7.0);

	for (int i = 0; i < n - 2; ++i)
	{
		A.set_coefficient(i, i + 2, 1);
		A.set_coefficient(i + 2, i, 1);
	}

	return  A*hh;
}

matricecarree assemblage_matrice_2(int const& n)
{
	matricecarree A(n);

	for (int i = 0; i < n - 2; ++i)
	{
		A.set_coefficient(i, 0, 1.0);
		A.set_coefficient(i, 1, 1.0 * (i + 1));
		for (int j = 1; j < n - 1; ++j)
		{
			A.set_coefficient(i, j + 1, pow(abs(i + 1 - j) * 1.0, 3));
		}
	}

	for (int j = 2; j < n; ++j)
	{
		A.set_coefficient(n - 2, j, 1.0);
	}

	for (int j = 1; j < n - 1; ++j)
	{
		A.set_coefficient(n - 1, j + 1, 1.0 * j);
	}

	return  A;
}

matricecarree assemblage_matrice_3(int const& n, std::vector<double> const& soleil, std::vector<double> const& temperature)
{
	matricecarree A(n);

	for (int i = 0; i < n - 2; ++i)
	{
		A.set_coefficient(i, 0, 1.0);
		A.set_coefficient(i, 1, soleil[i]);
		for (int j = 0; j < n - 2; ++j)
		{
			A.set_coefficient(i, j + 2, pow(abs(soleil[i]-soleil[j]), 3));
		}
	}
	
	for (int j = 2; j < n; ++j)
	{
		A.set_coefficient(n - 2, j, 1.0);
	}

	for (int j = 0; j < n -2; ++j)
	{
		A.set_coefficient(n - 1, j + 2, soleil[j]);
	}
	
	return  A;
}

double fonction_1(double const& x, int const& choix)
{
	if (choix == 1)
	{
		return 1;
	}
}

double sol_exacte_1(double const& x)
{
	double pi = 3.14159265358979323846;
	return 1.0/24*(pi-x)*(pi-x)*x*x;
}

void question1()
{
	std::fstream fichier;
	fichier.open("2019.csv", std::ios::in);

	int debut = 82;
	int nb_jours = 94;
	int n = nb_jours + 2;

	std::string line, word;
	std::vector<double> y(nb_jours, 0);

	//Recuperation de la temperature minimale
	for (int i = 0; i < debut; ++i)
	{
		std::getline(fichier, line);
	}

	for (int i = 0; i < nb_jours; ++i)
	{
		std::getline(fichier, line);
		std::stringstream s(line);
		std::getline(s, word, ',');
		std::getline(s, word, ',');
		std::getline(s, word, ',');

		y[i] = std::stod(word);
	}

	//Construction de Ay = z

	auto A = assemblage_matrice_2(6);
	std::vector<int> piv(n, 0);
	y.push_back(0);
	y.push_back(0);

	auto z = A.solvelu(y, piv);

	//Calcul de la temperature du lendemain
	double temp = 0;
	for (int i = 1; i < n - 1; ++i)
	{
		temp += z[i + 1] * pow(nb_jours - i, 3);
	}

	temp += z[0] + nb_jours * z[1];

	std::cout << "La prediction de la temperature minimal est de " << temp << std::endl;
	fichier.close();

}

void question2()
{
	std::fstream fichier;
	fichier.open("2019.csv", std::ios::in);

	int debut = 82;
	int nb_jours = 94;
	int n = nb_jours + 2;

	std::string line, word;
	std::vector<double> ensoleillement(nb_jours, 0);
	std::vector<double> temperature(nb_jours, 0);


	//Recuperation de l'ensoleillement
	for (int i = 0; i < debut; ++i)
	{
		std::getline(fichier, line);
	}

	for (int i = 0; i < nb_jours; ++i)
	{
		std::getline(fichier, line);
		std::stringstream s(line);
		for (int j = 0; j < 21 /* SUNHOUR*/; ++j)
		{
			std::getline(s, word, ',');
			if (j == 2)
			{
				temperature[i] = std::stod(word);
			}
		}
		ensoleillement[i] = std::stod(word);
	}

	double max_soleil = norme_infinie(ensoleillement);

	for (int i = 0; i < nb_jours; ++i)
	{
		ensoleillement[i] = ensoleillement[i] / max_soleil;
	}

	//Construction de Ay = z

	auto A = assemblage_matrice_3(n, ensoleillement, temperature);

	
	std::vector<int> piv(n, 0);
	ensoleillement.push_back(0);
	ensoleillement.push_back(0);
	temperature.push_back(0);
	temperature.push_back(0);

	auto z = A.solvelu(temperature, piv);

	std::cout << z;
	//Calcul de la temperature du lendemain
	double temp = 0;
	for (int i = 1; i < n - 1; ++i)
	{
		temp += z[i + 1] * pow(nb_jours - i, 3);
	}

	temp += z[0] + nb_jours * z[1];

	std::cout << "La prediction de la temperature minimal est de " << temp << std::endl;
	fichier.close();

}
void application1()
{
	double const pi = 3.14159265358979323846;
	int n = 0;
	double h = 0;

	for (int i = 3; i < 10; ++i)
	{
		n = pow(2, i);
		h = pi / (n + 1);

		std::vector<int> piv(n, 0);
		std::vector<double> U_exact(n, 0);
		std::vector<double> b(n, 1);

		matricecarree A = assemblage_matrice_1(n);

		for (int j = 1; j < n + 1; ++j)
		{
			U_exact[(j - 1)] = sol_exacte_1(j * h);
		}

		//auto U_chol = A.solvechol(b);
		auto U_lu = A.solvelu(b, piv);

		//auto err_chol = norme_infinie(U_exact-U_chol);
		auto err_lu = norme_infinie(U_exact - U_lu);

		std::cout  << " err_lu = " << err_lu << std::endl;

	}
}

void application2()
{
	std::cout << "Question 1 : " << std::endl;
	question1();

	std::cout << "Question 2 : " << std::endl;



}

