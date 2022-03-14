// SD_Proiect1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");
bool IsSorted(vector<long long> v)
{
    for (auto index = v.begin() + 1; index != v.end(); index++)
    {
        if (*index < *(index - 1))
            return false;
    }

    return true;
}

void Merge(vector<long long>& v, long long l, long long r, long long m)
{
    vector<long long> half1(m - l + 1);
    vector<long long> half2(r - m);
    long long index1 = 0, index2 = 0;
    for (auto i = l; i <= m; i++)
        half1[index1++] = v[i];
    for (auto i = m + 1; i <= r; i++)
        half2[index2++] = v[i];
    auto index_half1 = half1.begin();
    auto index_half2 = half2.begin();
    while (index_half1 != half1.end() && index_half2 != half2.end())
    {
        if (*index_half1 < *index_half2)
        {
            v[l++] = *index_half1;
            index_half1++;
        }
        else
        {
            v[l++] = *index_half2;
            index_half2++;
        }
    }
    while (index_half1 != half1.end())
    {
        v[l++] = *index_half1;
        index_half1++;
    }
    while (index_half2 != half2.end())
    {
        v[l++] = *index_half2;
        index_half2++;
    }
}

void MergeSort(vector<long long>& v, long long l, long long r)
{
    if (l >= r)
        return;
    long long m = (r - l) / 2 + l;
    MergeSort(v, m + 1, r);
    MergeSort(v, l, m);
    Merge(v, l, r, m);
}

long long Pivot(vector <long long>& v, long long l, long long r)
{
    long long m = (r - l) / 2 + l;
    if (v[l] > v[m])
        swap(v[l], v[m]);
    if (v[l] > v[r])
        swap(v[l], v[r]);
    if (v[m] > v[r])
        swap(v[m], v[r]);
    long long pivot = v[m];
    swap(v[m], v[r - 1]);
    long long index = l;
    for (long long j = l; j < r - 1; j++)
        if (v[j] < pivot)
            swap(v[index++], v[j]);
    swap(v[index], v[r - 1]);
    return index;

}
long long Pivot_random(vector <long long>& v, long long l, long long r)
{
    long long rand_poz = rand() % (r - l) + l;
    swap(v[rand_poz], v[r]);
    long long index = l;
    for (long long j = l; j < r; j++)
        if (v[j] < v[r])
            swap(v[index++], v[j]);
    swap(v[index], v[r]);
    return index;

}

