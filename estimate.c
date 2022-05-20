#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

double ** mult( double ** m1,int m1row, int m1cols, double ** m2, int m2row, int m2cols){
    //Creating rows vector
    double *rows = (double*)malloc(sizeof(double)*(m1row*m1cols)); 
    int index = 0;
    int phase;
    int second;
    for(phase = 0; phase< m1row; phase++){
       for(second =0; second < m1cols; second++){
           rows[index] = m1[phase][second];
           index =index+1;

       }
   }
    //Creating column vector
   double *columns = (double*)malloc(sizeof(double)*(m2row*m2cols));
   int count =0;
   int t = 0;
   int r;
   for(t = 0; t< m2cols; t++){
       for(r = 0; r < m2row; r++){
           columns[count] = m2[r][t];
           count++;
       }
   }
    
    
    //Multiplying column and row vectors
    int counter = 0;
    int track = 0;
    int inner = 0;
    double sum =0.0;
    int start;
    int size = m1cols;
    int length  = m2row*m2cols;
    double *product = (double *)malloc(sizeof(double)*(m1row*m2cols));
    for(start = 0; start < m1row; start++){
        for(inner = 0; inner < length; inner++){
            sum = sum + columns[inner] * rows[counter];
            counter++;
            if(counter != 0 && counter % size == 0){
                product[track] = sum;
                sum = 0;
                counter = counter -size;
                track = track +1;
                }
            }
             counter = counter+size;
    }
        double* temp;
        temp = rows;
        rows = product;
        product = NULL;
        free(temp);
        free(product);
        counter = 0;
        track = 0;
    //Making multiplied matrix
    double **mixm = malloc(m1row * sizeof(double *)); 
    int raise;
    for (raise = 0; raise < m1row; ++raise) { 
        mixm[raise] = malloc(m2cols * sizeof(double)); 
    }
    int s;
    int end;
    int pointer = 0;
    for(s = 0; s < m1row; s++){
        for(end = 0; end < m2cols; end++){
            mixm[s][end] = rows[pointer];
            pointer++; 
        }
    }

    free(rows);
    free(columns);
    return mixm;


}

double **transpose(double ** create, int rows, int cols){
   double **newtranspose = malloc(sizeof(double *) * cols);
   int st;
   for(st = 0; st < cols; ++st){
       newtranspose[st] = malloc(rows*sizeof(double));
    }

    int i; int j;

    for(i = 0; i < rows; i++){
        for(j  = 0; j < cols; j++){
            newtranspose[j][i] = create[i][j];
        }
    }

    return newtranspose;
}

double **invert(double ** made, int n){
    //identity matrix
    double ** id = malloc(sizeof(double *) * n);
    int s;
    for(s = 0; s< n; ++s){
        id[s] = malloc(n*sizeof(double));
    }
    int first;
    int second;
    for(first = 0; first < n; first++){
        for(second = 0; second <n; second++){
            if(first == second){
                id[first][second] = 1.0;
            }
            else{
                id[first][second] = 0.0;
            }
        }
    }    

    //inverting
    int p =0;
    double f = 0;
    int r = 0;
    int start;
    int z;
    for(p = 0; p < n; p++){
        f = made[p][p];
        for(r = 0; r < n; r++){
            made[p][r] = made[p][r] / f;
            id[p][r] = id[p][r] / f; 
        }
        for(start = p+1; start < n; start++){
            f = made[start][p];
            for(z = 0; z< n; z++){
                made[start][z] = made[start][z] - made[p][z] *f;
                id[start][z] = id[start][z] - id[p][z] *f;

            }
        }
    }
    int count;
    int bcount;
    double fcreate;
    int move;
    for(count = n-1; count >=0; count--){
        for(bcount = count-1; bcount >=0; bcount--){
            fcreate = made[bcount][count];
            for(move = 0; move < n; move++){
                made[bcount][move] = made[bcount][move] - made[count][move] *fcreate;
                id[bcount][move] = id[bcount][move] - id[count][move] *fcreate;
            }
        }
    }
    return id;

}

