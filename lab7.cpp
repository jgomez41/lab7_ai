#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main() {
    int row = 0;
    int col = 0;
   
	double data_set[100][4];
    double label_data[100];
    
	ifstream file( "data.csv" );
    string line; 
   
	int y_tilda = 0;
	int incorrect = 0; 
    int y_d = 0;
    double X;
    double w[3];
    int e = 0;
    int labels = 0;
	double alpha = 0.05;
    double theta = ((double)(rand()%10 ) /(10.0 - 0.5));

   	///////////////////////////////////////////////////////// 
	//random weights
    srand(time(NULL));
    for (int i = 0; i < 4; i++) 
        w[i]= (double)(rand()%10 )/(10.0 - 0.5);
    /////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////
   //FILE IO 
    while( getline( file, line ) ) {
        stringstream iss( line );
        string result;
        while( getline( iss, result, ',' ) ) {
            if (col != 4) {
                data_set[row][col] = atof( result.c_str() );
                col++;
            }
            else
                label_data[row] = atof( result.c_str() );
        }
        row++;
        col = 0;
    }
    ///////////////////////////////////////////////////////////

    //prelab checking for the petal length
    for (int i = 0; i < 100; i++) {
        int count = (data_set[i][2] > 0) ? 0 : 1;
        labels += count; 
    }
    //Lab
    for (int i = 0; i < 100; i++) {
        X = 0;
        y_d = label_data[i];            
        for (int j = 0; j < 4; j++) 
            X += (data_set[i][j] * w[j]);
		X -= theta;
        y_tilda = (X < 0) ? -1 : 1; //sign function
        e = y_d - y_tilda;
        
        if (e == 0) {
            cout << "iteration: " << i+1 << " [" 
			 << w[0] << " " << w[1] <<  " " << w[2] <<  " " << w[3] << "] \n"; 
			incorrect++;
 	    }
        else { // error ocurred     
            for (int j = 0; j < 4; j++)
                w[j] += alpha * data_set[i][j] * e;
            theta -= (alpha * e );
			cout << "There was an error\n";
        }
    }
    
    cout << "Percent correct: " << incorrect << "%\n";
    cout << "Correct labels: " << labels << "%\n"; //prelab output
    return 0;
}
