#include"matrix.hpp"
//#include"matcarree.hpp"



int main()
{

	matrice test(4,4);

	std::vector<double> v1 = { 1,1,1,1 };
	std::vector<double> v2 = { 1,5,5,5 };
	std::vector<double> v3 = { 1,5,14,14 };
	std::vector<double> v4 = { 1,5,14,15 };

	std::vector<double> b = { 4, 16, 34, 35 };

	test.set_coefficient(0, v1);
	test.set_coefficient(1, v2);
	test.set_coefficient(2, v3);
	test.set_coefficient(3, v4);


   

	test.ecrire_matrice("matrice2.txt"); 
	auto z = lire_matrice("matrice.txt");

	std::cout << z << std::endl;
    


	return 0;
}