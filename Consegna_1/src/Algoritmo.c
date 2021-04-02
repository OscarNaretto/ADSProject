#include <stdio.h>
#define N 10
#define K 4
#define CASO 7

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

        for (int i = low + 1; i  < high - low + 1; i++){
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
        for(int i=low;i<high - low + 1; i++){
        printf("%d \t", a[i]);
        }

    }else{
        int mid; // valore medio
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


//insertion sort

        /*for (int i = low; i < high; i++) {
            int tempVal = a[i + 1];
            int j = i + 1;
            while (j > low && a[j - 1] > tempVal) {
                a[j] = a[j - 1];
                j--;
            }
            a[j] = tempVal;
        }*/