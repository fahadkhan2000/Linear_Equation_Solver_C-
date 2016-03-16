//
//  main.cpp
//  Linear_Equation_Solver
//
//  Created by Fahad Ali Khan on 16/03/16.
//  Copyright (c) 2016 MapCase Media. All rights reserved.
//

#include <iostream>
#include "solver.h"

using namespace std;

int main(int argc, const char * argv[])
{
    LES a("A", 6, 6);
    LES b("B", 6, 1);
    
    a.fillSimulatedInput();
    b.fillSimulatedInput();
    
    cout << a << "\n Determinant : ";
    cout << a.detCalculate() << "\n";
    cout << b << "\n Determinant : ";
    cout << b.detCalculate() << "\n";
    
    LES ainv = a.inverse();
    LES q = a * ainv;
    q.setName("A * A'");
    cout << q << "\n";
    
    LES x = ainv * b;
    x.setName("X");
    cout << x << "\n";
    
    LES y = a * x;
    y.setName("Y");
    cout << y << "\n";
    
    return 0;
}
