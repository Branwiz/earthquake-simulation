# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# define WIDTH 20
# define HEIGHT 20
# define RADIUS 6

typedef struct{
    int A[HEIGHT][WIDTH]; // Stress Level Array
    int B[HEIGHT][WIDTH]; // Fault Line Array
} SimulationData;

// Prototyping Functions
void drawVerticalLine(int x, SimulationData *data);
void drawHorizontalLine(int y, SimulationData *data);
void drawCircle(int centerX, int centerY, SimulationData *data);
void plotCirclePoints(int cx, int cy, int x, int y, SimulationData *data);
void drawLine(int x1, int y1, int x2, int y2, SimulationData *data);

void createFaultLines(SimulationData *data);
void displayFaultLines(const SimulationData *data);
void simulateStress(SimulationData *data);
void displayStress();

// Main
int main(){
    SimulationData simData={0};

    printf("\n\n\t\t********************\n\t\tEARTHQUAKE SIMULATOR\n\t\t********************\n\n");

    createFaultLines(&simData);
    simulateStress(&simData);

    return 0;
}


// Functions
void drawVerticalLine(int x, SimulationData *data){
    if(x<0 || x>=WIDTH){
        printf("Error: x value %d is out of range!\n", x);
        return;
    }
    for(int row=0; row<HEIGHT; row++){
        data->B[row][x]=1;
    }
}

void drawHorizontalLine(int y, SimulationData *data){
    if(y<0 || y>=HEIGHT){
        printf("Error: y value %d is out of range!\n", y);
        return;
    }
    for(int col=0; col<WIDTH; col++){
        data->B[HEIGHT-y-1][col]=1;
    }
}

void drawCircle(int centerX, int centerY, SimulationData *data){
    int radius=RADIUS;
    int x=0;
    int y=radius;
    int p=1-radius;

    plotCirclePoints(centerX, centerY, x, y, data);

    while(x<y){
        x++;
        if(p<0){
            p+=2*x+1;
        } 
        else{
            y--;
            p+=2*(x-y)+1;
        }
        plotCirclePoints(centerX, centerY, x, y, data);
    }
}

void plotCirclePoints(int cx, int cy, int x, int y, SimulationData *data){
    int transformedCy=HEIGHT-1-cy;

    if (cx+x < WIDTH && transformedCy+y < HEIGHT) data->B[transformedCy+y][cx+x]=1;
    if (cx-x >= 0 && transformedCy+y < HEIGHT) data->B[transformedCy+y][cx-x]=1;
    if (cx+x < WIDTH && transformedCy-y >= 0) data->B[transformedCy-y][cx+x]=1;
    if (cx-x >= 0 && transformedCy-y >= 0) data->B[transformedCy-y][cx-x]=1;
    if (cx+y < WIDTH && transformedCy+x < HEIGHT) data->B[transformedCy+x][cx+y]=1;
    if (cx-y >= 0 && transformedCy+x < HEIGHT) data->B[transformedCy+x][cx-y]=1;
    if (cx+y < WIDTH && transformedCy-x >= 0) data->B[transformedCy-x][cx+y]=1;
    if (cx-y >= 0 && transformedCy-x >= 0) data->B[transformedCy-x][cx-y]=1;
}

void drawLine(int x1, int y1, int x2, int y2, SimulationData *data){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    int sx=(x1<x2) ? 1 : -1;
    int sy=(y1<y2) ? 1 : -1;
    int err=dx-dy;

    while(1){
        if(x1>=0 && x1<WIDTH && y1>=0 && y1<HEIGHT){
            data->B[HEIGHT-y1-1][x1]=1;
        }
        if(x1==x2 && y1==y2){
            break;
        }
        int e2=err*2;
        if(e2>-dy){
            err-=dy;
            x1+=sx;
        }
        if(e2<dx){
            err+=dx;
            y1+=sy;
        }
    }
}

