/*
Write C++ program to draw the following pattern. Use DDA line and Bresenham's circle 
drawing algorithm. Allpy the concept of encapsulation.
*/
#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

class pattern {
    public :
        void bresenham(int xc,int yc ,int r) {
            int xi = 0 ;
            int yi = r;

            int dp = 3 - 2*r;
            while(xi <= yi) {
                putpixel(xc+xi,yc+yi, WHITE);
                putpixel(xc-xi,yc+yi, WHITE);
                putpixel(xc+xi,yc-yi, WHITE);
                putpixel(xc-xi,yc-yi, WHITE);
                putpixel(xc+yi,yc+xi, WHITE);
                putpixel(xc-yi,yc+xi, WHITE);
                putpixel(xc+yi,yc-xi,WHITE);
                putpixel(xc-yi,yc-xi, WHITE);
                
                xi = xi + 1;
                if( dp < 0) {
                    dp = dp + 4*xi + 6;
                }
                else {
                    yi = yi - 1;
                    dp = dp + 4*(xi - yi) + 10;
                }
                delay(5);
            }
        }

        void dda(int x1 , int y1 , int x2 , int y2) {
            int dx , dy ;
            dx = (x2 - x1);
            dy = (y2 - y1);

            int steps;
            if( abs(dx) > abs(dy)) steps = abs(dx);
            else steps = abs(dy);

            float xinc , yinc;
            xinc = dx/(float)steps ;
            yinc = dy/(float)steps ;

            float x = x1 , y = y1;

            putpixel(round(x), round(y), WHITE);
            for(int i = 0 ; i < steps ; i++) {
                x = x + xinc;
                y = y + yinc;
                putpixel(round(x) , round(y) , WHITE);
                delay(5);
            }
        }
};

int main() {
    int gdrive = DETECT , gdmode;
    initgraph(&gdrive, &gdmode , NULL) ;

    float xc , yc, r;
    cout<<"\nEnter Center of circle and radius : (x,y,R) = ";
    cin>>xc>>yc>>r;
    pattern obj;
    //circles
    obj.bresenham(150,150,r);
    obj.bresenham(150,150,r/2);
    //triangle
    obj.dda(xc,yc-r,xc-0.86*r,yc+0.5*r);
    obj.dda(xc,yc-r,xc+0.86*r,yc+0.5*r);
    obj.dda((xc-0.866*r),yc+0.5*r,(xc+0.866*r),yc+0.5*r);

    getch();
    closegraph();
    return 0;
}