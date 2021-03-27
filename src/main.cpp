#include <iostream>
#include "DynamicModel.h"

int main() {
    DynamicModel model = DynamicModel(3.75e15, 3e10, 0.01, 1.62e15, 1e5, 0.1);
    std::cout << "PrimaryProd " << model.GetPrimaryProd() << "\n";
    std::cout << "Reductant " << model.GetReductantInput() << "\n";
    std::cout << "OcCarbon " << model.GetBuriedOC() << "\n";
    std::cout << "TotalTime " << model.GetTotalTime() << "\n";
    std::cout << "TimeStep" << model.GetTimeStep() << "\n";
    std::cout << "NumberOfSteps " << model.GetNumberOfSteps() << "\n";
    model.FindSteadyStates();
    std::cout << "OxygenSteadyState: " << model.OxygenSteadyState << std::endl;
    std::cout << "MethaneSteadyState: " << model.MethaneSteadyState << std::endl;
    std::cout << "OrganicCarbonSteadyState: " << model.OrganicCarbonSteadyState << std::endl;
    
    // std::cout << "Methane: " << std::endl;
    // for (int i = 0; i <= model.Methane.size(); i++)
    // {
    //     std::cout << model.Methane[i] << " "; 
    // }
    // std::cout << std::endl;
    // std::cout << "Oxygen: " << std::endl;
    // for (int i = 0; i <= model.Oxygen.size(); i++)
    // {
    //     std::cout << model.Oxygen[i] << " "; 
    // }
    // std::cout << std::endl;
    // std::cout << "OrganicCarbon: " << std::endl;
    // for (int i = 0; i <= model.OrganicCarbon.size(); i++)
    // {
    //     std::cout << model.OrganicCarbon[i] << " "; 
    // }
    // std::cout << std::endl;
    
    return 0;
}