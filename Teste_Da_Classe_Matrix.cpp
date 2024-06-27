#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include "vector.h"
#include "point.h"
#include "ray.h"
#include "matrix.h"
using namespace std;

int main(){

    Matrix matrix = Matrix();

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            double x;
            cin >> x;
            matrix.elements[i][j] = x;
        }
    }

    matrix.create_inverse();
    cout << endl;
    cout << endl;

   for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << matrix.elements_inverse[i][j] << "       ";
        }
        cout << endl;
    }

    return 0;
}