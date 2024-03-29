//
//  StretchReceptor.hpp
//  one
//
//  Created by Eduardo on 9/26/15.
//  Copyright © 2015 Eduardo Izquierdo. All rights reserved.
//

#include <cmath>

#include "VectorMatrix.h"
#include "random.h"
#include "Collide.h"

using namespace std;

class StretchReceptor {
public:
    
    StretchReceptor(int nSegs = 50, int nSR = 7, double SRgain = 0.0, double SRHeadgain = 0.0);

    void SetStretchReceptorParams(int nSegs, int nSR, double SRVNCgain, double SRHeadgain);
    
    void Update();
    
    void SetDorsalInput(int seg, double normlen){normSegLenD(seg) = normlen;};
    void SetVentralInput(int seg, double normlen){normSegLenV(seg) = normlen;};
    

    double HeadDorsalOutput(){return HD_sr;};
    double HeadVentralOutput(){return HV_sr;};
    double VCDorsalOutput(int i){return D_sr(i);};
    double VCVentralAOutput(int i){return VA_sr(i);};
    double VCVentralPOutput(int i){return VP_sr(i);};
    
    double NSR;
    double NSEGS;
    double NSEGSSR;
    double SRvncgain;
    double SRheadgain;
    double NSEGSHEADSTART,NSEGSHEAD, NSEGSVNCSTART;
    TVector<double> normSegLenD;
    TVector<double> normSegLenV;
    double HD_sr;
    double HV_sr;
    TVector<double> D_sr;
    TVector<double> VA_sr;
    TVector<double> VP_sr;
    
};


class ChemoReceptor {
public:
    VecXY foodpos;
    int target_nrn_idx;
    bool enabled = false;
    // AWA consts
    double alpha; double beta; double gamma;
    double kappa; double lambda;

    double max_distance;

    // storing value of fast and slow sense
    double F_i; double S_i;
    double F_im1; double S_im1;

    double C_ixy; double out_AWA_stim;

    void initialize(
        VecXY in_foodpos, 
        int in_target_nrn_idx, 
        double in_alpha, double in_beta, double in_gamma, 
        double in_kappa, double in_lambda, 
        double in_max_distance
    ){
        enabled = true;
        foodpos = in_foodpos;
        target_nrn_idx = in_target_nrn_idx;

        alpha = in_alpha; 
        beta = in_beta; 
        gamma = in_gamma;
        kappa = in_kappa; 
        lambda = in_lambda;

        max_distance = in_max_distance;

        F_im1 = 0.0;
        S_im1 = 0.0;
    }

    double get_concentration(VecXY headpos)
    {
        // TODO: make this more accurate -- corner distance, or full diffusion sim
        // set the concentration to zero if it is more than some max distance away
        // OPTIMIZE: make branchless by multiplying gradient by bool
        double food_dist_sqrd = dist_sqrd(headpos, foodpos);
        if (pow(dist_sqrd(headpos, foodpos), 0.5) > max_distance)
        {
            return 0.0;
        }
        else
        {
            return kappa * exp( food_dist_sqrd * lambda );
        }
    }


    /* 
    same function as `comp_sensory()` from 
    https://github.com/mivanit/CE_learning/blob/main/CE_learn/wormSim.py
    */
    double comp_sensory(VecXY headpos, double StepSize)
    {
        C_ixy = get_concentration(headpos);

        // iterate fast and slow sense
		F_i = F_im1 + StepSize * ( (alpha * C_ixy) - (beta * F_im1) );
		S_i = S_im1 + StepSize * ( gamma * (F_im1 - S_im1) );

        // update stim for AWA neuron
        out_AWA_stim = F_i - S_i;
        
        // update prev-timestep values
        F_im1 = F_i; S_im1 = S_i;

        // PRINTF_DEBUG("\n>> C_ixy: %f, F_i: %f, S_i: %f, out_AWA_stim: %f\n", C_ixy, F_i, S_i, out_AWA_stim)

        return out_AWA_stim;
    }
};

