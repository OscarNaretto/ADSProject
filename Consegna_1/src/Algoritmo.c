#include <stdio.h>
#define N 100    //dimensione vettore di appoggio merge
#define K 4     //costante di confronto per il passaggio da mergesort a insertionsort

void merge(int v1[], int p, int q, int r){
    printf("Merging\n");
    
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


int binarySearch(int a[], int item, int low, int high) {

    if (high <= low) {
        return (item > a[low])?  (low + 1): low;
    }

    int mid = (low + high)/2;
  
    if(item == a[mid]){
        return mid+1;
    } else if(item > a[mid]){
        return binarySearch(a, item, mid+1, high);
    }
    
    return binarySearch(a, item, low, mid-1);  
}


void algoritmo(int a[],int low, int high){

    if (high - low + 1 <= K){
        printf("Sorting\n");

        for (int i = low + 1; i  < high + 1; i++){
            int j = i - 1;
            int selected = a[i];

            //posizione in cui deve essere inserito selezionato
            int index = binarySearch(a, selected, low, j);

            //ciclo per spostare l'elemento cosi da fare 
            //spazio per l'elemento da inserire
            while (j >= index){
                a[j+1] = a[j];
                j--;
            }
            a[index] = selected; 
        }
    }else{
        int mid;
        if (low < high) {
            mid = (low+high)/2;
            printf("Division\n");
            algoritmo(a, low, mid);
            printf("Division\n");
            algoritmo(a, mid+1, high);
            merge(a, low, mid, high);
        }
    }

}

int main() {
    int a[] = { 37, 23, 0, 4, 62, 25, 12, 8};
    int size = sizeof(a) / sizeof(a[0]);

    printf("Sorted array: \n");
    algoritmo(a, 0, size - 1);
    printf("n=(%d) e K(%d)\n", size, K);
 
    
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
 
    return 0;
}