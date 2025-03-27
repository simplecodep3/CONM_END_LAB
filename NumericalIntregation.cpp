#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

// Function values at different x points
vector<double> x_values, f_values;

// Function to find f(x) for a given x
double function(double x) {
    for (size_t i = 0; i < x_values.size(); i++) {
        if (x == x_values[i]) return f_values[i];
    }
    return 0.0; // Default return value if x is not found
}

// Trapezoidal Rule
double trapezoidalRule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (function(a) + function(b));
    for (int i = 1; i < n; i++) {
        sum += function(a + i * h);
    }
    return h * sum;
}

// Simpson's 1/3 Rule (only applies if n is even)
double simpsonsOneThirdRule(double a, double b, int n) {
    if (n % 2 != 0) {
        cout << "Simpson’s 1/3 Rule requires an even n. Skipping.\n";
        return 0.0;
    }
    double h = (b - a) / n;
    double sum = function(a) + function(b);
    for (int i = 1; i < n; i++) {
        sum += (i % 2 == 0 ? 2 : 4) * function(a + i * h);
    }
    return (h / 3) * sum;
}

// Simpson's 3/8 Rule (only applies if n is a multiple of 3)
double simpsonsThreeEighthRule(double a, double b, int n) {
    if (n % 3 != 0) {
        cout << "Simpson’s 3/8 Rule requires n to be a multiple of 3. Skipping.\n";
        return 0.0;
    }
    double h = (b - a) / n;
    double sum = function(a) + function(b);
    for (int i = 1; i < n; i++) {
        sum += (i % 3 == 0 ? 2 : 3) * function(a + i * h);
    }
    return (3 * h / 8) * sum;
}

int main() {
    double a, b;
    int choice, n, num_points;
    
    cout << "Enter the number of data points: ";
    cin >> num_points;
    x_values.resize(num_points);
    f_values.resize(num_points);
    
    cout << "Enter the x values: ";
    for (int i = 0; i < num_points; i++) cin >> x_values[i];
    
    cout << "Enter the corresponding f(x) values: ";
    for (int i = 0; i < num_points; i++) cin >> f_values[i];
    
    cout << "Enter the lower limit of integration: ";
    cin >> a;
    cout << "Enter the upper limit of integration: ";
    cin >> b;
    cout << "Enter the number of sub-intervals: ";
    cin >> n;
    
    cout << "Select a numerical integration method:\n";
    cout << "1. Trapezoidal Rule\n";
    cout << "2. Simpson’s 1/3 Rule (requires even n)\n";
    cout << "3. Simpson’s 3/8 Rule (requires n multiple of 3)\n";
    cout << "4. Compute all applicable methods\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    cout << fixed << setprecision(6);
    
    if (choice == 1 || choice == 4) {
        cout << "Trapezoidal Rule: " << trapezoidalRule(a, b, n) << "\n";
    }
    if ((choice == 2 || choice == 4) && n % 2 == 0) {
        cout << "Simpson’s 1/3 Rule: " << simpsonsOneThirdRule(a, b, n) << "\n";
    }
    if ((choice == 3 || choice == 4) && n % 3 == 0) {
        cout << "Simpson’s 3/8 Rule: " << simpsonsThreeEighthRule(a, b, n) << "\n";
    }
    
    return 0;
}
