#ifndef FINAL_STATES
#define FINAL_STATES

class FinalStates{
public:
    // constructor
    FinalStates(double primary_prod_length, int final_states_length, double ReductantInput,
    double BuriedOC, double TotalTime, double TimeStep);

    // setters
    void SetPrimaryProd(double primary_prod_length);
    void SetFinalStatesVect(int final_states_length, double ReductantInput, double BuriedOC, 
        double TotalTime, double TimeStep);

    // getters
    std::vector<double> GetPrimaryProd() { return _PrimaryProd;  };
    std::vector< std::vector<double> > GetFinalStatesOxygen() { return _FinalStatesOxygen; };
    std::vector< std::vector<double> > GetFinalStatesMethane() { return _FinalStatesMethane; };

    // other methods
    void PlotFinalStates();
private:
    std::vector<double> _PrimaryProd;
    std::vector< std::vector<double> > _FinalStatesOxygen;
    std::vector< std::vector<double> > _FinalStatesMethane;

};

#endif