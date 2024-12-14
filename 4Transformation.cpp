/*
Write C++ program to draw 2-D object and perform following basic transformations :-
 a)Scaling b)Translation c)Rotation. Apply the concept of operator overloading.
*/
#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

class Triangle {
    private :
        int x1, y1, x2, y2, x3, y3;
    public :
        Triangle(int a1, int a2, int b1, int b2, int c1, int c2) {
            x1 = a1 ; y1 = a2; x2 = b1; y2 = b2; x3 = c1; y3 = c2;
            display();
        }

        void display() {
            int xmid = getmaxx() / 2;
            int ymid = getmaxy() / 2;
            //show axis
            line(xmid, 0, xmid, getmaxy());
            line(0, ymid, getmaxx(), ymid);
            //Draw Triangle
            line(x1 + xmid, y1+ymid, x2 + xmid, y2+ymid);
            line(x2 + xmid, y2+ymid, x3 + xmid, y3+ymid);
            line(x3 + xmid, y3+ymid, x1 + xmid, y1+ymid);
        }

        Triangle operator +(const pair<int , int> &translation) {
            int tx = translation.first;
            int ty = translation.second;
            return Triangle(x1+tx, y1+ty, x2+tx, y2+ty, x3+tx, y3+ty);
        }

        Triangle operator *(const pair<int , int> &scaling) {
            int sx = scaling.first;
            int sy = scaling.second;
            return Triangle(x1*sx,y1*sy,x2*sx,y2*sy,x3*sx,y3*sy);
        }

        Triangle operator *(float angle) {
            angle = angle * (M_PI / 180);
            float c = cos(angle);
            float s = sin(angle);
            int nx1 = x1 * c - y1 * s;
            int ny1 = x1 * s + y1 * c;
            int nx2 = x2 * c - y2 * s;
            int ny2 = x2 * s + y2 * c;
            int nx3 = x3 * c - y3 * s;
            int ny3 = x3 * s + y3 * c;

            return Triangle(nx1, ny1, nx2, ny2, nx3, ny3);
        }
};

int main() {

    int gdrive = DETECT , gdmode;
    initgraph(&gdrive, &gdmode, NULL);

    int x1 = 0, y1 = 0, x2 = 100, y2 = 0, x3 = 50, y3 = -87;
    Triangle triangle(x1, y1, x2, y2, x3, y3);
    while(true) {
        int ch;
        cout<<"\n1.Translation. \n2.Scaling. \n3.Rotation. \n4.Exit. \nEnter your choice : ";
        cin>>ch;

        cleardevice();
        triangle.display();
        if(ch == 1) {
            int tx, ty;
            cout<<"\nEnter translation factors(tx,ty) : ";
            cin>>tx>>ty;

            delay(300);
            cleardevice();
            Triangle translated = triangle + make_pair(tx, ty);
            translated.display();
        }
        else if(ch == 2) {
            float sx, sy;
            cout<<"\nEnter scaling factors(sx, sy) : ";
            cin>>sx>>sy;

            delay(3000);
            cleardevice();
            Triangle scaled = triangle * make_pair(sx,sy);
            scaled.display();
        }
        else if(ch == 3) {
            float angle;
            cout<<"\nEnter angle of Rotation(Degrees) : ";
            cin>>angle;
            
            delay(3000);
            cleardevice();
            Triangle rotated = triangle * angle;
            rotated.display();
        }
        else if(ch == 4) {
            cout<<"\nExited. Thank you..."<<endl;
            break;
        }
        else {
            cout<<"\nInvalid choice. Try again!!"<<endl;
        }
    }

    getch();
    closegraph();
    return 0;
}