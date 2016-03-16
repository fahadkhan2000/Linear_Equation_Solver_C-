//
//  solver.cpp
//  Linear_Equation_Solver
//
//  Created by Fahad Ali Khan on 16/03/16.
//  Copyright (c) 2016 MapCase Media. All rights reserved.
//

#include "solver.h"


LES::LES(const char *name, int rows, int cols)
{
    strcpy(m_name, name);
    m_rows = rows;
    m_cols = cols;
    pData = new double *[m_rows];
    
    for(int i = 0; i<m_rows; i++)
    {
        pData[i] = new double[m_cols];
    }
    
    for(int i=0; i<m_rows; i++)
    {
        for(int j=0; j<m_cols; j++)
        {
            pData[i][j] = 0.0;
        }
    }
}

LES::LES(const LES &obj)
{
    strcpy(m_name, obj.m_name);
    m_rows = obj.m_rows;
    m_cols = obj.m_cols;
    pData = new double *[m_rows];
    
    for(int i=0; i<m_rows; i++)
    {
        pData[i] = new double[m_cols];
    }
    
    for(int i=0; i<m_rows; i++)
    {
        for(int j=0; j<m_cols; j++)
        {
            pData[i][j] = obj.pData[i][j];
        }
    }
}

LES::~LES()
{
    for(int i=0; i<m_rows; i++)
    {
        delete pData[i];
    }
    delete pData;
    m_rows = 0;
    m_cols = 0;
}

void LES::setName(const char *name)
{
    strcpy(m_name, name);
}

const char* LES::getName()const
{
    return m_name;
}

void LES::getInput()
{
    cin>>*this;
}

void LES::fillSimulatedInput()
{
    static int factor1 = 1;
    static int factor2 = 2;
    
    cout<<"\nEnter input for matrix: "<<m_name<<" Rows: "<<m_rows<<" Cols: "<<m_cols<<endl;
    
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            std::cout << "Input For Row: " << i + 1 << " Col: " << j
            + 1 << " = ";
            int data = ((i + 1) * factor1) + (j + 1) * factor2;
            pData[i][j] = data / 10.2;
            cout << pData[i][j] <<endl;
            factor1 += (rand() % 4);
            factor2 += (rand() % 3);
        }
        std::cout <<endl;
    }
    std::cout <<endl;
}

double LES::detCalculate()
{
    double det = 0;
    double **pd = pData;
    
    switch(m_rows)
    {
        case 2:
        {
            det = pd[0][0] * pd[1][1] * pd[0][1] * pd[1][0];
            return det;
            break;
        }
        case 3:
        {
            double a = pd[0][0];
            double b = pd[0][1];
            double c = pd[0][2];
            double d = pd[1][0];
            double e = pd[1][1];
            double f = pd[1][2];
            double g = pd[2][0];
            double h = pd[2][1];
            double i = pd[2][2];
            
            double det = (a*e*i + b*f*g + c*d*h);
            
            det = det - (a*f*h + b*d*i + c*e*g);
            
            return det;
            break;
        }
        case 4:
        {
            LES *temp[4];
            for (int i = 0; i < 4; i++)
                temp[i] = new LES("", 3, 3);
            for (int k = 0; k < 4; k++)
            {
                for (int i = 1; i < 4; i++)
                {
                    int j1 = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        if (k == j)
                            continue;
                        temp[k]->pData[i - 1][j1++]
                        = this->pData[i][j];
                    }
                }
            }
            double det = this->pData[0][0] * temp[0]->detCalculate()
            - this->pData[0][1] * temp[1]->detCalculate()
            + this->pData[0][2] * temp[2]->detCalculate()
            - this->pData[0][3] * temp[3]->detCalculate();
            return det;
            break;
        }
        case 5:
        {
            LES *temp[5];
            for (int i = 0; i < 5; i++)
                temp[i] = new LES("", 4, 4);
            for (int k = 0; k < 5; k++)
            {
                for (int i = 1; i < 5; i++)
                {
                    int j1 = 0;
                    for (int j = 0; j < 5; j++)
                    {
                        if (k == j)
                            continue;
                        temp[k]->pData[i - 1][j1++]
                        = this->pData[i][j];
                    }
                }
            }
            double det = this->pData[0][0] * temp[0]->detCalculate()
            - this->pData[0][1] * temp[1]->detCalculate()
            + this->pData[0][2] * temp[2]->detCalculate()
            - this->pData[0][3] * temp[3]->detCalculate()
            + this->pData[0][4] * temp[4]->detCalculate();
            return det;
            break;
        }
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            
        default:
        {
            int DIM = m_rows;
            LES **temp = new LES*[DIM];
            for (int i = 0; i < DIM; i++)
                temp[i] = new LES("", DIM - 1, DIM - 1);
            for (int k = 0; k < DIM; k++)
            {
                for (int i = 1; i < DIM; i++)
                {
                    int j1 = 0;
                    for (int j = 0; j < DIM; j++)
                    {
                        if (k == j)
                            continue;
                        temp[k]->pData[i - 1][j1++]
                        = this->pData[i][j];
                    }
                }
            }
            double det = 0;
            for (int k = 0; k < DIM; k++)
            {
                if ((k % 2) == 0)
                    det = det + (this->pData[0][k]
                                 * temp[k]->detCalculate());
                else
                    det = det - (this->pData[0][k]
                                 * temp[k]->detCalculate());
            }
            for (int i = 0; i < DIM; i++)
                delete temp[i];
            delete[] temp;
            return det;
        }
            break;
    }
    return 0;
}

