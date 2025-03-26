#include <iostream>
#include <vector>
using namespace std;

// Function to calculate Lagrange interpolation and print Li(x)
double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double xp) {
    int n = x.size();
    double yp = 0.0;
    
    for (int i = 0; i < n; i++) {
        double term = y[i];
        double Li = 1.0; // Initialize Li(x)
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                 Li *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        term*=Li;
        cout << "L" << i << "(" << xp << ") = " << Li << endl; // Print Li(x)
        yp += term;
    }
    return yp;
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;
    
    vector<double> x(n), y(n);
    cout << "Enter the x values: ";
    for (int i = 0; i < n; i++) cin >> x[i];
    
    cout << "Enter the corresponding y values: ";
    for (int i = 0; i < n; i++) cin >> y[i];
    
    cout << "The Lagrange Polynomial is constructed.\n";
    
    double xp;
    cout << "Enter the point at which you need the value of the function: ";
    cin >> xp;
    
    double yp = lagrangeInterpolation(x, y, xp);
    cout << "The value of the function at x = " << xp << " is: " << yp << endl;
    
    return 0;
}
