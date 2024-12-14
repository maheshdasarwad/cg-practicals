/*
Write C++ program to implement Cohen Southerland line clipping algorithm.
*/

#include <iostream>
#include <graphics.h>
using namespace std;

int xmin = 50, ymin = 50, xmax = 300, ymax = 300;

class clipping
{
    private :
        int INSIDE = 0; // 0000
        int LEFT = 1;   // 0001
        int RIGHT = 2;  // 0010
        int BOTTOM = 4; // 0100
        int TOP = 8;    // 1000

    public :

        int computeCode(int x, int y) {
            int code = INSIDE;
            if(x < xmin) {
                code = LEFT;
            }
            else if(x > xmax) {
                code = RIGHT;
            }
            
            if(y < ymin) {
                code = BOTTOM;
            }
            else if(y > ymax) {
                code = TOP;
            }
            return code;
        }

        void cohenAlgo(int x1, int y1, int x2, int y2) {
            int code1 = computeCode(x1,y1);
            int code2 = computeCode(x2,y2);
            bool flag = false;

            while(true) {
                if(code1 == 0 && code2 == 0) {
                    flag = true;
                    break;
                }
                else if((code1 & code2) != 0) {
                    break;
                }
                else {
                    int x , y;
                    int codeOut;

                    if(code1 != 0){
                        codeOut = code1;
                    }
                    else {
                        codeOut = code2;
                    }

                    if((codeOut & TOP) != 0) {
                        x = x1 + (x2-x1)*(ymax - y1)/(y2-y1);
                        y = ymax;
                    }
                    else if((codeOut & BOTTOM) != 0) {
                        x = x1 + (x2-x1)*(ymin - y1)/(y2-y1);
                        y = ymin;
                    }
                    else if((codeOut & RIGHT) != 0) {
                        y = y1 + (y2 - y1)*(xmax-x1)/(x2-x1);
                        x = xmax;
                    }
                    else if((codeOut & LEFT) != 0) {
                        y = y1 + (y2-y1)*(xmin-x1)/(x2-x1);
                        x = xmin;
                    }

                    if(codeOut == code1) {
                        x1 = x;
                        y1 = y;
                        code1 = computeCode(x1,y1);
                    }
                    else {
                        x2 = x;
                        y2 = y;
                        code2 = computeCode(x2,y2);
                    }
                }
            }
            if(flag == true) {
                setcolor(GREEN);
                line(x1,y1,x2,y2);
            }
            else {
                line(x1,y1,x2,y2);
                cout<<"\nLine is outside the clipping window....!!!";
            }     
        }
};

int main()
{
    int gdrive = DETECT , gmode;
    initgraph(&gdrive, &gmode, NULL);

    // Draw clipping window
    setcolor(WHITE);
    rectangle(xmin, ymin, xmax, ymax);
    int x1,y1,x2,y2;
    cout<<"\nEnter the end points of line--->"<<endl;
    cout<<"Endpoint 1(x,y) : ";
    cin>>x1>>y1;
    cout<<"Endpoint 2(x,y) : ";
    cin>>x2>>y2;
    clipping obj;
    obj.cohenAlgo(x1,y1,x2,y2);

    getch();
    closegraph();
    return 0;
}