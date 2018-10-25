#include <QCoreApplication>
#include <iostream>
#include <cmath>
#include <random>


void MySwap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void printArray(int *arr, int n)
{
   for (int i=0; i < n; i++)
       printf("%d ", arr[i]);
   printf("\n");
}
void model_qsort(int* a, int len) {
    int part = len/2;
    MySwap(a[len - 1],a[part]);
    if (part > 0) model_qsort(a, part);
    if (part + 1 < len) model_qsort(a + part + 1, len - (part + 1));
}

void prepare_anti_killer(int* a, int length)
{
    int origidx[length];
    for (int i = 0; i < length; i++)
        origidx[i] = i;

    model_qsort(origidx,length);

    for (int i = 0; i < length; i++)
        a[origidx[i]] = i + 1;
}


/***************************************************************/ // Introsort
void ShiftDown(int *arr, int i, int n) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < n && arr[left] > arr[i]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        MySwap(arr[i], arr[largest]);
        ShiftDown(arr, largest, n);
    }
}

void BuildHeap(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        ShiftDown(arr, i, n);
    }
}

void HeapSort(int* a, int n) {
    int heapSize = n;
    BuildHeap(a,heapSize);
    while( heapSize > 1) {
        MySwap(a[0],a[heapSize - 1]);
        --heapSize;
        ShiftDown(a, 0, heapSize);
    }
}

int Partition( int* a, int n ) {
    if( n <= 1 ) {
        return 0;
    }
    //srand(time(NULL));
    //int random = rand() % (n - 1);
    //MySwap(a[random], a[n - 1]);
    const int& pivot = a[n - 1];
    int i = 0, j = n - 2;
    while( i <= j ) {
        for( ; a[i] < pivot; ++i ) {}
        for( ; j >= 0 && !( a[j] < pivot ); --j ) {}
        if( i < j ) {
             MySwap(a[i++], a[j--] );
        }
    }
    MySwap( a[i], a[n - 1] );
    return i;
}

void IntrosortUtil(int* arr, int n, int depthLimit)
{
    //std::cout << depthLimit << "\n";
    if (depthLimit == 0)
    {
        HeapSort(arr, n);
        return;
    }
    int part = Partition(arr, n);

    if (part > 0) IntrosortUtil(arr, part, depthLimit - 1);
    if (part + 1 < n)IntrosortUtil(arr + part + 1, n - (part + 1), depthLimit - 1);

}

void Introsort(int *arr, int n)
{
    int depthLimit = 2 * log(n);
    IntrosortUtil(arr, n, depthLimit);
}

/***************************************************************/ // QuickSort

void QuickSort(int* arr, int n)
{
    int part = Partition(arr, n);
    if (part > 0) QuickSort(arr, part);
    if (part + 1 < n)QuickSort(arr + part + 1, n - (part + 1));
}

/***************************************************************/ // InsertionSort
int BinarySearch( const int* arr, int first, int last, int element )
{
    while( first < last ) {
        int mid = ( first + last ) / 2;
        if( arr[mid] <= element )
            first = mid + 1;
        else
            last = mid;
    }
    return first;
}

void InsertionSort(int *a, int n)
{
    int loc, j, selected;

    for (int i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];
        loc = BinarySearch(a, 0, i, selected);
        while (j >= loc)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = selected;
    }
}

/***************************************************************/


unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

