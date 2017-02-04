//
//  Q_Learner.hpp
//  SF_P1_project
//
//  Created by Scott S Forer on 2/4/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Q_Learner_hpp
#define Q_Learner_hpp

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


using namespace std;


class Q_Learner
{
    friend class Parameters;
    friend class Individual;
    friend class Arm;
    
protected:
    
    
public:
    Parameters* pP;
    
    vector<Individual> indv;
    vector<Arm> lever;
    
    void Build_Agent();
    void Build_Arms();
    void Build_MAB();
    void Run_Pull();
    void Run_MAB();
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Builds agent
void Q_Learner::Build_Agent()
{
    for (int i=0; i<pP->num_agents; i++)
    {
        Individual I;
        indv.push_back(I);
    }
}


//-------------------------------------------------------------------------
//Builds arms
void Q_Learner::Build_Arms()
{
    for (int a=0; a<pP->num_arms; a++)
    {
        Arm A;
        lever.push_back(A);
        lever.at(a).arm_number = a;
        lever.at(a).arm_value = 0;
        //need to build the rest of the arm values
    }
}


//-------------------------------------------------------------------------
//Builds MAB
void Q_Learner::Build_MAB()
{
    Build_Agent();
    Build_Arms();
}



//-------------------------------------------------------------------------
//Builds MAB
void Q_Learner::Run_Pull()
{
    
}


//-------------------------------------------------------------------------
//Runs the entire MAB
void Q_Learner::Run_MAB()
{
    Build_MAB();
    for (int p=0; p<pP->num_pulls; p++)
    {
        Run_Pull();
    }
}

#endif /* Q_Learner_hpp */
