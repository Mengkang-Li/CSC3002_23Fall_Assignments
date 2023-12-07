#ifndef ALGO_SVM_MNIST_H
#define ALGO_SVM_MNIST_H

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include <fstream>

using namespace cv;
using namespace ml;
using namespace std;

Mat loadImgs(string s);
Mat loadLabels(string s);
void trainMnist();
void testMnist();
int randomTest(int m);
int reverse(int m);
void getWrongOnes();

#endif