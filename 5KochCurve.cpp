/*
Write C++ program to generate fractal patterns by using Koch curves.
*/

#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void drawKochCurve(int x1, int y1, int x2, int y2, int depth) {
    if(depth == 0) {
        line(x1, y1, x2, y2);
        return;
    }

    //calculate the points dividing the line into thirds
    int x3 = x1 + (x2 - x1) / 3;
    int y3 = y1 + (y2 - y1) / 3;
    int x4 = x1 + 2 * (x2 - x1) / 3;
    int y4 = y1 + 2 * (y2 - y1) / 3;

    //calculate the tip of the equilateral triangle
    int midx = (x1+x2) / 2;
    int midy = (y1+y2) / 2;
    int peakx = midx + (y1 - y2) * sqrt(3) / 6;
    int peaky = midy + (x2 - x1) * sqrt(3) / 6;

    drawKochCurve(x1, y1, x3, y3, depth - 1);
    drawKochCurve(x3, y3, peakx, peaky, depth - 1);
    drawKochCurve(peakx, peaky, x4, y4, depth-1);
    drawKochCurve(x4, y4, x2, y2, depth-1);
    delay(50);
}

int main() {
    int gdrive = DETECT, gdmode;
    initgraph(&gdrive, &gdmode, NULL);

    int depth;
    cout<<"\nEnter the depth of the Koch Curve : ";
    cin>>depth;
    drawKochCurve(150, 20, 20, 280, depth);
    drawKochCurve(280, 280, 150, 20, depth);
    drawKochCurve(20, 280, 280, 280, depth);    

    getch();
    closegraph();
    return 0;
}