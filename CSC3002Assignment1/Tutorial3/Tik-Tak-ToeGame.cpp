#include <iostream>
#include <vector>

using namespace std;
int judge(vector< vector<int> > pan);
int available(vector< vector<int> > pan);
int visualize(vector< vector<int> > pan);

int main(){
    vector< vector<int> > pan(3, vector<int>(3, 0));
    visualize(pan);
    int count = 1;
    while(available(pan) && !judge(pan)){
        int x, y;
        cin >> x;
        cin >> y;
        pan[x - 1][y - 1] = count;
        if(count == 1){
            count = -1;
        }else{
            count = 1;
        }
        visualize(pan);
    }
    cout << "Game over!" <<endl;
}

int judge(vector< vector<int> > pan){
    return (abs(pan[0][0] + pan[0][1] + pan[0][2]) == 3) || (abs(pan[1][0] + pan[1][1] + pan[2][2]) == 3) || (abs(pan[2][0] + pan[2][1] + pan[2][2]) == 3) ||
    (abs(pan[1][0] + pan[2][0] + pan[0][0]) == 3) || (abs(pan[0][1] + pan[1][1] + pan[2][1]) == 3) || (abs(pan[0][2] + pan[1][2] + pan[2][2]) == 3) ||
    (abs(pan[0][0] + pan[1][1] + pan[2][2]) == 3) || (abs(pan[0][2] + pan[1][1] + pan[2][0]) == 3);
}

int available(vector< vector<int> > pan){
    int result = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            result += abs(pan[i][j]);
        }
    return result != 9;
}

int visualize(vector< vector<int> > pan){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(pan[i][j] == -1){
                if(j != 2){
                    cout << " X " << "|";
                }else{
                    cout << " X " <<endl;
                }
                
            }else if(pan[i][j] == 1){
                if(j != 2){
                    cout << " Y " << "|";
                }else{
                    cout << " Y " <<endl;
                }
            }else{
                if(j != 2){
                    cout << "   " << "|";
                }else{
                    cout << "   " << endl;;
                }
            }
        }
        if(i != 2)
            cout << "---+---+---" <<endl;
    }
}