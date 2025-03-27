
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 void solveTridiagonal(vector<double>& a, vector<double>& b, vector<double>& c, 
                     vector<double>& d, int n) {
    vector<double> alphaV(n, 0);
    vector<double> betaV(n, 0);
    vector<double> x(n, 0);
    alphaV[0] = b[0];
    for(int i = 1; i < n; i++) {
        alphaV[i] = b[i] - (a[i] * c[i-1]) / alphaV[i-1];
    }
    betaV[0] = d[0]/b[0];
    for(int i = 1; i < n; i++) {
        betaV[i] = (d[i] - a[i] * betaV[i-1]) / alphaV[i];
    }
    x[n-1] = betaV[n-1];
    for(int i = n-2; i >= 0; i--) {
        x[i] = betaV[i] - (c[i] * x[i+1]) / alphaV[i];
    }
    cout << "\nSolution of the tridiagonal system of equations:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "alpha" << i+1 << " = " << alphaV[i] << " ,";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        cout << "beta" << i+1 << " = " << betaV[i] << " ,";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        cout << "x" << i+1 << " = " << x[i] << " ,";
           }
    cout << endl;
                     }
int main() {
    int n;
    cout << "Enter number of variables (>= 3): ";
    cin >> n;
    
    if(n < 3) {
        cout << "Number of variables must be >= 3" << endl;
        return 1;
    }
    
    vector<double> a(n,0), b(n,0), c(n,0), d(n,0);
    
    cout << "\nEnter main diagonal elements (b):" << endl;
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    cout << "Enter lower diagonal elements (a):" << endl;
    for(int i = 1; i < n; i++) {
        cin >> a[i];
    }
    
    cout << "Enter upper diagonal elements (c):" << endl;
    for(int i = 0; i < n-1; i++) {
        cin >> c[i];
    }
    
    cout << "Enter RHS vector elements (d):" << endl;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }
    
    solveTridiagonal(a, b, c, d, n);
    return 0;
}