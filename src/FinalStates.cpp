#include<vector>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <sciplot/sciplot.hpp>  
#include "DynamicModel.h"
#include "FinalStates.h"
#include "utils.h"

using namespace sciplot;

FinalStates::FinalStates(double primary_prod_length, int final_states_length, double ReductantInput,
    double BuriedOC, double TotalTime, double TimeStep)
{
    FinalStates::SetPrimaryProd(primary_prod_length);
    FinalStates::SetFinalStatesVect(final_states_length, ReductantInput, BuriedOC, TotalTime, TimeStep);
};

void FinalStates::SetPrimaryProd(double primary_prod_length)
{
    _PrimaryProd = logspace(11, 17, primary_prod_length);
};

void FinalStates::SetFinalStatesVect(int final_states_length, double ReductantInput, double BuriedOC, 
    double TotalTime, double TimeStep)
{
    for (auto primary_prod : GetPrimaryProd())
    {
        DynamicModel model = DynamicModel(primary_prod, ReductantInput, BuriedOC, TotalTime, TimeStep);
        model.FindFinalStates();
        int step = (int) model.Oxygen.size() / final_states_length;
        std::vector<double> oxygen;
        std::vector<double>  methane;
        // oxygen.empty();
        // methane.empty();
        for (int i = 1; i <= model.Oxygen.size(); i = i + step)
        {
            oxygen.push_back(mol_to_O2_PAL(model.Oxygen[i]));
            methane.push_back(mol_to_O2_PAL(model.Methane[i]));
        }
        _FinalStatesOxygen.push_back(oxygen);
        _FinalStatesMethane.push_back(methane);        
    }
     transpose(_FinalStatesOxygen);
     transpose(_FinalStatesMethane);
};

void FinalStates::PlotFinalStates()
{
    int systemRet = system("mkdir -p plots");
    if(systemRet == -1){
    std::cout << "plots directory already exists" << std::endl;
    }
    for (int i = 0; i < FinalStates::GetFinalStatesOxygen().size(); i++)
    {
         // Create a Plot object
        Plot plot;

        plot.size(800, 400);

        // Change its palette
        plot.palette("dark2");
        plot.ylabel("Oxygen mol");
        plot.xlabel("Primary Productivity mol");
        plot.gnuplot("set logscale x");
        plot.gnuplot("set logscale y");
        plot.xrange(1e11, 1e17);

        // Plot two functions
        plot.drawPoints(FinalStates::GetPrimaryProd(), GetFinalStatesOxygen()[i]).label("oxygen");
        plot.drawPoints(FinalStates::GetPrimaryProd(), GetFinalStatesMethane()[i]).label("methane");
        //plot.drawPoints(x, ).label("cos(x)");

        // Save the plot to a PDF file
        std::ostringstream ss;
        ss << std::setw(2) << std::setfill('0') << i;
        plot.save("plots/plot_" + ss.str() + ".png");
    }
    int systemRet1 = system("convert -delay 20 plots/plot_*.png -loop 0 plot.gif");
    if(systemRet1 == -1){
    std::cout << "The gif could not be created" << std::endl;
    }
};