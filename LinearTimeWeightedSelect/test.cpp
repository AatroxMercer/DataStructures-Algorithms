#include <iostream>
#define _MAX_N_ 100000
using namespace std;

int x[_MAX_N_] = {9,8,7,0,3,6,4,2,1,5};

void sort(int s, int e) {
	for (int i = s; i < e; i++)
		for (int j = i + 1; j <= e; j++)
			if (x[j] < x[i])
				swap(x[j], x[i]);
}



/*
    s: start index
    e: end index
    psv: partition standard
*/
void partition(int s, int e, int psv) {
    int l = s;
    int r = e;
    int psi;

    while (l < r) {
        if (x[l] < psv)
            l++;
        else if (x[l] > psv) {
            swap(x[l], x[r--]);
        }
        else if (x[l] == psv)
            psi = l++;
    }

    swap(x[psi], x[l]);
}

int main(int argc, char const *argv[])
{
    partition(0, 9, 5);
    for (int i = 0; i < 10; ++i)
        cout << x[i] << " ";

    return 0;
}
