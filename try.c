#include <string.h>
#include <stdio.h>

#include <stdlib.h>

void
BinaryInsertionSort (int a[], int n)
{
    register int i, m;
    int hi, lo, tmp;

    for (i = 1; i < n; i++) {
        lo = 0, hi = i;
        m = i / 2;

        do {
            if (a[i] > a[m]) {
                lo = m + 1;
            } else if (a[i] < a[m]) {
                hi = m;
            } else
                break;

            m = lo + ((hi - lo) / 2);
        } while (lo < hi);

        if (m < i) {
            tmp = a[i];
            memmove (a + m + 1, a + m, sizeof (int) * (i - m));
            a[m] = tmp;
        }
    }
}
int main ()
{
	int a[100],i;
	for(i=0;i<100;i++)
	{
		a[i]=i;
	}
	a[50]=0;
	a[60]=10;
	BinaryInsertionSort(a,100);
	for(i=0;i<100;i++)
	{
		printf("a[%d]=%d\n",i,a[i]);
	}
   return(0);
}
