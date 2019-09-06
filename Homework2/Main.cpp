/*
Sebastian Gonzalo Vives Faus A02025211
- Tarea No. 2. Analisis de algoritmos
-     9/6/2019
*/

#include <iostream>
#include <chrono>
#include <array>
#include<vector>
#include<algorithm>
using namespace std;
using namespace std::chrono;

//Randomize array

void scramble_array(int arr[],int size){
    srand(time(NULL));

    for(int i = 0; i<size;i++){
        arr[i] = rand()%(size*10);
    }
}

//Print array
void print_arr(int arr[], int size){
    for(int i = 0; i< size; i++){
        cout<< arr[i]<<" ";
    }
}

//Binary Tree Sort
struct Node
{
    int key;
    struct Node *left, *right;
};

// A utility function to create a new BST Node
struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Stores inoder traversal of the BST
// in arr[]
void storeSorted(Node *root, int arr[], int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

/* A utility function to insert a new
   Node with given key in BST */
Node* insert(Node* node, int key)
{
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) Node pointer */
    return node;
}

// This function sorts arr[0..n-1] using Tree Sort
void treeSort(int arr[], int n)
{
    struct Node *root = NULL;

    // Construct the BST
    root = insert(root, arr[0]);
    for (int i=1; i<n; i++)
        insert(root, arr[i]);

    // Store inoder traversal of the BST
    // in arr[]
    int i = 0;
    storeSorted(root, arr, i);
}

//BUBBLE SORT!
// Code obtained from: https://www.geeksforgeeks.org/bubble-sort/
void swap(int *x, int *y){
    int temporal = *x;
    *x = *y;
    *y = temporal;
}

void BubbleSort(int arr[], int size){
    for (int i = 0; i < size-1; i++){
     for (int j = 0; j < size-i-1; j++){
        if (arr[j] > arr[j+1]){
            swap(&arr[j], &arr[j+1]);
        }//if1
     }//for2
    }//for1
}

