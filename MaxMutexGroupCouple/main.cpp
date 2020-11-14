#include <stack>
#include <vector>
#include <cstring>
#include <iostream>
#define _MAX_H_ 1000
#define _MAX_L_ 20
using namespace std;

bool non_mutex[_MAX_L_][_MAX_L_];
bool matrix[_MAX_H_][_MAX_L_];

int ans, cnt_a, cnt_b;
vector<int> best_a, best_b;
vector<int> costlist[_MAX_L_];
bool curr_a[_MAX_L_], curr_b[_MAX_L_];

/*
    curr: current node index
    calculate the cost of picking curr node
*/ 
void calc_cost(int curr) {
    costlist[curr].clear();

    // cost of non mutex
    for (int i = 0; i < _MAX_L_; ++i)
        if (curr_b[i] && non_mutex[i][curr])
            costlist[curr].push_back(i);
    
    // self cost
    if (curr_b[curr])
        costlist[curr].push_back(curr);
}

// set new best answer
void build_up(bool flag = true) {
    best_a.clear();
    best_b.clear();
    // build up
    if (flag) {
        for (int i = 0; i < _MAX_L_; ++i)
            if (curr_a[i]) best_a.push_back(i);
            else if (curr_b[i]) best_b.push_back(i);
    }
    else
        for (int i = 0; i < _MAX_L_; ++i)
            if (curr_a[i]) best_b.push_back(i);
            else if (curr_b[i]) best_a.push_back(i);
    ans = cnt_a + cnt_b;
    // cout << "A" << cnt_a << " " << best_a.size() << endl;
    // cout << "B" << cnt_b << " " << best_b.size() << endl;
}

void judgeAnswer() {
    // strict better answer
    if (cnt_a + cnt_b > ans) {
        build_up(cnt_a >= cnt_b);
        return ;
    }

    // best differences
    int d_curr = abs(cnt_a - cnt_b);
    int d_ans = abs((int)best_a.size() - (int)best_b.size());

    if (d_curr > d_ans) return ;
    if (d_curr < d_ans) {
        build_up(cnt_a >= cnt_b);
        return ;
    }
    
    // biggest A
    if (max(cnt_a, cnt_b) > best_a.size()) {
        build_up(cnt_a >= cnt_b);
        return ;
    }

    // cheapest A
    int sum_curr = 0;
    for (int i = 0; i < _MAX_L_; ++i)
        if (curr_a[i]) sum_curr += i;
        else if (curr_b[i]) sum_curr -= i;

    int sum_best = 0;
    for (int i = 0; i < best_a.size(); ++i)
        sum_best += best_a[i];
    for (int i = 1; i < best_b.size(); ++i)
        sum_best -= best_b[i];

    if (-abs(sum_curr) < sum_best) {
        build_up(sum_curr > 0);
        return ;
    }

}

/*
    left: pick node
    right: drop node
*/
void backtrace(int depth) {
    // bound: no need to searcch
    if (cnt_a + cnt_b < ans) return ;

    // find one answer
    if (depth < _MAX_L_) {
        // calculate the cost of picking left node
        calc_cost(depth);

        // if the cost is bigger than feedback, drop left node
        // else pick left node
        // p.s. when choosing the first item of A, ignore cost
        if (costlist[depth].size() <= 1 || cnt_a == 0) {
            // go left
            cnt_a++;
            curr_a[depth] = true;
            cnt_b -= costlist[depth].size();
            for (int i = 0; i < costlist[depth].size(); ++i)
                curr_b[costlist[depth][i]] = false;
            backtrace(depth + 1);

            // recover
            cnt_a--;
            curr_a[depth] = false;
            cnt_b += costlist[depth].size();
            for (int i = 0; i < costlist[depth].size(); ++i)
                curr_b[costlist[depth][i]] = true;
        }

        // pick right node
        // cost of picking right node is always 0
        backtrace(depth + 1);
    } else {
    // searching answer
        if (cnt_a == 0 || cnt_a == _MAX_L_) return ;

        // a unchecked answer
        judgeAnswer();
    }
}

void mmgc() {
    // init
    ans = cnt_a = 0;
    cnt_b = _MAX_L_;
    best_a.clear();
    best_b.clear();
    memset(non_mutex, 0, sizeof(non_mutex));
    memset(curr_a, 0, sizeof(curr_a));
    for (int i = 0; i < _MAX_L_; ++i) {
        costlist[i].clear();
        curr_b[i] = true;
    }

    for(int i = 0; i < _MAX_H_; ++i)
        for (int j = 0; j < _MAX_L_; ++j)
            cin >> matrix[i][j];

    for (int i = 0; i < _MAX_L_; ++i)
        for (int j = i + 1; j < _MAX_L_; ++j)
            for (int h = 0; h < _MAX_H_; ++h)
                if (matrix[h][i] && matrix[h][j]) {
                    non_mutex[i][j] = non_mutex[j][i] = true;
                    break;
                }

    // judge solvablility
    for (int i = 0; i < _MAX_L_; ++i)
        for (int j = i+1; j < _MAX_L_; ++j)
            if (!non_mutex[i][j])
                backtrace(0);
}


int main(int argc, char const *argv[])
{
    freopen("exp_6.in", "r", stdin);

    int num;
    cin >> num;
    while (num--) {
        mmgc();
        // cout << "Total: " << ans << endl;
        // cout << best_a.size() << ":\t";
        for (int i = 0; i < best_a.size(); ++i)
            cout << best_a[i] << " ";
        cout << endl;
        // cout << best_b.size() << ":\t";
        for (int i = 0; i < best_b.size(); ++i)
            cout << best_b[i] << " ";
        cout << endl;
    }

    return 0;
}
