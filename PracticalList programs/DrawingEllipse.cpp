#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<math.h>
using namespace std;

void plotpoints(int x, int y,int *p){
    putpixel(x+p[0],getmaxy()-(y+p[1]),255);
    putpixel(x+p[0],getmaxy()-(-y+p[1]),255);
    putpixel(-x+p[0],getmaxy()-(-y+p[1]),255);
    putpixel(-x+p[0],getmaxy()-(y+p[1]),255);
}

void Ellipse(int a,int b, int *p){
	int x=0,y=b;
	int sa=a*a;
	int sb=b*b;
	double d1=sb-sa*b+0.25*sa;
	plotpoints(x,y,p);
	while( sa*(y-0.5) > sb*(x+1)){ // Region 1
		if(d1<0) { //choose E   E= b^2 (2x + 3)
			d1+=sb*((2*x)+3);
		}
		else{	//choose SE    SE= b^2 (2x + 3) + a^2 (-2y + 2)
			d1+=sb*((2*x)+3) + sa*(-(2*y)+2);
			y--;
		}
		x++;
		plotpoints(x,y,p);
	}
	double d2 = sb*(x+0.5)(x+0.5) + sa(y-1)*(y-1) -sa*sb;
	while (y>0){ // Region 2
		if(d2<0){ // choose SE  SE= b^2 (2x + 2) + a^2 (-2y + 3)
			d2+= sb*((2*x)+2) + sa*(-(2*y)+3);
			x++;
		}
		else { // choose S    S= a^2 (-2y + 3)
			d2+= sa*(-(2*y)+3);
		}
		y--;
		plotpoints(x,y,p);
	}
}
int main(){
    int gd = DETECT, gm;
	char pathtodriver[] = "";
	initgraph(&gd, &gm, pathtodriver);
    int *p=new int(2);

	
    int a =50;
    int b =60;

    p[0]=200;
    p[1]=300;

	Ellipse(a,b,p);
    getch();
    closegraph();
    return 0;
}
