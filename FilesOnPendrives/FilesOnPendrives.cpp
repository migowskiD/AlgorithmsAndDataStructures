#pragma warning(disable:4996)
#include <iostream>

using namespace std;

struct Files //struktura tworz¹ca pojedynczy plik
{
    int id;
    int size;
};


void swapfunction(Files f[], int p, int q)//funkcja zamieniajace elementy
{
    Files temp;
    temp.size = f[p].size;
    temp.id = f[p].id;
    f[p].size = f[q].size;
    f[p].id = f[q].id;
    f[q].size = temp.size;
    f[q].id = temp.id;

}


void quicks(Files f[], int start, int end)
{
    int p = start - 1, q = end + 1, pivot = f[(start + end) / 2].size;
    while (true)
    {
        while (f[--q].size > pivot); //szukamy mniejszego z prawej strony
        while (f[++p].size < pivot); //szukamy wiekszego z lewej
        if (p <= q)
            swapfunction(f, p, q);
        else break;
    }
    if (end > p)
        quicks(f, p, end);//sortowanie rekurencyjne prawej strony
    if (start < q)
        quicks(f, start, q);//sortowanie rekurencyjne lewej strony
}


void revquickid(Files f[], int start, int end)//sortowanie od najwiekszych po id
{
    int p = start - 1, q = end + 1, pivot = f[(start + end) / 2].id;
    while (true)
    {
        while (f[--q].id < pivot);
        while (f[++p].id > pivot);
        if (p <= q)
            swapfunction(f, p, q);
        else break;
    }
    if (end > p)
        revquickid(f, p, end);
    if (start < q)
        revquickid(f, start, q);
}


int main()
{
    int n, p;
    scanf("%d%d", &n, &p);
    Files* f = new Files[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &f[i].id, &f[i].size);
    }
    quicks(f, 0, n - 1);
    int k = 0, count = 0, check = 0;
    for (int i = 0; i < n; i++) //liczymy ile plikow wejdzie do pierwszego i drugiego pendrive
    {
        if (k + f[i].size <= p)
        {
            k += f[i].size;
            count++;
        }
        else if (check == 0)
        {
            k = 0;
            if (k + f[i].size <= p)
            {
                k += f[i].size;
                count++;
                check = i;
            }
            else break;
        }
    }
    //sortowanie po id
    revquickid(f, 0, check - 1);
    revquickid(f, check, count - 1);
    for (int i = 0; i < count; i++)
    {
        if (i == 0)
        {
            printf("%d\n1: ", count);
        }
        else if (i == check)
        {
            printf("\n2: ");
        }
        printf("%d ", f[i].id);
    }
    if (check == 0)
        printf("\n2: ");
    delete[] f;
}