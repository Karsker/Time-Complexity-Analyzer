#include<iostream>
#include<climits>
#include<vector>
#include<time.h>
#include<iomanip>
#include<chrono>
using namespace std;
using namespace std::chrono;
void merge(double* A, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    double* sub_one = new double[n1];
    double* sub_two = new double[n2];
    int i,j,k;
    for (i = 0; i < n1; i++) {
        sub_one[i] = A[low + i];
    }
    for (j = 0; j < n2; j++) {
        sub_two[j] = A[mid+1+j];
    }
    i = 0;
    j = 0;
    k = low;
    while(i < n1 && j < n2) {
        if (sub_one[i] < sub_two[j]) {
            A[k] = sub_one[i];
            i++;
        } else {
            A[k] = sub_two[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
      A[k] = sub_one[i];  
      i++;
      k++;
    }
    while (j < n2) {
      A[k] = sub_two[j];
      j++;
      k++;
    }

    delete(sub_one);
    delete(sub_two);
}
void mergeSort(double* A, int low, int high) {
    if (low == high) {
        return;
    } else {
        int mid = (low+high)/2;
        mergeSort(A, low, mid);
        mergeSort(A, mid+1, high);
        merge(A, low, mid, high);
    }
}
int main () {
    int n;
    cin >> n;
    double* elements = new double[n];
    for (int i = 0; i < n; i++) {
        cin >> elements[i];
    }
    auto start = high_resolution_clock::now();
    mergeSort(elements, 0, n-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    //for (int i = 0; i < n; i++) {
    //    cout << elements[i] << endl;
    //}
    //cout << "Input size: " << n << endl;
    cout << duration.count()<< endl;
    return 0;
}
