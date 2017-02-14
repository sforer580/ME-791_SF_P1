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
    void Load_Arm_Data();
    void Build_MAB();
    int Smart_Pull();
    int Random_Pull();
    void Get_Payout_Info(int arm);
    void Update_Expected_Reward(int arm);
    void Run_Pull(int p);
    void Agent_Data();
    void Arm_Data();
    void Get_Total_Times_Pulled();
    void Reset_Individual();
    void Write_Arms_Pulled_To_txt_File();
    void Write_Rewards_To_txt_File();
    void Write_Percent_LH_To_txt_File();
    void Write_Arm_Data_To_txt_File();
    void Delete_txt_Files();
    void Text_File_Functions();
    void Run_MAB();
    void Stat_Run();
    
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
        for (int a=0; a<pP->num_arms; a++)
        {
            indv.at(i).payout_sum.push_back(0);
            indv.at(i).num_of_pulls.push_back(0);
            indv.at(i).ave_arm_pay_out.push_back(0);
            indv.at(0).expected_reward.push_back(100);
        }
        for (int p=0; p<pP->num_pulls; p++)
        {
            for (int a=0; a< pP->num_arms; a++)
            {
                indv.at(0).total_times_pulled.push_back(0);
                indv.at(0).percent_LH.push_back(0);
            }
        }
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
        lever.at(a).payout = 0;
        //need to build the rest of the arm values
        double r = (double)rand() / (double)RAND_MAX;
        lever.at(a).mean = pP->min_pay + r * (pP->max_pay - pP->min_pay);
        lever.at(a).standard = ((double) rand() / (RAND_MAX)) * pP->stdv;
    }
}


//-------------------------------------------------------------------------
//Loads Arm data
void Q_Learner::Load_Arm_Data()
{
    if (pP->load_arm_data == 1)
    {
        ifstream ifile("Arm_data.txt", ios::in);
        vector<double> sw;
        
        //check to see that the file was opened correctly:
        if (!ifile.is_open())
        {
            cerr << "There was a problem opening the input file!\n";
            exit(1);//exit or do additional error checking
        }
        double num = 0.0;
        //keep storing values from the text file so long as data exists:
        while (ifile >> num)
        {
            sw.push_back(num);
        }
        int c = 0;
        for (int a=0; a<pP->num_arms; a++)
        {
            lever.at(a).arm_number = sw.at(c);
            lever.at(a).payout = sw.at(c+1);
            lever.at(a).mean = sw.at(c+2);
            lever.at(a).standard = sw.at(c+3);
            c += 4;
        }
    }
}


//-------------------------------------------------------------------------
//Builds MAB
void Q_Learner::Build_MAB()
{
    Build_Agent();
    Build_Arms();
    Load_Arm_Data();
}


//-------------------------------------------------------------------------
//Runs the optimal pull
int Q_Learner::Smart_Pull()
{
    //cout << "TYPE OF PULL" << "\t" << "Smart" << endl;
    //gets the best arm number based on the expected reward for each arm
    int best_arm = 0;
    const double e = numeric_limits<double>::min();
    for (int a=1; a<pP->num_arms; a++)
    {
        if (indv.at(0).expected_reward.at(best_arm) < indv.at(0).expected_reward.at(a))
        {
            best_arm = a;
        }
    }
    
    lever.at(best_arm).payout = 0;
    //Box-Muller Transform
    double u1 = 0;
    double u2 = 0;
    double z0 = 0;
    double z1 = 0;
    while (u1 <= e)
    {
        u1 = ((double) rand() / (RAND_MAX));
        u2 = ((double) rand() / (RAND_MAX));
    }
    //cout << u1 << endl;
    //cout << u2 << endl;
    z0 = sqrt(-2.0 * log(u1)) * cos((2*3.14159) * u2);
    //cout << z0 << endl;
    z1 = sqrt(-2.0 * log(u1)) * sin((2*3.14159) * u2);
    double sigma = lever.at(best_arm).standard;
    double mu = lever.at(best_arm).mean;
    lever.at(best_arm).payout = z0 * sigma + mu;
    //cout << "check" << "\t" << sigma << "\t" << mu << "\t" << lever.at(best_arm).payout << endl;
    return best_arm;
}


//-------------------------------------------------------------------------
//Runs the random pull
int Q_Learner::Random_Pull()
{
    //cout << "TYPE OF PULL" << "\t" << "RANDOM" << endl;
    int rr = rand() % pP->num_arms;
    lever.at(rr).payout = 0;
    const double e = numeric_limits<double>::min();
    
    //Box-Muller Transform
    double u1 = 0;
    double u2 = 0;
    double z0 = 0;
    double z1 = 0;
    while (u1 <= e)
    {
        u1 = ((double) rand() / (RAND_MAX));
        u2 = ((double) rand() / (RAND_MAX));
    }
    //cout << u1 << endl;
    //cout << u2 << endl;
    z0 = sqrt(-2.0 * log(u1)) * cos((2*3.14159) * u2);
    //cout << z0 << endl;
    //z1 = sqrt(-2.0 * log(u1)) * sin((2*3.14159) * u2);
    double sigma = lever.at(rr).standard;
    double mu = lever.at(rr).mean;
    lever.at(rr).payout = z0 * sigma + mu;
    //cout << "check" << "\t" << sigma << "\t" << mu << "\t" << lever.at(rr).payout << endl;
    return rr;
}


