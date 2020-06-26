#include <iostream>
#include <fstream>
using namespace std;
struct metszesfa {
    int** szom;
    int** pont;
    int pontszam;
};
int** elek1, ** pontok1, ** szomszed1, * levelek1, gyoker1, n1;
int** elek2, ** pontok2, ** szomszed2, * levelek2, gyoker2, n2;
void bitstringcreator(int n, int* k, int akt);
int sz, levelszam;
int** bitstrings;
void adathalmaz(int**& elek1, int**& pontok, int**& szomszed, int*& levelek, int& gyoker, const char* be, int& n1);
metszesfa metszes(int* bitstring, int* levelek, int levelszam, int** pontokn, int** szomszedn, int n, int gyoker);
metszesfa metszes2(int* bitstring, int* levelek, int levelszam, int** pontokn, int** szomszedn, int n, int gyoker);
bool isomorph(metszesfa fa1, metszesfa fa2, int gyoker1, int gyoker2);

int main()
{
    adathalmaz(elek1, pontok1, szomszed1, levelek1, gyoker1, "be1.txt", n1);
    adathalmaz(elek2, pontok2, szomszed2, levelek2, gyoker2, "be2.txt", n2);
    int n = levelszam;
    int* k = new int[6];
    int x = pow(2, n);
    bitstrings = new int* [x];
    for (int q = 0; q < x; q++)
    {
        bitstrings[q] = new int[n];
    }
    sz = 0;
    bitstringcreator(levelszam, k, 0);
    metszesfa maxfa1,maxfa2;
    int maxpontszam = 0;
    for (int p = 0; p < x; ++p) {
        for (int i = 0; i < x; ++i)
        {
            metszesfa fa1, fa2;
            fa1 = metszes2(bitstrings[i], levelek1, levelszam, pontok1, szomszed1, n1, gyoker1);
            fa2 = metszes2(bitstrings[p], levelek2, levelszam, pontok2, szomszed2, n2, gyoker2);
            cout << &fa1.pont << " " << &fa2.pont << endl;
            for (int w = 0; w < levelszam; ++w)
            {
                cout << bitstrings[i][w];
            }
            cout << endl;
            for (int p = 1; p <= n1; ++p)
            {
                for (int e = 1; e <= n1; ++e)
                {
                    cout << fa1.szom[p][e] << " ";
                }
                cout << endl;
            }
            if (isomorph(fa1, fa2, gyoker1, gyoker2) == true)
            {
                int xe = 111;
                if (fa1.pontszam > maxpontszam)
                {
                    maxpontszam = fa1.pontszam;
                    maxfa1 = fa1;
                    maxfa2 = fa2;
                }
                //cout << endl << xe << endl;

            }
            /*for (int w = 0; w < levelszam; ++w)
            {
                cout << bitstrings[i][w];
            }
            cout << endl;
            for (int p = 1; p <= n1; ++p)
            {
                for (int e = 1; e <= n1; ++e)
                {
                    cout << fa1.szom[p][e] << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (int c = 0; c <= 5; ++c)
            {
                for (int h = 1; h <= n1; ++h)
                {
                    cout << fa1.pont[c][h]<<" ";
                }
                cout << endl;
            }
            cout << endl;
            cout << fa1.pontszam << " "<<fa2.pontszam<<endl;
            for (int c = 0; c <= 5; ++c)
            {
                for (int h = 1; h <= n2; ++h)
                {
                    cout << fa2.pont[c][h] << " ";
                }
                cout << endl;
            }
         */   //system("pause");
        }
    }
    cout << maxpontszam;
    return 0;
}
bool isomorph(metszesfa fa1, metszesfa fa2, int gyoker1, int gyoker2)
{
    cout << gyoker1 << " " << gyoker2 << endl;
    //system("pause");
    if (fa1.pont[5][gyoker1] == 1 && fa2.pont[5][gyoker2] == 1)
    {
        return false;
    }
    else
    {
        if (fa1.pont[5][gyoker1] == 0 && fa2.pont[5][gyoker2] == 0)
        {
            int a1 = 0, b1 = 0, a2 = 0, b2 = 0;
            for (int i = 1; i <= n1; ++i)
            {
                if (fa1.szom[gyoker1][i] == 1 && i != fa1.pont[2][gyoker1])
                {
                    if (a1 == 0)
                        a1 = i;
                    else
                        b1 = i;
                }
            }
            for (int i = 1; i <= n2; ++i)
            {
                if (fa2.szom[gyoker2][i] == 1 && i != fa2.pont[2][gyoker2])
                {
                    if (a2 == 0)
                        a2 = i;
                    else
                        b2 = i;
                }
            }
            if ((isomorph(fa1, fa2, a1, a2) == true && isomorph(fa1, fa2, b1, b2) == true) || (isomorph(fa1, fa2, a1, b2) == true && isomorph(fa1, fa2, b1, a2) == true))
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    }
}
metszesfa metszes2(int* bitstring, int* levelek, int levelszam, int** pontokn, int** szomszedn, int n, int gyoker)
{
    metszesfa fa;
    fa.pontszam = n;
    int** szomszed = new int* [n + 1];
    int** pontok = new int* [6];
    for (int i = 1; i <= n1; i++)
    {
        szomszed[i] = new int[n + 1]();
    }
    for (int i = 0; i < 6; ++i)
    {
        pontok[i] = new int[n1 + 1]();
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            szomszed[i][j] = szomszedn[i][j];
        }
    }
    for (int i = 0; i <= 5; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            pontok[i][j] = pontokn[i][j];
        }
    }
    for (int i = 0; i < levelszam; ++i)
    {
        if (bitstring[i] == 0)
        {
            fa.pontszam--;
            int aktlevel = levelek[i + 1];
            pontok[5][aktlevel] = 0;
            for (int z = 1; z <= n; ++z)
            {
                if (szomszed[aktlevel][z] == 1)
                {
                    szomszed[aktlevel][z] = 0;
                    szomszed[z][aktlevel] = 0;
                }
            }
            if (pontok[3][aktlevel] != 0)
            {
                for (int q = 1; q <= n; q++)
                {
                    if (pontok[2][q] == pontok[2][aktlevel] && q != aktlevel)
                    {
                        pontok[3][q]--;
                    }
                }
            }
            else
            {
                pontok[5][pontok[2][aktlevel]] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int szamlalo = 0;
        int gyermek = 0;
        if (pontok[5][i] == 0 && i!=gyoker)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (j != pontok[2][i] && szomszed[i][j] == 1)
                {
                    szamlalo++;
                    gyermek = j;
                }
            }
            if (szamlalo == 1)
            {
                pontok[2][gyermek] = pontok[2][i];
                szomszed[gyermek][pontok[2][gyermek]] = 1;
                szomszed[pontok[2][gyermek]][gyermek] = 1;
                fa.pontszam--;
                for (int g = 1; g <= n; ++g)
                {
                    szomszed[g][i] = 0;
                    szomszed[i][g] = 0;
                }
            }
        }
    }
    fa.szom = szomszed;
    fa.pont = pontok;
    return fa;

}
metszesfa metszes(int* bitstring, int*levelek,int levelszam,int** pontokn,int** szomszedn,int n,int gyoker)
{
    metszesfa fa;
    fa.pontszam = n;
    int** szomszed = new int* [n+1];
    int** pontok = new int* [6];
    for (int i = 1; i <= n1; i++)
    {
        szomszed[i] = new int[n + 1]();
    }
    for (int i = 0; i < 6; ++i)
    {
        pontok[i] = new int[n1 + 1]();
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            szomszed[i][j] = szomszedn[i][j];
        }
    }
    for (int i = 0; i <= 5; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            pontok[i][j] = pontokn[i][j];
        }
    }
    for (int i = 0; i < levelszam; ++i)
    {
        if (bitstring[i] == 0)
        {
            fa.pontszam--;
            int aktlevel = levelek[i + 1];
            pontok[5][aktlevel] = 0;
            for (int z = 1; z <= n; ++z)
            {
                if (szomszed[aktlevel][z] == 1)
                {
                    szomszed[aktlevel][z] = 0;
                    szomszed[z][aktlevel] = 0;
                }
            }
            if (pontok[3][aktlevel] != 0 && pontok[2][aktlevel]!=gyoker)
            {
                for (int q = 1; q <= n; q++)
                {
                    if (pontok[2][q] == pontok[2][aktlevel] && q!=aktlevel)
                    {
                        bool qfigyelo = false;
                        for (int v = 0; v < levelszam; ++v)
                        {
                            if (bitstring[v] == 0 && levelek[v + 1] == q)
                            {
                                qfigyelo = true;
                                pontok[5][pontok[2][aktlevel]] = 1;
                            }
                        }
                        if (qfigyelo == false)
                        {
                            int os = pontok[2][q];
                            pontok[2][q] = pontok[2][pontok[2][q]];
                            fa.pontszam--;
                            szomszed[q][os] = 1;
                            szomszed[os][q] = 1;
                            for (int f = 1; f <= n; ++f)
                            {
                                szomszed[os][f] = 0;
                                szomszed[f][os] = 0;
                            }
                        }
                    }
                }
            }
            else
            {
                if (pontok[2][aktlevel] != gyoker)
                {
                    pontok[5][pontok[2][aktlevel]] = 1;
                }
            }

        }
    }
    fa.szom = szomszed;
    fa.pont = pontok;
    return fa;
    
}
void adathalmaz(int**& elek1, int**& pontok, int**& szomszed, int*& levelek, int& gyoker, const char* be, int& n1)
{
    ifstream in(be);
    if (!in.is_open()) {
        cout << "Error opening in_file\n";
    }
    in >> n1;
    cout << n1<<endl;
    /*elek1 = (int**)malloc((n1 - 1) * sizeof(int*));
    pontok = (int**)calloc(5, sizeof(int*));
    szomszed = (int**)calloc(n1 + 1, sizeof(int*));
    levelek = (int*)calloc(n1, sizeof(int));*/
    elek1= new int* [n1 - 1];
    pontok= new int* [6];
    szomszed= new int* [n1 + 1];
    levelek = new int[n1];

    for (int i = 0; i < n1 - 1; ++i)
    {
        //elek1[i] = (int*)malloc(2 * sizeof(int));
        elek1[i] = new int[2];
    }
    for (int i = 0; i < 6; ++i)
    {
        //pontok[i] = (int*)calloc(n1 + 1, sizeof(int));
        pontok[i] = new int[n1 + 1]();
    }
    for (int i = 1; i <= n1; i++)
    {
        //szomszed[i] = (int*)calloc(n1 + 1, sizeof(int));
        szomszed[i] = new int[n1 + 1]();
    }
    for (int i = 0; i < n1 - 1; ++i)
    {
        //fscanf(f, "%d %d", &elek1[i][0], &elek1[i][1]);
        in >> elek1[i][0];
        in >> elek1[i][1];
        //printf("%d - %d \n", elek1[i][0], elek1[i][1]);
        cout << elek1[i][0] << " - " << elek1[i][1]<<endl;
        pontok[0][elek1[i][0]]++;
        pontok[0][elek1[i][1]]++;
        szomszed[elek1[i][0]][elek1[i][1]] = 1;
        szomszed[elek1[i][1]][elek1[i][0]] = 1;
    }
    
    //fscanf(f, "%d", &gyoker);
    in >> gyoker;
    pontok[1][gyoker] = 1;
    for (int i = 0; i <= 1; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", pontok[i][j]);
            cout << pontok[i][j]<<" ";
        }
        cout << endl;
    }
    //printf("\n Szomszedsagi matrix \n");
    cout << endl << "Szomszedsagi matrix" << endl;
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", szomszed[i][j]);
            cout << szomszed[i][j]<<" ";
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
    //printf("levelek: \n");
    cout << "levelek: " << endl;
    for (int i = 1; i <= levelszam; ++i)
    {
        //printf("%d ", levelek[i]);
        cout << levelek[i] << " ";
        pontok[5][levelek[i]] = 1;
    }
    cout << endl;
    int aktualis = 1, vege = 2;
    //int* sor = (int*)calloc(n1 + 1, sizeof(int));
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
        while (aktual <= vege)
        {

            for (int j = 1; j <= n1; ++j)
            {
                if (szomszed[sor[aktual]][j] != 0 && (pontok[1][j] > pontok[1][sor[aktual]]))
                {
                    vege++;
                    sor[vege] = j;
                    szamlalo++;
                }
            }
            aktual++;
        }
        pontok[4][i] = szamlalo;

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

}
void bitstringcreator(int n, int* k, int akt) {
    bool figyelo = true;
    for (int i = 1; i >= 0; --i)
    {
        k[akt] = i;
        if (akt < n)
        {
            bitstringcreator(n, k, akt + 1);
        }
        else
        {
            if (figyelo == true)
            {
                for (int j = 0; j < n; ++j)
                {
                    bitstrings[sz][j] = k[j];
                    //cout << bitstrings[sz][j];
                }
                //cout << " " << sz << endl;
                sz++;
                figyelo = false;
            }
        }
    }


}
