#include <iostream>
#include <vector>
using namespace std;


int main(){
    int  M, N, K, buff;
    vector<int> vM, vN;
    cin >> M >> N >> K;
    for(int i = 0; i < M; i++){
        cin >> buff;
        vM.push_back(buff);
    }
    for(int i = 0; i < N; i++){
        cin >> buff;
        vN.push_back(buff);
    }
    if(M > N) //never impossible
        cout << "normal";
        
    else if(M == N){
        int flag = 1;
        for(int i = 0; i < M; i++){
            if(vM[i] != vN[i]){
                flag = 0;
                cout << "normal";
                break;
            }
        }
        if(flag == 1)
            cout << "secret";    
    }

    else{
        int flag = 1;
        for(int i = 0; i + M <= N; i++){
            flag = 1;
            for(int j =0; j < M; j++){
                if(vN[i + j] != vM[j]){
                    flag = 0;
                    break;
                }
            }
            if(flag == 1){
                cout << "secret";
                break;
            }
        }
        if(flag == 0){
            cout << "normal";
        }
    }
    return 0;
}