//Cocktail Sort
// Code obtained from: https://www.geeksforgeeks.org/cocktail-sort/
void CocktailSort(int a[], int n)
{
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;

        // loop from left to right same as
        // the bubble sort
        for (int i = start; i < end; ++i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // if nothing moved, then array is sorted.
        if (!swapped)
            break;

        // otherwise, reset the swapped flag so that it
        // can be used in the next stage
        swapped = false;

        // move the end point back by one, because
        // item at the end is in its rightful spot
        --end;

        // from right to left, doing the
        // same comparison as in the previous stage
        for (int i = end - 1; i >= start; --i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        // increase the starting point, because
        // the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}


//Selection Sort
// Code obtained from: https://www.geeksforgeeks.org/selection-sort/
void SelectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
        if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

//Insertion Sort
// Code obtained from: https://www.geeksforgeeks.org/insertion-sort/
void InsertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//Merge Sort
// Code obtained from: https://www.geeksforgeeks.org/merge-sort/
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
   int* L = new int[n1];
   int* R = new int[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete [] L;
    delete[] R;
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void MergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        MergeSort(arr, l, m);
        MergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

//Shell Sort
// Code obtained form: https://www.geeksforgeeks.org/shellsort/
/* function to sort arr using shellSort */
int ShellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    return 0;
}

//Heap Sort
// Code obtained from: https://www.geeksforgeeks.org/heap-sort/
void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void HeapSort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

//Quick Sort
// Code obtained from: https://www.geeksforgeeks.org/quick-sort/
/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//Bucket Sort
// Code obtained from: //https://www.programmingalgorithms.com/algorithm/bucket-sort?lang=C%2B%2B
void BucketSort(int* data, int count) {
	int minValue = data[0];
	int maxValue = data[0];

	for (int i = 1; i < count; i++)
	{
		if (data[i] > maxValue)
			maxValue = data[i];
		if (data[i] < minValue)
			minValue = data[i];
	}

	int bucketLength = maxValue - minValue + 1;
	vector<int>* bucket = new vector<int>[bucketLength];

	for (int i = 0; i < bucketLength; i++)
	{
		bucket[i] = vector<int>();
	}

	for (int i = 0; i < count; i++)
	{
		bucket[data[i] - minValue].push_back(data[i]);
	}

	int k = 0;
	for (int i = 0; i < bucketLength; i++)
	{
		int bucketSize = bucket[i].size();

		if (bucketSize > 0)
		{
			for (int j = 0; j < bucketSize; j++)
			{
				data[k] = bucket[i][j];
				k++;
			}
		}
	}
}


//Radix Sort
// Code obtained from: https://www.geeksforgeeks.org/radix-sort/
// A function to do counting sort of arr[] according to
// the digit represented by exp.
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
            cout<<mx<<endl;
    return mx;
}
void countSort(int arr[], int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
//Count Sort
void CountSort(int *array, int size) {
      int sizep = size+1;
   int* output= new int[sizep];
   int max = getMax(array, size);
   int* count = new int[max+1]; //create count array (max+1 number of elements)

   for(int i = 0; i<=max; i++)
      count[i] = 0; //initialize count array to all zero
   for(int i = 1; i <=size; i++)
      count[array[i]]++; //increase number count in count array.
   for(int i = 1; i<=max; i++)
      count[i] += count[i-1]; //find cumulative frequency

   for(int i = size; i>=1; i--) {
      output[count[array[i]]] = array[i];
      count[array[i]] -= 1; //decrease count for same numbers
   }

   for(int i = 1; i<=size; i++) {
      array[i] = output[i]; //store output array to main array
   }
}

int main(){
    //Determine size of array by input
    int size, arr_size;
    int menu_option;
    bool menu = true;

    while(menu){
        cout<<"--Choose the size of the array (program must be restarted in order to reset): \n 1. 10 \n 2. 100 \n 3. 1,000 \n 4. 10,000 \n 5. 100,000 \n 6. 1,000,000 \n "<< endl;
        cin>> menu_option;
        switch (menu_option)
        {
        case 1:
            size = 10;
            menu = false;
            break;
        case 2:
            size = 100;
            menu = false;
            break;
        case 3:
            size = 1000;
            menu = false;
            break;
        case 4:
            size = 10000;
            menu = false;
            break;
        case 5:
            size = 100000;
            menu = false;
            break;
        case 6:
            size = 1000000;
            menu = false;
            break;
        default:
            cout<< "Input not valid, please enter a valid option";
            break;
        }
    }
    cout<< "Size of the array: "<<size<<endl;

    //Declaring size and randomizing the array.
    //int arr[size];
    int* arr = new int[size];
     arr_size = size ;

    scramble_array(arr, arr_size);
      //print_arr(arr, arr_size);

    //Choose Method Menu
    menu = true;
    while(menu){

      cout<<"Choose Sorting Method"<<endl;
      cout<<" 1. Bubble Sort \n 2. Cocktail Sort \n 3. Insertion Sort \n 4. Merge Sort \n 5. Shell Sort \n 6. Selection Sort \n 7. Heap Sort \n 8. Quick Sort \n 9. Tree Sort \n 10. Bucket Sort \n 11. Radix Sort \n 12. Counting Sort"<<endl;
      cin>>menu_option;

      //Select Function
      auto start = high_resolution_clock::now();
      if(menu_option == 1){
            BubbleSort(arr, arr_size);
            menu = false;
      }
      else if( menu_option == 2){
            CocktailSort(arr,arr_size);
            menu = false;
      }
      else if( menu_option == 3){
            InsertionSort(arr,arr_size);
            menu = false;
      }
      else if( menu_option == 4){
            MergeSort(arr, 0,arr_size-1);
            menu = false;
      }
      else if( menu_option ==5){
            ShellSort(arr,arr_size);
            menu = false;
      }
      else if( menu_option == 6){
            SelectionSort(arr,arr_size);
            menu = false;
      }
      else if( menu_option == 7){
            HeapSort(arr,arr_size);
            menu = false;
      }
      else if( menu_option == 8){
            quickSort(arr,0,arr_size-1);
            menu = false;
      }
      else if( menu_option == 9){
            treeSort(arr, arr_size);
            menu = false;
      }
      else if( menu_option == 10){
            BucketSort(arr, arr_size);
            menu = false;
      }
      else if( menu_option == 11){
            radixsort(arr, arr_size);
            menu = false;
      }
      else if( menu_option == 12){
            CountSort(arr, arr_size);
            menu = false;
      }
      else{
            cout<<"Select a valid option";
      }
      auto stop = high_resolution_clock::now();
      auto duration = duration_cast<microseconds>(stop - start);
      cout << "Time of execution "<< duration.count() <<" microseconds"<< endl;
    }

    delete [] arr;
    return 0;
}
