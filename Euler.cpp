#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Define the differential equation dy/dx = f(x, y)
double f(double x, double y) {
    return 2 + sqrt(x * y);  // Example: dy/dx = 2 + sqrt(x*y)
}

// Euler Method
double euler(double x0, double y0, double h, int steps, int precision) {
    double x = x0, y = y0;
    cout << "\nEuler Method:\n";
    cout << "n\t\tx\t\t y" << endl;
    for (int i = 0; i < steps; i++) {
        y = y + h * f(x, y);
        x = x + h;
        cout << i + 1 << "\t\t" << fixed << setprecision(precision) << x << "\t \t" << y << endl;
    }
    return y;
}

// Modified Euler Method
double modified_euler(double x0, double y0, double h, int steps, int precision) {
    double x = x0, y = y0;
    cout << "\nModified Euler Method:\n";
    cout << "n\t\tx\t\t y" << endl;
    for (int i = 0; i < steps; i++) {
        double y_m = y + h * f(x, y);
        double y_m1 = y + (h / 2) * (f(x, y) + f(x + h, y_m));
        
        while (abs(y_m1 - y_m) > pow(10, -precision)) {
            y_m = y_m1;
            y_m1 = y + (h / 2) * (f(x, y) + f(x + h, y_m));
        }
        y = y_m1;
        x = x + h;
        cout << i + 1 << "\t\t" << fixed << setprecision(precision) << x << "\t " << y << endl;
    }
    return y;
}

// Comparison of both methods
void compare_methods(double x0, double y0, double h, int steps, int precision) {
    double x = x0, y_euler = y0, y_mod_euler = y0;
    cout << "\nComparison of Euler and Modified Euler Methods:\n";
    cout << "n\t\tx\t\t Euler\t \tModified Euler" << endl;
    for (int i = 0; i < steps; i++) {
        y_euler = y_euler + h * f(x, y_euler);
        
        double y_m = y_mod_euler + h * f(x, y_mod_euler);
        double y_m1 = y_mod_euler + (h / 2) * (f(x, y_mod_euler) + f(x + h, y_m));
        
        while (abs(y_m1 - y_m) > pow(10, -precision)) {
            y_m = y_m1;
            y_m1 = y_mod_euler + (h / 2) * (f(x, y_mod_euler) + f(x + h, y_m));
        }
        y_mod_euler = y_m1;
        x = x + h;
        cout << i + 1 << "\t\t" << fixed << setprecision(precision) << x << "\t\t " << y_euler << "\t " << y_mod_euler << endl;
    }
}

int main() {
    double x0, y0, h;
    int steps, choice, precision;
    
    cout << "Enter initial value of x (x0): ";
    cin >> x0;
    cout << "Enter initial value of y (y0): ";
    cin >> y0;
    cout << "Enter step size (h): ";
    cin >> h;
    cout << "Enter number of steps: ";
    cin >> steps;
    cout << "Enter desired precision (number of decimal places): ";
    cin >> precision;
    
    do {
        cout << "\nChoose an option:";
        cout << "\n1. Euler method";
        cout << "\n2. Modified Euler method";
        cout << "\n3. Compare both methods";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                euler(x0, y0, h, steps, precision);
                break;
            case 2:
                modified_euler(x0, y0, h, steps, precision);
                break;
            case 3:
                compare_methods(x0, y0, h, steps, precision);
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}