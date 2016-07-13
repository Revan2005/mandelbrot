/*#include "mainwindow.h"
#include <QApplication>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;*/

#include "opencv2/opencv.hpp"

using namespace cv;

class Zespolniak{
public:
    double x;
    double y;
    Zespolniak(double a, double b);
};

Zespolniak::Zespolniak(double a, double b){
    x = a;
    y = b;
}

int drawPoint(Mat &picture, Zespolniak c);
void convertToPrint(Zespolniak &c);
void squareZespolniak(Zespolniak &c);
double distance(Zespolniak c1, Zespolniak c2);
//void convertFrom(Point &p);


double skala = 0.00002;
int w = 1000;
const int h = 1000;
double przesunieciePoziomo = 0.415;
double przesunieciePionowo = 0.34;
double bokPoziomo = w * skala;
double bokPionowo = h * skala;

Zespolniak poczatekObszaru(przesunieciePoziomo - bokPoziomo / 2, przesunieciePionowo - bokPionowo / 2);
Zespolniak koniecObszaru(przesunieciePoziomo + bokPoziomo / 2, przesunieciePionowo + bokPionowo / 2);


int main(int, char**)
{
    Mat picture(h, w, CV_8UC3, Scalar(0,0,0));
    namedWindow("Mandelbrot",1);

    /*
     * Point pt = Point(0, 0);
    convertTo(pt);
    Point pt2 = Point(-100, -50);
    convertTo(pt2);

    cv::circle(picture, pt, 5, Scalar(255, 255, 255));
    cv::circle(picture, pt2, 5, Scalar(255, 255, 255));
    */

    for(double a=poczatekObszaru.x; a<=koniecObszaru.x; a+=skala){
        for(double b=poczatekObszaru.y; b<=koniecObszaru.y; b+=skala){
            Zespolniak pt(a, b);
            //std::cout << "Sekwencja dla punktu " <<a << " + "<< b<< " i :"<<std::endl<<std::endl;
            drawPoint(picture, pt);
            //std::cout << std::endl << std::endl << std::endl;
        }
    }
    Zespolniak c00(0, 0);
    convertToPrint(c00);
    Point pt00(c00.x, c00.y);
    cv::line(picture, pt00, pt00, Scalar(255,0,0), 1);

    const String& text = "Mandelbrot";
    cv::putText(picture, text, Point(0,30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0, 255), 1);

    //string textPunktNiestatyczny = "punkt (" + przesunieciePoziomo + ", " + przesunieciePionowo + ")";

    Zespolniak srodek(przesunieciePoziomo, przesunieciePionowo);
    convertToPrint(srodek);
    Point srodekObrazka(srodek.x, srodek.y);
    std::ostringstream s;
    s << "(" << przesunieciePoziomo << ", " << przesunieciePionowo << ")";
    std::string napisSrodek = s.str();
    cv::putText(picture, napisSrodek, srodekObrazka, FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,255, 0), 1);
    cv::circle(picture, srodekObrazka, 1, Scalar(255, 0 ,0));

    imshow("Mandelbrot", picture);
    imwrite("Mandelbrot.jpg",picture);
    imwrite("Mandelbrot.png",picture);
    imwrite("Mandelbrot.bmp",picture);
    waitKey(0);
    return 0;
}

int drawPoint(Mat &picture, Zespolniak c){
    //Zespolniak sequencePrev(1, 1);
    Zespolniak sequence(0,0);
    int counter = 0;
    while(counter < 600){
        //std::cout<< sequence.x << " + " <<sequence.y << " i " << std::endl;
        //sequencePrev = sequence;
        squareZespolniak(sequence);
        sequence.x += c.x;
        sequence.y += c.y;
        counter++;
        if(distance(sequence, Zespolniak(0, 0)) >= 2){
            convertToPrint(c);
            Point p(c.x, c.y);
            if(counter < 100){
                Scalar kolor(0,0,0);
                cv::line(picture, p, p, kolor, 1);

            }
            if((100<=counter)&&(counter < 200)){
                Scalar kolor(255,0,0);
                cv::line(picture, p, p, kolor, 1);

            }
            if((200<=counter)&&(counter < 300)){
                Scalar kolor(0,255,0);
                cv::line(picture, p, p, kolor, 1);

            }
            if((300<=counter)&&(counter < 400)){
                Scalar kolor(0,0,255);
                cv::line(picture, p, p, kolor, 1);

            }
            if((400<=counter)&&(counter < 500)){
                Scalar kolor(255,255,0);
                cv::line(picture, p, p, kolor, 1);

            }
            if((500<=counter)&&(counter < 10000)){
                Scalar kolor(255,0,255);
                cv::line(picture, p, p, kolor, 1);
            }
            return 0;
        }
    }
    convertToPrint(c);
    Point p(c.x, c.y);
    cv::line(picture, p, p, Scalar(255,255,255), 1);
    return 1;
}

void convertToPrint(Zespolniak &p){
    p.x -= przesunieciePoziomo;
    p.y -= przesunieciePionowo;
    p.x *= 1/skala;
    p.y *= 1/skala;
    p.x = p.x + w/2;
    p.y = h - (p.y + h/2);
}

double distance(Zespolniak c1, Zespolniak c2){
    return sqrt( (c1.x - c2.x)*(c1.x - c2.x) + (c1.y - c2.y)*(c1.y - c2.y) );
}

void squareZespolniak(Zespolniak &c){
    Zespolniak tmpC(c.x, c.y);
    c.x = c.x*c.x - c.y*c.y;
    c.y = 2*tmpC.x*tmpC.y;
}