void QuickSort(vector <long long>& v, long long l, long long r)
{
    if (l >= r)
        return;
    long long partition_index = Pivot(v, l, r);
    QuickSort(v, l, partition_index - 1);
    QuickSort(v, partition_index + 1, r);

}
void QuickSort_Random(vector <long long>& v, long long l, long long r)
{
    if (l >= r)
        return;
    long long partition_index = Pivot_random(v, l, r);
    QuickSort(v, l, partition_index - 1);
    QuickSort(v, partition_index + 1, r);

}
void BubbleSort(vector <long long>& v, long long n)
{
    bool sw = false;
    for (auto i = 0; i < n - 1; i++)
    {
        for (auto j = i + 1; j < n; j++)
            if (v[i] > v[j])
            {
                swap(v[i], v[j]);
                sw = true;
            }
        if (sw == false)
            return;
    }
}
long long Max_Value(vector <long long>& v)
{
    long long Mx = v[0];
    for (auto index = v.begin() + 1; index != v.end(); index++)
        if (*index > Mx)
            Mx = *index;
    return Mx;
}
void CountSort(vector <long long>& v, long long power, long long base)
{
    vector <long long> Count(base);


    long long n = v.size();
    vector <long long> Output(n);

    for (long long index = 0; index < n; index++)
        Count[(v[index] / power) % base]++;


    for (long long i = 1; i < base; i++)
        Count[i] += Count[i - 1];

    for (long long index = n - 1; index >= 0; index--)
    {
        Output[Count[(v[index] / power) % base] - 1] = v[index];
        Count[(v[index] / power) % base]--;
    }

    for (long long i = 0; i < n; i++)
        v[i] = Output[i];
}
void RadixSort(vector <long long>& v, long long base)
{
    long long Mx = Max_Value(v);
    for (long long power = 1; Mx / power > 0; power *= base)
        CountSort(v, power, base);

}
void ShellSort(vector <long long>& v, long long n)
{
    for (long long gap = n >> 1 + 1; gap > 0; gap = gap >> 1)
        for (long long i = gap; i < n; i++)
        {
            long long temp = v[i];
            long long j;
            for (j = i; j >= gap && v[j - gap] > temp; j = j - gap)
                v[j] = v[j - gap];
            v[j] = temp;
        }
}
void CountSort_OpBiti(vector <long long>& v, long long power, long long base)
{
    vector <long long> Count(base);


    long long n = v.size();
    vector <long long> Output(n);

    for (long long index = 0; index < n; index++)
        Count[(v[index] >> power) % base]++;


    for (long long i = 1; i < base; i++)
        Count[i] += Count[i - 1];

    for (long long index = n - 1; index >= 0; index--)
    {
        Output[Count[(v[index] >> power) % base] - 1] = v[index];
        Count[(v[index] >> power) % base]--;
    }

    for (long long i = 0; i < n; i++)
        v[i] = Output[i];
}
void RadixSort_OpBiti(vector <long long>& v, long long base)
{
    long long Mx = Max_Value(v);
    for (long long kontor = 0; (Mx >> (kontor * base)) > 0; kontor++)
        CountSort_OpBiti(v, (kontor * base), (1 << base));


}
int main()
{

    long long MaxNumber;
    long long Size;
    while (fin >> Size >> MaxNumber)
    {
        vector<long long>v(Size);
        vector<long long>cv(Size);
        srand(time(NULL));
        fout << "Size = " << Size << " " << '\n' << "Max Number = " << MaxNumber << '\n' << "Elementele sunt in ordine aleatorie." << '\n' << '\n';
        for (long long i = 0; i < Size; i++)
        {
            long long RandomNum = rand() % MaxNumber;
            v[i] = RandomNum;
            cv[i] = v[i];
        }
        // Elementele sunt ordonate aleatoriu
        auto start = chrono::steady_clock::now();
        MergeSort(v, 0, v.size() - 1);
        auto stop = chrono::steady_clock::now();
        double elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "MergeSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        if (!(Size >= 10000000 && MaxNumber <= 1000))
        {
            for (long long i = 0; i < Size; i++)
                v[i] = cv[i];

            start = chrono::steady_clock::now();
            QuickSort(v, 0, Size - 1);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "QuickSort cu pivot = mediana din 3: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';

            for (long long i = 0; i < Size; i++)
                v[i] = cv[i];

            start = chrono::steady_clock::now();
            QuickSort_Random(v, 0, Size - 1);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "QuickSort cu pivot random: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';
        }
        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        start = chrono::steady_clock::now();
        sort(v.begin(), v.end());
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "STL_Sort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        start = chrono::steady_clock::now();
        RadixSort(v, 10);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 10: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        long long doi_opt = 1 << 8;
        start = chrono::steady_clock::now();
        RadixSort(v, doi_opt);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 2^8: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        start = chrono::steady_clock::now();
        RadixSort_OpBiti(v, 8);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort cu operatii pe biti in baza 2^8: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        long long doi_saispe = 1 << 16;
        start = chrono::steady_clock::now();
        RadixSort(v, doi_saispe);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 2^16: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        start = chrono::steady_clock::now();
        RadixSort_OpBiti(v, 16);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort cu operatii pe biti in baza 2^16: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        for (long long i = 0; i < Size; i++)
            v[i] = cv[i];

        start = chrono::steady_clock::now();
        ShellSort(v, Size);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "ShellSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        if (Size <= 10000)
        {
            for (long long i = 0; i < Size; i++)
                v[i] = cv[i];

            start = chrono::steady_clock::now();
            BubbleSort(v, Size);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "BubbleSort: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';

        }
        // Elementele sunt ordonate crescator
        fout << '\n' << '\n';
        fout << "Size = " << Size << " " << '\n' << "Max Number = " << MaxNumber << '\n';
        fout << "Elementele sunt sortate crescator." << '\n' << '\n';
        RadixSort_OpBiti(v, 16);

        start = chrono::steady_clock::now();
        MergeSort(v, 0, v.size() - 1);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "MergeSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';
        if (!(Size >= 10000000 && MaxNumber <= 1000))
        {
            start = chrono::steady_clock::now();
            QuickSort(v, 0, Size - 1);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "QuickSort cu pivot = mediana din 3: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';

            start = chrono::steady_clock::now();
            QuickSort_Random(v, 0, Size - 1);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "QuickSort cu pivot random: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';
        }
        start = chrono::steady_clock::now();
        sort(v.begin(), v.end());
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "STL_Sort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        start = chrono::steady_clock::now();
        RadixSort(v, 10);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 10: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        doi_opt = 1 << 8;
        start = chrono::steady_clock::now();
        RadixSort(v, doi_opt);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 2^8: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        start = chrono::steady_clock::now();
        RadixSort_OpBiti(v, 8);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort cu operatii pe biti in baza 2^8: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        doi_saispe = 1 << 16;
        start = chrono::steady_clock::now();
        RadixSort(v, doi_saispe);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 2^16: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        start = chrono::steady_clock::now();
        RadixSort_OpBiti(v, 16);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort cu operatii pe biti in baza 2^16: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        start = chrono::steady_clock::now();
        ShellSort(v, Size);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "ShellSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        start = chrono::steady_clock::now();
        BubbleSort(v, Size);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "BubbleSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        // Elementele sunt ordonate descrescator
        fout << '\n' << '\n';
        fout << "Size = " << Size << " " << '\n' << "Max Number = " << MaxNumber << '\n';
        fout << "Elementele sunt sortate descrescator." << '\n' << '\n';
        sort(v.begin(), v.end(), greater <>());

        start = chrono::steady_clock::now();
        MergeSort(v, 0, v.size() - 1);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "MergeSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());
        if (!(Size >= 10000000 && MaxNumber <= 1000))
        {
            start = chrono::steady_clock::now();
            QuickSort(v, 0, Size - 1);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "QuickSort cu pivot = mediana din 3: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';

            sort(v.begin(), v.end(), greater <>());

            start = chrono::steady_clock::now();
            QuickSort_Random(v, 0, Size - 1);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "QuickSort cu pivot random: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';

            sort(v.begin(), v.end(), greater <>());
        }
        start = chrono::steady_clock::now();
        sort(v.begin(), v.end());
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "STL_Sort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());

        start = chrono::steady_clock::now();
        RadixSort(v, 10);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 10: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());

        doi_opt = 1 << 8;
        start = chrono::steady_clock::now();
        RadixSort(v, doi_opt);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 2^8: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());

        start = chrono::steady_clock::now();
        RadixSort_OpBiti(v, 8);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort cu operatii pe biti in baza 2^8: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());

        doi_saispe = 1 << 16;
        start = chrono::steady_clock::now();
        RadixSort(v, doi_saispe);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort in baza 2^16: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());

        start = chrono::steady_clock::now();
        RadixSort_OpBiti(v, 16);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "RadixSort cu operatii pe biti in baza 2^16: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        sort(v.begin(), v.end(), greater <>());

        start = chrono::steady_clock::now();
        ShellSort(v, Size);
        stop = chrono::steady_clock::now();
        elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
        fout << "ShellSort: " << elapsed_time / 1e9 << " " << '\n';

        if (IsSorted(v))
            fout << "Elementele sunt sortate.";
        else fout << "Elemenetele nu sunt sortate.";

        fout << '\n' << '\n';

        if (Size <= 10000)
        {
            for (long long i = 0; i < Size; i++)
                v[i] = cv[i];

            start = chrono::steady_clock::now();
            BubbleSort(v, Size);
            stop = chrono::steady_clock::now();
            elapsed_time = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
            fout << "BubbleSort: " << elapsed_time / 1e9 << " " << '\n';

            if (IsSorted(v))
                fout << "Elementele sunt sortate.";
            else fout << "Elemenetele nu sunt sortate.";

            fout << '\n' << '\n';

        }

        fout << '\n' << '\n' << '\n' << '\n';

    }





}

