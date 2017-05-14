#include <math.h>
#include <algorithm>
#include <iostream>
#include "stdlib.h"
#include <ctime>
using namespace std;

int *a;
void quickSort(int l, int r){
int x = a[l + (r - l) / 2];
int i = l;
int j = r;
while(i <= j)
{
while(a[i] < x) i++;
while(a[j] > x) j--;
if(i <= j)
{
swap(a[i], a[j]);
i++;
j--;
}
}
if (i<r)
quickSort(i, r);

if (l<j)
quickSort(l, j);
}

using namespace std;
void introsort_r(int a[], int first, int last, int depth);
void _introsort(int a[], int n, int Min, int Max);
int _partition(int a[], int first, int last);
void _insertion(int a[], int n);
void _swap(int *a, int *b);
void _doheap(int a[], int begin, int end);
void _heapsort(int a[], int begin, int end);
bool _isSorted(int a[], int end);

void introsort_r(int a[], int first, int last, int depth){
  while(last - first > 0 ) {
		if(depth=0)
			_heapsort(&a[first], first,  last-first+1 );
		else {
			int pivot;
			if( _isSorted(a, last))
				break;
			pivot = _partition(a, first, last);
			introsort_r(a, pivot+1, last, depth-1);
			last = pivot -1;
		}
	}
}

void _introsort(int a[], int n,int Min,int Max){
	introsort_r ( a, 0, n-1, (int(2*log(double(n)))));
	_insertion(a, n);
}

int _partition ( int a[], int first, int last){
	int pivot, mid = (first+last)/2;

	pivot = a[first] > a[mid]  ? first : mid;

	if( a[pivot] > a[last])
		pivot = last;

	_swap( &a[pivot], &a[first] );
	pivot = first;

	while ( first < last ){
		if ( a[first] <= a[last] )
			_swap( &a[pivot++], &a[first] );
		++first;
	}

	_swap (&a[pivot], &a[last]);
	return pivot;
}

void _insertion ( int a[], int n ) {
	int i;
	for ( i = 1; i < n; i++ ) {
		int j, save = a[i];
		for ( j = i; j >= 1 && a[j - 1] > save; j-- )
			a[j] = a[j - 1];
		a[j] = save;
	}
}

void _swap(int *a, int *b){
	int save = *a;
	*a = *b;
	*b = save;
}
void _doheap(int a[], int begin, int end ){
	int save = a[begin];
	while (begin <= end /2) {
		int k = 2* begin;
		while ( k < end && a[k] <a[k+1])
			++k;
		if( save >= a[k])
			break;
		a[begin] = a[k];
		begin = k;
	}
	a[begin] = save;
}

void _heapsort(int a[], int begin, int end ){
	int i;
	for(int i = (end-1) / 2; i >= begin; i--){
		_doheap( a, i , end-1);
	}
	for( i=end-1; i>begin; i --){
		_swap( &a[i], &a[begin]);
		_doheap(a, begin, i-1);
		}
}
bool _isSorted(int a[], int end){
	for(int i=0; i<end; i++){
		if(a[i] > a[i+1]){
			return false;
		} else {
			return true;
		}
	}
	return true;
}
int main()
{int Min=1;
int *f; int n=0;
    int Max=100;
for(n= 1;n<Max*Max;n+=1000){

    a=new int [n];
    f=new int [n];
    for (int i=0;i<n;i++){
        a[i]=Min + rand() %Max;
        f[i]=Min + rand() %Max;
    }

    /*for (int p=0;p<n;p++)
        cout<<a[p]<<" ";
    cout<<endl;

    for (int p=0;p<n;p++)
        cout<<f[p]<<" ";
    cout<<endl;
    cout<<endl;*/

    unsigned int starttime_q =  clock();
    quickSort(0,n-1);
    unsigned int endtime_q = clock();
    unsigned int searchtime_q = endtime_q- starttime_q;
    unsigned int starttime_c =  clock();
    _introsort(a,n,Min,Max);
    unsigned int endtime_c = clock();
    unsigned int searchtime_c = endtime_c - starttime_c;


    cout<<searchtime_q<<"\t"<<searchtime_c<<"\t"<<n<<"\n";
    delete[]a;
    delete[]f;
}}