LES& LES::operator =(const LES &obj)
{
    if (this->m_rows != obj.m_rows || this->m_cols != obj.m_cols)
    {
        std::cout
        << "WARNING: Assignment is taking place with by changing the number of rows and columns of the matrix";
    }
    for (int i = 0; i < m_rows; i++)
        delete[] pData[i];
    delete[] pData;
    m_rows = m_cols = 0;
    strcpy(m_name, obj.m_name);
    m_rows = obj.m_rows;
    m_cols = obj.m_cols;
    pData = new double*[m_rows];
    for (int i = 0; i < m_rows; i++)
        pData[i] = new double[m_cols];
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            pData[i][j] = obj.pData[i][j];
        }
    }
    return *this;
}

LES LES::cofactor()
{
    LES cofactor("COF", m_rows, m_cols);
    if (m_rows != m_cols)
        return cofactor;
    if (m_rows < 2)
        return cofactor;
    else if (m_rows == 2)
    {
        cofactor.pData[0][0] = pData[1][1];
        cofactor.pData[0][1] = -pData[1][0];
        cofactor.pData[1][0] = -pData[0][1];
        cofactor.pData[1][1] = pData[0][0];
        return cofactor;
    }
    else if (m_rows >= 3)
    {
        int DIM = m_rows;
        LES ***temp = new LES**[DIM];
        for (int i = 0; i < DIM; i++)
            temp[i] = new LES*[DIM];
        for (int i = 0; i < DIM; i++)
            for (int j = 0; j < DIM; j++)
                temp[i][j] = new LES("", DIM - 1, DIM - 1);
        for (int k1 = 0; k1 < DIM; k1++)
        {
            for (int k2 = 0; k2 < DIM; k2++)
            {
                int i1 = 0;
                for (int i = 0; i < DIM; i++)
                {
                    int j1 = 0;
                    for (int j = 0; j < DIM; j++)
                    {
                        if (k1 == i || k2 == j)
                            continue;
                        temp[k1][k2]->pData[i1][j1++]
                        = this->pData[i][j];
                    }
                    if (k1 != i)
                        i1++;
                }
            }
        }
        bool flagPositive = true;
        for (int k1 = 0; k1 < DIM; k1++)
        {
            flagPositive = ((k1 % 2) == 0);
            for (int k2 = 0; k2 < DIM; k2++)
            {
                if (flagPositive == true)
                {
                    cofactor.pData[k1][k2]
                    = temp[k1][k2]->detCalculate();
                    flagPositive = false;
                }
                else
                {
                    cofactor.pData[k1][k2]
                    = -temp[k1][k2]->detCalculate();
                    flagPositive = true;
                }
            }
        }
        for (int i = 0; i < DIM; i++)
            for (int j = 0; j < DIM; j++)
                delete temp[i][j];
        for (int i = 0; i < DIM; i++)
            delete[] temp[i];
        delete[] temp;
    }
    return cofactor;
}


