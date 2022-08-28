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