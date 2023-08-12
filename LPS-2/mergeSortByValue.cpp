#include<iostream>
#include<climits>
#include<vector>
#include<time.h>
using namespace std;
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
        double mid_val = (A[low] + A[high])/2;
        int flag = 0;
        int mid_ind = low;
        for (int i = low+1; i < high; i++) {
            if (A[i] > mid_val) {
                mid_ind = i-1;
                flag = 1;
            }
        }
        mergeSort(A, low, mid_ind);
        mergeSort(A, mid_ind+1, high);
        merge(A, low, mid_ind, high);
    }
}
int main () {
    int n;
    cin >> n;
    double* elements = new double[n];
    for (int i = 0; i < n; i++) {
        cin >> elements[i];
    }
    clock_t start = clock();
    mergeSort(elements, 0, n-1);
    clock_t end = clock();
    double run_time = (double)(end-start)/CLOCKS_PER_SEC;
    // for (int i = 0; i < n; i++) {
    //     cout << elements[i] << endl;
    // }
    //cout << "Input size: " << n << endl;
    cout << run_time << endl;
    return 0;
}
