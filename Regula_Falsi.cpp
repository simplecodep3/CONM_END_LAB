#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Define the function for which we are finding the root
double f(double x) {
    return x * exp(x) - sin(x);
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

// Regula-Falsi method implementation
void regulaFalsi(double a, double b, double tolerance, int maxIterations) {
    if (f(a) * f(b) >= 0) {
        cout << "Invalid interval. f(a) and f(b) must have opposite signs." << endl;
        return;
    }

    double c; // Point of intersection
    for (int i = 0; i < maxIterations; ++i) {
        // Calculate the point of intersection
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        double fc = f(c);

        // Print the current step
        cout << "Iteration " << i + 1 << ": c = " << c << ", f(c) = " << fc << endl;

        // Check if the root is found or if the interval is within tolerance
        if (fabs(fc) < tolerance) {
            cout << "Root found at x = " << c << " after " << i + 1 << " iterations." << endl;
            return;
        }

        // Narrow the interval
        if (f(a) * fc < 0) {
            b = c; // Root is in [a, c]
        } else {
            a = c; // Root is in [c, b]
        }
    }

    cout << "Maximum iterations reached. Approximate root is x = " << c << endl;
}

int main() {
    int choice;
    double a, b, tolerance;
    int maxIterations, maxSteps;

    cout << "Choose an option:";
    cout << "\n1. Manually enter interval";
    cout << "\n2. Automatically find interval";
    cout << "\nEnter your choice: ";
    cin >> choice;

    cout << "Enter the tolerance: ";
    cin >> tolerance;
    cout << "Enter the maximum number of iterations: ";
    cin >> maxIterations;

    if (choice == 1) {
        cout << "Enter the interval [a, b]: ";
        cin >> a >> b;
    } else if (choice == 2) {
        cout << "Enter the maximum number of steps for interval search: ";
        cin >> maxSteps;
        vector<double> interval = findInterval(0, maxSteps);
        if (interval.empty()) {
            cout << "No interval found where the function changes sign." << endl;
            return 0;
        }
        a = interval[0];
        b = interval[1];
    } else {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    // Call the Regula-Falsi method
    regulaFalsi(a, b, tolerance, maxIterations);

    return 0;
}
