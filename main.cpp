//
//  main.cpp
//  SF_P1_project
//
//  Created by Scott S Forer on 2/2/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <ctime>
#include <random>

#include "Parameters.hpp"
#include "Individual.hpp"
#include "Arm.hpp"
#include "Q_Learner.hpp"


//-------------------------------------------------------------------------
//Checks for convergence
void Run_Test_A()
{
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "TEST A" << "\t";
    Parameters P;
    Parameters* pP;
    Q_Learner Q;
    Arm A;
    pP = &P;
    Q.pP = &P;
    pP->num_arms = 1;
    Q.Build_MAB();
    Q.Run_MAB();
    //cout << Q.indv.at(0).expected_reward.at(0) << endl;
    assert(Q.indv.at(0).expected_reward.at(0) > (Q.lever.at(0).mean - Q.lever.at(0).standard));
    assert(Q.indv.at(0).expected_reward.at(0) < (Q.lever.at(0).mean + Q.lever.at(0).standard));
    cout << "PASS" << endl;
    //cout << "cp" << endl;
    cout << endl;
    cout << endl;
}


//-------------------------------------------------------------------------
//Checks if the action value learner has a high likelihood of choosing the best arm
void Run_Test_B()
{
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "TEST B" << "\t";
    Parameters P;
    Parameters* pP;
    Q_Learner Q;
    Arm A;
    pP = &P;
    Q.pP = &P;
    Q.Build_MAB();
    Q.Run_MAB();
    int best_arm = 0;
    for (int a=1; a<pP->num_arms; a++)
    {
        if (Q.indv.at(0).expected_reward.at(best_arm) < Q.indv.at(0).expected_reward.at(a))
        {
            best_arm = a;
        }
    }
    for (int a=1; a<pP->num_arms; a++)
    {
        assert(Q.indv.at(0).expected_reward.at(best_arm) >= Q.indv.at(0).expected_reward.at(a));
    }
    cout << "PASS" << endl;
    //cout << "cp" << endl;
    cout << endl;
    cout << endl;
}


//-------------------------------------------------------------------------
//Writes the parameters to a txt file
void Write_Parameters_To_txt_File(Parameters* pP)
{
    ofstream File3;
    File3.open("Parameters.txt");
    File3 << pP->num_pulls << "\t" << pP->num_sr << "\t" << pP->num_arms << endl;
    File3.close();
}


int main()
{
    srand(time(NULL));
    Run_Test_A();
    Run_Test_B();
    Parameters P;
    Q_Learner Q;
    Q.pP = &P;
    Parameters* pP;
    pP = &P;
    
    Q.Build_MAB();
    Q.Delete_txt_Files();
    for (int sr=0; sr<pP->num_sr; sr++)
    {
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        cout << "SR" << "\t" << sr << endl;
        Q.Stat_Run();
        cout << endl;
        cout << endl;
    }
    Q.Get_Total_Times_Pulled();
    Q.Write_Percent_LH_To_txt_File();
    Write_Parameters_To_txt_File(pP);
}
