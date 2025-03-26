#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
double f(double x, double y) {
    return 2+sqrt(x*y);  
}
 double rk2(double x, double y, double h) {
    double k1 = h * f(x, y);
    double k2 = h * f(x + h, y + k1);
    return y + 0.5 * (k1 + k2);
 }
  double rk4(double x, double y, double h) {
    double k1 = h * f(x, y);
    double k2 = h * f(x + h / 2, y + k1 / 2);
    double k3 = h * f(x + h / 2, y + k2 / 2);
    double k4 = h * f(x + h, y + k3);
    return y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
}
 int main(){
        double x0, y0, h;
        int n, choice;
        cout << "Enter initial conditions (x0, y0): ";
        cin >> x0 >> y0;
        cout << "Enter step size (h): ";
        cin >> h;
        cout << "Enter number of steps: ";
        cin >> n;
        do {
            cout << "\nChoose an option:";
            cout << "\n1. Runge-Kutta 2nd order";
            cout << "\n2. Runge-Kutta 4th order";
            cout << "\n3. Compare both methods";
            cout << "\n4. Exit";
            cout << "\nEnter your choice: ";
            cin >> choice;
            double x = x0, y_rk2 = y0, y_rk4 = y0;
            if (choice == 1 || choice == 2) {
                cout << "\nStep\tx\ty" << (choice == 1 ? " (RK2)\n" : " (RK4)\n");
                for (int i = 0; i <= n; i++) {
                    cout << fixed << setprecision(6) << i << "\t" << x << "\t" << (choice == 1 ? y_rk2 : y_rk4) << "\n";
                    if (choice == 1) y_rk2 = rk2(x, y_rk2, h);
                    else y_rk4 = rk4(x, y_rk4, h);
                    x += h;
                }
            } else if (choice == 3) {
                cout << "\nStep\tx\tRK2\tRK4\tError\n";
                for (int i = 0; i <= n; i++) {
                    double error = abs(y_rk4 - y_rk2);
                    cout << i << "\t" << x << "\t" << y_rk2 << "\t" << y_rk4 << "\t" << error << "\n";
                    y_rk2 = rk2(x, y_rk2, h);
                    y_rk4 = rk4(x, y_rk4, h);
                    x += h;
                }
            }
        } while (choice != 4);
        return 0;
 }