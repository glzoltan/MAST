#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
int** elek1, ** pontok1, ** szomszed1,**gyermekM1, * levelek1,*Psor, gyoker1, n1;
int** elek2, ** pontok2, ** szomszed2,**gyermekM2, * levelek2,*Poszlop, gyoker2, n2;
int** mastM;
void bitstringcreator(int n, int* k, int akt);
int sz, levelszam;
int** bitstrings;
void adathalmaz(int**& elek1, int**& pontok, int**& szomszed,int**&gyermek, int*& levelek,int*& Pkoor, int& gyoker, const char* be, int& n1);
void postorder(int**& pontok, int**& gyermekM, int aktual, int*&Pkoor,int& meret);
void matrixepites(int**& mastM, int*& Psor, int*& Poszlop, int& n1, int& n2, int**& gyermekM1, int**& gyermekM2, int**& pontok1, int**& pontok2);
int MASTkitolt(int**& mastM,int fa1pont, int fa2pont, int**& gyermekM1, int**& gyermekM2,int& n1, int& n2, int**& pontok1, int**& pontok2);
void recMAST(int**& mastM, int fa1pont, int fa2pont, int**& gyermekM1, int**& gyermekM2, int**& pontok1, int**& pontok2);
int main()
{
    adathalmaz(elek1, pontok1, szomszed1, gyermekM1,levelek1,Psor, gyoker1, "be11.txt", n1);
    adathalmaz(elek2, pontok2, szomszed2, gyermekM2,levelek2,Poszlop, gyoker2, "be22.txt", n2);
    matrixepites(mastM, Psor, Poszlop, n1, n2,gyermekM1,gyermekM2,pontok1,pontok2);
    recMAST(mastM, gyoker1, gyoker2, gyermekM1, gyermekM2, pontok1, pontok2);
    return 0;

}
void recMAST(int**& mastM, int fa1pont, int fa2pont, int**& gyermekM1, int**& gyermekM2, int**& pontok1, int**& pontok2)
{
    int ertek = mastM[pontok1[6][fa1pont]][pontok2[6][fa2pont]];
    if (pontok1[5][fa1pont] == 1 && pontok2[5][fa2pont] == 1)
    {
        if (fa1pont == fa2pont)
        {
            cout << endl <<fa1pont << " " << fa2pont;
        }
    }
    else
    {
        if (pontok1[5][fa1pont] == 0 && pontok2[5][fa2pont] == 1)
        {
            int sor1 = gyermekM1[fa1pont][1];
            int sor2 = gyermekM1[fa1pont][2];
            int ertek1 = mastM[pontok1[6][sor1]][pontok2[6][fa2pont]];
            int ertek2 = mastM[pontok1[6][sor2]][pontok2[6][fa2pont]];
            if (ertek == ertek1)
            {
                recMAST(mastM, gyermekM1[fa1pont][1], fa2pont, gyermekM1, gyermekM2, pontok1, pontok2);
            }
            else
            {
                if (ertek == ertek2)
                {
                    recMAST(mastM, gyermekM1[fa1pont][2], fa2pont, gyermekM1, gyermekM2, pontok1, pontok2);
                }
            }
        }
        if (pontok1[5][fa1pont] == 1 && pontok2[5][fa2pont] == 0)
        {
            int oszlop1 = gyermekM2[fa2pont][1];
            int oszlop2 = gyermekM2[fa2pont][2];
            int ertek1 = mastM[pontok1[6][fa1pont]][pontok2[6][oszlop1]];
            int ertek2 = mastM[pontok1[6][fa1pont]][pontok2[6][oszlop2]];
            if (ertek == ertek1)
            {
                recMAST(mastM, fa1pont, gyermekM2[fa2pont][1], gyermekM1, gyermekM2, pontok1, pontok2);
            }
            else
            {
                if (ertek == ertek2)
                {
                    recMAST(mastM, fa1pont, gyermekM2[fa2pont][2], gyermekM1, gyermekM2, pontok1, pontok2);
                }
            }
        }
        if (pontok1[5][fa1pont] == 0 && pontok2[5][fa2pont] == 0)
        {
            int sor1 = gyermekM1[fa1pont][1];
            int sor2 = gyermekM1[fa1pont][2];
            int oszlop1 = gyermekM2[fa2pont][1];
            int oszlop2 = gyermekM2[fa2pont][2];
            int ertek1 = mastM[pontok1[6][sor1]][pontok2[6][oszlop1]];
            int ertek2 = mastM[pontok1[6][sor2]][pontok2[6][oszlop2]];
            int ertek3 = mastM[pontok1[6][sor1]][pontok2[6][oszlop2]];
            int ertek4 = mastM[pontok1[6][sor2]][pontok2[6][oszlop1]];
            if (ertek == ertek1+ertek2)
            {
                recMAST(mastM, gyermekM1[fa1pont][1], gyermekM2[fa2pont][1], gyermekM1, gyermekM2, pontok1, pontok2);
                recMAST(mastM, gyermekM1[fa1pont][2], gyermekM2[fa2pont][2], gyermekM1, gyermekM2, pontok1, pontok2);
                cout << endl << fa1pont << " " << fa2pont;
            }
            else
            {
                if (ertek == ertek3+ertek4)
                {
                    recMAST(mastM, gyermekM1[fa1pont][1], gyermekM2[fa2pont][2], gyermekM1, gyermekM2, pontok1, pontok2);
                    recMAST(mastM, gyermekM1[fa1pont][2], gyermekM2[fa2pont][1], gyermekM1, gyermekM2, pontok1, pontok2);
                    cout << endl << fa1pont << " " << fa2pont;
                }
            }
        }
        

    }
}
void matrixepites(int**& mastM, int*& Psor, int*& Poszlop, int& n1, int& n2, int**& gyermekM1, int**& gyermekM2, int**& pontok1, int**& pontok2)
{
    mastM = new int* [n1 + 1];
    for (int i = 0; i <= n1; ++i)
    {
        mastM[i] = new int[n2 + 1]();
    }
    for (int i = 1; i <= n1; ++i)
    {
        mastM[i][0] = Psor[i];
    }
    for (int i = 1; i <= n2; ++i)
    {
        mastM[0][i] = Poszlop[i];
    }
    for (int i = 0; i <= n1; ++i)
    {
        for (int j = 0; j <= n2; ++j)
        {
            cout << mastM[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 1; i <= n1; ++i)
    {
        for (int j = 1; j <= n2; ++j)
        {
           mastM[i][j]=MASTkitolt(mastM, mastM[i][0], mastM[0][j],gyermekM1,gyermekM2,n1,n2,pontok1,pontok2);
        }
    }
    cout << endl;
    for (int i = 0; i <= n1; ++i)
    {
        for (int j = 0; j <= n2; ++j)
        {
            cout << setw(3)<<mastM[i][j] << " ";
        }
        cout << endl;
    }
}
int MASTkitolt(int**& mastM, int fa1pont, int fa2pont, int**& gyermekM1, int**& gyermekM2, int& n1, int& n2,int**& pontok1, int**& pontok2)
{
    int eset = 0;
    if (pontok1[5][fa1pont] == 1 && pontok2[5][fa2pont] == 1)
    {
        eset = 1;
    }
    if (pontok1[5][fa1pont] == 1 && pontok2[5][fa2pont] == 0)
    {
        eset = 2;
    }
    if (pontok1[5][fa1pont] == 0 && pontok2[5][fa2pont] == 1)
    {
        eset = 3;
    }
    if (pontok1[5][fa1pont] == 0 && pontok2[5][fa2pont] == 0)
    {
        eset = 4;
    }
    switch (eset) {
        case 1:
        {
            if (fa1pont == fa2pont)
                return 1;
            else
                return 0;
            
        }
        case 2:
        {
            if (gyermekM2[fa2pont][0] == 1)
            {
                int a = gyermekM2[fa2pont][1];
                int oszlop = pontok2[6][a];
                int sor = pontok1[6][fa1pont];
                return mastM[sor][oszlop];
            }
            else
            {
                int a = gyermekM2[fa2pont][1];
                int b = gyermekM2[fa2pont][2];
                int oszlop1 = pontok2[6][a];
                int oszlop2 = pontok2[6][b];
                int sor = pontok1[6][fa1pont];
                if (mastM[sor][oszlop1] >= mastM[sor][oszlop2])
                    return mastM[sor][oszlop1];
                else
                    return mastM[sor][oszlop2];
            }
            
        }
        case 3:
        {
            if (gyermekM1[fa1pont][0] == 1)
            {
                int a = gyermekM1[fa1pont][1];
                int sor = pontok1[6][a];
                int oszlop = pontok1[6][fa2pont];
                return mastM[sor][oszlop];
            }
            else
            {
                int a = gyermekM1[fa1pont][1];
                int b = gyermekM1[fa1pont][2];
                int sor1 = pontok1[6][a];
                int sor2 = pontok1[6][b];
                int oszlop = pontok2[6][fa2pont];
                if (mastM[sor1][oszlop] >= mastM[sor2][oszlop])
                    return mastM[sor1][oszlop];
                else
                    return mastM[sor2][oszlop];
            }
          
        }
        case 4:
        {
            int* max= new int[7];
            //elsot az elsovel, masodikat a masodikkal
            int sor1 = gyermekM1[fa1pont][1];
            int oszlop1 = gyermekM2[fa2pont][1];
            sor1 = pontok1[6][sor1];
            oszlop1 = pontok2[6][oszlop1];
            
            int sor2 = gyermekM1[fa1pont][2];
            int oszlop2 = gyermekM2[fa2pont][2];
            sor2 = pontok1[6][sor2];
            oszlop2 = pontok2[6][oszlop2];
            max[1] = mastM[sor1][oszlop1] + mastM[sor2][oszlop2];


            //elsot masodikkal, masodikat az elsovel
             sor1 = gyermekM1[fa1pont][1];
             oszlop1 = gyermekM2[fa2pont][2];
            sor1 = pontok1[6][sor1];
            oszlop1 = pontok2[6][oszlop1];

             sor2 = gyermekM1[fa1pont][2];
             oszlop2 = gyermekM2[fa2pont][1];
            sor2 = pontok1[6][sor2];
            oszlop2 = pontok2[6][oszlop2];
            max[2] = mastM[sor1][oszlop1] + mastM[sor2][oszlop2];

            //elso gyokeret az elso gyermekkel
            int sor = pontok1[6][fa1pont];
            int oszlop = gyermekM2[fa2pont][1];
            oszlop = pontok2[6][oszlop];
            max[3] = mastM[sor][oszlop];

            //elso gyokeret a masodik gyermekkel
             sor = pontok1[6][fa1pont];
             oszlop = gyermekM2[fa2pont][2];
            oszlop = pontok2[6][oszlop];
            max[4] = mastM[sor][oszlop];

            //masodik gyokeret az elso gyermekkel
             sor = gyermekM1[fa1pont][1];
             oszlop = pontok2[6][fa2pont];
            sor = pontok1[6][sor];
            max[5] = mastM[sor][oszlop];

            //masodik gyokeret a masodik gyermekkel
             sor = gyermekM1[fa1pont][2];
             oszlop = pontok2[6][fa2pont];
            sor = pontok1[6][sor];
            max[6] = mastM[sor][oszlop];

            int retmax = -1;
            for (int i = 1; i <= 6; ++i)
            {
                if (max[i] > retmax)
                {
                    retmax = max[i];
                }
            }
            return retmax;
        }
        default:
            return -1;
    }
    return 1;
}
void postorder(int**& pontok, int**& gyermekM, int aktual, int*&Pkoor, int& meret)
{
    if (gyermekM[aktual][0] == 0)
    {
        //cout << aktual;
        meret++;
        pontok[6][aktual] = meret;
        Pkoor[meret] = aktual;
    }
    else
    {
        if (gyermekM[aktual][0] == 1)
        {
            int a = gyermekM[aktual][1];
            postorder(pontok, gyermekM, a,Pkoor,meret);
            //cout << aktual;
            meret++;
            pontok[6][aktual] = meret;
            Pkoor[meret] = aktual;
            
        }
        else
        {
            int a = gyermekM[aktual][1];
            int b = gyermekM[aktual][2];
            postorder(pontok, gyermekM, a, Pkoor, meret);
            postorder(pontok, gyermekM, b, Pkoor, meret);
            //cout << aktual;
            meret++;
            pontok[6][aktual] = meret;
            Pkoor[meret] = aktual;
        }
    }
}
void adathalmaz(int**& elek1, int**& pontok, int**& szomszed,int**&gyermekM, int*& levelek,int*& Pkoor, int& gyoker, const char* be, int& n1)
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
    Pkoor = new int[n1+1];
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
    postorder(pontok, gyermekM, gyoker, Pkoor, m);

    cout << endl << endl;
    for (int i = 0; i <= 6; ++i)
    {
        for (int j = 1; j <= n1; j++)
        {
            //printf("%d ", pontok[i][j]);
            cout << setw(3)<<pontok[i][j] << " ";
        }
        //printf("\n");
        cout << endl;
    }
    //printf("\n");
    cout << endl;
}