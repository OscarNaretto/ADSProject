#include <stdio.h>
#define N 50 
#define K 1
#define CASO 2

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

void algoritmo(int a[],int i, int j){
    //int size = sizeof(a)/sizeof(a[0]);
    int size = j-i+1;

    if(size <= K){
        printf("Binary\n");
        int loc, k, selected;

        for (i = 1; i < size; i++){
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
    }else{
        printf("Merge\n");
        //int v1[], int p, int r
        int q; // valore medio
        if (i < j) {
            q = (i+j)/2;
            algoritmo(a, i, q);
            algoritmo(a, q+1, j);
            merge(a, i, q, j);
        }
    }

}

int main()
{
    int a[]
        = { 37, 23, 0};
    //int n = sizeof(a) / sizeof(a[0]), i;

    int i;

    printf("Sorted array: \n");
    algoritmo(a,0,CASO);
    printf("n=(%d) e K(%d)\n", CASO+1, K);
 
    
    for (i = 0; i < CASO+1; i++)
        printf("%d ", a[i]);
 
    return 0;
}


