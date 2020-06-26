#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
using namespace std;
int** elek1, ** pontok1, ** szomszed1, ** gyermekM1, * levelek1, * post1, gyoker1, n1,levelszam1;
int** elek2, ** pontok2, ** szomszed2, ** gyermekM2, * levelek2, * post2, gyoker2, n2,levelszam2;
int** mastM;
void bitstringcreator(int n, int* k, int akt);
int sz, MASTn=0;
int** bitstrings;
void adathalmaz(int**& elek1, int**& pontok, int**& szomszed, int**& gyermek, int*& levelek, int*& post, int& gyoker, const char* be, int& n1,int& levelszam);
void postorder(int**& pontok, int**& gyermekM, int aktual, int*& Pkoor, int& meret);
float hasonlit(int*& post1, int*& post2, int e1, int v1, int e2, int v2);
float hasonlit2(int*& post1, int*& post2, int e1, int v1, int e2, int v2);
void MAST(int cs1, int cs2, int**& pontok1, int**& pontok2, int*& post1, int*& post2, int**& gyermekM1, int**& gyermekM2, int e1, int v1, int e2, int v2);
void MAST2(int cs1, int cs2, int**& pontok1, int**& pontok2, int*& post1, int*& post2, int**& gyermekM1, int**& gyermekM2, int e1, int v1, int e2, int v2);
int comparequick(const void* a, const void* b);
int bsearchfunc(const void* a, const void* b);
int main()
{
    adathalmaz(elek1, pontok1, szomszed1, gyermekM1, levelek1, post1, gyoker1, "be11.txt", n1,levelszam1);
    adathalmaz(elek2, pontok2, szomszed2, gyermekM2, levelek2, post2, gyoker2, "be22.txt", n2,levelszam2);
    //MAST(gyoker1, gyoker2, pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, 1, levelszam1, 1, levelszam2);
    MAST2(gyoker1, gyoker2, pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, 1, levelszam1, 1, levelszam2);
    cout << endl << MASTn;
    return 0;

}
void MAST2(int cs1, int cs2, int**& pontok1, int**& pontok2, int*& post1, int*& post2, int**& gyermekM1, int**& gyermekM2, int e1, int v1, int e2, int v2)
{
    cout << cs1 << " " << cs2 << endl;
    if (e1 == v1 || e2 == v2)
    {
        if (cs1 == cs2)
        {
            MASTn++;
        }
        cout << "rekurzio vege" << endl;
    }
    else
    {
        int h1 = (e1 + v1) / 2;
        int h2 = (e2 + v2) / 2;
        int a = hasonlit2(post1, post2, e1, h1, e2, h2);
        int b = hasonlit2(post1, post2, e1, h1, h2 + 1, v2);
        int c = hasonlit2(post1, post2, h1 + 1, v1, e2, h2);
        int d = hasonlit2(post1, post2, h1 + 1, v1, h2 + 1, v2);
        if (a > b && c < d)
        {
            MAST(gyermekM1[cs1][1], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, e2, h2);
            MAST(gyermekM1[cs1][2], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1 + 1, v1, h2 + 1, v2);
        }
        else
        {
            if (b > a && c > d)
            {
                MAST(gyermekM1[cs1][1], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, h2 + 1, v2);
                MAST(gyermekM1[cs1][2], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1 + 1, v1, e2, h2);
            }
            else
            {
                if (a > b && c == d)
                {
                    MAST(gyermekM1[cs1][1], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, e2, h2);
                }
                if (a < b && c == d)
                {
                    MAST(gyermekM1[cs1][1], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, h2 + 1, v2);
                }
                if (a == b && c > d)
                {
                    MAST(gyermekM1[cs1][2], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1 + 1, v1, e2, h2);
                }
                if (a == b && c < d)
                {
                    MAST(gyermekM1[cs1][2], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1 + 1, v1, h2 + 1, v2);
                }
            }
        }


    }
}
void MAST(int cs1, int cs2,int**& pontok1, int**& pontok2, int*& post1, int*& post2,int**& gyermekM1, int**& gyermekM2, int e1, int v1, int e2, int v2)
{
    cout << cs1 << " " << cs2 << endl;
    if (e1 == v1 || e2 == v2)
    {
        if (cs1 == cs2)
        {
            MASTn++;
        }
        cout << "rekurzio vege"<<endl;
    }
    else
    {
        int h1 = (e1 + v1) / 2;
        int h2 = (e2 + v2) / 2;
        int a = hasonlit(post1, post2, e1, h1, e2, h2);
        int b = hasonlit(post1, post2, e1, h1, h2 + 1, v2);
        int c = hasonlit(post1, post2, h1 + 1, v1, e2, h2);
        int d = hasonlit(post1, post2, h1 + 1, v1, h2 + 1, v2);
        if (a > b && c < d)
        {
            MAST(gyermekM1[cs1][1], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, e2, h2);
            MAST(gyermekM1[cs1][2], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1+1, v1, h2+1, v2);
        }
        else
        {
            if (b > a && c > d)
            {
                MAST(gyermekM1[cs1][1], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, h2+1, v2);
                MAST(gyermekM1[cs1][2], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1 + 1, v1, e2, h2);
            }
            else
            {
                if (a > b && c == d)
                {
                    MAST(gyermekM1[cs1][1], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, e2, h2);
                }
                if (a < b && c == d)
                {
                    MAST(gyermekM1[cs1][1], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, e1, h1, h2+1, v2);
                }
                if (a == b && c > d)
                {
                    MAST(gyermekM1[cs1][2], gyermekM2[cs2][1], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1+1, v1, e2, h2);
                }
                if (a == b && c < d)
                {
                    MAST(gyermekM1[cs1][2], gyermekM2[cs2][2], pontok1, pontok2, post1, post2, gyermekM1, gyermekM2, h1 + 1, v1, h2+1, v2);
                }
            }
        }
        

    }
}
int comparequick(const void* a, const void* b)
{
    const int* x = (int*)a;
    const int* y = (int*)b;
    if (*x > * y)
        return 1;
    else if (*x < *y)
        return -1;
    return 0;
}
int bsearchfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
float hasonlit2(int*& post1, int*& post2, int e1, int v1, int e2, int v2)
{
    float s = 0;
    int* quickpost = new int[v2-e2+1];
    int j = -1;
    for (int i = e2; i <= v2; ++i)
    {
        ++j;
        quickpost[j] = post2[i];
    }
    qsort(quickpost, j, sizeof(int), comparequick);
    for (int i = e1; i <= v1; ++i)
    {
        int* item;
        int value = post1[i];
        item = (int*)bsearch(&value, quickpost, j+1, sizeof(int), bsearchfunc);
        if (item != NULL) {
            s=s+1;
        }
    }
    float n = (float)v1 - e1 + 1;
    float x = (s * 100) / n;
    return x;
}
float hasonlit(int*& post1, int*& post2, int e1, int v1, int e2, int v2)
{
    float s = 0;
    for (int i = e1; i <= v1; ++i)
    {
        for (int j = e2; j <= v2; j++)
        {
            if (post1[i] == post2[j])
            {
                s = s + 1;
            }
        }
    }
    float n = (float)v1 - e1 + 1;
    float x = (s * 100) / n;
    return x;
}
void postorder(int**& pontok, int**& gyermekM, int aktual, int*& post, int& meret)
{
    if (gyermekM[aktual][0] == 0)
    {
        //cout << aktual;
        if (pontok[5][aktual] == 1)
        {
            meret++;
            pontok[6][aktual] = meret;
            post[meret] = aktual;
        }
    }
    else
    {
        if (gyermekM[aktual][0] == 1)
        {
            int a = gyermekM[aktual][1];
            postorder(pontok, gyermekM, a, post, meret);
            //cout << aktual;
            if (pontok[5][aktual] == 1)
            {
                meret++;
                pontok[6][aktual] = meret;
                post[meret] = aktual;
            }

        }
        else
        {
            int a = gyermekM[aktual][1];
            int b = gyermekM[aktual][2];
            postorder(pontok, gyermekM, a, post, meret);
            postorder(pontok, gyermekM, b, post, meret);
            //cout << aktual;
            if (pontok[5][aktual] == 1)
            {
                meret++;
                pontok[6][aktual] = meret;
                post[meret] = aktual;
            }
        }
    }
}
void adathalmaz(int**& elek1, int**& pontok, int**& szomszed, int**& gyermekM, int*& levelek, int*& post, int& gyoker, const char* be, int& n1,int &levelszam)
{
    ifstream in(be);
    if (!in.is_open()) {
        cout << "Error opening in_file\n";
    }
    in >> n1;
    cout << n1 << endl;
    elek1 = new int* [n1 - 1];
    gyermekM = new int* [n1 + 1];
    pontok = new int* [7];
    szomszed = new int* [n1 + 1];

    levelek = new int[n1];
    post = new int[n1 + 1];
    for (int i = 0; i < n1 - 1; ++i)
    {
        elek1[i] = new int[2];
    }
    for (int i = 0; i < 7; ++i)
    {
        pontok[i] = new int[n1 + 1]();
    }
    for (int i = 1; i <= n1; i++)
    {
        szomszed[i] = new int[n1 + 1]();
    }
    for (int i = 0; i <= n1; ++i)
    {
        gyermekM[i] = new int[3]();
    }
    for (int i = 0; i < n1 - 1; ++i)
    {
        in >> elek1[i][0];
        in >> elek1[i][1];
        cout << elek1[i][0] << " - " << elek1[i][1] << endl;
        pontok[0][elek1[i][0]]++;
        pontok[0][elek1[i][1]]++;
        szomszed[elek1[i][0]][elek1[i][1]] = 1;
        szomszed[elek1[i][1]][elek1[i][0]] = 1;
    }

    in >> gyoker;
    pontok[1][gyoker] = 1;
    for (int i = 0; i <= 1; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            cout << pontok[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl << "Szomszedsagi matrix" << endl;
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", szomszed[i][j]);
            cout << szomszed[i][j] << " ";
        }
        cout << endl;
    }
    levelszam = 0;
    for (int i = 1; i <= n1; ++i)
    {
        if (pontok[0][i] == 1 && i != gyoker)
        {
            ++levelszam;
            levelek[levelszam] = i;
        }
    }
    cout << "levelek: " << endl;
    for (int i = 1; i <= levelszam; ++i)
    {
        cout << levelek[i] << " ";
        pontok[5][levelek[i]] = 1;
    }
    cout << endl;
    int aktualis = 1, vege = 2;
    int* sor = new int[n1 + 1]();
    sor[aktualis] = gyoker;
    for (int i = 1; i < n1; ++i)
    {
        int s = 1;
        int gyermek = 0;
        int gyel = vege;
        for (int j = 1; j <= n1; ++j)
        {

            if (szomszed[sor[aktualis]][j] == 1 && pontok[1][j] == 0)
            {
                sor[vege] = j;
                pontok[1][j] = pontok[1][sor[aktualis]] + 1;
                pontok[2][j] = sor[aktualis];
                vege++;
                gyermek++;
            }
        }
        for (int k = gyel; k < vege; k++)
        {
            pontok[3][sor[k]] = gyermek - 1;
        }
        aktualis++;
    }
    //printf("\n\n");
    cout << endl << endl;
    for (int i = 0; i <= 4; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", pontok[i][j]);
            cout << pontok[i][j] << " ";
        }
        cout << endl;
    }
    //printf("\n");
    cout << endl;
    for (int i = 1; i <= n1; ++i)
    {
        //printf("%d ", sor[i]);
        cout << sor[i] << " ";
    }

    for (int i = 1; i <= n1; ++i)
    {
        sor[1] = i;
        int szamlalo = 0;
        int aktual = 1;
        int vege = 1;
        gyermekM[i][0] = 0;
        while (aktual <= vege)
        {

            for (int j = 1; j <= n1; ++j)
            {

                if (szomszed[sor[aktual]][j] != 0 && (pontok[1][j] > pontok[1][sor[aktual]]))
                {
                    vege++;
                    sor[vege] = j;
                    szamlalo++;
                    /*gyermekM[sor[aktual]][0]++;
                    gyermekM[sor[aktual]][gyermekM[sor[aktual]][0]] = j;*/
                }
            }
            aktual++;
        }
        pontok[4][i] = szamlalo;
        for (int k = 1; k <= n1; ++k)
        {
            if (szomszed[i][k] != 0 && pontok[1][k] > pontok[1][i])
            {
                gyermekM[i][0]++;
                int gysz = gyermekM[i][0];
                gyermekM[i][gysz] = k;
            }
        }

    }
    //printf("\n\n");
    cout << endl << endl;
    for (int i = 0; i <= 5; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", pontok[i][j]);
            cout << pontok[i][j] << " ";
        }
        //printf("\n");
        cout << endl;
    }
    //printf("\n");
    cout << endl;
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 0; j <= 2; ++j)
        {
            cout << gyermekM[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    int m = 0;
    postorder(pontok, gyermekM, gyoker, post, m);

    /*cout << endl << endl;
    for (int i = 0; i <= 6; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", pontok[i][j]);
            cout << setw(3) << pontok[i][j] << " ";
        }
        //printf("\n");
        cout << endl;
    }
    //printf("\n");
    cout << endl;*/
    cout << endl;
    for (int i = 1; i <= levelszam; ++i)
    {
        cout << post[i] << " ";
    }
    cout << endl;
}