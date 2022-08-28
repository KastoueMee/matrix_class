#include"matrix.hpp"
#include"matricecarree.hpp"



int main()
{

	matricecarree test(4);

	std::vector<double> v1 = { 1,1,1,1 };
	std::vector<double> v2 = { 1,5,5,5 };
	std::vector<double> v3 = { 1,5,14,14 };
	std::vector<double> v4 = { 1,5,14,15 };

	std::vector<double> b = { 4, 16, 34, 35 };

	test.set_coefficient(0, v1);
	test.set_coefficient(1, v2);
	test.set_coefficient(2, v3);
	test.set_coefficient(3, v4);



	std::cout << test << std::endl;
	std::cout << test.chol() << std::endl;



	return 0;
}