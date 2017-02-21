//
//  merge.cpp
//  Hw4
//
//  Created by Nilesh Gupta on 8/4/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//
#include <iostream>
using namespace std;

void merge(int data[],int n1, int n2, int &count)
{
	int i=0, j=0, k=0;
	int *temp = new int[n1+n2];
	int *sechalf = data + n1;
	
	while (i < n1 || j < n2)
	{
		if (i == n1)
			temp[k++] = sechalf[j++];
		else if (j == n2)
			temp[k++] = data[i++];
		else if (data[i] < sechalf[j])
			temp[k++] = data[i++];
		else
		{
			for(int l = i+1; l < n1; l++)
				if(data[l] > sechalf[j])
					count++;
			
			if(data[i] != sechalf[j])
				count++;
			temp[k++] = sechalf[j++];
		}
	}
	for (i=0;i<n1+n2;i++)
		data[i] = temp[i];
	delete [] temp;
}

void mergeSort(int data[], int n, int &inv)
{
	if(n == 1)
		return;
	
	mergeSort(data, n/2, inv);
	mergeSort(data + (n/2), n-(n/2), inv);
	
	merge(data, n/2, n-n/2, inv);
	
}

//int main()
//{
//	int arr[] = {1,2,5,3,4,2};
//	
//	int inv = 0;
//	mergeSort(arr, 6, inv);
//
//	cout << inv << endl;
//}