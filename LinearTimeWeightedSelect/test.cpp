#include <iostream>
#include <algorithm>
using namespace std;
struct po
{
    int num;
    double w;
    bool operator<(const po &a) { return num < a.num; };
} s[10000];

int select(po *c, int n, double p = 0.5) //通过分治进行查找
{
    if (n < 5)
    {
        sort(c, c + n);
        double wei = 0;
        for (int i = 0; i < n; i++)
        {
            wei = wei + c[i].w;
            if (wei >= p)
                return c[i].num;
        }
    }
    int tol = n;
    int i = 0;
    while (tol >= 5)
    {
        for (int i = 0; i < n / 5; i++)
        {
            sort(c + 5 * i, c + 5 * i + 5);
            swap(c[i], c[5 * i + 2]);
        }
        i = 0;
        tol = tol / 5;
    }
    po a = c[0];
    po *pos = partition(c, c + n, [a](po a1) { return a1.num < a.num; });
    int nl = pos - c;
    double wl = 0;
    double wll = 0;
    for (i = 0; i < nl; i++)
        wl = wl + c[i].w;
    wll = wl - c[i].w;
    if (wll < p && wl >= p)
        return a.num;
    else if (wl > p)
        return select(c, nl, p);
    else
        return select(c + nl + 1, n - nl - 1, p - wl);
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> s[i].num;
    for (int i = 0; i < n; ++i)
        cin >> s[i].w;

    cout << "带权中位数: " << select(s, 9, 0.5);
    return 0;
}
