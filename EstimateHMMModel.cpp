#include <iostream>
#include <vector>
#include <float.h>
#include <cmath>
#include <cassert>

using namespace std;

vector<double> c;

// matrices
vector<vector<double> > a;
vector<vector<double> > b;
vector<vector<double> > pi;
vector<vector<double> > alpha;
vector<vector<double> > beta;
vector<vector<vector<double> > > digama;
vector<vector<double> > gama;
vector<int> o;


void calcAlpha() {
    // initialize alpha_1(i)
    c[0] = 0;
    for (int i = 0; i <= a.size()-1; ++i) {
        alpha[0][i] = b[i][o[0]] * pi[0][i];
        c[0] += alpha[0][i];
    }
    // scale alpha
    c[0] = 1/c[0];
    for (int i = 0; i <= a.size()-1; ++i) {
        alpha[0][i] *= c[0];
    }

    // calculate alpha iteratively
    for (int t = 1; t <= o.size()-1; ++t) {
        c[t] = 0;
        for (int i = 0; i <= a.size()-1; ++i) {
            alpha[t][i] = 0;
            for (int j = 0; j <= a.size()-1; ++j) {
                alpha[t][i] += a[j][i] * alpha[t-1][j];
            }
            alpha[t][i] *= b[i][o[t]];
            c[t] += alpha[t][i];
        }

        c[t] = 1/c[t];
        for (int i = 0; i <= a.size()-1; ++i) {
            alpha[t][i] *= c[t];
        }
    }
}

void calcBeta() {
    // initialize beta_T(i)
    for (int i = 0; i <= a.size()-1; ++i) {
        beta[o.size()-1][i] = c[o.size()-1];
    }

    // calculate beta interatively
    for (int t = o.size()-2; t >= 0; --t) {
        for (int i = 0; i <= a.size()-1; ++i) {
            beta[t][i] = 0;
            for (int j = 0; j < a.size(); ++j) {
                beta[t][i] += a[i][j] * beta[t+1][j] * b[j][o[t+1]];
            }
            beta[t][i] *= c[t];
        }
    }
}

void calcAlphaBeta() {
        c[0] = 0;
        for (int i = 0; i <= a.size()-1; ++i) {
            alpha[0][i] = b[i][o[0]] * pi[0][i];
            c[0] += alpha[0][i];
        }
        // scale alpha
        c[0] = 1/c[0];
        for (int i = 0; i <= a.size()-1; ++i) {
            alpha[0][i] *= c[0];
        }

        for (int i = 0; i <= a.size()-1; ++i) {
            beta[o.size()-1][i] = 1;
        }

        // calculate alpha iteratively
        for (int t = 1, tt = o.size()-2; t <= o.size()-1; ++t, --tt) {
            c[t] = 0;
            for (int i = 0; i <= a.size()-1; ++i) {
                alpha[t][i] = 0;
                for (int j = 0; j <= a.size()-1; ++j) {
                    alpha[t][i] += a[j][i] * alpha[t-1][j];
                }
                alpha[t][i] *= b[i][o[t]];
                c[t] += alpha[t][i];
            }

            c[t] = 1/c[t];
            for (int i = 0; i <= a.size()-1; ++i) {
                alpha[t][i] *= c[t];
                beta[tt][i] = 0;
                for (int j = 0; j < a.size(); ++j) {
                    beta[tt][i] += a[i][j] * beta[tt+1][j] * b[j][o[tt+1]];
                }
                beta[tt][i] *= c[t];
            }
        }
    }

void calcgamas() {
    for (int t = 0; t <= o.size()-2; ++t) {
        double denom = 0;
        for (int i = 0; i <= a.size()-1; ++i) {
            for (int j = 0; j <= a.size()-1; ++j) {
                denom += alpha[t][i] * a[i][j] * b[j][o[t+1]] * beta[t+1][j];
            }
        }
        for (int i = 0; i <= a.size()-1; ++i) {
            gama[t][i] = 0;
            for (int j = 0; j <= a.size()-1; ++j) {
                digama[t][i][j] = (alpha[t][i] * a[i][j] * b[j][o[t+1]] * beta[t+1][j]) / denom;
                gama[t][i] += digama[t][i][j];
            }
        }
    }

    // special case
    double denom = 0;
    for (int i = 0; i <= a.size()-1; ++i) {
        denom += alpha[o.size()-1][i];
    }
    for (int i = 0; i <= a.size()-1; ++i) {
        gama[o.size()-1][i] = alpha[o.size()-1][i]/denom;
    }
}

