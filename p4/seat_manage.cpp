#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

int isDining[10001]={0, }; //각 id에 해당하는 사람들이 식사를 하고 있는지를 나타내는 배열(식사를 마치면, isDined로 이동)
int isDined[10001]={0, };
int seat[22][22]={0, }; //각 자리에 해당하는 id를 나타내는 배열(0이면 비어있음) 

int isCleanzone(int x, int y){
    return (seat[x][y]==0 && seat[x-1][y]==0 && seat[x+1][y]==0 && seat[x][y-1]==0 && seat[x][y+1]==0);
}
int is_completely_empty(int N, int M){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(seat[i][j]!=0) return 0;
        }
    }
    return 1;
}

int is_completely_filled(int N, int M){
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(seat[i][j]==0){ //상하좌우도 다 비어있는지 점검해야함. 
                if(isCleanzone(i, j)) return 0;
            }
        }
    }
    return 1;
}
unsigned int calculate_safety(int x, int y, vector<pair<int, int>> seated){
    unsigned int buffer;
    unsigned int safety = -1;
    for(auto iter =seated.begin(); iter !=seated.end(); iter++){
        buffer= (x-iter->first)*(x-iter->first)+(y-iter->second)*(y-iter->second);
        if(buffer < safety) safety = buffer;
    }
    return safety;
}


pair<int, int> safe_seat(int N, int M){ 
    vector<pair<int, int>> seated;
    vector<unsigned int> safe_rate;
    //현재 앉아 있는 좌석 확보
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(seat[i][j]!=0){
                seated.push_back(make_pair(i, j));
            }
        }
    }
    //비어있는 좌석들을 seated의 좌석들과 계산하여, 안전도를 쭉 조사한다.
    unsigned int safety;
    int x, y;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(seat[i][j]==0 && isCleanzone(i, j)){
                safety = calculate_safety(i, j, seated);
                safe_rate.push_back(safety);
            }
        }
    }
    //(비효율적이지만) 안전도의 최솟값에 해당하는 좌표를 순회로 찾는다.
    auto min_safety = max_element(safe_rate.begin(), safe_rate.end());
    unsigned int safe= *min_safety;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            if(safe == calculate_safety(i, j , seated))
                return make_pair(i, j); 
        }
    }
    exit(-1); //제대로 됐다면 반드시 위의 return에서 걸려야함.
}
int main(){
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<pair<string, int>> queries(Q); //in 1, out 2와 같은 command를 저장하는 데이터
    for(int i=0; i<Q; i++){
        cin >> queries[i].first >> queries[i].second;
    }

    for(int i=0; i<Q; i++){
        if(queries[i].first == "In"){
            //식사중이거나, 이미 식사를 한 경우
            if(isDined[queries[i].second]){     //식사를 이미 한 경우
                cout << queries[i].second << " already ate lunch." << endl;
            }
            else if(isDining[queries[i].second]){       //식사중인 경우
                cout << queries[i].second<< " already seated." << endl;
            }
            else{ //좌석 배정, 신경써야할것은, 배정을 받으면 isdining에 등록해야한다. 반대로 out에서 나갈때는 isdined에 등록하고 isdining은 배제
                if(is_completely_filled(N, M)){
                    cout << "There are no more seats." << endl;
                }
                else if(is_completely_empty(N, M)){
                    cout<< queries[i].second<<" gets the seat (1, 1)." << endl;
                    seat[1][1] = queries[i].second; 
                    isDining[queries[i].second]=1;
                }
                else{
                    pair<int, int> p = safe_seat(N, M);
                    cout<< queries[i].second<<" gets the seat (" << p.first << ", "<<p.second<< ")."<<endl;
                    seat[p.first][p.second] = queries[i].second;
                    isDining[queries[i].second] = 1;
                }
            }
        }
        else{   //command: Out
            if(isDining[queries[i].second]==0 && isDined[queries[i].second]==0){ //아직 식사를 하지 않은 경우
                cout<< queries[i].second << " didn't eat lunch." << endl;
            }
            else if(isDined[queries[i].second]==1){   //이미 다 먹고 떠남
                cout << queries[i].second << " already left seat." << endl;
            }
            else{
                int j, k;
                for(j=1; j<=N; j++){
                    for(k=1; k<=M; k++){
                        if(seat[j][k]==queries[i].second)
                            break;
                    }
                    if(seat[j][k]==queries[i].second)
                            break;
                }
                cout << queries[i].second << " leaves from the seat (" << j <<", " << k << ")." << endl;
                seat[j][k]=0;   isDining[queries[i].second] = 0;    isDined[queries[i].second] = 1;

            }
        }
    }
    
}