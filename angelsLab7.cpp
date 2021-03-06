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
int counter = 0;

#define rnd() ((double)(rand()) / RAND_MAX) - 0.5

// we need a class of a Neuron
class Neuron {
	public:
			float feature[150][4];
			float labels[150][3];
			float HIDDENOUTPUTARRAY[450];
			float Output_errors[450];
			float Hiddenweights[12];
			float Outputweights[9];
			float thetas[6];
			float Output_deltas[450];
			float Hidden_deltas[450];
			
			float charge,y,gain,wgain; //gain = -1 (bias). wgain = theta
			float Hiddencharge[3]; //, Hiddencharge2,Hiddencharge3;
			float Outputcharge[3]; //1, Outputcharge2,Outputcharge3;
			float Hiddenoutput[3];
			float OUTPUToutput[450];
	Neuron () {
			//srand(time(NULL));
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
    int col = 0;
    int row = 0;

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

			/*----- HIDDEN LAYER ----*/
	for (int epoch = 0; epoch < 150; epoch++) {
		for (int i=0; i < 4; i++) {
			n.Hiddencharge[0] += (n.feature[epoch][i] * n.Hiddenweights[i]);
			n.Hiddencharge[1] += (n.feature[epoch][i] * n.Hiddenweights[i+4]);
			n.Hiddencharge[2] += (n.feature[epoch][i] * n.Hiddenweights[i+8]);
		}
		for (int i = 0; i < 3; i++) {
			n.Hiddencharge[i] = n.Hiddencharge[i] - n.thetas[i];
		}
		// OUTPUT of Hidden Layer neurons (tilda y)
		for (int i = 0; i < 3; i++) {
			sigmoid(n.Hiddencharge[i]);
			n.HIDDENOUTPUTARRAY[counter] = output;
			counter++;
		}
		//spit out our charges
		/*for (int i=0; i < 3; i++)
			cout << "Hidden Charges: " << n.Hiddencharge[i] << " ";*/
		//cout << endl ; 
		n.Hiddencharge[0] = 0;
		n.Hiddencharge[1] = 0;
		n.Hiddencharge[2] = 0;
	}  // end of epoch.	 
	/*---- FINISHED WITH THE HIDDEN LAYER -----*/
		
	// spit out hidden layer outputs	
		/*for (int i=0; i < 450; i++) {
			if (i % 3 == 0) {
				cout << endl;
				cout << "---------" << endl;
			}
			cout << "Hidden outputs: " << n.HIDDENOUTPUTARRAY[i] << endl;
		} */
		cout << "-- End of Hidden Layer --" << endl << endl;
	
	// reset Global Counter
	counter = 0;
	output = 0.0;

				/*----- OUTPUT LAYER ------*/	
	for (int epoch = 0; epoch < 450; epoch+=3) {
		for (int i=0; i < 3; i++) {
			n.Outputcharge[0] += (n.HIDDENOUTPUTARRAY[epoch+i] * n.Outputweights[i]);
			n.Outputcharge[1] += (n.HIDDENOUTPUTARRAY[epoch+i+3] * n.Outputweights[i+3]);
			n.Outputcharge[2] += (n.HIDDENOUTPUTARRAY[epoch+i+6] * n.Outputweights[i+6]);
		}
		for (int i = 0; i < 3; i++) {
			n.Outputcharge[i] = n.Outputcharge[i] - n.thetas[i+3];
		}
		// OUTPUT of OUTPUT Layer neurons (tilda y)
		for (int i = 0; i < 3; i++) {
			sigmoid(n.Outputcharge[i]);
			n.OUTPUToutput[counter] = output;
			counter++;
		}
		//spit out our charges
		/*for (int i=0; i < 3; i++)
			cout << "OUTPUT CHARGES: " << n.Outputcharge[i] << " "; */
		//cout << endl;
		n.Outputcharge[0] = 0;
		n.Outputcharge[1] = 0;
		n.Outputcharge[2] = 0;
	}  // end of epoch.	
	
	// spit out our Output of the OUTPUT LAYER (tilda y)	
	/*for (int i=0; i < 450; i++) {
		if (i % 3 == 0) {
			cout << endl;
			cout << "---------" << endl;
		} 
		//cout << "OUTPUT outputs: " << n.OUTPUToutput[i] << endl;
	} */
	cout << "-- End of OUTPUT  Layer --" << endl << endl;
	counter = 0;
		/* END OF OUTPUT LAYER */

	//calculate error e = (Yd - tilay), then Delta = y*(1 - y)*(e)
	for (int i=0; i < 150; i++) {
		for (int j=0; j < 3; j++) {
			n.Output_errors[counter] = n.labels[i][j] - n.OUTPUToutput[counter];
			counter++;
		}	
	}

	counter = 0;
	for (int i=0; i < 3; i++)
			cout << "errors(e) " << n.Output_errors[i] << endl;

	// Now, after (e), we calc. Delta = y*(1 - y)*(e)
	for (int i=0; i < 150; i++) {
		for (int j=0; j < 3; j++) {
			n.Output_deltas[counter] = n.OUTPUToutput[counter] * (1 - n.OUTPUToutput[counter]) *
					n.Output_errors[counter];
			counter++;
		}
	}
	counter = 0;
	cout << endl << "-- End of Output Deltas --" << endl;

	// Spit out our Delta values for the Output Layer's Neurons.
	for (int i=0; i < 450; i++)
		cout << "Delta[" << i << "] = " << n.Output_deltas[i] << endl;
	cout << "Done with Output Layer's Deltas" << endl;
	//------  END OF FEED-FORWARD. ------//


    return 0;
}
