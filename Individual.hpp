//
//  Individual.hpp
//  SF_P1_project
//
//  Created by Scott S Forer on 2/4/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Individual_hpp
#define Individual_hpp

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


class Individual
{
    friend class Parameters;
    friend class Q_Learner;
    friend class Arm;
    
protected:
    
    
public:
    vector<double> payout_sum;
    vector<int> num_of_pulls;
    vector<double> ave_arm_pay_out;
    vector<double> expected_reward;
    
    //storage
    vector<int> arms_pulled;
    vector<double> reward;
    
private:
};


#endif /* Individual_hpp */
