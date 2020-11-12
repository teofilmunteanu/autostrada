/*
Trebuie să fie blocată o singură șosea din județ, astfel încât traficul să rămână posibil între oricare două localități. 
Cunoscând N numărul de localități din județ, acestea fiind codificate prin numere naturale din mulțimea 1, 2, …, N și 
M numărul de șosele care leagă direct câte două localități ale județului, să se afle K numărul de șosele care nu trebuie bloate și care sunt aceste șosele. 
Fiecare șosea este determinată în mod unic de două numere naturale X și Y reprezentând cele două localități legate direct de șosea.

Citire:
Pe prima linie N M două numere naturale reprezentând numărul de localități din județ, respectiv numărul de șosele directe între perechi distincte de localități, 
iar pe următoarele M linii perechi de numere naturale X Y, reprezentând codurile localităților legate direct prin șosea

Afișare:
Pe prima linie un singur număr natural K, reprezentând numărul de șosele care nu trebuie blocate, 
iar pe următoarele K linii se află câte o pereche de numere X Y, reprezentând numerele de ordine ale localităților între care există șosea ce nu trebuie blocată. 
Perechile sunt afișate în ordine lexicografică.
*/
#include <iostream>
#include <algorithm>

#define nmax 130

using namespace std;

struct abcd
{
    int x, y;
}v[nmax],sol[nmax];

int n, m,k;
bool a[nmax][nmax];
bool aux[nmax][nmax];

void mat_lant(int el);
bool comp_mat();
bool f(abcd a, abcd b);

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        a[x][y] = a[y][x] = true;
        v[++k].x = min(x,y);
        v[k].y = max(x,y);
    }
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (a[i][k] && a[k][j])
                {
                    a[i][j] = true;
                }
            }
        }
    }
    for (int it = 1; it <= k; ++it)
    {
        mat_lant(it);
        if (!comp_mat())
        {
            sol[0].x++;
            sol[sol[0].x].x = v[it].x;
            sol[sol[0].x].y = v[it].y;
        }
    }
    for (int i = 1; i < sol[0].x; ++i)
    {
        for (int j = i ; j <= sol[0].x; ++j)
        {
            if (sol[i].x > sol[j].x)
            {
                swap(sol[i], sol[j]);
            }
            else
            {
                if (sol[i].x == sol[j].x)
                {
                    if (sol[i].y > sol[j].y)
                    {
                        swap(sol[i], sol[j]);
                    }
                }
            }
        }
    }
    cout << sol[0].x << '\n';
    for (int i = 1; i <= sol[0].x; ++i)
    {
        cout << sol[i].x << ' ' << sol[i].y << '\n';
    }
}
void mat_lant(int el)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            aux[i][j] = aux[j][i] = false;
        }
    }

    for (int i = 1; i <= k; ++i)
    {
        if (i != el)
        {
            aux[v[i].x][v[i].y] = aux[v[i].y][v[i].x] = true;
        }
    }
    for (int k = 1; k <= n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (aux[i][k] && aux[k][j])
                {
                    aux[i][j] = true;
                }
            }
        }
    }

}
bool comp_mat()
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (aux[i][j] != a[i][j])
            {
                return false;
            }
        }
    }
    return true;
}