void time_test(void) {
    unsigned long long tb, te, t_mid_i = 0, t_mid_q = 0, t_mid_ins = 0;
    srand(time(NULL));
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-1000,1000);

    int arr_size_beg = 100;
    int arr_size_end = 1000;
    int arr_inc = 100;
    int kol_exp = 100;
    int *arr = nullptr, *copy = nullptr;
    /******************************************************/
    std::cout << "random case\n";
    std::cout << " N      intro       quick     insert\n";
    for(int i = arr_size_beg; i <= arr_size_end; i += arr_inc) {
        arr = (int*)calloc(i,sizeof(int));
        copy = (int*)calloc(i,sizeof(int));
        t_mid_i = 0;
        t_mid_q = 0;
        t_mid_ins = 0;
        if(!arr) {
            std::cout << "memory error";
            return;
        }
        for(int j = 0; j < i; j++) {
            arr[j] = distribution(generator);
        }

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            Introsort(copy,i);
            te = tick();
            t_mid_i += (te - tb);
        }
        t_mid_i /= kol_exp;

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            QuickSort(copy,i);
            te = tick();
            t_mid_q += (te - tb);
        }
        t_mid_q /= kol_exp;

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            InsertionSort(copy,i);
            te = tick();
            t_mid_ins += (te - tb);
        }
        t_mid_ins /= kol_exp;
        printf("%5d %8lld %8lld %8lld\n", i, t_mid_i, t_mid_q, t_mid_ins);

        //printArray(copy, i);
        free(arr);
        free(copy);
    }
    /******************************************************/
    std::cout << "worst case\n";
    std::cout << " N      intro       quick     insert\n";
    for(int i = arr_size_beg; i <= arr_size_end; i += arr_inc) {
        arr = (int*)calloc(i,sizeof(int));
        copy = (int*)calloc(i,sizeof(int));
        t_mid_i = 0;
        t_mid_q = 0;
        t_mid_ins = 0;
        if(!arr) {
            std::cout << "memory error";
            return;
        }
        for(int j = 0; j < i; j++) {
            arr[j] = j;
        }

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            Introsort(copy,i);
            te = tick();
            t_mid_i += (te - tb);
        }
        t_mid_i /= kol_exp;

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            QuickSort(copy,i);
            te = tick();
            t_mid_q += (te - tb);
        }
        t_mid_q /= kol_exp;

        for(int j = 0; j < i; j++) {
            arr[j] = i - j;
        }

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            InsertionSort(copy,i);
            te = tick();
            t_mid_ins += (te - tb);
        }
        t_mid_ins /= kol_exp;
        printf("%5d %8lld %8lld %8lld\n", i, t_mid_i, t_mid_q, t_mid_ins);

        //printArray(copy, i);
        free(arr);
        free(copy);
    }
    /******************************************************/
    std::cout << "best case\n";
    std::cout << " N      intro       quick     insert\n";
    for(int i = arr_size_beg; i <= arr_size_end; i += arr_inc) {
        arr = (int*)calloc(i,sizeof(int));
        copy = (int*)calloc(i,sizeof(int));
        t_mid_i = 0;
        t_mid_q = 0;
        t_mid_ins = 0;
        if(!arr) {
            std::cout << "memory error";
            return;
        }
        prepare_anti_killer(arr,i);

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            Introsort(copy,i);
            te = tick();
            t_mid_i += (te - tb);
        }
        t_mid_i /= kol_exp;

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            QuickSort(copy,i);
            te = tick();
            t_mid_q += (te - tb);
        }
        t_mid_q /= kol_exp;

        for(int j = 0; j < i; j++) {
            arr[j] = i;
        }

        for(int j = 0; j < kol_exp; j++) {
            memmove(copy,arr,i * sizeof(int));
            tb = tick();
            InsertionSort(copy,i);
            te = tick();
            t_mid_ins += (te - tb);
        }
        t_mid_ins /= kol_exp;
        printf("%5d %8lld %8lld %8lld\n", i, t_mid_i, t_mid_q, t_mid_ins);

        //printArray(copy, i);
        free(arr);
        free(copy);
    }
}
int main()
{
    //int arr[] = {3, 1, 23, -9, 233, 23, -313, 32, -9};
    /*int arr[] = {5,4,3,2,1,0};
    int n = sizeof(arr) / sizeof(arr[0]);
    Introsort(arr, n);
    printArray(arr, n);*/
    time_test();
    /*
    int n = 10;
    int *a = new int[n];
    prepare_anti_killer(a,n);
    printArray(a,n);*/

    return(0);
}
