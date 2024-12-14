#include <iostream>
#include <graphics.h>
using namespace std;

// Base class to draw and fill a polygon
class Polygon {
    protected:
        int vertices[4][2]; // Stores the coordinates of the polygon vertices
        int numVertices;

    public:
        Polygon() {

            vertices[0][0] = 150; vertices[0][1] = 50;
            vertices[1][0] = 250; vertices[1][1] = 300;
            vertices[2][0] = 150; vertices[2][1] = 250;
            vertices[3][0] = 50;   vertices[3][1] = 300;
            numVertices = 4;
        }

        void drawPolygon() {
            for (int i = 0; i < numVertices; i++) {
                int x1 = vertices[i][0];
                int y1 = vertices[i][1];
                int x2 = vertices[(i + 1) % numVertices][0];
                int y2 = vertices[(i + 1) % numVertices][1];
                line(x1, y1, x2, y2);
                delay(1000);
            }
        }
};

// Derived class to implement the scan-line fill algorithm
class ScanFill : public Polygon {
public:
    void fillPolygon() {
        // Find ymin and ymax
        int ymin = vertices[0][1], ymax = vertices[0][1];
        for (int i = 1; i < numVertices; i++) {
            if (vertices[i][1] < ymin) ymin = vertices[i][1];
            if (vertices[i][1] > ymax) ymax = vertices[i][1];
        }

        // Scan-line algorithm
        for (int y = ymin; y <= ymax; y++) {
            int intersections[10], count = 0;

            // Find intersection points
            for (int i = 0; i < numVertices; i++) {
                int x1 = vertices[i][0], y1 = vertices[i][1];
                int x2 = vertices[(i + 1) % numVertices][0];
                int y2 = vertices[(i + 1) % numVertices][1];

                if ((y >= y1 && y < y2) || (y >= y2 && y < y1)) {
                    float x = x1 + (float)(y - y1) * (x2 - x1) / (y2 - y1);
                    intersections[count++] = (int)x;
                }
            }

            // Sort intersection points
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (intersections[i] > intersections[j]) {
                        swap(intersections[i], intersections[j]);
                    }
                }
            }

            // Fill between pairs of intersections
            for (int i = 0; i < count; i += 2) {
                setcolor(RED);
                line(intersections[i], y, intersections[i + 1], y);
            }

            delay(50); // Delay for visualization
        }
    }
};

int main() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, NULL);

    ScanFill polygon;
    polygon.drawPolygon();
    polygon.fillPolygon();

    getch();
    closegraph();
    return 0;
}