//-------------------------------------------------------------------------
//Gives the payout to the agent
void Q_Learner::Get_Payout_Info(int arm)
{
    //updates the number of pulls on an arm
    double n = 0;
    indv.at(0).num_of_pulls.at(arm) += 1;
    n = indv.at(0).num_of_pulls.at(arm);
    
    //updates the payout sum of an arm
    double pay = 0;
    pay = lever.at(arm).payout;
    indv.at(0).payout_sum.at(arm) += pay;
    
    //gets the average payout for that arm
    double sum = 0;
    sum = indv.at(0).payout_sum.at(arm);
    indv.at(0).ave_arm_pay_out.at(arm) = sum/n;
    
    //saves the payout info to a vector for book keeping
    indv.at(0).arms_pulled.push_back(arm);
    indv.at(0).reward.push_back(pay);
    
    //cout << "ARM" << "\t" << arm << "\t";
    //cout << "NUMBER OF PULLS" << "\t" << indv.at(0).num_of_pulls.at(arm) << "\t";
    //cout << "PAYOUT" << "\t" << pay << "\t";
    //cout << "AVE PAYOUT" << "\t" << indv.at(0).ave_arm_pay_out.at(arm) << "\t";
    //cout << "EXPECTED PAYOUT" << "\t" << indv.at(0).expected_reward.at(arm) << "\t";
}


//-------------------------------------------------------------------------
//Updates the expected reward for that arm
void Q_Learner::Update_Expected_Reward(int arm)
{
    indv.at(0).expected_reward.at(arm) = lever.at(arm).payout*pP->alpha + indv.at(0).expected_reward.at(arm)*(1-pP->alpha);
    //cout << "NEW EXPECTED PAYOUT" << "\t" << indv.at(0).expected_reward.at(arm) << endl;
}

//-------------------------------------------------------------------------
//Runs the pull functions
void Q_Learner::Run_Pull(int p)
{
    double r = ((double) rand() / (RAND_MAX));
    if (p > 1)
    {
        int arm = 0;
        if (r <= (1 - pP->epsilon))
        {
            arm = Smart_Pull();
            Get_Payout_Info(arm);
            Update_Expected_Reward(arm);
        }
        else
        {
            arm = Random_Pull();
            Get_Payout_Info(arm);
            Update_Expected_Reward(arm);
        }
    }
    else
    {
        int arm = 0;
        arm = Random_Pull();
        Get_Payout_Info(arm);
        Update_Expected_Reward(arm);
    }
}

//-------------------------------------------------------------------------
//Resets the individual
void Q_Learner::Reset_Individual()
{
    for (int i=0; i<pP->num_agents; i++)
    {
        for (int a=0; a<pP->num_arms; a++)
        {
            indv.at(i).payout_sum.at(a) = 0;
            indv.at(i).num_of_pulls.at(a) = 0;
            indv.at(i).ave_arm_pay_out.at(a) = 0;
            indv.at(i).expected_reward.at(a) = 100;
        }
        indv.at(i).reward.clear();
        for (int p=0; p<pP->num_pulls; p++)
        {
            indv.at(0).all_arms_pulled.push_back(indv.at(0).arms_pulled.at(p));
        }
        indv.at(i).arms_pulled.clear();
    }
}


//-------------------------------------------------------------------------
//Outputs the agent data
void Q_Learner::Agent_Data()
{
    //cout << "----------------------------------------------------------" << endl;
    //cout << "AGENT DATA" << endl;
    for (int a=0; a<pP->num_arms; a++)
    {
        //cout << "ARM" << "\t" << a << "\t" << "MEAN" << "\t" << indv.at(0).ave_arm_pay_out.at(a) << endl;
    }
    //cout << endl;
}


//-------------------------------------------------------------------------
//Outputs the arm data
void Q_Learner::Arm_Data()
{
    int best = 0;
    for (int a=0; a<pP->num_arms; a++)
    {
        if (lever.at(best).mean < lever.at(a).mean)
        {
            best = a;
        }
    }
    //cout << "----------------------------------------------------------" << endl;
    //cout << "ARM DATA" << endl;
    cout << "BEST ARM" << "\t" << best << "\t" << "MEAN" << "\t" << lever.at(best).mean << "\t" << "SIGMA" <<  "\t" << lever.at(best).standard << endl;
    for (int a=0; a<pP->num_arms; a++)
    {
        cout << "ARM" << "\t" << a << "\t" << "MEAN" << "\t" << lever.at(a).mean << "\t" << "SIGMA" <<  "\t" << lever.at(a).standard << endl;
    }
    
}


