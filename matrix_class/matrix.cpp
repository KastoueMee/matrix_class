#include"matrix.hpp"

/* *****************************************************
CONSTRUCTEURS ET DESTRUCTEURS
******************************************************** */

//Defaut constructor
matrice::matrice()
{
    size1 = 1;
    size2 = 1;
    matrix = new std::vector<double>[size1];
    matrix[0].push_back(0);
}

matrice::matrice(int nb_lignes, int nb_colonnes) : 
    size1(nb_lignes), size2(nb_colonnes)
{
    /* Dynamically allocates memory for size1 std::vector<double> continuously
       and returns a pointer to the first element of the sequence,
       which is assigned top(a pointer). matrix[0] refers to the first
       element, matrix[1] refers to the second element, and so on.
       Donc matrix[0] est, pour l'instant, un vecteur vide, qui repro?=sente
       la premio?=re ligne de la matrice. */

    matrix = new std::vector < double >[size1];
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            matrix[i].push_back(0);
        }
    }
}

//Copy operator
matrice::matrice(const matrice& m) :
    size1(m.size1),
    size2(m.size2)
{
    matrix = new std::vector < double >[size1];
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            matrix[i].push_back(m.matrix[i][j]);
        }
    }
}

//Pour effectuer B=A. C'est donc B qui appele la fonction
matrice& matrice::operator= (const matrice& m)
{
    //Cas ou on veut faire m=m, pour ne pas supprimer m.
    //this est le pointeur sur B
    if (&m == this)
    {
        return *this;
    }

    //If B and A don't have the same size we resize.
    if (size1 != m.size1 || size2 != m.size2)
    {
        delete[]matrix;
        matrix = new std::vector < double >[m.size1];
        size1 = m.size1;
        size2 = m.size2;
    }

    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            matrix[i].push_back(m.matrix[i][j]);
        }
    }
    return *this;
}

matrice matrice::operator+ (const matrice& m)
{
    assert(size1 == m.size1 && size2 == m.size2);
    matrice somme(m.size1, m.size2);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            somme.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
        }
    }

    return somme;
}

matrice matrice::operator- (const matrice& m)
{
    assert(size1 == m.size1 && size2 == m.size2);
    matrice somme(m.size1, m.size2);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            somme.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
        }
    }

    return somme;
}

matrice matrice::operator*(const matrice& m)
{
    assert(size2 == m.size1);
    matrice prod(size1, m.size2);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < m.size2; ++j)
        {
            for (int k = 0; k < size2; ++k)
                prod.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
        }
    }
    return prod;
}

matrice matrice::operator*(const double& lambda)
{
    matrice prod(size1, size2);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            prod.matrix[i][j] = lambda * matrix[i][j];
        }
    }
    return prod;
}

std::vector<double> matrice::operator*(const std::vector<double>& v)
{
    assert(size2 == std::size(v));
    std::vector<double> prod(size1, 0);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            prod[i] += matrix[i][j] * v[j];
        }
    }
    return prod;
}






/*****************************************************
MANIPULATION DE LA MATRICE
******************************************************/

//Change l'element (i,j) par x.
bool matrice::set_coefficient(int const& i, int const& j, double const& x)
{
    assert(i < size1 && j < size2);
    matrix[i][j] = x;
    return true;
}

//Change la ligne i par le vecteur x.
bool matrice::set_coefficient(int const& i, std::vector < double >const& x)
{
    assert(std::size(x) == size2 && i < size1);
    for (int j = 0; j < std::size(x); ++j)
    {
        matrix[i][j] = x[j];
    }
    return true;
}

//Return the j-th column
std::vector<double> matrice::colonne(int const& j)
{
    assert(j < size2);
    std::vector < double >col(size1);
    for (int i = 0; i < size1; ++i)
    {
        col[i] = matrix[i][j];
    }
    return col;
}

//Return the transposition
matrice matrice::transpose()
{
    matrice transp(size1, size2);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            transp.matrix[j][i] = matrix[i][j];
        }
    }
    return transp;
}

//Return the i-th line
std::vector<double> matrice::operator[](int const& i)
{
    assert(i < size1);
    std::vector < double >ligne(size2);
    for (int j = 0; j < size2; ++j)
    {
        ligne[j] = matrix[i][j];
    }
    return ligne;
}

//Return a_i,j
double matrice::operator() (int const& i, int const& j)
{
    assert(i < size1&& j < size2);
    return matrix[i][j];
}





void matrice::ecrire_matrice(std::string const& nom_fichier)
{
    std::ofstream fichier{ nom_fichier, std::ios::app };

    fichier << size1 << "," << size2 ;
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            fichier << "," << matrix[i][j];
        }
    }
}






/*****************************************************
                         FRIENDS
******************************************************/



std::vector<double> operator*(std::vector<double> const& v, matrice const& m)
{
    assert(std::size(v) == m.size1);
    std::vector<double> prod(m.size2, 0);
    for (int i = 0; i < m.size2; ++i)
    {
        for (int j = 0; j < m.size1; ++j)
        {
            prod[i] += m.matrix[j][i] * v[j];
        }
    }
    return prod;
}

std::istream& operator >> (std::istream& in, matrice& m)
{
    std::cout << "Entrez les " << m.size1 *
        m.size2 << " coefficients de la matrice : " << std::endl;
    for (int i = 0; i < m.size1; ++i)
    {
        std::cout << "Ligne : " << i << std::endl;
        for (int j = 0; j < m.size2; ++j)
        {
            in >> m.matrix[i][j];
        }
    }

    return in;
}

std::ostream& operator<< (std::ostream& os, const matrice& m)
{
    for (int i = 0; i < m.size1; ++i)
    {
        os << "[ ";
        for (int j = 0; j < m.size2 - 1; ++j)
        {
            os << m.matrix[i][j] << ", ";
        }
        os << m.matrix[i][m.size2 - 1] << " ] " << std::endl;
    }

    return os;
}

matrice lire_matrice(std::string const& nom_fichier)
{
    std::ifstream fichier{ nom_fichier };
    std::string phrase, mot;
    int ligne, colonne, i, j;

    //Récupère la ligne du fichier
    std::getline(fichier, phrase);

    //Transforme la ligne en stringstream
    std::stringstream s(phrase);

    //Recupere size1 dans mot
    std::getline(s, mot, ',');
    ligne = (std::stoi(mot));

    //Recupere size2
    std::getline(s, mot, ',');
    colonne = (std::stoi(mot));

    matrice lire(ligne, colonne);
    i = 0;
    j = 0;
    while (std::getline(s, mot, ','))
    {
        lire.set_coefficient(i, j, std::stod(mot));

        if (j != colonne - 1)
        {
            ++j;
        }
        else
        {
            j = 0;
            ++i;
        }
    }
    return lire;
}