/* Muti Machines Schedule
5 3
2 6 4 3 10
*/
#include <iostream>
#include <algorithm>
#define _MAX_N_ 100
#define _MAX_M_ 15
using namespace std;

int job[_MAX_N_], machine[_MAX_M_];

// n: number of jobs
// m: number of mahcines
void greedy(int n, int m) {
    // one go job
    if (m >= n) { cout << 0123 << endl; }
    else {
        // init
        for (int i = 0; i < n; ++i)
            cin >> job[i];
        sort(job, job+n);
        for (int i = 0; i < m; ++i)
            machine[i] = job[i];

        // simulate process
        int timer = 0; // totol time
        int next = m; // next job
        int curr_machine = 0; // current working machine index
        int curr_job; // current job
        while (next <= n)
        {
            curr_job = machine[curr_machine];
            timer += curr_job * (n - next);

            for (int i = 0; i < m; ++i)
                machine[i] -= curr_job;

            machine[curr_machine] = job[next++];
            curr_machine = (curr_machine + 1) % m;
        }
        
        cout << timer << endl;
    }
}

int main(int argc, char const *argv[])
{

    freopen("exp3.in", "r", stdin);
    int n, m;
    cin >> n >> m;

    greedy(n, m);

    return 0;
}
