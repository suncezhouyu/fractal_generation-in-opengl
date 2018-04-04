#include <GL/glut.h>
#include <unistd.h>
#include <stdio.h>
#define n 301

void myDisplay(void);

int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(n,n);
    glutCreateWindow("fractal");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glPointSize(1);
    glutDisplayFunc(myDisplay);

    glutMainLoop();
    return 0;
}

void myDisplay(void)
{
    int matrix[n * n] = {0};
    GLfloat setx[n * n], sety[n * n];
    int pos, condense, r, already, k, pos_index;
    int tempx, tempy, l, q, p = 0;

    int num = 1;
    matrix[(n * n - 1) /2] = 1;//set the middle element
    setx[0] = 0.0f;
    sety[0] = 0.0f;

    while(p<4000)
    {
        //generate a new point on the edge
        already = 1;
        while(already)
        {
            r = rand();
            r = r%4;
            switch(r)
            {
                case 0://first line
                    r = rand();
                    pos = r%n;
                    if(matrix[pos] != 1)
                        already=0;
                    break;
                case 1://last line
                    r = rand();
                    pos = (r%n) + n * (n-1);
                    if(matrix[pos] != 1)
                        already =0;
                    break;
                case 2://left-most column
                    r = rand();
                    pos = (r%n) * n;
                    if(matrix[pos] != 1)
                        already=0;
                    break;
                case 3:
                    r = rand();
                    pos = (r%n) *n + (n-1);
                    if(matrix[pos] != 1)
                        already = 0;
                    break;
                default:
                    break;
            }//end of switch
        }//end of while(already)
        matrix[pos] = 1;

        //move a new point around
        condense = 0;
        while(!condense)
        {
            tempx = pos%n - (n-1)/2;
            tempy = pos/n - (n-1)/2;
        
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(0.0f, 0.0f, 0.0f);

            glBegin(GL_POINTS);
            for(k=0;k<num;k++)//draw the condensed points
                glVertex2f(setx[k], sety[k]);
            glVertex2f(((GLfloat) tempx) * 2.0f/((GLfloat) n), ((GLfloat) tempy) * 2.0f/((GLfloat) n));//draw the new point
            glEnd();
       
            glutSwapBuffers();
        

            //judge if the new point is adsorbed
            pos_index = (((pos > 0) && (pos < (n-1))) << 7) + (((pos > (n*(n-1))) && pos < (n*n -1)) << 6); //first line and last line
            pos_index = pos_index + (((pos%n == 0) && (pos != 0) && (pos != n*(n-1))) << 5);//left-most column
            pos_index = pos_index + (((pos%n == (n-1)) && (pos != (n-1)) && (pos != n*n-1)) << 4);//right-most column
            pos_index = pos_index + ((pos == 0) << 3) + ((pos == (n-1)) << 2) + ((pos == (n * (n-1))) << 1) + (pos == (n*n-1));//4 corners
            
            switch(pos_index)
            {
                case 1<<7://first line
                    if(matrix[pos-1] || matrix[pos+1] || matrix[pos + n])
                    {
                        condense=1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[pos] = 0;
                        r = rand();
                        r = r%3;
                        switch(r)
                        {
                            case 0:
                                pos = pos -1;
                                break;
                            case 1:
                                pos = pos + 1;
                                break;
                            default:
                                pos = pos + n;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1<<6://last line
                    if(matrix[pos-1] || matrix[pos+1] || matrix[pos - n])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[pos] = 0;
                        r = rand();
                        r = r%3;
                        switch(r)
                        {
                            case 0:
                                pos = pos -1;
                                break;
                            case 1:
                                pos = pos + 1;
                                break;
                            default:
                                pos = pos - n;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1<<5://left-most column
                    if(matrix[pos-n] || matrix[pos+n] || matrix[pos + 1])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[pos] = 0;
                        r = rand();
                        r = r%3;
                        switch(r)
                        {
                            case 0:
                                pos = pos -n;
                                break;
                            case 1:
                                pos = pos + n;
                                break;
                            default:
                                pos = pos + 1;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1<<4://right-most column
                    if(matrix[pos-1] || matrix[pos+n] || matrix[pos - n])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[pos] = 0;
                        r = rand();
                        r = r%3;
                        switch(r)
                        {
                            case 0:
                                pos = pos -1;
                                break;
                            case 1:
                                pos = pos + n;
                                break;
                            default:
                                pos = pos - n;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1<<3://upper-left corner
                    if(matrix[1] || matrix[n])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[0] = 0;
                        r = rand();
                        r = r%2;
                        switch(r)
                        {
                            case 0:
                                pos = 1;
                                break;
                            default:
                                pos = n;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1<<2://upper-right corner
                    if(matrix[2*n-1] || matrix[n-2])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[n-1] = 0;
                        r = rand();
                        r = r%2;
                        switch(r)
                        {
                            case 0:
                                pos = 2*n-1;
                                break;
                            default:
                                pos = n-2;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1<<1://lower-left corner
                    if(matrix[n*n-n+1] || matrix[n*n-2*n])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[n*n-n] = 0;
                        r = rand();
                        r = r%2;
                        switch(r)
                        {
                            case 0:
                                pos = n*n-2*n;
                                break;
                            default:
                                pos = n*n-n+1;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                case 1://lower-right corner
                    if(matrix[n*n-n-1] || matrix[n*n-2])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[n*n-1] = 0;
                        r = rand();
                        r = r%2;
                        switch(r)
                        {
                            case 0:
                                pos = n*n-n-1;
                                break;
                            default:
                                pos = n*n-2;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
                default://not on the edge of matrix
                    if(matrix[pos+1] || matrix[pos-1] || matrix[pos-n] || matrix[pos+n])
                    {
                        condense =1;
                        num++;
                        setx[num] = ((GLfloat) tempx) * 2.0f/((GLfloat) n);
                        sety[num] = ((GLfloat) tempy) * 2.0f/((GLfloat) n);
                    }
                    else
                    {
                        matrix[pos] = 0;
                        r = rand();
                        r = r%4;
                        switch(r)
                        {
                            case 0:
                                pos--;
                                break;
                            case 1:
                                pos++;
                                break;
                            case 2:
                                pos = pos +n;
                                break;
                            default:
                                pos = pos -n;
                                break;
                        }
                        matrix[pos] = 1;
                    }
                    break;
            }//end of switch
        }//end of while(!condense)
    p++; 
    }//end of while(p)
}
