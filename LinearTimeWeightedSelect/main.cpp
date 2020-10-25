/* linear time weighted select
10
256 760 591 761 621 446 774 555 342 67 
0.1124 0.0250 0.1149 0.1637 0.1073 0.0689 0.1819 0.1218 0.0646 0.0394 
591
*/
#include <iostream>
#define _MAX_N_ 1000
using namespace std;

struct Elem {
    int value;
    double weight;
} x[_MAX_N_];

void sort(int s, int e) {
	for (int i = s; i < e; i++)
		for (int j = i + 1; j <= e; j++)
			if (x[j].value < x[i].value)
				swap(x[j], x[i]);
}

// s : start
// e : end
// sv: standard value
int partition(int s, int e, int sv) {
    int i = s, j = e + 1;
	while (true) {
		while (x[++i].value < sv && i < e);
		while (x[--j].value > sv && j > s);
		if (i < j)
    		swap(x[i], x[j]);
        else
			break;
	}

	for (int k = s; k <= e; ++k)
		if (x[k].value == sv)
		{
			swap(x[k], x[j]);
			break;
		}
	return j;
}

// s : start
// e : end
int select(int s, int e, int ranking) {
    if (e - s < 10) {
        sort(s, e);
        return x[s + ranking].value;
    }

    for (int i = 0; i <= (e-s-4) / 5; ++i) {
        int gp = s + 5 * i;
        sort(gp, gp + 4);
        swap(x[s + i], x[gp + 2]);
    }

    int midval = select(s, s+(e-s-4)/5, (e-s-4)/10);

    int mid = partition(s, e, midval);
    int count = mid - s;

    if (ranking <= count) return select(s, mid, ranking);
    else return select(mid + 1, e, ranking - count - 1);
}

// s : start
// e : end
// tw : target weight
int weightedSelect(int s, int e, double tw) {
    if (e - s < 10) {
        sort(s, e);

        double sum = 0;
        for (int i = s; i < e; ++i) {
            sum += x[i].weight;
            if (sum >= tw)
                return x[i].value;
        }
    }

    int mid = (s + e) / 2;
    select(s, e, mid);

	double sum = 0;
	for (int i = s; i <= mid; ++i)
		sum += x[i].weight;

	if (tw <= sum) return weightedSelect(s, mid, tw);
	else return weightedSelect(mid + 1, e, tw - sum);
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> x[i].value;
    for (int i = 0; i < n; ++i)
        cin >> x[i].weight;

    cout << endl << weightedSelect(0, n-1, 0.5) << endl;

    return 0;
}
