#include <iostream>
#include <stdlib.h> // for abs()
#include <algorithm>// for sort()

using namespace std;
#define MAX_N 50
#define MAX_M 13
#define INF 0x7FFFFFFF

typedef struct{
    int y, x;
}pos;

int N, M;
pos house[2 * MAX_N];
pos shop[MAX_M];
int H, S;   // H : number of house input, S : number of shop input
bool selected[MAX_M];
int solution = INF;

void Input(void){
    int tmp;

    cin >> N >> M;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++){
            cin >> tmp;

            if (tmp == 1)
                house[H++] = {y,x};
            else if (tmp == 2)
                shop[S++] = {y,x};
        }
}

int Chicken_Dist(pos p1, pos p2){
    int dist = abs(p1.y - p2.y) + abs(p1.x - p2.x);
    return dist;
}

int Get_Tot_Min_Dist(){
    int tot_min_dist = 0;
    
    for (int h = 0; h < H; h++){
        int min_dist = INF;

        for (int s = 0; s < MAX_M; s++){
            if (selected[s]){
                int tmp = Chicken_Dist(house[h], shop[s]);

                if (tmp < min_dist) min_dist = tmp;


                /* the below code is for debugging */
                // cout << "house : " << h <<", shop : " << s << ", tmp dist : " << tmp << endl;
                /////////////////////////////////////
            }
            if (min_dist == 1) break;
        }
        
        tot_min_dist += min_dist;
    }

    /* the below code is for debugging */
    // cout << "tot min dist : " << tot_min_dist << endl;
    /////////////////////////////////////
    return tot_min_dist;
}


void nCr(int n, int r, int index, int count){
    if(count == r){
        /* the below code is for debugging */
        // cout << "\nselected : ";
        // for (int s = 0; s < MAX_M; s++)
        //     if (selected[s]) cout << s << " ";
        // cout << endl;
        /////////////////////////////////////
        
        int tmp_min_dist = Get_Tot_Min_Dist();

        if (tmp_min_dist < solution) solution = tmp_min_dist;
        return;
    }
    
    for (int i = index; i < n; i++){
        if (selected[i]) continue;

        selected[i] = true;
        nCr(n, r, i, count+1);
        selected[i] = false;
    }
    
}

int Solve(){
    nCr(S, M, 0, 0);
    return solution;
}

int main(void){
    Input();
    cout << Solve();
    return 0;
}