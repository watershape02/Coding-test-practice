#include <iostream>
#include <string>
using namespace std;
string onoffList[10] =
{"1110111", "0010010", "1011101", "1011011", "0111010",
"1101011", "1101111", "1110010", "1111111", "1111011"};

/*
두 문자열을 자리별 비교하여, 다른 자리의 수를 반환한다. 
*/
int compare(string a, string b){
    int counter = 0;
    for(int i = 0; i < 7; i++){
        if(a[i] != b[i]){
            counter++;
        }
    }
    return counter;
}

// 두 정수를 넣어서, 숫자가 바뀔때, 눌러야하는 스위치의 개수를 반환한다.
int changeCounter(int before, int after){
    string strBefore = to_string(before);
    string strAfter = to_string(after);
    int beforeunit, afterunit;
    int differcount = 0;
    while(before != 0 || after != 0){
        beforeunit = before % 10; afterunit = after % 10;
        
        // 자릿수가 다른 수보다 낮아서, 더 안남은 경우
        if(before == 0)
            differcount += compare("0000000", onoffList[afterunit]);
        else if(after == 0)
            differcount +=compare(onoffList[beforeunit], "0000000");
        
        // 둘다 숫자가 있는 경우
        else{
            differcount += compare(onoffList[beforeunit], onoffList[afterunit]);
        }

        //10으로 나눠주면서, 각 자리수를 관찰한다.
        before /= 10; after /= 10;
    }
    return differcount;
}

int main() {
    int testcaseNumber;
    int testcase[1000][2];

    cin >> testcaseNumber;
    for(int i = 0; i<testcaseNumber; i++){
        cin >> testcase[i][0] >>testcase[i][1];
    }
    for(int i = 0; i<testcaseNumber; i++){
        cout << changeCounter(testcase[i][0], testcase[i][1]) << endl;
    }
    return 0;
}