void createFaultLines(SimulationData *data){
    int choice;
    while(1){
        printf("\nPlease choose a fault line shape to generate...\n");
        printf("1: Vertical Line\n");
        printf("2: Horizontal Line\n");
        printf("3: Circle\n");
        printf("4: Point to Point Line\n");
        printf("-1: Begin Simulation\n\n");
        printf("ENTER: ");
        scanf("%d",&choice);

        if(choice==-1){
            break;
        }

        int x,y,x2,y2;
        switch (choice){
            case 1:
                printf("\nAt what X location would you like to place this vertical line? (0-%d)\n\nENTER: ", WIDTH-1);
                scanf("%d", &x);
                drawVerticalLine(x,data);
                break;
            case 2:
                printf("\nAt what Y location would you like to place this vertical line? (0-%d)\n\nENTER: ", HEIGHT-1);
                scanf("%d", &y);
                drawHorizontalLine(y,data);
                break;
            case 3:
                printf("At what X, Y location would you like to place this circle? (0-%d), (0-%d)\n\nENTER: ", WIDTH-1, HEIGHT-1);
                scanf("%d %d", &x, &y);
                drawCircle(x,y,data);
                break;
            case 4:
                printf("Enter X,Y of start point (0-%d), (0-%d): ", WIDTH-1, HEIGHT-1);
                scanf("%d %d", &x, &y);
                printf("Enter X,Y of end point (0-%d), (0-%d): ", WIDTH-1, HEIGHT-1);
                scanf("%d %d", &x2, &y2);
                drawLine(x,y,x2,y2,data);
                break;
            default:
                printf("Invalid option!\n");
        }

        displayFaultLines(data);
    }
}

void displayFaultLines(const SimulationData *data){
    printf("\n\n-----------------------\nPrinting the Fault Line\n-----------------------\n");
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            if(data->B[i][j]==1){
                printf("\033[31m1\033[0m\t");
            }
            else{
                printf("0\t");
            }
        }
        printf("\n\n");
    }
}

void simulateStress(SimulationData *data){
    srand(time(NULL));

    while(1){

        system("cls");

        int earthquake=0;

        printf("--------------------\nPrinting the Surface\n--------------------\n");
        for(int i=0;i<HEIGHT;i++){
            for(int j=0;j<WIDTH;j++){
                int *stress=&data->A[i][j];

                // Update Stresses 
                if(data->B[i][j]==1){
                    *stress+=rand()%11;
                }
                else{
                    *stress+=(rand()%11)-5;
                    if(*stress<0){
                        *stress=0;
                    }
                }

                // Earthquake Test
                if(*stress>=200){
                    earthquake=1;
                }

                // Printing
                if(*stress>=100){
                    printf("\033[31m%d\033[0m\t", *stress); // Red
                }
                else if(*stress>=50){
                    printf("\033[33m%d\033[0m\t", *stress); // Yellow
                }
                else{
                    printf("\033[32m%d\033[0m\t", *stress); // Green
                }
            }
            printf("\n\n");
        }
        if(earthquake){
            sleep(1);
            break;
        }
        // Delay Updata
        sleep(1);
    }

    // Earthquake Occured
    system("cls");
    printf("\n\n\n\033[1;31m******************************************************************************************************************************************************************\n\t\t\t\t\t\t\t\t\t\t\tEARTHQUAKE!!\n******************************************************************************************************************************************************************\033[0m\n\n\n");
    printf("--------------------\nPrinting the Surface\n--------------------\n");
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            int *stress=&data->A[i][j];

            // Printing Earthquake Surface
            if (*stress>=200) {
                printf("\033[31;43m%d\033[0m\t", *stress);  // Red text on yellow bg
            }
            else if(*stress>=100){
                printf("\033[31m%d\033[0m\t", *stress); // Red
            }
            else if(*stress>=50){
                printf("\033[33m%d\033[0m\t", *stress); // Yellow
            }
            else{
                printf("\033[32m%d\033[0m\t", *stress); // Green
            }
        }
        printf("\n\n");
    }
    sleep(100);
}