//-------------------------------------------------------------------------
//Gets the total amount of times when an arm was pulled in a stat run
void Q_Learner::Get_Total_Times_Pulled()
{
    for (int a=0; a<pP->num_arms; a++)
    {
        for (int s=0; s<pP->num_sr; s++)
        {
            for (int p=0; p<pP->num_pulls; p++)
            {
                if (indv.at(0).all_arms_pulled.at(s*pP->num_pulls+p) == a)
                {
                    indv.at(0).total_times_pulled.at(pP->num_pulls*a+p) += 1;
                }
            }
        }
    }
    
    int c = 0;
    for (int a=0; a<pP->num_arms; a++)
    {
        for (int p=0; p<pP->num_pulls; p++)
        {
            indv.at(0).percent_LH.at(c) = indv.at(0).total_times_pulled.at(c)/pP->num_sr;
            c += 1;
        }
    }
    
    /*
    cout << "TOTAL TIMES PULLED" << endl;
    int c = 0;
    for (int a=0; a<pP->num_arms; a++)
    {
        cout << "ARM" << "\t" << a << endl;
        for (int p=0; p<pP->num_pulls; p++)
        {
            cout << indv.at(0).total_times_pulled.at(c) << "\t";
            c += 1;
        }
        cout << endl;
    }
    cout << endl;
    */
}


//-------------------------------------------------------------------------
//Writes the arms that were pulled to a txt file
void Q_Learner::Write_Arms_Pulled_To_txt_File()
{
    ofstream File1;
    File1.open("Arms_Pulled.txt", ios_base::app);
    for (int p=0; p<pP->num_pulls; p++)
    {
        File1 << indv.at(0).arms_pulled.at(p) << "\t";
    }
    File1 << endl;
    File1.close();
}


//-------------------------------------------------------------------------
//Writes the arms that were pulled to a txt file
void Q_Learner::Write_Rewards_To_txt_File()
{
    ofstream File2;
    File2.open("Rewards.txt", ios_base::app);
    for (int p=0; p<pP->num_pulls; p++)
    {
        File2 << indv.at(0).reward.at(p) << "\t";
    }
    File2 << endl;
    File2.close();
}


//-------------------------------------------------------------------------
//Writes the percent likelihood that each arm is pulled to a txt file
void Q_Learner::Write_Percent_LH_To_txt_File()
{
    ofstream File4;
    File4.open("Percent_LH.txt");
    int c = 0;
    for (int a=0; a<pP->num_arms; a++)
    {
        for (int p=0; p<pP->num_pulls; p++)
        {
            File4 << indv.at(0).percent_LH.at(c) << "\t";
            c += 1;
        }
    }
}
        
        
//-------------------------------------------------------------------------
//Writes the arm data to a txt file
void Q_Learner::Write_Arm_Data_To_txt_File()
{
    if (pP->save_arm_data == 1)
    {
        ofstream File5;
        File5.open("Arm_Data.txt");
        for (int a=0; a<pP->num_arms; a++)
        {
            lever.at(a).payout = 0;
            File5 << lever.at(a).arm_number << "\t" << lever.at(a).payout << "\t" << lever.at(a).mean << "\t" << lever.at(a).standard << endl;
        }
    }
}


//-------------------------------------------------------------------------
//Runs the text file functions
void Q_Learner::Delete_txt_Files()
{
    if( remove( "Rewards.txt" ) != 0 )
        perror( "ERROR DELETING FILE" );
    else
        puts( "Rewards FILE SUCCEDDFULLY DELETED" );
    
    if( remove( "Arms_Pulled.txt" ) != 0 )
        perror( "ERROR DELETING FILE" );
    else
        puts( "Arms_Pulled FILE SUCCEDDFULLY DELETED" );
    cout << endl;
    cout << endl;
}
        
        


//-------------------------------------------------------------------------
//Runs the text file functions
void Q_Learner::Text_File_Functions()
{
    Write_Arms_Pulled_To_txt_File();
    Write_Rewards_To_txt_File();
}


//-------------------------------------------------------------------------
//Runs the entire MAB
void Q_Learner::Run_MAB()
{
    for (int p=0; p<pP->num_pulls; p++)
    {
        //cout << "PULL" << "\t" << p << endl;
        Run_Pull(p);
        //cout << endl;
    }
    Agent_Data();
    Arm_Data();
}


//-------------------------------------------------------------------------
//Runs a stat run
void Q_Learner::Stat_Run()
{
    Run_MAB();
    Text_File_Functions();
    Reset_Individual();
}

#endif /* Q_Learner_hpp */
