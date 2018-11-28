// Significant Inversions in an array
#include <bits/stdc++.h>

using namespace std;

long CountInMerge(long *array, long l, long mid, long r, long *temp) {
    long inversionCount = 0;
    long i = l, j = mid + 1;
    long k;

    while ((i <= mid) && (j <= r)) {
        if (array[i] > 2 * array[j]) {
            inversionCount += mid - i + 1;
            j++;
        } else i++;
    }
    i = l, j = mid + 1, k = l;
    while ((i <= mid) && (j <= r)) {
        if (array[i] <= array[j]) {
            temp[k] = array[i];
            k++;
            i++;
        }
        if (array[i] > array[j]) {
            temp[k] = array[j];
            j++;
            k++;
        }
    }
    while (i <= mid) {
        temp[k] = array[i];
        i++;
        k++;
    }

    while (j <= r) {
        temp[k] = array[j];
        k++;
        j++;
    }
    for (long p = l; p <= r; p++) array[p] = temp[p];
    return inversionCount;
}

long SignificantInversion(long array[], long l, long r, long *temp) {
    long inversionCount = 0;
    if (r > l) {
        long mid = (l + r) / 2;
        inversionCount = SignificantInversion(array, l, mid, temp);
        inversionCount += SignificantInversion(array, mid + 1, r, temp);
        inversionCount += CountInMerge(array, l, mid, r, temp);
    }
    return inversionCount;
}


int main() {
    freopen("input.text", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        long n;
        cin >> n;
        long arr[n];
        long *temp = new long[n];
        for (int i = 0; i < n; i++) cin >> arr[i];
        cout << SignificantInversion(arr, 0, n - 1, temp) << endl;
    }
    return 0;
}