#ifndef DYNAMIC_MODEL
#define DYNAMIC_MODEL

#include<vector>

class DynamicModel
{
public:
    DynamicModel(long double PrimaryProd, long double ReductantInput, long double BuriedOC, 
    long double OxygenInitialCond, long double TotalTime, long double TimeStep);
    long double GetHydrogenEscape(){ return _HydrogenEscape;};
    long double GetPrimaryProd(){ return _PrimaryProd; };
    long double GetReductantInput(){ return _ReductantInput;};
    long double GetBuriedOC(){ return _BuriedOC; };
    long double GetOcExposure(){ return _OcExposure; };
    long double GetTotalTime() { return _TotalTime; };
    long double GetTimeStep() { return _TimeStep; };
    int Getsave_every() { return _save_every; };
    int Getprint_every() { return _print_every; };
    long double GetNumberOfSteps() { return _NumberOfSteps; };
    // setters
    void SetHydrogenEscape(long double HydrogenEscape){ _HydrogenEscape = HydrogenEscape;};
    void SetPrimaryProd(long double PrimaryProd){ _PrimaryProd = PrimaryProd; };
    void SetReductantInput(long double ReductantInput){ _ReductantInput = ReductantInput; };
    void SetBuriedOC(long double BuriedOC){ _BuriedOC = BuriedOC; };
    void SetOcExposure(long double OcExposure){ _OcExposure = OcExposure; };
    void SetTotalTime( long double TotalTime) { _TotalTime = TotalTime; };
    void SetTimeStep( long double TimeStep) { _TimeStep = TimeStep; };
    void Setsave_every( long double save_every) { _save_every = save_every; };
    void Setprint_every( long double print_every) { _print_every = print_every; };
    void SetNumberOfSteps( long double NumberOfSteps) { _NumberOfSteps = NumberOfSteps; };
    // fraction of OC decomposed by heterotrophic aerobic respiration
    long double OcDecomposed(long double oxygen);
    // fraction of methane produced used by methanotrophs
    long double MethaneProduced(long double oxygen);
    // fraction of the organic carbonavailable to decomposers 
    long double OcAvailable(long double oxygen);
    // methane oxidation parametrization
    long double MethaneOxidation(long double oxygen);
    // function to find steady states
    void FindSteadyStates();
    std::vector<long double> Oxygen;
    std::vector<long double> Methane;
    std::vector<long double> OrganicCarbon;
    std::vector<long double> Time;
    long double OxygenSteadyState;
    long double OrganicCarbonSteadyState;
    long double MethaneSteadyState;
    long double OxygenInitialCond;

private:
    // primary productivity
    long double _PrimaryProd;
    // reductant input
    long double _ReductantInput;
    // fraction of organic carbon buried in sediments
    long double _BuriedOC;
    // hydrogen escape coefficient
    long double _HydrogenEscape {3.7e-5};
    // rate of exposure of buried organic carbon from the crust 
    long double _OcExposure {6e-9};
    // inhibition of aerobic respiration at the Pasteur point [mol]
    long double const _ARInhibition {1.36e19};
    // coefficient of methane used by methanotrophs[mol]
    long double const _MethanotrophsMethane {2.73e17};
    // coefficients of methane oxidation parametrization
    long double const _PolynomialCoeffs [5] = {0.0030084, -0.1655405, 3.2305351, -25.8343054,
        71.5397861};
    long double _TotalTime {1e7};
    long double _TimeStep{1};
    int _save_every {1000};
    int _print_every{10000};
    int _NumberOfSteps;
    
};


#endif