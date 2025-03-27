#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <climits>
using namespace std;
bool isDiagonallyDominant(vector<vector<double>>& A, int n) {
    for(int i = 0; i < n; i++) {
        double sum = 0;
        double diag = abs(A[i][i]);
        
        for(int j = 0; j < n; j++) {
            if(i != j) {
                sum += abs(A[i][j]);
            }
        }
        
        if(diag <= sum) {
            return false;
        }
    }
    return true;
}

bool makeDiagonallyDominant(vector<vector<double>>& A, vector<double>& b, int n) {
    for (int i = 0; i < n; ++i) {
        int maxRow = i;
        double maxValue = abs(A[i][i]);
        for (int j = i + 1; j < n; ++j) {
            if (abs(A[j][i]) > maxValue) {
                maxValue = abs(A[j][i]);
                maxRow = j;
            }
        }
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }
    }
    return isDiagonallyDominant(A, n);
}

int findRank(vector<vector<double>> A, int n, int m) {
    const double EPSILON = 1e-10;
    int rank = 0;
    vector<bool> rowSelected(n, false);

    for(int col = 0; col < m; col++) {
        int row;
        for(row = 0; row < n; row++) {
            if(!rowSelected[row] && abs(A[row][col]) > EPSILON)
                break;
        }

        if(row != n) {
            rank++;
            rowSelected[row] = true;
            for(int i = 0; i < n; i++) {
                if(i != row && abs(A[i][col]) > EPSILON) {
                    double mult = A[i][col] / A[row][col];
                    for(int j = col; j < m; j++)
                        A[i][j] -= mult * A[row][j];
                }
            }
        }
    }
    return rank;
}

bool checkConsistency(vector<vector<double>>& A, vector<double>& b, int n) {
    // Create augmented matrix
    vector<vector<double>> aug(n, vector<double>(n + 1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][n] = b[i];
    }

    int rankA = findRank(A, n, n);
    int rankAug = findRank(aug, n, n + 1);

    cout<< "Rank of coefficient matrix: " << rankA << endl;
    cout<< "Rank of augmented matrix: " << rankAug << endl;

    return (rankA == rankAug);
}

vector<double> gaussSeidel(vector<vector<double>>& A, vector<double>& b, vector<double>& initial, int n, 
                          double tolerance, int maxIter) {
    vector<double> x = initial;    // Initialize with given initial values
    vector<double> xPrev(n);
    vector<double> diff(n); // To store the difference in solutions
    for(int iter = 0; iter < maxIter; iter++) {
        xPrev = x;
        //double maxDiff = 0;
        for(int i = 0; i < n; i++) {
            double sum1 = 0,sum2=0;
            for(int j = 0; j < i; j++) {
                sum1 += A[i][j] * xPrev[j];
                }
            for(int j = i + 1; j < n; j++) {
                sum2 += A[i][j] * x[j];
                }
            x[i] = (b[i] - sum1 - sum2) / A[i][i];
            diff[i] = abs(x[i] - xPrev[i]);
           }
              // Check for convergence
            bool converged = true;
            for (int i = 0; i < n; i++) {
                if (diff[i] > tolerance) {
                    converged = false;
                    break;
                    }
                     }
            // Display iteration information
            cout << "Iteration " << iter + 1 << ": ";
            for (int i = 0; i < n; i++) {
                cout << "x[" << i << "] = " << x[i] << ", ";
                }
                cout<<endl;

            if (converged) {
                cout << "Converged in " << iter + 1 << " iterations." << endl;
                break;
            }
            if (iter == maxIter - 1) {
                cout << "Reached maximum iterations." << endl;
            }

        } // end of iteration
        return x;
    }
    


int main() {
    int n;
    cout << "Enter size of system: ";
    cin >> n;
    
    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n);
    
    cout << "Enter coefficient matrix:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    
    cout << "Enter RHS vector:" << endl;
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    if(!isDiagonallyDominant(A, n)) {
        cout << "Matrix is not diagonally dominant. Attempting to make it diagonally dominant..." << endl;
        if(!makeDiagonallyDominant(A, b, n)) {
            cout << "Failed to make the matrix diagonally dominant." << endl;
        } else {
            cout << "Successfully made the matrix diagonally dominant." << endl;
        }
    }
    
    if(!checkConsistency(A, b, n)) {
        cout << "System is inconsistent" << endl;
        return 1;
    }
    
    double tolerance;
    int maxIter;
    cout << "Enter tolerance: ";
    cin >> tolerance;
    cout << "Enter maximum iterations: ";
    cin >> maxIter;
    vector<double> initial(n, 0);
    for(int i = 0; i < n; i++) {
        cout << "Enter initial value for x[" << i << "]: ";
        cin >> initial[i];
    }
    
    
    vector<double> solution = gaussSeidel(A, b, initial, n, tolerance, maxIter);
    
    cout << "\nFinal Solution:" << endl;
    for(int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << solution[i] << endl;
    }
    
    return 0;
}