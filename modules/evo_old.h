// these funcs were originally defined in main, but are now unused

// ------------------------------------
// Genotype-Phenotype Mapping
// ------------------------------------
void GenPhenMapping(TVector<double> &gen, TVector<double> &phen)
{
    // --------------------------------
    // Parameters for the Ventral Nerve Cord Unit
    // --------------------------------
    // Bias
    phen(1) = MapSearchParameter(gen(1), -BiasRange, BiasRange);        // DB, VBa, VBp
    phen(2) = MapSearchParameter(gen(2), -BiasRange, BiasRange);        // DD, VDa, VDp

    // Time Constant
    phen(3) = MapSearchParameter(gen(3), TauMin, TauMax);               // DB, VBa, VBp
    phen(4) = MapSearchParameter(gen(4), TauMin, TauMax);               // DD, VDa, VDp

    // Self connections
    phen(5) = MapSearchParameter(gen(5), -SCRange, SCRange);            // DB, VBa, VBp
    phen(6) = MapSearchParameter(gen(6), -SCRange, SCRange);            // DD, VDa, VDp

    // Chemical synapses
    phen(7) = MapSearchParameter(gen(7), -CSRange, CSRange);            // DB -> DD, VBa -> VDa, VBp -> VDp

    phen(8) = MapSearchParameter(gen(8), -CSRange, CSRange);          // DB -> VDa, DB -> VDp, VBa -> DD /2, VBp -> DD /2

    phen(9) = MapSearchParameter(gen(9), -CSRange, CSRange);          // DD -> VDa

    // Gap junctions across class within unit
    phen(10) = MapSearchParameter(gen(10), 0.0, ESRange);      // DD - VDa, DD - VDp

    // Gap junctions per class
    phen(11) = MapSearchParameter(gen(11), 0.0, ESRange);      // VD - VD, DD - DD
    phen(12) = MapSearchParameter(gen(12), 0.0, ESRange);      // VB - VB, DB - DB

    // Gap junctions across class, across neural unit
    phen(13) = MapSearchParameter(gen(13), 0.0, ESRange);      // VB -> DB+1

    // Stretch receptor
    phen(14) = MapSearchParameter(gen(14), -SRmax, 0.0);        // B- class SR weight

    // NMJ Weight
    phen(15) = MapSearchParameter(gen(15), 0.0, NMJmax);       // DB, VBa, VBp
    phen(16) = MapSearchParameter(gen(16), -NMJmax, 0.0);      // DD, VDa, VDp

    // --------------------------------
    // Parameters for the Head circuit
    // --------------------------------
    // Bias
    phen(17) = MapSearchParameter(gen(17), -BiasRange, BiasRange);    // SMDD, SMDV
    phen(18) = MapSearchParameter(gen(18), -BiasRange, BiasRange);    // RMDD, RMDV

    // Time Constant
    phen(19) = MapSearchParameter(gen(19), TauMin, TauMax);           // SMDD, SMDV
    phen(20) = MapSearchParameter(gen(20), TauMin, TauMax);           // RMDD, RMDV

    // Self connections
    phen(21) = MapSearchParameter(gen(21), -SCRange, SCRange);      // SMDD, SMDV
    phen(22) = MapSearchParameter(gen(22), 4.0, SCRange);           // RMDD, RMDV

    // Chemical synapses
    phen(23) = MapSearchParameter(gen(23), -HCSRange, HCSRange);      // SMDD -> SMDV, SMDV -> SMDD
    phen(24) = MapSearchParameter(gen(24), -HCSRange, HCSRange);      // SMDD -> RMDV, SMDV -> RMDD
    phen(25) = MapSearchParameter(gen(25), -HCSRange, HCSRange);      // RMDD -> RMDV, RMDV -> RMDD

    // Gap junctions across class within unit
    phen(26) = MapSearchParameter(gen(26), 0.0, ESRange);      // SMDD - RMDD, SMDV - RMDV
    phen(27) = MapSearchParameter(gen(27), 0.0, ESRange);      // RMDV - RMDD

    // SMD Stretch Receptor
    phen(28) = MapSearchParameter(gen(28), -SRmax, 0.0);        // SMD- class SR weight

    // NMJ Weight
    phen(29) = MapSearchParameter(gen(29), 0.0, NMJmax);    // SMDD, SMDV
    phen(30) = MapSearchParameter(gen(30), 0.0, NMJmax);    // RMDD, RMDV
}

void curvRatio(TVector<double> &v, TVector<double> &antposcurv)
{
    for (int i = 1; i <= N_curvs; i++)
    {
        if (i <= 11)
            antposcurv(1) += fabs(v(i));
        else
            antposcurv(2) += fabs(v(i));
    }
}


// ------------------------------------
// Display functions
// ------------------------------------
#if ENABLE_CTOR_GENO
    void EvolutionaryRunDisplay(int Generation, double BestPerf, double AvgPerf, double PerfVar) 
    {
        cout << Generation << " " << BestPerf << " " << AvgPerf << " " << PerfVar << endl;
    }

    void ResultsDisplay(TSearch &s)
    {
        TVector<double> bestVector;
        ofstream BestIndividualFile;

        bestVector = s.BestIndividual();
        BestIndividualFile.open("best.gen.dat");
        BestIndividualFile << setprecision(32);
        BestIndividualFile << bestVector << endl;
        BestIndividualFile.close();
    }
#endif