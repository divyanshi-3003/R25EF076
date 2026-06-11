#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 25
#define MAX_SHAPES 100

char canvas[HEIGHT][WIDTH];

enum
{
    RECTANGLE = 1,
    LINE,
    TRIANGLE,
    CIRCLE
};

typedef struct
{
    int type;

    int x1,y1;
    int x2,y2;
    int x3,y3;

    int width,height;
    int radius;

} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void clearCanvas()
{
    for(int i=0;i<HEIGHT;i++)
        for(int j=0;j<WIDTH;j++)
            canvas[i][j]='_';
}

void putPixel(int x,int y)
{
    if(x>=0 && x<WIDTH && y>=0 && y<HEIGHT)
        canvas[y][x]='*';
}

void drawLineCanvas(int x1,int y1,int x2,int y2)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int sx = (x1<x2)?1:-1;
    int sy = (y1<y2)?1:-1;

    int err = dx-dy;

    while(1)
    {
        putPixel(x1,y1);

        if(x1==x2 && y1==y2)
            break;

        int e2 = 2*err;

        if(e2>-dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2<dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangleCanvas(int x,int y,int w,int h)
{
    for(int i=x;i<x+w;i++)
    {
        putPixel(i,y);
        putPixel(i,y+h-1);
    }

    for(int j=y;j<y+h;j++)
    {
        putPixel(x,j);
        putPixel(x+w-1,j);
    }
}

void drawTriangleCanvas(int x1,int y1,int x2,int y2,int x3,int y3)
{
    drawLineCanvas(x1,y1,x2,y2);
    drawLineCanvas(x2,y2,x3,y3);
    drawLineCanvas(x3,y3,x1,y1);
}

void drawCircleCanvas(int cx,int cy,int r)
{
    for(int y=0;y<HEIGHT;y++)
    {
        for(int x=0;x<WIDTH;x++)
        {
            int d = (x-cx)*(x-cx) + (y-cy)*(y-cy);

            if(abs(d-r*r) <= r)
                putPixel(x,y);
        }
    }
}

void redrawCanvas()
{
    clearCanvas();

    for(int i=0;i<shapeCount;i++)
    {
        Shape s = shapes[i];

        switch(s.type)
        {
            case RECTANGLE:
                drawRectangleCanvas(
                    s.x1,s.y1,
                    s.width,s.height);
                break;

            case LINE:
                drawLineCanvas(
                    s.x1,s.y1,
                    s.x2,s.y2);
                break;

            case TRIANGLE:
                drawTriangleCanvas(
                    s.x1,s.y1,
                    s.x2,s.y2,
                    s.x3,s.y3);
                break;

            case CIRCLE:
                drawCircleCanvas(
                    s.x1,s.y1,
                    s.radius);
                break;
        }
    }
}

void displayCanvas()
{
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
            printf("%c",canvas[i][j]);

        printf("\n");
    }
}

void addShape()
{
    Shape s;

    printf("\n1.Rectangle\n2.Line\n3.Triangle\n4.Circle\n");
    printf("Choice: ");
    scanf("%d",&s.type);

    switch(s.type)
    {
        case RECTANGLE:
            printf("x y width height: ");
            scanf("%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.width,&s.height);
            break;

        case LINE:
            printf("x1 y1 x2 y2: ");
            scanf("%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.x2,&s.y2);
            break;

        case TRIANGLE:
            printf("x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.x2,&s.y2,
                  &s.x3,&s.y3);
            break;

        case CIRCLE:
            printf("centerX centerY radius: ");
            scanf("%d%d%d",
                  &s.x1,&s.y1,
                  &s.radius);
            break;
    }

    shapes[shapeCount++] = s;
    redrawCanvas();
}

void deleteShape()
{
    int index;

    printf("Shape index (0-%d): ",
           shapeCount-1);

    scanf("%d",&index);

    if(index<0 || index>=shapeCount)
        return;

    for(int i=index;i<shapeCount-1;i++)
        shapes[i]=shapes[i+1];

    shapeCount--;

    redrawCanvas();
}

void modifyShape()
{
    int index;

    printf("Shape index: ");
    scanf("%d",&index);

    if(index<0 || index>=shapeCount)
        return;

    Shape *s = &shapes[index];

    if(s->type==RECTANGLE)
    {
        printf("new x y width height: ");
        scanf("%d%d%d%d",
              &s->x1,&s->y1,
              &s->width,&s->height);
    }
    else if(s->type==LINE)
    {
        printf("new x1 y1 x2 y2: ");
        scanf("%d%d%d%d",
              &s->x1,&s->y1,
              &s->x2,&s->y2);
    }
    else if(s->type==TRIANGLE)
    {
        printf("new x1 y1 x2 y2 x3 y3: ");
        scanf("%d%d%d%d%d%d",
              &s->x1,&s->y1,
              &s->x2,&s->y2,
              &s->x3,&s->y3);
    }
    else if(s->type==CIRCLE)
    {
        printf("new centerX centerY radius: ");
        scanf("%d%d%d",
              &s->x1,&s->y1,
              &s->radius);
    }

    redrawCanvas();
}

int main()
{
    clearCanvas();

    int choice;

    while(1)
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1.Add Shape\n");
        printf("2.Delete Shape\n");
        printf("3.Modify Shape\n");
        printf("4.Display\n");
        printf("5.Exit\n");

        printf("Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                deleteShape();
                break;

            case 3:
                modifyShape();
                break;

            case 4:
                displayCanvas();
                break;

            case 5:
                return 0;
        }
    }
}
