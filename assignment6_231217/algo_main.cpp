#include "algo_svm_mnist.h"

int main(){

    // Train process.
    trainMnist();

    // Test process
    testMnist();

    // Single test
    cout << "Type in a number to get the prediction." << endl;
    while(!cin.eof()){
        int m;
        cin >> m;
        int prediction = randomTest(m);
        cout << "The prediction of the number is" << prediction << endl;
    }
   // getWrongOnes();
}