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
    double temp;
    // Sort the sub array individually if size is less than or equal to 5
    // An array of 5 cannot be broken down to subarrays of length more than 3
    if (high - low <= 4) {
        // For sorting array of size 3 in constant time
        if (high-low == 2) {
            if (A[low] > A[low+1]) {
                swap(A[low], A[low+1]);
            }
            if (A[low+1] > A[low+2]) {
                swap(A[low+1], A[low+2]);
                if (A[low] > A[low+1]) {
                    swap(A[low], A[low+1]);
                }
            }
            return;
        }
        // For arrays of size 4 and 5
        int min;
        for (int i = low; i < (high-1); i++) {
            min = i;
            for (int j = i+1; j < (high); j++) {
                if (A[j] < A[min]) {
                    min = j;
                }
            }
            swap(A[i], A[min]);
        }
    } // for all other sizes 
    else {
        int mid = (low+high)/2;
        mergeSort(A, low, mid);
        mergeSort(A, mid+1, high);
        merge(A, low, mid, high);
        
    }
}
int main () {
    int n;
    double inp;
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
