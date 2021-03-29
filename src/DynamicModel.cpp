#include<iostream>
#include<vector>
#include <math.h> 
#include "DynamicModel.h"


// constructor
DynamicModel::DynamicModel(double PrimaryProd, double ReductantInput, double BuriedOC, 
double TotalTime, double TimeStep)
{
    // set primary productivity
    SetPrimaryProd(PrimaryProd);
    // set reductant input
    SetReductantInput(ReductantInput);
    // set rate of burial of OC
    SetBuriedOC(BuriedOC);
    // Set total time
    _TotalTime = TotalTime;
    // Set time step
    _TimeStep = TimeStep;
    // set number of time stpes
    _NumberOfSteps = (int) _TotalTime / _TimeStep;  
    // set initial conditions
    Oxygen.push_back(2 * GetReductantInput() / GetHydrogenEscape());
    Methane.push_back(GetReductantInput() / GetHydrogenEscape());
    OrganicCarbon.push_back(GetBuriedOC() * (GetReductantInput()) / GetOcExposure());          
};

double DynamicModel::OcDecomposed(double oxygen) 
{
    return oxygen / (oxygen + _ARInhibition);
}

// fraction of methane produced used by methanotrophs
double DynamicModel::MethaneProduced(double oxygen) 
{
    return oxygen / (oxygen + _MethanotrophsMethane);
}

// fraction of the organic carbon available to decomposers 
double DynamicModel::OcAvailable(double oxygen) 
{
    return (1 - DynamicModel::OcDecomposed(oxygen)) * (1 - DynamicModel::MethaneProduced(oxygen));
}

// methane oxidation parametrization 
double DynamicModel::MethaneOxidation(double oxygen) 
{
    // std::cout << _PolynomialCoeffs[0] * pow(log10(oxygen), 4) <<  std::endl;
    // std::cout << _PolynomialCoeffs[1] * pow(log10(oxygen), 3)  <<  std::endl;
    // std::cout << _PolynomialCoeffs[2] * pow(log10(oxygen), 2) <<  std::endl;
    // std::cout << _PolynomialCoeffs[3] * log10(oxygen) <<  std::endl;
    // std::cout << _PolynomialCoeffs[4] <<  std::endl;
    // std::cout << pow(10,
    //     _PolynomialCoeffs[0] * pow(log10(oxygen), 4) + 
    //     _PolynomialCoeffs[1] * pow(log10(oxygen), 3) +
    //     _PolynomialCoeffs[2] * pow(log10(oxygen), 2) +
    //     _PolynomialCoeffs[3] * log10(oxygen) +
    //     _PolynomialCoeffs[4]) << std::endl;
    return pow(10,
        _PolynomialCoeffs[0] * pow(log10(oxygen), 4) + 
        _PolynomialCoeffs[1] * pow(log10(oxygen), 3) +
        _PolynomialCoeffs[2] * pow(log10(oxygen), 2) +
        _PolynomialCoeffs[3] * log10(oxygen) +
        _PolynomialCoeffs[4]);
}

void DynamicModel::FindFinalStates()
{
double OxygenLast = Oxygen[0];
double MethaneLast = Methane[0];
double OrganicCarbonLast = OrganicCarbon[0];
// std::cout <<"----------------------------------------------" << std::endl;
// std::cout << "OxygenLast: " << OxygenLast << std::endl;
// std::cout << "MethaneLast: " << MethaneLast << std::endl;
// std::cout << "OrganicCarbonLast: " << OrganicCarbonLast << std::endl;


for (int i=0; i <= _NumberOfSteps; i ++)
    {
    // double omega = OcAvailable(OxygenLast);
    // double phi = MethaneOxidation(OxygenLast);
    double MethaneStep =  GetTimeStep() / 2 * (
        OcAvailable(OxygenLast) * (1 - GetBuriedOC()) * (GetPrimaryProd() + GetReductantInput()) +
        OcAvailable(OxygenLast) * GetOcExposure() * OrganicCarbonLast -
        2 * GetHydrogenEscape() * MethaneLast -
        MethaneOxidation(OxygenLast) * pow(MethaneLast, 0.7)
    );
    double OxygenStep =  GetTimeStep() * (
        OcAvailable(OxygenLast) * GetPrimaryProd() -
        (1 - OcAvailable(OxygenLast)) * GetReductantInput() +
        GetBuriedOC() * (1 - OcAvailable(OxygenLast)) * (GetPrimaryProd() + GetReductantInput()) -
        (1 - OcAvailable(OxygenLast)) * GetOcExposure() * OrganicCarbonLast -
        GetHydrogenEscape() * MethaneLast -\
        MethaneOxidation(OxygenLast) * pow(MethaneLast, 0.7)
    );
    double OrganicCarbonStep =  GetTimeStep() * (
        GetBuriedOC() * (GetPrimaryProd() + GetReductantInput())
        - GetOcExposure() * OrganicCarbonLast
    );
    MethaneLast = MethaneLast + MethaneStep;
    OxygenLast = OxygenLast + OxygenStep;
    OrganicCarbonLast = OrganicCarbonLast + OrganicCarbonStep;

    // std::cout <<"Step " << i << std::endl;
    // std::cout <<"----------------------------------------------" << std::endl;
    // std::cout << "omega: " << omega << std::endl;
    // std::cout << "phi: " << phi << std::endl;
    // std::cout << "OxygenStep: " << OxygenStep << std::endl;
    // std::cout << "MethaneStep: " << MethaneStep << std::endl;
    // std::cout << "OrganicCarbonStep: " << OrganicCarbonStep << std::endl;
    // std::cout <<"----------------------------------------------" << std::endl;
    // std::cout << "OxygenLast: " << OxygenLast << std::endl;
    // std::cout << "MethaneLast: " << MethaneLast << std::endl;
    // std::cout << "OrganicCarbonLast: " << OrganicCarbonLast << std::endl;
    if (i % Getsave_every() ==0)
    {
        Methane.push_back(MethaneLast);
        Oxygen.push_back(OxygenLast);
        OrganicCarbon.push_back(OrganicCarbonLast);
        Time.push_back( i * GetTimeStep());
    }
    if (i % Getprint_every() == 0)
    {
        std::cout << "------------------------------" << std::endl;
        std::cout << "Time : " << i * GetTimeStep() << std::endl;
        std::cout << "Oxygen : " << OxygenLast << std::endl;
        std::cout << "Methane : " << MethaneLast << std::endl;
        std::cout << "Organic Carbon: " << OrganicCarbonLast << std::endl;

    }
        
}
OxygenSteadyState = Oxygen.back();
MethaneSteadyState = Methane.back();
OrganicCarbonSteadyState = OrganicCarbon.back();
};