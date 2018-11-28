// FFT
#include <bits/stdc++.h>

using namespace std;

complex<double> *calculateFFT(complex<double> coefficients[], int N) {
    if (N == 1) return coefficients;
    complex<double> aOdd[N / 2];
    complex<double> aEven[N / 2];
    int index = 0;
    for (int i = 0; i <= N - 2; i += 2) {
        aOdd[index] = coefficients[i + 1];
        aEven[index] = coefficients[i];
        index++;
    }
    complex<double> *yOdd = calculateFFT(aOdd, N / 2);
    complex<double> *yEven = calculateFFT(aEven, N / 2);
    auto *y = new complex<double>[N];

    double theta = (2 * M_PI) / N;
    complex<double> OmegaN(cos(theta), sin(theta));
    complex<double> Omega(1, 0);
    for (int k = 0; k < (N / 2); k++) {
        y[k] = yEven[k] + Omega * yOdd[k];
        y[k + N / 2] = yEven[k] - Omega * yOdd[k];
        Omega = Omega * OmegaN;
    }
    return y;
}


int main() {
    freopen("input.text", "r", stdin);
    int d;
    cin >> d;
    double realCoefficients[d];
    double imgCoefficients[d];
    for (int i = 0; i < d; i++) cin >> realCoefficients[i];
    for (int i = 0; i < d; i++) cin >> imgCoefficients[i];
    int n;
    cin >> n;
    complex<double> coefficients[n];
    for (int i = 0; i < d; i++) {
        complex<double> complexSet(realCoefficients[i], imgCoefficients[i]);
        coefficients[i] = complexSet;
    }
    if (d < n) {
        for (int i = d; i < n; i++) {
            complex<double> complexSet(0, 0);
            coefficients[i] = complexSet;
        }
    }
    auto Y = calculateFFT(coefficients, n);
    cout << setprecision(5) << fixed;
    for (int i = 0; i < n; i++) {
        cout << real(Y[i]) << " ";
    }
    cout<<endl;
    for (int i = 0; i < n; i++) {
        cout << imag(Y[i]) << " ";
    }

    return 0;
}