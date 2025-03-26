#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

// Define the function to be integrated
double function(double x) {
    return cos(2*x)/(1+sin(x)); // Example function: f(x) = x^2
}

// Function to compute Legendre polynomial roots and weights for given n (precomputed for common cases)
void getLegendreRootsWeights(int n, vector<double>& t_k, vector<double>& lambda_k) {
    if (n == 2) {
        t_k= {-0.5773502692, 0.5773502692};
        lambda_k = {1.0, 1.0};
    } else if (n == 3) {
        t_k = {-0.7745966692, 0.0, 0.7745966692};
           lambda_k= {0.5555555556, 0.8888888889, 0.5555555556};
    } else if (n == 4) {
        t_k= {-0.8611363116, -0.3399810436, 0.3399810436, 0.8611363116};
        lambda_k = {0.3478548451, 0.6521451549, 0.6521451549, 0.3478548451};
    } else {
        cout << "Quadrature points beyond 4 are not precomputed.\n";
        exit(1);
    }
}

// Gauss-Legendre Quadrature function
double gaussLegendreQuadrature(double a, double b, int n) {
    vector<double> t_k, lambda_k;
    getLegendreRootsWeights(n, t_k, lambda_k);
    
    double integral = 0.0;
    for (int i = 0; i < n; i++) {
        double x_k = 0.5 * (b - a) * t_k[i] + 0.5 * (b + a);
        integral += lambda_k[i] * function(x_k);
    }
    return 0.5 * (b - a) * integral;
}

int main() {
    double a, b;
    int n;
    
    cout << "Enter the lower limit of integration: ";
    cin >> a;
    cout << "Enter the upper limit of integration: ";
    cin >> b;
    cout << "Enter the number of quadrature points (2, 3, or 4): ";
    cin >> n;
    
    vector<double> t_k, lambda_k;
    getLegendreRootsWeights(n, t_k,lambda_k);
    
    cout << "Legendre Polynomial Roots: ";
    for (double root : t_k) cout << root << " ";
    cout << "\n";
    
    double result = gaussLegendreQuadrature(a, b, n);
    cout << "Value of the integral: " << fixed << setprecision(6) << result << "\n";
    
    return 0;
}