#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;
 void display(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
 }
// Function to display a matrix
void displayMatrix(const vector<vector<double>>& matrix , vector<vector<double>>& inverse )
   { int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << " | ";
        for (int j = 0; j < n; ++j) {
            cout << setw(10) << inverse[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
  void swap(vector<double>& a, vector<double>& b) {
        vector<double> temp = a;
        a = b;
        b = temp;
    }
 double determinant(const vector<vector<double>>& matrix) {
    int n = matrix.size();

    // Base case: If the matrix is 1x1, return the single element
    if (n == 1) {
        return matrix[0][0];
    }

    // Base case: If the matrix is 2x2, return ad - bc
    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    // Recursive case: Compute determinant using Laplace expansion
    double det = 0.0;
    for (int col = 0; col < n; col++) {
        // Create a submatrix by excluding the first row and current column
        vector<vector<double>> submatrix;
        for (int i = 1; i < n; i++) {
            vector<double> row;
            for (int j = 0; j < n; j++) {
                if (j != col) { // Skip the current column
                    row.push_back(matrix[i][j]);
                }
            }
            submatrix.push_back(row);
        }

        // Recursive call to calculate the determinant of the submatrix
        double subDet = determinant(submatrix);

        // Add or subtract the current element's contribution to the determinant
        det += ((col % 2 == 0 ? 1 : -1) * matrix[0][col] * subDet);
    }

    return det;
}  

// Function to check if the matrix is singular
bool isSingular(const vector<vector<double>>& matrix) {
    return fabs(determinant(matrix)) < 1e-9;
}

// Function to find the inverse of a matrix using elementary row operations
bool findInverse(vector<vector<double>>& matrix, vector<vector<double>>& inverse) {
    int n = matrix.size();
    inverse = vector<vector<double>>(n, vector<double>(n, 0.0));

    // Initialize the inverse matrix as the identity matrix
    for (int i = 0; i < n; ++i) {
        inverse[i][i] = 1.0;
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; ++i) {
        
        if (fabs(matrix[i][i]) < 1e-9) {
            bool swapped = false;
            for (int j = i + 1; j < n; ++j) {
                if (fabs(matrix[j][i]) > 1e-9) {
                    swap(matrix[i], matrix[j]);
                    swap(inverse[i], inverse[j]);
                    swapped = true;
                    cout << "R" << i + 1 << " <---> " << " R" <<j + 1 << endl;
                    break;
                }
            }
            if (!swapped) {
                return false; // Matrix is singular
            }
        }

        double diag = matrix[i][i];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] /= diag;
            inverse[i][j] /= diag;
            
        }
           if(i==n-1){
                cout<<"R"<<i+1<<" = R"<<i+1<<"/"<<diag<<endl;
            }
         for(int j=i+1;j<n;j++) {
            double factor = matrix[j][i];
            cout<<"R"<<j+1<<" = R"<<j+1<<" - ("<<factor<<"/"<<diag<<")R"<<i+1<<endl;
            for(int k=0;k<n;k++) {
                matrix[j][k] -= factor * matrix[i][k];
                inverse[j][k] -= factor * inverse[i][k];
            }
         }
        // Display the matrix after each row operation
      //  cout << "Matrix after row operation " << i + 1 << ":\n";
        displayMatrix(matrix,inverse);
         
        //cout << "Inverse matrix after row operation " << i + 1 << ":\n";
       // displayMatrix(inverse);
    }

    // Perform back substitution
     for(int i=n-1; i>0; i--) {
          for( int j=i-1; j>=0; j--) {
              double factor = matrix[j][i];
              cout<<"R"<<j<<" = R"<<j<<" - ("<<factor<<")R"<<i+1<<endl;
              for(int k=0; k<n; k++) {
                  matrix[j][k] -= factor * matrix[i][k];
                  inverse[j][k] -= factor * inverse[i][k];
              }
          }
     }  


    return true;
}

int main() {
    int n;
    cout << "Enter the order of the square matrix: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    vector<vector<double>> inverse(n, vector<double>(n,0));

    cout << "Enter the elements of the matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    if (isSingular(matrix)) {
        cout << "The given matrix is singular and the inverse doesn't exist.\n";
    } else {
        if (findInverse(matrix, inverse)) {
            cout << "The inverse of the matrix is:\n";
            display(inverse);
        } else {
            cout << "The given matrix is singular and the inverse doesn't exist.\n";
        }
    }

    return 0;
}