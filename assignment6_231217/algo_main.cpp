#include "algo_svm_mnist.h"

int main(){

    // Train process.
    trainMnist();

    // Test process
    testMnist();

    // getWrongOnes();
    
    // Single test
    cout << "Type in 1 to start single test, or 0 to end the program." << endl;
    int i;
    cin >> i;
    if (i == 0){
        return 0;
    }else{
        cout << "Type in a number to get the prediction." << endl;
        while(!cin.eof()){
            int m;
            cin >> m;
            int prediction = randomTest(m);
            cout << "The prediction of the number is " << prediction << "." << endl;
        }
    }
    
   return 0;

}