#include <iostream>
#include <stdlib.h>
#include <vector>
#include "DynamicModel.h"
#include <sciplot/sciplot.hpp>  
#include "FinalStates.h"
using namespace sciplot;


int main() {
    FinalStates final_states = FinalStates(100.0, 50, 3e10, 0.01, 1e4, 0.01);
    final_states.PlotFinalStates();
}