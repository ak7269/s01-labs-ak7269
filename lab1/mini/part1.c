#include <stdio.h>
#include <assert.h>

// Assign the value of 15 to the integer variable pointed
// to by ptr.
//
// This should only take one line of code!
void
set_to_fifteen(int *ptr)
{
	// TODO:
	*ptr=15;
}

// Return the sum of all elements in the given array.  The array
// "arr" has "n" elements.
//
// Note that before, we used pointers to reference single variables
// in memory, but now we are using them to refer to many elements.
// The "arr" pointer points to the first element in the array in memory.
// Because pointers themselves don't carry any length information
// (like array objects do in Java), we generally have to pass in a
// length parameter to functions which use pointers to reference
// arrays.
int
array_sum(int *arr, int n)
{
	// TODO: Your code here.
	int sum=0;
	for(int i=0;i<n;i++)
	{
	sum=sum+arr[i];

	}
	if(sum>=0)
	{
	return sum;
	}
	return -1;

}
