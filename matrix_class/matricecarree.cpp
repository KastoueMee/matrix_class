#include"matricecarree.hpp"
matricecarree matricecarree::transpose()
{
    matricecarree trans(size1);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size1; ++j)
        {
            trans.matrix[j][i] = matrix[i][j];
        }
    }
    return trans;
}

matricecarree matricecarree::operator*(const double& lambda)
{
    matricecarree prod(size1);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < size2; ++j)
        {
            prod.matrix[i][j] = lambda * matrix[i][j];
        }
    }
    return prod;
}

matricecarree matricecarree::chol()
{
    double coef;
    matricecarree b(size1);
    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            coef = 0;
            for (int k = 0; k < j; ++k)
            {
                coef -= b.matrix[i][k] * b.matrix[j][k];
            }
            coef += matrix[i][j];
            if (j != i)
            {
                b.matrix[i][j] = coef / b.matrix[j][j];
            }
            else
            {
                b.matrix[i][i] = sqrt(coef);
            }
        }
    }

    return b;
}

matricecarree matricecarree::lu(std::vector<int>& piv)
{
    double a_max = 0;
    double j_max = 0;
    int aux_1 = 0;
    double aux = 0;

    for (int i = 0; i < size1; ++i)
    {
        piv[i] = i;
    }

    for (int j = 0; j < size1 - 1; ++j)
    {
        a_max = abs(matrix[piv[j]][j]);
        j_max = j;
        for (int i = j + 1; i < size1; ++i)
        {
            if (abs(matrix[piv[i]][j]) > a_max)
            {
                a_max = abs(matrix[piv[i]][j]);
                j_max = i;
            }
        }

        aux_1 = piv[j];
        piv[j] = piv[j_max];
        piv[j_max] = aux_1;

        for (int i = j + 1; i < size1; ++i)
        {
            aux = matrix[piv[i]][j] / matrix[piv[j]][j];
            matrix[piv[i]][j] = aux;
            for (int k = j + 1; k < size1; ++k)
            {
                matrix[piv[i]][k] = matrix[piv[i]][k] - aux * matrix[piv[j]][k];
            }
        }
    }

    return *this;
}

std::vector<double> matricecarree::solvelu(std::vector<double> const& b, std::vector<int>& piv)
{
    auto PA = this->lu(piv);
    double c = 0;
    std::vector<double> x(size1, 0);

    for (int i = 0; i < size1; ++i)
    {
        c = 0;
        for (int j = 0; j < i; ++j)
        {
            c += PA.matrix[piv[i]][j] * x[j];
        }
        x[i] = b[piv[i]] - c;
    }

    for (int i = size1 - 1; i >= 0; --i)
    {
        c = 0;
        for (int j = i + 1; j < size1; ++j)
        {
            c += PA.matrix[piv[i]][j] * x[j];
        }
        x[i] = (x[i] - c ) / PA.matrix[piv[i]][i];
    }

    return x;
}

std::vector<double> matricecarree::forward(std::vector<double> const& b)
{
    assert(size1 == std::size(b));
    std::vector<double> sol(size1, 0);

    for (int i = 0; i < size1; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            sol[i] -= matrix[i][j] * sol[j];
        }
        sol[i] += b[i];
        sol[i] /= matrix[i][i];
    }

    return sol;
}

std::vector<double> matricecarree::backward(std::vector<double> const& b)
{
    assert(size1 == std::size(b));
    std::vector<double> sol(size1, 0);
    for (int i = size1 - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < size1; ++j)
        {
            sol[i] -= matrix[i][j] * sol[j];
        }
        sol[i] += b[i];
        sol[i] /= matrix[i][i];
    }
    return sol;
}

std::vector<double> matricecarree::solvechol(std::vector<double> const& b)
{
    auto B = chol();
    return (B.transpose()).backward((B.forward(b)));
}

