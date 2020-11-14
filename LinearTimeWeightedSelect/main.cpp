#include <iostream>
#define _MAX_N_ 100000
using namespace std;

struct Element {
    int value;
    double weight;
} x[_MAX_N_];

/*
    s: start index
    e: end index
    psv: partition standard value
*/
int partition(int s, int e, int psv) {
    int l = s;
    int r = e;
    int psi;

    while (l < r)
        if (x[l].value < psv)
            l++;
        else if (x[l].value == psv)
            psi = l++;
        else
            swap(x[l], x[r--]);

    swap(x[psi], x[l]);
    return l;
}

void sort(int s, int e) {
	for (int i = s; i < e; i++)
		for (int j = i + 1; j <= e; j++)
			if (x[j].value < x[i].value)
				swap(x[j], x[i]);
}

// k : NO.k  start from 0
// ps: patition stantdard
Element select(int s, int e, int k) {
    if (e - s < 100) {
        sort(s, e);
        return x[s + k + 1];
    }

    for (int i = 0; i <= (e-s-4)/5; ++i) {
        int l = s + 5 * i;
        sort(l, l + 4);
        swap(x[s+i], x[l+2]);
    }

    Element ps = select(s, s + (e-s)/5 - 1, (e-s) / 10);
    int mid = partition(s, e, ps.value);
    int no_dot = mid - s;

    if (k > no_dot) return select(mid + 1, e, k- no_dot);
    return select(s, mid, k);
}

// tp: target percent
Element weightedSelect(int s, int e, double tp) {
    // short enough
    if (e - s < 100) {
        sort(s, e);

        double sum = .0;
        for (int i = s; i <= e; ++i) {
            sum += x[i].weight;
            if (sum >= tp)
                return x[i];
        }
    }
    
    // ranking of median
    // offset from start
    int ps_no = (e - s) / 2 - 1;
    Element ps = select(s, e, ps_no);

    double weight_left = .0;
    for (int i = 0; i <= ps_no; ++i)
        weight_left += x[s+i].weight;
    // cout << s << " " << ps_no << " " << e << endl;
    // cout << weight_left << " " << tp << endl;
    
    if (weight_left < tp) return weightedSelect(ps_no + s + 1, e, tp - weight_left);
    else return weightedSelect(s, s + ps_no, tp);
}

int main(int argc, char const *argv[])
{
    freopen("exp1_in.txt", "r", stdin);

    int times = 25;
    while (times--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> x[i].value;
        for (int i = 0; i < n; ++i)
            cin >> x[i].weight;

        cout << weightedSelect(0, n-1, 0.5).value << endl;
    }

    return 0;
}
