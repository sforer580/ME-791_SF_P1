//
//  Parameters.hpp
//  SF_P1_project
//
//  Created by Scott S Forer on 2/4/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp

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


class Parameters
{
    friend class Individual;
    friend class Q_Learner;
    friend class Arm;
    
protected:
    
    
public:
    int num_agents = 1;
    int num_arms = 10;
    int num_pulls = 1000;
    double min_pay = 5;                     //[reward]
    double max_pay = 80;                    //[reward]
    double stdv = 5;
    double epsilon = 0.1;
    double alpha = 0.1;
    
private:
};

#endif /* Parameters_hpp */
