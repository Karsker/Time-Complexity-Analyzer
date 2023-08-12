#include<iostream>
#include<climits>
#include<time.h>
using namespace std;
void merge(double* A, int low, int div1, int div2, int high) {
    // Find the lengths for three temporary arrays
    int n1 = div1 - low + 1 + 1;
    int n2 = div2 - div1 + 1;
    int n3 = high - div2 + 1;

    // Create three temporary arrays to hold the values
    double* sub_one = new double[n1];
    double* sub_two = new double[n2];
    double* sub_three = new double[n3];
    sub_one[n1-1] = INT_MAX;
    sub_two[n2-1] = INT_MAX;
    sub_three[n3-1] = INT_MAX;
    // Fill the arrays with values from the original array
    for (int i = 0; i < n1-1; i++) {
        sub_one[i] = A[low+i];
    }
    for (int i = 0; i < n2-1; i++) {
        sub_two[i] = A[div1+i+1];
    }
    for (int i = 0; i < n3-1; i++) {
        sub_three[i] = A[div2+i+1];
    }

    int i = 0, j = 0, k = 0, m = low;
    // Compare the values in the three arrays and arrange them
    while(m<=(high-low)) {
        if (sub_one[i] < sub_two[j] && sub_one[i] < sub_three[k]) {
            A[m] = sub_one[i];
            i++;
        } else if (sub_two[j] < sub_one[i] && sub_two[j] < sub_three[k]) {
            A[m] = sub_two[j];
            j++;
        } else {
            A[m] = sub_three[k];
            k++;
        }
        m++;
    }

    // Fill values from any non empty array(s)

    // while (i < n1) {
    //     A[m] = sub_one[i];
    //     i++;
    //     m++;
    // }
    // while (j < n2) {
    //     A[m] = sub_two[j];
    //     j++;
    //     m++;
    // }
    // while (k < n3) {
    //     A[m] = sub_three[k];
    //     k++;
    //     m++;
    // }
    delete(sub_one);
    delete(sub_two);
    delete(sub_three);

}
void mergeSort(double* A, int low, int high) {
    // We cannot divide an array of size < 3 into three
    if (high-low < 2) {
        // Sort the 2 size subarray
        if (A[low] > A[high]) {
            double temp = A[high];
            A[high] = A[low];
            A[low] = temp;
        }
        return;
    }
    else {
        // Find the first point of division 
        // Divide the array in the ratio 1:2
        int div1 = (2*low + high)/3;
        // Find the second point of division
        // Divide the array in the ratio 2:1
        int div2 = (low + 2*high)/3;
        mergeSort(A, low, div1);
        mergeSort(A, div1+1, div2);
        mergeSort(A, div2 + 1, high);
        merge(A, low, div1, div2, high);
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
    //for (int i = 0 ; i < n; i++) {
    //    cout << elements[i] << endl;
    //}
    // cout << "Input size: " << n << endl;
    cout << run_time << endl;
    return 0;
}
