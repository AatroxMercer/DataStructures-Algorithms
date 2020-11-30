#include <map>
#include <queue>
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>

// target : up left down right
const int route[9][4] = {
    {-1,-1,3,1},    {-1,0,4,2},     {-1,1,5,-1},
    {0,-1,6,4},     {1,3,7,5},      {2,4,8,-1},
    {3,-1,-1,7},    {4,6,-1,8},     {5,7,-1,-1}
};
const int _MAX_QUEUE_ = 9 * 8 *  7 * 6 * 5 * 4 * 3 * 2;
using namespace std;

class Frame {
public:
    int gap, step, status;

    Frame(int status, int gap, int step):
        status(status), gap(gap), step(step) {}
    
    Frame(char* str, int step):
        step(step) {
        this->status = Frame::calcStatus(str);
        this->gap = Frame::findNine(str);
    }

    // int calcCost() {
	// 	char str[10];
	// 	int count = 0;
    //     loadStatus(str);
	// 	for (int i = 0; i < 9; ++i)
	// 		if(str[i] != target[i])
	// 			count++;

    //     return (this->cost = count + this->step);
    // }

    void loadStatus(char* str) {
        sprintf(str, "%d", this->status);
    }

    static int findNine(char* str) {
        int index = -1;
        while (str[++index] != '9');
        return index;
    }

    static int calcStatus(char* str) {
        int temp;
        sscanf(str, "%d", &temp);
        return temp;
    }
};
queue<Frame> que;
map<int, bool> visited;

bool judgeSolvablity(char* origin, char* target) {
    int cnt_origin = 0;
    int cnt_target = 0;
    for (int i = 0; i < 9 - 1; ++i) {
        char curr_origin = origin[i];
        char curr_target = target[i];

        for (int j = i + 1; j < 9; ++j) {
            if (curr_origin > origin[j])
                cnt_origin++;
            if (curr_target > target[j])
                cnt_target++;
        }
    }

    return (cnt_origin % 2) == (cnt_target % 2);

}

int bfs(char* origin, char* target) {
    int goal = Frame::calcStatus(target);
    que.push(*new Frame(origin, 0));
    visited[que.front().status] = true;

    if (que.front().status == goal)
        return 0;
    
    while (!que.empty()) {
        Frame curr = que.front();
        char curr_str[10];
        curr.loadStatus(curr_str);

        que.pop();
        for (int i = 0; i < 4; ++i) {
            int swap_index = route[curr.gap][i];
            // check edge
            if (swap_index == -1) continue;

            swap(curr_str[curr.gap], curr_str[swap_index]);
            
            int curr_status = Frame::calcStatus(curr_str);
            if (curr_status == goal) // reach end
                return curr.step + 1;
            if (!visited[curr_status]) { // not visited
                que.push(*new Frame(curr_status, swap_index, curr.step + 1));
                visited[que.front().status] = true;
            }

            swap(curr_str[curr.gap], curr_str[swap_index]);
        }
    }
    return -1;
}


int main(int argc, char const *argv[])
{
    char origin[10], target[10];
    cin >> origin >> target;
    cout << origin << "--->" << target << endl;

    if (judgeSolvablity(origin, target))
        cout << bfs(origin, target) << endl;
    else
        cout << -1 << endl;
    
    return 0;
}
