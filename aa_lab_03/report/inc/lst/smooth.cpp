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