int main(int argc, char **argv){
    //Getting initial data on rows and columns
    int a;
    int columns;
    int rows;
    //Getting train info.
    FILE *f = fopen(argv[1], "r");
    char d;
    fscanf(f,"%c",&d);
    char c;
    do {
    c = fgetc(f);
    } while (c != '\n');
    fscanf(f, "%d", &a);
    char word;
    word = d;
    columns = a;
    fscanf(f,"%d", &a);
    rows = a;
    columns = columns + 1;

    //Getting actual data
    FILE *actual = fopen(argv[2], "r");
    char nex;
    fscanf(actual,"%c", &nex);
    char amt;
    do {
    amt = fgetc(actual);
    } while (amt != '\n');
    char makeword;
    makeword = nex;
    int num;
    fscanf(actual, "%d", &num);
    int truecols;
    truecols = num;
    truecols = num+1;
    int truerows;
    fscanf(actual,"%d", &num);
    truerows = num;
   
    

if(word == 't' && makeword == 'd'){
    //Getting matrix data
    int i; 
    double **X = malloc(rows * sizeof(double *)); 
    for (i = 0; i < rows; ++i) { 
        X[i] = malloc((columns) * sizeof(double)); 
    }
    int probe;
    int colB = 1;
    double **Y = malloc(rows * sizeof(double *));
    for (probe = 0; probe < rows; ++probe) { 
        Y[probe] = malloc(colB * sizeof(double)); 
    }
    int start;
    int j;
    double r;
    for(start = 0; start < rows; start++){
        for(j = 0; j <= columns; j++){
            if(j != columns){
                if(j == 0){
                    X[start][j] = 1;
                }
                else{
                    fscanf(f, "%lf", &r);
                    X[start][j] = r;
                }
            }
            else{
                fscanf(f, "%lf", &r);
                Y[start][0] = r;
            }
        }
    }
    //Getting Weight value
    double **t;
    t = transpose(X,rows, columns);
    double **prod;
    prod = mult(t,columns,rows,X,rows,columns);
    double **inverse;
    inverse = invert(prod,columns);
    double **productA;
    productA = mult(inverse,columns,columns, t, columns, rows);
    double **weight;
    weight = mult(productA, columns, rows, Y, rows, colB);

    //Freeing all 2D arrays
        //Free t
        int c1;
        for(c1 = 0; c1 < columns; ++c1){
            free(t[c1]);
        }
        free(t);

        //Free product
        int c2;
        for(c2 = 0; c2 < columns; ++c2){
            free(prod[c2]);
        }
        free(prod);

      //Free inverse
        int c3;
        for(c3 = 0; c3 < columns; c3++){
            free(inverse[c3]);
        }
        free(inverse);
        
        //Free productA
        int c4;
        for(c4 = 0; c4 < columns; c4++){
            free(productA[c4]);
        }
        free(productA);
    
    //Making X prime
    int finum; 
    double **house = malloc(truerows * sizeof(double *)); 
    for (finum = 0; finum < truerows; ++finum) { 
        house[finum] = malloc((truecols) * sizeof(double)); 
    }
    int ki;
    int kf;
    double val;
    for(ki = 0; ki < truerows; ki++){
        for(kf = 0; kf < truecols; kf++){
            if(kf == 0){
                house[ki][kf] = 1.0;
            }
            else{
                fscanf(actual, "%lf ", &val);
                house[ki][kf] = val;
            }
        }
    
    }

    //Finding the values of Y
    double** finalY;
    finalY = mult(house,truerows,truecols, weight, columns,colB);
    int tim;
    int jim;
    for(tim = 0; tim < truerows; tim++){
        for(jim = 0; jim < colB; jim++){
            printf("%.0f\n", finalY[tim][jim]);
        }
    }


    //Freeing Weight
    int c5;
    for(c5 = 0; c5 < columns; c5++){
        free(weight[c5]);
    }
    free(weight);    
        
    //Freeing finalY
    int c6;
    for(c6 = 0; c6 < truerows; c6++){
        free(finalY[c6]);
    }
    free(finalY);
    // Freeing house
    int c7;
    for(c7 =0; c7 < truerows; c7++){
        free(house[c7]);
    }
    free(house);



    /*int ret;
    int obj;
    for(ret = 0; ret < rows; ret++){
        for(obj = 0; obj < colB; obj++){
            printf("%lf ", Y[ret][obj]);
        }
        printf("\n");
    }*/

   /* int open;
    for(open = 0; open < columns; ++open){
        free(t[open]);
    }
    free(t);*/
   
///Matrix test code;
    /*int std;
    int next;
    for (std = 0; std < rows; std++){
        for(next = 0; next < columns; next++){
            printf("%lf ", X[std][next]);
        }
        printf("\n");
    }*/
    int close;
    for(close = 0; close < rows; ++close){
        free(X[close]);
    }
    free(X);
    /*int l;
    for(l = 0; l < rows; l++){
        printf("%lf \n", Y[l][0]);
    }*/
    int closeB;
    for(closeB = 0; closeB < rows; ++closeB){
        free(Y[closeB]);
    }
    free(Y);
}
    return 0;
}