#include <stdio.h>
#define N 10
#define K 2
#define CASO 7

/*
//funzioni per ordinare a[] di dimensione n
void insertionSort(int a[], int n){
    int i, j, loc, k, selected;

        for (i = 1; i < n; i++){
            j = i - 1;
            selected = a[i];
            
            //posizione in cui deve essere inserito selezionato
            loc = binarySearch(a, selected, 0, j);

        //cilco per spostare l'elemento cosi da fare 
        //spazio per l'elemento da inserire
            while (j >= loc){
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = selected;  
        }
}*/

/*void mergeSort(int v1[], int p, int r){
  int q;
  if (p < r) {
    q = (p+r)/2;
    mergeSort(v1, p, q);
    mergeSort(v1, q+1, r);
    merge(v1, p, q, r);
  }
}*/

/*if size <= k
then inserctionSort
else mergeSort*/
int binarySearch(int a[], int elem, int i, int j){
    if(j <= i)
        return (elem > a[i]) ? (i + 1) : i;   //espressione_test ? azione_true : azione_false;

    int mid = (i + j)/2;

    if(elem == a[mid])
        return mid+1;

    if(elem > a[mid])
        return binarySearch(a, elem, mid+1, j);
    return binarySearch(a, elem, i, mid-1);
}


void merge(int v1[], int p, int q, int r){
    int k = 0, i, j, v2[N];
    i = p;
    j = q + 1;

    while (i<=q && j<=r){
        if(v1[i] < v1[j]){
            v2[k] = v1[i];
            i++;
        }else{
            v2[k] = v1[j];
            j++;
        }
        k++;
    }
    
    while(i <= q){
        v2[k] = v1[i];
        i++;
        k++;
    }
    
    while(j <= r){
        v2[k] = v1[j];
        j++;
        k++;
    }
    
    k = p;
    while(k <= r){
        v1[k] = v2[k-p];
        k++;
    }
}

void algoritmo(int a[],int low, int high){

    if(high - low <= K){ // controllare <=
        /*nt loc, k, selected;

        i++;
        while(i < size){
            j = i - 1;
            selected = a[i];

            //posizione in cui deve essere inserito selezionato
           // loc = binarySearch(a, selected, 0, j);

            //cilco per spostare l'elemento cosi da fare 
            //spazio per l'elemento da inserire
            while (j >= 0 && a[j] > selected){
                a[j+1] = a[j];
                j--;
            }
            a[j+1] = selected; 
            i++; 
        }
        for(i=0;i<size; i++){
        printf("%d \t", a[i]);
        }*/

    for (int i = low; i < high; i++) {
            int tempVal = a[i + 1];
            int j = i + 1;
            while (j > low && a[j - 1] > tempVal) {
                a[j] = a[j - 1];
                j--;
            }
            a[j] = tempVal;
        }

    }else{
        printf("MergeSort\n");
        //int v1[], int p, int r
        int mid; // valore medio
        if (low < high) {
            mid = (low+high)/2;
            algoritmo(a, low, mid);
            algoritmo(a, mid+1, high);
            merge(a, low, mid, high);
            printf("Merging\n");
        }
    }

}

int main()
{
    int a[]
        = { 37, 23, 0, 4, 62, 25, 12, 8};
    //int n = sizeof(a) / sizeof(a[0]), i;

    int i;

    printf("Sorted array: \n");
    algoritmo(a,0,CASO);
    printf("n=(%d) e K(%d)\n", CASO+1, K);
 
    
    for (i = 0; i < CASO+1; i++)
        printf("%d ", a[i]);
 
    return 0;
}


