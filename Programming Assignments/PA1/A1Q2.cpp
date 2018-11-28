// Multiply with FFT
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

//    double theta = (2 * M_PI) / N;
//    complex<double> OmegaN(cos(theta), sin(theta));
//    complex<double> Omega(1, 0);
    for (int k = 0; k < (N / 2); k++) {
        double theta = (2 * M_PI * k) / N;
        complex<double> Omega(cos(theta), sin(theta));
        y[k] = yEven[k] + Omega * yOdd[k];
        y[k + N / 2] = yEven[k] - Omega * yOdd[k];

//        Omega = Omega * OmegaN;
    }
    return y;
}


int main() {
    freopen("input.text", "r", stdin);
    int d1, d2;
    cin >> d1 >> d2;
    double realCoefficients1[d1];
    double imgCoefficients1[d1];

    double realCoefficients2[d2];
    double imgCoefficients2[d2];
    for (int i = 0; i < d1; i++) cin >> realCoefficients1[i];
    for (int i = 0; i < d1; i++) cin >> imgCoefficients1[i];

    for (int i = 0; i < d2; i++) cin >> realCoefficients2[i];
    for (int i = 0; i < d2; i++) cin >> imgCoefficients2[i];

    int n;
    cin >> n;
    n = int(pow(2, ceil(log2(abs(d1 + d2 - 1)))));
//    cout << "n: "<<n;
    // For matrix A
    complex<double> coefficientsA[n];
    for (int i = 0; i < d1; i++) {
        complex<double> complexSet(realCoefficients1[i], imgCoefficients1[i]);
        coefficientsA[i] = complexSet;
    }
    if (d1 < n) {
        for (int i = d1; i < n; i++) {
            complex<double> complexSet(0, 0);
            coefficientsA[i] = complexSet;
        }
    }
    // For matrix B
    complex<double> coefficientsB[n];
    for (int i = 0; i < d2; i++) {
        complex<double> complexSet(realCoefficients2[i], imgCoefficients2[i]);
        coefficientsB[i] = complexSet;
    }
    if (d2 < n) {
        for (int i = d2; i < n; i++) {
            complex<double> complexSet(0, 0);
            coefficientsB[i] = complexSet;
        }
    }
    auto YA = calculateFFT(coefficientsA, n);
    auto YB = calculateFFT(coefficientsB, n);
    complex<double> YC[n];
    for (int i = 0; i < n; i++) {
        YC[i] = YA[i] * YB[i];
    }

    auto inverseFFT = calculateFFT(YC, n);
    for (int i = 0; i < n; i++) {
        inverseFFT[i] /= n;
    }
    for(int i=1;i<=n/2;i++) {
        swap(inverseFFT[i], inverseFFT[n - i]);
    }


    cout << setprecision(5) << fixed;
    for (int i = 0; i < d1+d2-1; i++) {
        (real(inverseFFT[i]) > -0.00001 && real(inverseFFT[i]) <0) ? cout << 0.00000 << " " : cout << real(inverseFFT[i]) << " ";
    }
    cout << endl;
    for (int i = 0; i < d1+d2-1; i++) {
        (imag(inverseFFT[i]) > -0.00001 && imag(inverseFFT[i]) <0) ? cout << 0.00000 << " " :cout << imag(inverseFFT[i]) << " ";
    }
    return 0;
}