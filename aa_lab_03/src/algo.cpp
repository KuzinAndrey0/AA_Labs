#include "../inc/algo.h"
#include "../inc/general.h"

#include <iostream>
#include <vector>
 
using namespace std;
 
int leonardo(int k)
{
    if (k < 2) {
        return 1;
    }
    return leonardo(k - 1) + leonardo(k - 2) + 1;
}
 

void heapify(vector<int>& arr, int start, int end)
{
    int i = start;
    int j = 0;
    int k = 0;
 
    while (k < end - start + 1) {
        if (k & 0xAAAAAAAA) {
            j = j + i;
            i = i >> 1;
        }
        else {
            i = i + j;
            j = j >> 1;
        }
 
        k = k + 1;
    }
 
    while (i > 0) {
        j = j >> 1;
        k = i + j;
        while (k < end) {
            if (arr[k] > arr[k - i]) {
                break;
            }
            swap(arr[k], arr[k - i]);
            k = k + i;
        }
 
        i = j;
    }
}



void swap(int *a, int *b) {
   int temp;
   temp = *a;
   *a = *b;
   *b = temp;
}

void sort_shaker(vector<int> &arr)
{
  int m = arr.size();
   int i, j, k;
   for(i = 0; i < m;) {
      for(j = i+1; j < m; j++) {
         if(arr[j] < arr[j-1])
            swap(&arr[j], &arr[j-1]);
      }
      m--;
      for(k = m-1; k > i; k--) {
         if(arr[k] < arr[k-1])
            swap(&arr[k], &arr[k-1]);
      }
      i++;
   }
}
void sort_shell(vector<int> &arr)
{
  int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2) 
    { 
        for (int i = gap; i < n; i += 1) 
        { 
            int temp = arr[i]; 
            int j;             
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) 
                arr[j] = arr[j - gap]; 
            arr[j] = temp; 
        } 
    }
}

void sort_smooth(vector<int> &arr)
{
    int n = arr.size();
 
    int p = n - 1;
    int q = p;
    int r = 0;
 
    while (p > 0) {
        if ((r & 0x03) == 0) {
            heapify(arr, r, q);
        }
 
        if (leonardo(r) == p) {
            r = r + 1;
        }
        else {
            r = r - 1;
            q = q - leonardo(r);
            heapify(arr, r, q);
            q = r - 1;
            r = r + 1;
        }
 
        swap(arr[0], arr[p]);
        p = p - 1;
    }
 
    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        while (j > 0 && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j = j - 1;
        }
    }
 
}