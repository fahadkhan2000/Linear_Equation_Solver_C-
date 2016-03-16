//
//  solver.h
//  Linear_Equation_Solver
//
//  Created by Fahad Ali Khan on 16/03/16.
//  Copyright (c) 2016 MapCase Media. All rights reserved.
//

#ifndef __Linear_Equation_Solver__solver__
#define __Linear_Equation_Solver__solver__

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <strings.h>

using namespace std;

class LES
{
private:
    int m_rows;
    int m_cols;
    char m_name[128];
    LES();
    
public:
    double **pData;
    LES(const char *name, int rows, int cols);
    LES(const LES &other);
    ~LES();
    void setName(const char *name);
    const char* getName() const;
    void getInput();
    void fillSimulatedInput();
    double detCalculate();
    LES cofactor();
    LES adjoint();
    LES transpose();
    LES inverse();
    LES& operator =(const LES &obj);
    LES operator +(const LES &obj);
    LES operator -(const LES &obj);
    LES operator *(const LES &obj);
    bool operator ==(const LES &obj);
    
    friend std::istream& operator>>(std::istream &is, LES &m);
    friend std::ostream& operator<<(std::ostream &os, const LES &m);
};



#endif /* defined(__Linear_Equation_Solver__solver__) */
