/* Minimum Cost Tree
7 4
1 3 4 5
*/
#include <iostream>
#include <cstring>
#define inf 0x3f3f3f3f

using namespace std;

// pos : the coordinate of point
// cost : the best cost between i & j
int pos[200], cost[200][200];

// i: start position 
// j: end position
// return the real cost between i & j
int calc_cost(int i, int j) {
    if (j - i < 2)
        return 0;
    else 
        return cost[i][j];
}


// l: the total sum
// n: num of addend
// solve minimum cost tree problem
void dp(int l, int n) {
    // clean container
    memset(pos, 0, sizeof(pos));
    memset(cost, inf, sizeof(cost));

    // init data
    for (int i = 1; i <= n; ++i) {
        cin >> pos[i];
        cost[i][i] = 0;
    }
    pos[++n] = l;
    pos[0] = cost[0][0] = cost[n][n] = 0;

    // dp calculate answer
    for (int i = n - 1; i >= 0; --i)
        for (int j = i; j <= n; ++j)
            for (int k = i; k < j; ++k) {
                cost[i][j] = min(
                    cost[i][j], 
                    pos[j] - pos[i] + calc_cost(i, k) + calc_cost(k, j)
                    );
            }
    
    // output
    cout << cost[0][n] << endl;;

    // print dp matrix
    for (int j = 0; j <= n; j++){
        for (int i = 0; i <= j; i++)
             cout << cost[i][j] << "\t";
             cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    freopen("exp2_in.txt", "r", stdin);

    int l, n;
    cin >> l >> n;
    dp(l, n);

    return 0;
}