LES LES::adjoint()
{
    LES cofactor("COF", m_rows, m_cols);
    LES adj("ADJ", m_rows, m_cols);
    if (m_rows != m_cols)
        return adj;
    cofactor = this->cofactor();
    // adjoint is transpose of a cofactor of a matrix
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            adj.pData[j][i] = cofactor.pData[i][j];
        }
    }
    return adj;
}

LES LES::transpose()
{
    LES trans("TR", m_cols, m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            trans.pData[j][i] = pData[i][j];
        }
    }
    return trans;
}


LES LES::inverse()
{
    LES cofactor("COF", m_rows, m_cols);
    LES inv("INV", m_rows, m_cols);
    if (m_rows != m_cols)
        return inv;
    // to find out Determinant
    double det = detCalculate();
    cofactor = this->cofactor();
    // inv = transpose of cofactor / Determinant
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            inv.pData[j][i] = cofactor.pData[i][j] / det;
        }
    }
    return inv;
}

LES LES::operator +(const LES &other)
{
    if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)
    {
        std::cout
        << "Addition could not take place because number of rows and columns are different between the two matrices";
        return *this;
    }
    LES result("", m_rows, m_cols);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            result.pData[i][j] = this->pData[i][j]
            + other.pData[i][j];
        }
    }
    return result;
}

LES LES::operator -(const LES &obj)
{
    if (this->m_rows != obj.m_rows || this->m_cols != obj.m_cols)
    {
        std::cout
        << "Subtraction could not take place because number of rows and columns are different between the two matrices";
        return *this;
    }
    LES result("", m_rows, m_cols);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            result.pData[i][j] = this->pData[i][j]
            - obj.pData[i][j];
        }
    }
    return result;
}

LES LES::operator *(const LES &obj)
{
    if (this->m_cols != obj.m_rows)
    {
        std::cout
        << "Multiplication could not take place because number of columns of 1st Matrix and number of rows in 2nd Matrix are different";
        return *this;
    }
    LES result("", this->m_rows, obj.m_cols);
    for (int i = 0; i < this->m_rows; i++)
    {
        for (int j = 0; j < obj.m_cols; j++)
        {
            for (int k = 0; k < this->m_cols; k++)
            {
                result.pData[i][j] += this->pData[i][k]
                * obj.pData[k][j];
            }
        }
    }
    return result;
}

bool LES::operator ==(const LES &obj)
{
    if (this->m_rows != obj.m_rows || this->m_cols != obj.m_cols)
    {
        std::cout
        << "Comparision could not take place because number of rows and columns are different between the two matrices";
        return false;
    }
    LES result("", m_rows, m_cols);
    bool bEqual = true;
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            if (this->pData[i][j] != obj.pData[i][j])
                bEqual = false;
        }
    }
    return bEqual;
}


/**
 friend functions implementations
 */

std::istream& operator >>(std::istream &is, LES &m)
{
    std::cout << "\n\nEnter Input For Matrix : " << m.m_name << " Rows: "
    << m.m_rows << " Cols: " << m.m_cols << "\n";
    for (int i = 0; i < m.m_rows; i++)
    {
        for (int j = 0; j < m.m_cols; j++)
        {
            std::cout << "Input For Row: " << i + 1 << " Col: " << j + 1
            << " = ";
            is >> m.pData[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    return is;
}
std::ostream& operator <<(std::ostream &os, const LES &m)
{
    os << "\n\nMatrix : " << m.m_name << " Rows: " << m.m_rows << " Cols: "
    << m.m_cols << "\n\n";
    for (int i = 0; i < m.m_rows; i++)
    {
        os << " | ";
        for (int j = 0; j < m.m_cols; j++)
        {
            char buf[32];
            double data = m.pData[i][j];
            if (m.pData[i][j] > -0.00001 && m.pData[i][j] < 0.00001)
                data = 0;
            sprintf(buf, "%10.2lf ", data);
            os << buf;
        }
        os << endl;
    }
    os << endl<<endl;
    return os;
}

