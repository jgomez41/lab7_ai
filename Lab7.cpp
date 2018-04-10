/*
 * author: Angel Rojas
 * date: 4-10-18
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
//float sigmoide = 2.7182818284590452353602874713527;
//float output = 0.0;

#define rnd() ((double)(rand()) / RAND_MAX) - 0.5

// we need a class of a Neuron
class Neuron {
	public:
			float feature[150][4];
			float labels[150][3];
			float weights[5];
			float thetas[5];
			float charge,y;
	Neuron (){
			weights[0] = rnd();
			weights[1] = rnd();
			weights[2] = rnd();
			weights[3] = rnd();
			weights[4] = rnd();
			/*for (int i=0; i<5; i++)
				thetas[i] = rnd();*/
			charge = y = 0;
	}
}n;

/*float sigmoid(float X) {
	output = 1 / (1 + (pow(sigmoide,-X)));
	return output;
} */

int main() {
    srand(unsigned(time(NULL)));
    //float data[100][4];
	double perc = 0.0;
    float value[5];
    char buff[80];
    int col = 0;
    int row = 0;
    int y = 0;
	int success = 0;
    int yd;
    int error;
    //double charge = 0;
    double learningRate = 0.05;
    double weight[3];
    weight[0] = ((double)rand()/(RAND_MAX)) - .5;
    weight[1] = ((double)rand()/(RAND_MAX)) - .5;
    weight[2] = ((double)rand()/(RAND_MAX)) - .5;
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






	//n.charge = 50.5;
	//sigmoid(50.4);
	//cout << "After Signoid call, Output is: " << output << endl;
    






	// Let's run through 200 trials, called epoch
	/*for (int epochs = 0; epochs < 200; epochs++) {
        success = 0;
		rowIteration = 0;
		cout << "Epoch#: " << epochs << " ";
        for (int i=0; i< 100; ++i) {
            n.charge = 0;
            rowIteration++;
            for (int j=0; j< 4; ++j) {
				// Charge is our CSV data * our Rand weights.
                n.charge += n.feature[i][j] * weight[j];
			}	
			n.charge -= theta;

			// This is the circleSigma -> circle Sign (or Step)
           if (n.charge >= 0)
               y = 1; // Sign: ~Y
           else
               y = -1; // Step: ~y
            
			// Yd - is the actual tag (1 or -1) of the CSV index.
			// error is 0 or not 0 (success or failed.)
            yd = value[i];
            error = yd - y;
            if ( error != 0 ) {
                for (int j=0; j< 4; ++j) {
					// calc. for the # of Wrong guesses
					cout << "WRONG GUESS" << endl;
                    weight[j] = weight[j] + 
								(learningRate*n.feature[i][j]*error);
                }
                theta = theta + learningRate * (-1) * error;
            	} else {
                	success++;
                	if (success >= 90) {
						cout << " #of correct: " << success << endl;
						cout << endl;
						cout << "Weights are [" << 
                	    	weight[0] << " " << weight[1] <<  " " << 
							weight[2] <<  " " << weight[3] << "]" <<endl;
                    	cout << endl;
						break;
                	} 
            	}
        	}
    } // end of epoch */
    //cout << "Final Success counter:" << success 
	//		<< " " << "#of rows" << rowIteration << endl;
    //perc = (success/rowIteration) * 100;
    //cout << "Percent correct: " << perc << endl;

    return 0;
}
