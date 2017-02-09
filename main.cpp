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
    cout << "TEST A" << endl;
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
    //cout << "cp" << endl;
    cout << endl;
    cout << endl;
}


//-------------------------------------------------------------------------
//Checks if the action value learner has a high likelihood of choosing the best arm
void Run_Test_B()
{
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "TEST B" << endl;
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
    //cout << "cp" << endl;
    cout << endl;
    cout << endl;
}



int main()
{
    srand(time(NULL));
    Run_Test_A();
    Run_Test_B();
    Parameters P;
    Q_Learner Q;
    Q.pP = &P;
    Q.Build_MAB();
    for (int sr=0; sr<100; sr++)
    {
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        cout << "SR" << "\t" << sr << endl;
        Q.Run_MAB();
        Q.Text_File_Functions();
        Q.Reset_Individual();
        cout << endl;
        cout << endl;
    }
}
