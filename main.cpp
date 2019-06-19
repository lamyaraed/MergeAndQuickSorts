/**
 *  @file    main.cpp
 *  @author  Mahmoud Ahmed Tawfik (20160227) - Sara Zakareia Adam (20170384) - Lamya Raed Aly (20170339)
 *  @date    31/03/2019
 *  @version 1.0
 *
 *  @Problem MergeAndQuick(P5)
 *
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <fstream>
using namespace std;
using namespace std::chrono;
void QuickSort(vector <int>&vec, int left, int right)
{
    int i = left;
    int j = right;
    int temp;
    int x= (left+right)/2 ;
    int pivot = vec.at(x);

    while (i<=j)
    {
        while ( vec.at(i)<pivot )
            i++;
        while ( vec.at(j)>pivot )
            j--;
        if (i<=j)
        {
            temp = vec.at(i);
            vec.at(i) = vec.at(j);
            vec.at(j) = temp;
            i++;
            j--;
        }
    }
    if( left<j )
        QuickSort(vec, left, j);
    if ( i<right )
        QuickSort(vec, i, right);
}

void merge(vector <int>&vec, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    vector <int> L(n1);
    vector <int> R(n2);
    for (i = 0; i < n1; i++)
        L.at(i)= vec.at(l+i);
    for (j = 0; j < n2; j++)
        R[j] = vec[m + 1+ j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            vec[k] = L[i];
            i++;
        }
        else
        {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>&vec, int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(vec, l, m);
        mergeSort(vec, m+1, r);

        merge(vec, l, m, r);
    }
}
void printVector(vector <int>&A, int size)
{
    int i;
    cout << "{";
    for (i=0; i < size; i++)
    {
        cout<< A[i];
        if (i+1 != size)
            cout <<",";
        if ((i+1) % 10 == 0)
            cout << endl;
    }
    cout << "}";
    cout << "\n";
}

int main()
{
    int x;
    ofstream GraphFile;
    GraphFile.open("Graph.csv", ios::app);
    vector <double> vec1time(20);
    vector <double> vec2time(20);
    x=0;
    int y=0;
    do
    {
        x+=5000;
        double d1,d2;
        vector <int> vec1(x);
        vector <int> vec2(x);
        for (int z=0; z<x; z++)
        {
            int tempValue;
            tempValue = rand()%x + 1;
            vec1[z]=tempValue;
            vec2[z]=tempValue;
        }
        int vec1_size = vec1.size();
        int vec2_size = vec2.size();

        auto start1 = high_resolution_clock::now();
        mergeSort(vec1, 0, vec1_size - 1);
        auto stop1 = high_resolution_clock::now();
        auto duration1 = duration_cast<milliseconds>(stop1 - start1);
        d1=duration1.count();
        vec1time[y]=d1;

        auto start2 = high_resolution_clock::now();
        QuickSort(vec2, 0, vec2_size - 1);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<milliseconds>(stop2 - start2);

        d2=duration2.count();
        vec2time[y]=d2;
        y++;

    }
    while (x<100000);
    int l=5000;
    GraphFile << "Data Size" << "," << "Merge Sort Time" << "," << "Quick Sort" <<endl;
    for (int k=0; k<vec1time.size(); k++)
    {
        GraphFile << l << "," << vec1time[k] << "," << vec2time[k] << endl;
        l+=5000;
    }
    cout << "Merge" <<endl;
    for (int i=0; i<20; i++)
    {
        cout << vec1time[i] <<" ";
    }
    cout << endl;
    cout << "Quick" <<endl;
    for (int i=0; i<20; i++)
    {
        cout << vec2time[i] <<" ";
    }

    return 0;
}
