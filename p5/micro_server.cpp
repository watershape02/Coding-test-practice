#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int how_many300(vector<int> arr){
    int count = 0;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] == 300){
            count++;
        }
    }
    return count;
}
int how_many_600plus(vector<int> arr){
    int count = 0;
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] > 600){
            count++;
        }
    }
    return count;
}


int main(){
    int T, N; //테스트케이스의 개수, 서브프로그램의 개수
    vector<vector<int>> v;
    vector<int> result;
    int buff1;
    cin >> T;
    v.resize(T);
    for(int i=0; i<T; i++){
        cin >> N;
        for(int j=0; j < N; j++){
            cin >> buff1;
            v[i].push_back(buff1);
        }
    }
    int iresult, num300;
    for(int i=0; i<T; i++){
        num300 = how_many300(v[i]);
        sort(v[i].begin(), v[i].end());
        //300만 제거
        v[i].erase(remove(v[i].begin(), v[i].end(), 300), v[i].end());
        //600 넘어가는건 제거후 iresult에 그 개수만큼 반영
        iresult=how_many_600plus(v[i]);
        v[i].erase(remove_if(v[i].begin(), v[i].end(), [](int n) {
        return n > 600;
    }), v[i].end());
        if(!v[i].empty()){
            vector<int>::iterator p1 = v[i].begin();
            vector<int>::iterator p2 = v[i].end()-1;
            vector<int> failer;
            while(p1 < p2){
                if(*p1 + *p2 > 900){
                    failer.push_back(*p2);
                    p2--;
                }
                else{
                    p2--;
                    p1++;
                    iresult++;
                }
            }
            if(p1 == p2){
                failer.push_back(*p1);
            }
            if(failer.size() >= num300){
                iresult += failer.size();
            }
            else{
                iresult += failer.size();

                num300 -= failer.size();
                iresult += (num300 + 2) / 3;
            }
        cout << iresult << endl;
    }
    else{
        cout << iresult + (num300 + 2) / 3 << endl;
    }
}
}