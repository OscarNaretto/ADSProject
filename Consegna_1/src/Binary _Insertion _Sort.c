#include <stdio.h>

//ricerca binaria di a[i..j]
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
}

/*
test
int main()
{
    int a[]
        = { 37, 23, 0, 17, 12, 72, 31, 46, 100, 88, 54 };
    int n = sizeof(a) / sizeof(a[0]), i;
 
    insertionSort(a, n);
 
    printf("Sorted array: \n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
 
    return 0;
}*/