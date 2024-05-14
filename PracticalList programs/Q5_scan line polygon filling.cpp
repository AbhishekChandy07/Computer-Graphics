//Q5. Write a program to fill a polygon using Scan line fill algorithm. 


#include <iostream>
#include <graphics.h>
using namespace std;

const int WINDOW_HEIGHT = 1000; // Define your window height

typedef struct {
    int x;
    int y;
} dcPt;

typedef struct tEdge {
    int xUpper;
    float xIntersect, dxPerScan;
    struct tEdge *next;
} Edge;

void insertEdge(Edge *list, Edge *edge) {
    Edge *p, *q = list;
    p = q->next;
    while (p != NULL) {
        if (edge->xIntersect < p->xIntersect)
            break;
        else {
            q = p;
            p = p->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}

int yNext(int k, int cnt, dcPt *pts) {
    int j;
    if ((k + 1) > (cnt - 1))
        j = 0;
    else
        j = k + 1;
    while (pts[k].y == pts[j].y)
        if ((j + 1) > (cnt - 1))
            j = 0;
        else
            j++;

    return (pts[j].y);
}

void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge *edge, Edge *edges[]) {
    edge->dxPerScan = ((float)(upper.x - lower.x)) / (upper.y - lower.y);
    edge->xIntersect = lower.x;
    if (upper.y < yComp)
        edge->xUpper = upper.y - 1;
    else
        edge->xUpper = upper.y;
    insertEdge(edges[lower.y], edge);
}

void buildEdgeList(int cnt, dcPt *pts, Edge *edges[]) {
    Edge *edge;
    dcPt v1, v2;
    int i, yPrev = pts[cnt - 1].y;
    v1.x = pts[cnt - 1].x; v1.y = pts[cnt - 1].y;
    for (i = 0; i < cnt; i++) {
        v2 = pts[i];

        if (v1.y != v2.y) { // Non-horizontal line
            edge = (Edge *)malloc(sizeof(Edge));
            if (v1.y < v2.y) // Up-going edge
                makeEdgeRec(v1, v2, yNext(i, cnt, pts), edge, edges);
            else // Down-going edge
                makeEdgeRec(v2, v1, yPrev, edge, edges);
        }
        yPrev = v1.y;
        v1 = v2;
    }
}

void buildActiveList(int scan, Edge *active, Edge *edges[]) {
    Edge *p, *q;
    p = edges[scan]->next;
    while (p) {
        q = p->next;
        insertEdge(active, p);
        p = q;
    }
}

void fillscan(int scan, Edge *active) {
    Edge *pl = active->next, *p2;
    int i;

    while (pl && pl->next) {
        p2 = pl->next;
        for (i = pl->xIntersect; i < p2->xIntersect; i++)
            putpixel(i, scan, WHITE); // Assuming you want to fill with white color
        pl = p2->next;
    }
}

void deleteAfter(Edge *q) {
    Edge *p = q->next;
    q->next = p->next;
    free(p);
}

void updateActiveList(int scan, Edge *active) {
    Edge *q = active, *p = active->next;
    while (p)
        if (scan >= p->xUpper) {
            p = p->next;
            deleteAfter(q);
        }
        else {
            p->xIntersect = p->xIntersect + p->dxPerScan;
            q = p;
            p = p->next;
        }
}

void resortActiveList(Edge *active) {
    Edge *q, *p = active->next;
    active->next = NULL;
    while (p) {
        q = p->next;
        insertEdge(active, p);
        p = q;
    }
}

void scanFill(int cnt, dcPt *pts) {
    Edge *edges[WINDOW_HEIGHT], *active;
    int i, scan;

    for (i = 0; i < WINDOW_HEIGHT; i++) {
        edges[i] = (Edge *)malloc(sizeof(Edge));
        edges[i]->next = NULL;
    }

    buildEdgeList(cnt, pts, edges);
    active = (Edge *)malloc(sizeof(Edge));
    active->next = NULL;

    for (scan = 0; scan < WINDOW_HEIGHT; scan++) {
        buildActiveList(scan, active, edges);
        if (active->next) {
            fillscan(scan, active);
            updateActiveList(scan, active);
            resortActiveList(active);
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of points of the polygon: ";
    cin >> n;

    dcPt *pts = new dcPt[n + 1]; 

    cout << "Enter the coordinates of the points (x y format):\n";
    for (int i = 0; i < n; ++i) {
        cin >> pts[i].x >> pts[i].y;
    }

    pts[n] = pts[0]; 

    initwindow(800, 600, "Polygon Fill");
    setcolor(GREEN);
    drawpoly(n + 1, (int *)pts);
    delay(1000);

    scanFill(n + 1, pts); 

    delay(10000);
    closegraph();
    return 0;
}