void estimateA() {
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < a.size(); ++j) {
            double sum1 = 0;
            double sum2 = 0;
            for (int t = 0; t < o.size()-1; ++t) {
                sum1 += digama[t][i][j];
                sum2 += gama[t][i];
            }
            a[i][j] = sum1 / sum2;
        }
    }
}

void estimateB() {
    for (int j = 0; j < a.size(); ++j) {
        for (int k = 0; k < b[0].size(); ++k) {
            double sum1 = 0;
            double sum2 = 0;
            for (int t = 0; t < o.size(); ++t) {
                if (o[t] == k) {
                    sum1 += gama[t][j];
                }
                sum2 += gama[t][j];
            }

            b[j][k] = sum1 / sum2;
        }
    }
}

void estimate() {
        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a.size(); ++j) {
                double sum1 = 0;
                double sum2 = 0;
                for (int t = 0; t < o.size()-1; ++t) {
                    sum1 += digama[t][i][j];
                    sum2 += gama[t][i];
                }
                a[i][j] = sum1 / sum2;
            }
            for (int k = 0; k < b[0].size(); ++k) {
                double sum1 = 0;
                double sum2 = 0;
                for (int t = 0; t < o.size(); ++t) {
                    if (o[t] == k) {
                        sum1 += gama[t][i];
                    }
                    sum2 += gama[t][i];
                }

                b[i][k] = sum1 / sum2;
            }
        }
    }

void estimatePi() {
    for (int i = 0; i < a.size(); ++i) {
        pi[0][i] = gama[0][i];
    }
}

double computeLog() {
    double sum = 0;
    for (int i = 0; i < c.size(); ++i) {
        sum += log(c[i]);
    }

    return -sum;
}

vector<int> readObs() {
    int n;
    cin >> n;
    vector<int> obs;
    for (int i = 0; i < n; i++) {
        int elem;
        cin >> elem;
        obs.push_back(elem);
    }
    return obs;
}

vector<vector<double> > readMatrix() {
    int rows;
    cin >> rows;
    int columns;
    cin >> columns;
    vector<vector<double> > matrix;
    matrix.resize(rows);


    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            double elem;
            cin >> elem;
            matrix[i].push_back(elem);
        }
    }
    return matrix;
}

void printMatrix(vector<vector<double> > const &matrix ) {
    cout << matrix.size() << " " << matrix[0].size() << " ";
    for (int i = 0; i < matrix.size() ; ++i) {
        for (int j = 0; j < matrix[0].size() ; ++j) {
            cout << matrix[i][j] << " ";
        }
    }
    cout << endl;
}

int main(void){


    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    a = readMatrix();
    b = readMatrix();
    pi = readMatrix();
    o = readObs();

    c.resize(o.size());
    alpha.resize(o.size());
    beta.resize(o.size());
    gama.resize(o.size());
    digama.resize(o.size());
    for (int i = 0; i < o.size(); ++i) {
        alpha[i].resize(a.size());
        beta[i].resize(a.size());
        gama[i].resize(a.size());
        digama[i].resize(a.size());
        for (int j = 0; j < digama[i].size(); ++j) {
            digama[i][j].resize(a.size());
        }
    }

    double oldLogProb = -DBL_MAX;

    int iter = 30;

    while (iter--) {

        //calcAlpha();
        calcAlphaBeta();

        double logProb = computeLog(); 
        if(oldLogProb > logProb) {
            break;
        }

        oldLogProb = logProb;

        // Calculations
        //calcBeta();
        calcgamas();

        // Estimation
        //estimateA();
        //estimateB();
        estimate();
        estimatePi();
    }

    printMatrix(a);
    printMatrix(b);

    return 0;
}