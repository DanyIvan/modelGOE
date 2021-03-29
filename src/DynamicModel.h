#ifndef DYNAMIC_MODEL
#define DYNAMIC_MODEL

#include<vector>

class DynamicModel
{
public:
    // constructor
    DynamicModel(double PrimaryProd, double ReductantInput, double BuriedOC, 
    double TotalTime, double TimeStep);
    // geters
    double GetHydrogenEscape(){ return _HydrogenEscape;};
    double GetPrimaryProd(){ return _PrimaryProd; };
    double GetReductantInput(){ return _ReductantInput;};
    double GetBuriedOC(){ return _BuriedOC; };
    double GetOcExposure(){ return _OcExposure; };
    double GetTotalTime() { return _TotalTime; };
    double GetTimeStep() { return _TimeStep; };
    int Getsave_every() { return _save_every; };
    int Getprint_every() { return _print_every; };
    double GetNumberOfSteps() { return _NumberOfSteps; };
    // setters
    void SetHydrogenEscape(double HydrogenEscape){ _HydrogenEscape = HydrogenEscape;};
    void SetPrimaryProd(double PrimaryProd){ _PrimaryProd = PrimaryProd; };
    void SetReductantInput(double ReductantInput){ _ReductantInput = ReductantInput; };
    void SetBuriedOC(double BuriedOC){ _BuriedOC = BuriedOC; };
    void SetOcExposure(double OcExposure){ _OcExposure = OcExposure; };
    void SetTotalTime( double TotalTime) { _TotalTime = TotalTime; };
    void SetTimeStep( double TimeStep) { _TimeStep = TimeStep; };
    void Setsave_every( double save_every) { _save_every = save_every; };
    void Setprint_every( double print_every) { _print_every = print_every; };
    void SetNumberOfSteps( double NumberOfSteps) { _NumberOfSteps = NumberOfSteps; };

    // other methods
    
    // fraction of OC decomposed by heterotrophic aerobic respiration
    double OcDecomposed(double oxygen);
    // fraction of methane produced used by methanotrophs
    double MethaneProduced(double oxygen);
    // fraction of the organic carbonavailable to decomposers 
    double OcAvailable(double oxygen);
    // methane oxidation parametrization
    double MethaneOxidation(double oxygen);
    // function to find steady states
    void FindFinalStates();
    std::vector<double> Oxygen;
    std::vector<double> Methane;
    std::vector<double> OrganicCarbon;
    std::vector<double> Time;
    double OxygenSteadyState;
    double OrganicCarbonSteadyState;
    double MethaneSteadyState;
    double OxygenInitialCond;

private:
    // primary productivity
    double _PrimaryProd;
    // reductant input
    double _ReductantInput;
    // fraction of organic carbon buried in sediments
    double _BuriedOC;
    // hydrogen escape coefficient
    double _HydrogenEscape {3.7e-5};
    // rate of exposure of buried organic carbon from the crust 
    double _OcExposure {6e-9};
    // inhibition of aerobic respiration at the Pasteur point [mol]
    double const _ARInhibition {1.36e19};
    // coefficient of methane used by methanotrophs[mol]
    double const _MethanotrophsMethane {2.73e17};
    // coefficients of methane oxidation parametrization
    double const _PolynomialCoeffs [5] = {0.0030084, -0.1655405, 3.2305351, -25.8343054,
        71.5397861};
    double _TotalTime {1e7};
    double _TimeStep{1};
    int _save_every {1000};
    int _print_every{50000};
    int _NumberOfSteps;
    
};


#endif