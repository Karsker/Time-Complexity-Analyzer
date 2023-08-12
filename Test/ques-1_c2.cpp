#include<iostream>
#include<cstdio>
#include<time.h>
using namespace std;

int main() {
    int elements[1000000], n, i, j, key,k;
    clock_t start_time = clock();
    cin >> n;
    for (i = 0; i < n; i++) {
        cin >> elements[i];
    }
    cin >> k;
    // Apply insertion sort
    for (i = 1; i < n; i++) {
        j = i - 1;
        key = elements[i];
        while(j >= 0 && elements[j] > key) {
            elements[j+1] = elements[j];
            j--;
        }
        elements[j+1] = key;
    }

    // Search for the element k
    int mid, beg, end;
    beg = 0;
    end = n-1;
    int k_ind;
    while (beg <= end) {
            mid = (beg+end)/2;
        if (elements[mid] == k) {
            k_ind = mid;
            break;
        }
        else if (elements[mid] < k) {
            beg = mid+1;
        } else {
            end = mid-1;
        } 
    }
    
    clock_t end_time = clock();
    double run_time = double(end_time-start_time)/CLOCKS_PER_SEC;
    //cout << "Position of " << k << ": " << k_ind+1 << endl;
    cout << run_time << endl;
}