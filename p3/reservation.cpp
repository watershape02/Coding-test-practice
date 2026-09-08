#include <iostream>
#include <string>
#include <map>
using namespace std;

int emptyCounter(string timeTable){
    int counter = 0;
    int i=0;
    while(i < 9){
        if(timeTable[i]=='1'){
            i++;
            continue;
        }
        else{
            counter++;
            while(timeTable[i+1] == '0' && i < 9){
                i++;
            }
            i++;
        }
    }
    return counter;
}
void print_info(string name, string timeTable){
    int start_idx, end_idx;
    cout << "Room " << name << ":\n";
    int empty = emptyCounter(timeTable);
    if(empty == 0){
        cout << "Not available" << endl;
    }
    else{
        cout << empty << " available:\n";
        int i = 0;
        while(i < 9){
            if(timeTable[i]=='1'){
                i++;
                continue;
            }
            else{
                start_idx = i;
                do{
                    i++;
                }while(i < 9 && timeTable[i] == '0');
                end_idx = i;
                if(start_idx==0)
                    cout <<"09-"<<end_idx+9<<endl;
                else
                    cout << start_idx + 9 << '-' << end_idx + 9 << endl;
            }
        }
    }
}
int main() {
    int room_num, reserve_num;
    string name_buff;
    map<string, string> m;
    cin >> room_num >> reserve_num;

    for(int i=0; i<room_num; i++){
        cin >> name_buff;
        m.insert({name_buff, "000000000"}); // 0: empty, 1:full
    }

    int start_time, end_time, start_idx, full_idx, full_num;
    for(int i=0; i<reserve_num; i++){
        cin >> name_buff >> start_time >> end_time;
        start_idx = start_time - 9;
        full_num = end_time - start_time;

        for(int j = start_idx; j < start_idx + full_num; j++){
            m[name_buff][j]='1';
        }
    }

    auto it = m.begin();
    print_info(it->first, it->second);
    it++;

    for(; it != m.end(); it++){
        cout << "-----" <<endl;
        print_info(it->first, it->second);
    }
    return 0;
}