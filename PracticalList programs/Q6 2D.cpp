//Q6. Write a program to apply various 2D transformations on a 2D object (use homogenous coordinates). 

#include<stdio.h>
#include<graphics.h>
#include<iostream>
#include<cmath>
using namespace std;
const int MAX=100;
void readPolygon(int edges, int polygon[][3]) 
{
    cout << "Enter the coordinates of the vertices:\n";
    for (int i = 0; i < edges; ++i) 
	{
        cout << "Vertex " << i + 1 << ": ";
        cin >> polygon[i][0] >> polygon[i][1];
        polygon[i][2] = 1; // Set the homogenous coordinate to 1
    }
}
void drawPolygon(int edges, int polygon[][3]) 
{
    for (int i = 0; i < edges; ++i) 
	{
        int j = (i + 1) % edges; 
        line(polygon[i][0], polygon[i][1], polygon[j][0], polygon[j][1]);
    }
}

void multiply(int mat1[][3], float mat2[][3], int res[][3], int r1, int c1, int r2, int c2) {
    if (c1 != r2) {
        // Matrices cannot be multiplied
        cout << "Error: Incompatible matrix sizes for multiplication." << endl;
        return;
    }

    // Perform matrix multiplication
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            res[i][j] = 0;
            for (int k = 0; k < c1; ++k) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int main()
{
 	int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
	int edges;
	 cout << "Enter the number of edges of the polygon: ";
	cin>>edges;
	int polygon[edges][3];
	int transformed[edges][3];
	readPolygon(edges, polygon);
	drawPolygon(edges, polygon);
	int choice;
    cout << "Choose the transformation:\n";
    cout << "1. Translation\n";
    cout << "2. Scaling\n";
    cout << "3. Rotation\n";
    

    double tx, ty, sx, sy;
    double x;
    float translate [3][3]= {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    float scale [3][3]={{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    float rotation [3][3]={
	        {1, 0, 0},
	        {0, 1, 0},
	        {0, 0, 1}};
    setcolor(RED);
    do
    {
    	cout << "Enter your choice: ";
    	cin >> choice;
	    switch (choice) 
		{
	        case 1:
	            cout << "Enter the translation parameters (tx ty): ";
	            cin >> tx >> ty;
	            translate[2][0]=tx;
	            translate[2][1]=ty;
	            multiply(polygon,translate,transformed,edges,3,3,3);
	            drawPolygon(edges, transformed);
	        	break;
	        case 2:
	            cout << "Enter the scaling factors (sx sy): ";
	            cin >> sx >> sy;
	            scale[0][0]=sx;
	            scale[1][1]=sy;
	            multiply(polygon,scale,transformed,edges,3,3,3);
	            drawPolygon(edges, transformed);
	            break;
	        case 3:
	            cout << "Enter the rotation angle (in degrees): ";
	            cin >> x;
	            x = x * (M_PI / 180); // Convert degrees to radians
	    		rotation[0][1] = -sin(x);   
	    		rotation[1][0] = sin(x);
	    		rotation[1][1] = cos(x);
		        multiply(polygon,rotation,transformed,edges,3,3,3);
		        drawPolygon(edges, transformed);
	            break;
	        default:
	            cout << "Invalid choice!";
	    }
	}while(choice<4);
    getch();
    closegraph();

    return 0;
}
