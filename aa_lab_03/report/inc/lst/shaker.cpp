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