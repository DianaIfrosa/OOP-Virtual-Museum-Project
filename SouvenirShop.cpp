#include "SouvenirShop.h"
#include <fstream>
#include <iostream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include "cvui.h"
using namespace std;
using namespace cv;

const int v0 = 89;
const int v1 = 52;
const int v2 = 29;
const string generalpath = "./photos/souv";
const int waiting_time = 3000;

//singleton
SouvenirShop* SouvenirShop::shop=nullptr;

SouvenirShop::SouvenirShop(): room() {

	ifstream fin("souvenirs.in.txt");
	string name,price;
	while(fin>>name>>price)
		items.emplace_back(make_pair(name,price));

}
void SouvenirShop::Visit() {

	Mat frame = Mat(Size(1100, 600), CV_8UC3);
	cvui::init("Souvenir Shop", 10);

	while(true) {

		int xval=40, yval=120;
		frame = Scalar(v0, v1, v2); //colour
		cvui::text(frame, 40, 40, "Welcome to our Souvenir Shop!");
		cvui::text(frame, 40, 60,
		           "Call to our store (+40798765432) in order to purchase your favourite items and receive your order. The items and prices will be shown below.");
		cvui::text(frame, 40, 80, "Click 'See product' to see a picture of the specific product.");

		for(int i=0;i<items.size();++i) {
				cvui::text(frame, xval, yval, items[i].first);
				cvui::text(frame, xval+ items[i].first.length()*10 + 15, yval, items[i].second + " $");
				if(cvui::button(frame, xval+items[i].first.length()*10 + 100, yval-10, "See product"))
				{ string path=generalpath;

				  path+=to_string(i+1);
				  path+=".jpg";

				  Mat image = imread(path, IMREAD_UNCHANGED);
				  namedWindow(items[i].first, WINDOW_AUTOSIZE);
				  imshow(items[i].first, image);
				  setWindowProperty(items[i].first, WND_PROP_TOPMOST, 1); //aduce imaginea in fata ide-ului
				  waitKey(waiting_time);

				}
				  yval += 40;
			}
        if(cvui::button(frame, 1000, 20, "Exit"))
        	break;

		cvui::update();
		imshow("Souvenir Shop", frame);
		setWindowProperty("Souvenir Shop", WND_PROP_TOPMOST, 1); //aduce butonul in fata ide-ului

	}

	destroyAllWindows();

}
void SouvenirShop::Close() {

	cout<<"The museum shop has been closed!\n";
	state=false;

}



