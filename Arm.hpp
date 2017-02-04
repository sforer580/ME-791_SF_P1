//
//  Arm.hpp
//  SF_P1_project
//
//  Created by Scott S Forer on 2/4/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Arm_hpp
#define Arm_hpp

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


class Arm
{
    friend class Parameters;
    friend class Individual;
    friend class Q_Learner;
    
protected:
    
    
public:
    int arm_number;
    double arm_value;
    double alpha = 1;
    double epsilon = 1;
    double sigma;
    double mean;
    
private:
};

#endif /* Arm_hpp */
