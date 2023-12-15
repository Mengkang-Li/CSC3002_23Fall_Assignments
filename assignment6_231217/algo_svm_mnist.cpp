#include "algo_svm_mnist.h"

int reverse(int m){
    /*
    This function is used to change Big-Edian data to Little-Edian data.
    */
    unsigned char c1, c2, c3, c4;
    // get every bit of the integer m
    c1 = m & 255;
    c2 = (m >> 8) & 255;
    c3 = (m >> 16) & 255;
    c4 = (m >> 24) & 255;
    // return the transformed integer.
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

Mat loadImgs(string s){

    /*
    The MNIST dataset consists of four int data at the head of the file.
    They are: data information(des); number of imgs; row of image; column of image;
    Use four number to get the information. 
    */
    ifstream is(s, ios::binary);

    // read data information
    int info;
    is.read((char*) &info, sizeof(info));
    info = reverse(info);
    
    // read number of imgs
    int numOfImgs;
    is.read((char*) &numOfImgs, sizeof(numOfImgs));
    numOfImgs = reverse(numOfImgs);

    // read row number of a single image
    int rowOfImg;
    is.read((char*) &rowOfImg, sizeof(rowOfImg));
    rowOfImg = reverse(rowOfImg);

    // read column number of a single image
    int colOfImg;
    is.read((char*) &colOfImg, sizeof(colOfImg));
    colOfImg = reverse(colOfImg);

    // SVM algo needs CV32FC1 Mat, so when read in img data, we need change the original CV8UC1 to CV32FC1
    // loading
    int imgSize = colOfImg * rowOfImg;
    Mat ans = Mat::zeros(numOfImgs, imgSize, CV_32FC1);

    for(int i = 0; i < numOfImgs; i++){
        Mat mid = Mat::zeros(rowOfImg, colOfImg, CV_8UC1);
        Mat temp = Mat::zeros(rowOfImg, colOfImg, CV_32FC1);
        is.read((char*) mid.data, imgSize);
        mid.convertTo(temp, CV_32FC1);
        memcpy(ans.data + i * imgSize * sizeof(float), temp.data, imgSize * sizeof(float));
    }

    // ormalization
    ans = ans / 255;
    return ans;
}

Mat loadLabels(string s){
    /*
    This is used to load labels of dataset.
    For label data set, the head consists of two features. One is file information, the other is number of labels.

    */

    // Load the file.
    ifstream is(s, ios::binary);
    // read file info
    int info;
    is.read((char*) &info, sizeof(info));
    info = reverse(info);

    // read number of labels
    int numOfLabels;
    is.read((char*) &numOfLabels, sizeof(numOfLabels));
    numOfLabels = reverse(numOfLabels);

    // load data to Mat. SVM model needs CV_32SC1, MNIST labels are CV_8UC1, before load first change it.
    // the data type of labels are numoflabels * 1
    // loading
    Mat ans;
    Mat mid = Mat::zeros(numOfLabels, 1, CV_8SC1);
    is.read((char*) mid.data, numOfLabels);
    mid.convertTo(ans, CV_32SC1);
    return ans;
}

void trainMnist(){
    /*
    This function is used to train an SVM model.
    */

    // create a model object 
    Ptr<SVM> svm = SVM::create();

    // set the parameters
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::RBF);
    svm->setC(5.0);
    svm->setGamma(0.018);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 200, FLT_EPSILON));

    // load data
    Mat img = loadImgs("data/train-images.idx3-ubyte");
    Mat labels = loadLabels("data/train-labels.idx1-ubyte");
    TrainData::create(img, ROW_SAMPLE, labels);
    // train the model
    svm -> train(img, ROW_SAMPLE, labels);
    // save the model
    svm -> save("svm_mnist.xml");
}   

void testMnist(){
    /*
    This function is to use trained model to get the accuracy on the test set.
    */

    // create an SVM model 
    Ptr<SVM> svm = SVM::create();

    // load the model
    svm = Algorithm::load<SVM>("svm_mnist.xml");

    // load data
    Mat imgs = loadImgs("data/t10k-images.idx3-ubyte");
    Mat labels = loadLabels("data/t10k-labels.idx1-ubyte");

    // predict
    Mat predictions;

    // get the accuracy
    int correct = 0;
    svm -> predict(imgs, predictions);
    for(int i = 0; i < predictions.rows; i++){
        if((int) predictions.at<float>(i, 0) == labels.at<int>(i, 0)){
            correct++;
        }
    }
    double accuracy = ((float) correct) / predictions.rows;

    cout << "Accuracy is: " << accuracy * 100 << "%" << endl;
}

int randomTest(int m){

    /*
    This function is used to get a random sequence number, then show the corresponding image, prediction and the real label.
    */
    // create an SVM model 
    Ptr<SVM> svm = SVM::create();

    // load the model
    svm = Algorithm::load<SVM>("svm_mnist.xml");

    // get some para of the data set 
    ifstream is("data/t10k-images.idx3-ubyte");
    int colOfImg, rowOfImg;
    is.ignore(2 * sizeof(colOfImg));
    is.read((char*) &rowOfImg, sizeof(rowOfImg));
    is.read((char*) &colOfImg, sizeof(colOfImg));
    rowOfImg = reverse(rowOfImg);
    colOfImg = reverse(colOfImg);
    is.close();

    // load data
    Mat imgs = loadImgs("data/t10k-images.idx3-ubyte");
    Mat labels = loadLabels("data/t10k-labels.idx1-ubyte");

    // start testing 
    Mat certain = Mat::zeros(1, rowOfImg * colOfImg, CV_32FC1);        
    memcpy(certain.data, imgs.data + m * rowOfImg * colOfImg * sizeof(float), rowOfImg * colOfImg * sizeof(float));
    int prediction = (int) svm -> predict(certain);
    return prediction;

}

void getWrongOnes(){
    /*
    This function is used to see which part of the set is predicted not correctly. 
    */
    Ptr<SVM> svm = SVM::create();

    // load the model
    svm = Algorithm::load<SVM>("svm_mnist.xml");

    Mat imgs = loadImgs("data/t10k-images.idx3-ubyte");
    Mat labels = loadLabels("data/t10k-labels.idx1-ubyte");
    Mat predictions;
    svm -> predict(imgs, predictions);
    for(int i = 0; i < predictions.rows; i++){
    if((int) predictions.at<float>(i, 0) != labels.at<int>(i, 0)){
            cout << i << endl;
        }
    }
    // load data
    ifstream is("data/t10k-images.idx3-ubyte");
    int colOfImg, rowOfImg;
    is.ignore(2 * sizeof(colOfImg));
    is.read((char*) &rowOfImg, sizeof(rowOfImg));
    is.read((char*) &colOfImg, sizeof(colOfImg));
    rowOfImg = reverse(rowOfImg);
    colOfImg = reverse(colOfImg);
    is.close();
    while(!cin.eof()){
        int m;
        cin >> m;
        Mat sampleImg = Mat::zeros(rowOfImg, colOfImg, CV_32FC1);
        memcpy(sampleImg.data, imgs.data + m * rowOfImg * colOfImg * sizeof(float), rowOfImg * colOfImg * sizeof(float));
        string s = "m = " + to_string(m) + " with prediction = " + to_string((int) predictions.at<float>(m, 0)) + ", lebel = " + to_string(labels.at<int>(m, 0));
        cout << s << endl;
        imshow(s, sampleImg);
        waitKey(500);
    }
}