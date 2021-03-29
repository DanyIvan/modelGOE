#ifndef UTILS
#define UTILS

#include<vector>
#include <algorithm>
#include <functional>
#include <string>
#include <valarray>

// create log spaced vector
template <typename T0, typename T1, typename U = double>
auto logspace(T0 x0, T1 x1, std::size_t numintervals) -> std::vector<U>
{
    std::vector<U> result;
    for(std::size_t i = 0; i <= numintervals; ++i)
        result.push_back(
        	pow(10, x0 + i * (x1 - x0) / static_cast<U>(numintervals))
        );

    return result;
}

// convert mol to present levels of atmopsheric oxygen (PAL)
double mol_to_O2_PAL(double mol)
{
    return mol * 29 / 5.2e21;
};


// This code comes from https://stackoverflow.com/questions/49444856/transpose-of-a-2d-matrix-using-vectors-in-c/49445850
void transpose(std::vector<std::vector<double> > &b)
{
    if (b.size() == 0)
        return;

    std::vector<std::vector<double> > trans_vec(b[0].size(), std::vector<double>());

    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            trans_vec[j].push_back(b[i][j]);
        }
    }

    b = trans_vec;    // <--- reassign here
}

#endif
