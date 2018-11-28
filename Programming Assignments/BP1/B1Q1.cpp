#include <bits/stdc++.h>

using namespace std;

long CountInMerge(long *array, long l, long mid, long r, long *temp) {
    long inversionCount = 0;
// Assume that A[l...mid] and A[mid+1...r] both are sorted and now merging both the sorted arrays
    long i = l, j = mid, k = l;
    while ((i <= mid - 1) && (j <= r)) {
        if (array[i] <= array[j]) {
            temp[k] = array[i];
            k++;
            i++;
        } else if(array[i] > 2*array[j]){
            temp[k] = array[j];
            j++;
            k++;
            inversionCount += mid - i;
        } else{
            temp[k] = array[j];
            j++;k++;
        }
    }
    while (i <= mid - 1) {
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
        inversionCount += CountInMerge(array, l, mid + 1, r, temp);
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
//        for(int i=0; i<n; i++) cout << arr[i] << " ";
//        cout << endl;
    }
    return 0;
}