/*
 * author: Angel Rojas
 * date: 4-17-18
 * filename: Lab7.cpp
 */

#include <iostream>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
using namespace std;

// Global variable of how many times we iterate a row
int rowIteration = 0;
float sigmoide = 2.7182818284590452353602874713527;
float output = 0.0;

#define rnd() ((double)(rand()) / RAND_MAX) - 0.5

// we need a class of a Neuron
class Neuron {
	public:
			float feature[150][4];
			float labels[150][3];
			float Output_errors[3];
			float Hiddenweights[12];
			float Outputweights[9];
			float thetas[6];
			float delta[6];
			float charge,y,gain,wgain; //gain = -1 (bias). wgain = theta
			float Hiddencharge1, Hiddencharge2,Hiddencharge3;
			float Outputcharge1, Outputcharge2,Outputcharge3;
			float Hiddenoutput[3];
			float OUTPUToutput[3];
	Neuron () {
			for (int i=0; i<12; i++)
					Hiddenweights[i] = rnd();

			for (int i=0; i<9; i++)
					Outputweights[i] = rnd();

			for (int i=0; i<6; i++)
				thetas[i] = rnd();
			
			charge = y = 0;
	}
}n;

float sigmoid(float X) {
	output = 1 / (1 + (pow(sigmoide,-X)));
	return output;
} 

int main() {
    srand(unsigned(time(NULL)));
    //float data[100][4];
	//double perc = 0.0;
    float value[5];
    char buff[80];
    int col = 0;
    int row = 0;
    //int y = 0;
	int success = 0;
    int yd;
    int error;
    //double charge = 0;
    double learningRate = 0.05;
    //double weight[3];
    //weight[0] = ((double)rand()/(RAND_MAX)) - .5;
    //weight[1] = ((double)rand()/(RAND_MAX)) - .5;
    //weight[2] = ((double)rand()/(RAND_MAX)) - .5;
    double theta = ((double)rand()/(RAND_MAX)) - .5;
	float alpha = 0.05;

	// Initialize which file we're going to read in	
	//ifstream file( "setosa_v_versicolor.csv" );
	ifstream file( "iris.csv" );
    string line;
	// let's open up the CSV input file
    while (getline( file, line)) {
        istringstream iss( line );
        string theIndex;
        while (getline(iss, theIndex, ',')) {
            //if (col != 4) {
              if (col >= 0 && col < 4) {
				n.feature[row][col] = atof(theIndex.c_str() );
                col++;
			  }
            else if (col == 4) {
                //value[row] = atof(theIndex.c_str());
                n.labels[row][0] = atof(theIndex.c_str());
        		col++;
				}
			else if (col == 5) {
                n.labels[row][1] = atof(theIndex.c_str());
				col++;
				}
			else if (col == 6) {
                n.labels[row][2] = atof(theIndex.c_str());
				col++;
				}
			}
        row++;
		//we need to reset column val. to count the correct # of COLUMNS
        if (col == 7 )
			col = 0;
    }

	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 4; j++) {
			cout << n.feature[i][j] << " ";
		}
		cout << "\n";
	}
	
	cout << "\n\n=======================================================\n";

	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 3; j++) {
			cout << n.labels[i][j] << " ";
		}
		cout << "\n";
	}
/* END OF READING THE FILE FOR INPUT */	

/* begin feed forward */
// 4 input neurons, 3 hidden neurons, 3 output neurons
// Calculating the Hidden Layer charges
	for (int i=0; i < 4; i++) {
		n.Hiddencharge1 += (n.feature[0][i] * n.Hiddenweights[i]);
		n.Hiddencharge2 += (n.feature[0][i] * n.Hiddenweights[i+4]);
		n.Hiddencharge3 += (n.feature[0][i] * n.Hiddenweights[i+8]);
	}
	n.Hiddencharge1 = n.Hiddencharge1 - n.thetas[0];
	n.Hiddencharge2 = n.Hiddencharge2 - n.thetas[1];
	n.Hiddencharge3 = n.Hiddencharge3 - n.thetas[2];
	
	// OUTPUT of Hidden Layer neurons (tilda y)
	sigmoid(n.Hiddencharge1);
	n.Hiddenoutput[0] = output;
	sigmoid(n.Hiddencharge2);
	n.Hiddenoutput[1] = output;
	sigmoid(n.Hiddencharge3);
	n.Hiddenoutput[2] = output;
	
	cout << "->Hidden Charges: " << n.Hiddencharge1 << "2: " << n.Hiddencharge2 << "3: " << n.Hiddencharge3 << endl;
	for (int i=0; i < 3; i++)
		cout << "Hidden outputs: " << n.Hiddenoutput[i] << endl;

	// Send our Output of Hidden Layer -> Output Layer
	for (int i=0; i < 3; i++) {
		n.Outputcharge1 += (n.Hiddenoutput[i] * n.Hiddenweights[i]);
		n.Outputcharge2 += (n.Hiddenoutput[i] * n.Hiddenweights[i+3]);
		n.Outputcharge3 += (n.Hiddenoutput[i] * n.Hiddenweights[i+6]);
	}
	n.Outputcharge1 = n.Outputcharge1 - n.thetas[3];
	n.Outputcharge2 = n.Outputcharge2 - n.thetas[4];
	n.Outputcharge3 = n.Outputcharge3 - n.thetas[5];

	// OUTPUT of Output Layer neurons (tilda y)
	sigmoid(n.Outputcharge1);
	n.OUTPUToutput[0] = output;
	sigmoid(n.Outputcharge2);
	n.OUTPUToutput[1] = output;
	sigmoid(n.Outputcharge3);
	n.OUTPUToutput[2] = output;
	
	cout << "->OUTPUTlayer Charges: " << n.Outputcharge1 << "2: " << n.Outputcharge2 << "3: " << n.Outputcharge3 << endl;
	for (int i=0; i < 3; i++)
		cout << "Out.Layer outputs: " << n.OUTPUToutput[i] << endl;

	//calculate error e = (Yd - tilay), then Delta = y*(1 - y)*(e)
	for (int i=0; i < 3; i++)
		n.Output_errors[i] = n.labels[0][i] - n.OUTPUToutput[i];

	for (int i=0; i < 3; i++)
			cout << "errors(e) " << n.Output_errors[i] << endl;

	//cout << "First Feature row: " << n.feature[0][0] << n.feature[0][1] << n.feature[0][2] << n.feature[0][3] << endl;

	//n.charge = 50.5;
	//sigmoid(50.4);
	//cout << "After Signoid call, Output is: " << output << endl;    

    return 0;
}
