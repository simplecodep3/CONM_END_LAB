#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * exp(x) - sin(x);
}

// Define the first derivative of the function
double df(double x) {
    return exp(x) * (x + 1) - cos(x);
}

// Define the second derivative for convergence check
double dff(double x) {
    return exp(x) * (x + 2) + sin(x);
}

// Function to find an interval where the root lies
vector<double> findInterval(int start, int maxSteps) {
    for (int i = start; i < start + maxSteps; ++i) {
        if (f(i) * f(i + 1) < 0) {
            return {static_cast<double>(i), static_cast<double>(i + 1)};
        }
    }
    for (int i = start; i > start - maxSteps; --i) {
        if (f(i) * f(i - 1) < 0) {
            return {static_cast<double>(i - 1), static_cast<double>(i)};
        }
    }
    return {}; // No interval found
}

// Newton-Raphson method implementation with convergence check
void newtonRaphson(double x0, double tolerance, int maxIterations) {
    double fx0 = f(x0);
    double dfx0 = df(x0);
    double dffx0 = dff(x0);

    // Check convergence condition |f(x0) * d''(x0)| < [d'(x0)]²
    if (fabs(fx0 * dffx0) >= dfx0 * dfx0) {
        cout << "Warning: Newton-Raphson may not converge at x0 = " << x0 << endl;
        return;
    }

    double x = x0;
    for (int i = 0; i < maxIterations; ++i) {
        double fx = f(x);
        double dfx = df(x);

        if (fabs(dfx) < 1e-10) {
            cout << "Derivative too small. No convergence." << endl;
            return;
        }

        double x1 = x - fx / dfx;

        cout << "Iteration " << i + 1 << ": x = " << x1 << ", f(x) = " << f(x1) << endl;

        if (fabs(x1 - x) < tolerance) {
            cout << "Root found at x = " << x1 << " after " << i + 1 << " iterations." << endl;
            return;
        }

        x = x1;
    }

    cout << "Maximum iterations reached. Approximate root is x = " << x << endl;
}

int main() {
    int methodChoice, intervalChoice;
    double tolerance;
    int maxIterations, maxSteps;

    cout << "Choose an interval method:";
    cout << "\n1. Manual Interval Entry";
    cout << "\n2. Automatic Interval Search";
    cout << "\nEnter your choice: ";
    cin >> intervalChoice;

    cout << "Enter the tolerance: ";
    cin >> tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;

    double x0;
    if (intervalChoice == 1) {
        double a, b;
        cout << "Enter the interval [a, b]: ";
        cin >> a >> b;
        x0 = (a + b) / 2; // Use the midpoint as the initial guess
    } else {
        cout << "Enter the maximum number of steps for interval search: ";
        cin >> maxSteps;
        vector<double> interval = findInterval(0, maxSteps);
        if (interval.empty()) {
            cout << "No interval found where the function changes sign." << endl;
            return 0;
        }
        x0 = (interval[0] + interval[1]) / 2; // Midpoint of the found interval
    }

    // Call the Newton-Raphson method
    newtonRaphson(x0, tolerance, maxIterations);
    return 0;
}
