#include <iostream>
#include "arithmetic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <bits/stdc++.h> 
#include <vector>
#include <array>
#include <string>
#include <typeinfo>
#include <fstream>
#include <time.h>
using namespace std;

#define LEARNING_RATE    0.1
#define MAX_ITERATION    100

extern "C" {
	// inside here this code will become c binary as opposed to c++
}

int main(){
	srand(time(NULL));
	/*int p1x, p2x, p1y, p2y;
	
	*/
  string user_in;
  cout << "What file would you like to test? ";
  getline (cin, user_in);

	int listSize;
	string line;
	ifstream pointfile (user_in);

	//store the x,y from .txt file
	vector <string> pts; 
	vector <string> tokens;
	vector <string> tok_space;
	int iter = 0;

	if (pointfile.is_open()){
    	while (getline (pointfile,line)){	
    		//pts.push_back(line);
     		//cout << pts.at(iter) << '\n';
     
    		// stringstream class check1
    		stringstream check1(line);
    		string intermediate;

    		// Tokenizing w.r.t. space ' '
    		while(getline(check1, intermediate, ' ')) //use "," to tokenize ,
    		{
       			tokens.push_back(intermediate);
    		}
        /*
        while(getline(check1, intermediate, '\t')) //use "," to tokenize ,
        {
            tokens.push_back(intermediate);
        } */
    	}
    	//close file
    	pointfile.close();
  	} else {
  		cout << "Unable to open file"<<endl; 
  	}

  	//loop to tokenize ","
  	string space;
  	for(int i = 0; i < tokens.size(); i++){
    	stringstream check2(tokens[i]);
        while(getline(check2, space, ',')) //use "," to tokenize ,
    	{

       		tok_space.push_back(space);
    		}	
    	}
    //loop to remove puncuation
    for(int j = 0; j < tok_space.size(); j++){
    	// set string to contents at index j
    	string str = tok_space[j];

    	//check for punc characters
    	for(int k = 0, len = str.size(); k<len; k++ ){
    		if (ispunct(str[k]) && str[k] != '-'){
    			str.erase(k--, 1);
    			len = str.size();
    		}
    	}

    	if (str.size() > 1){
    		if (str.substr(0,1) == "-"){
    			tok_space[j] = str.substr(0,2) + "." + str.substr(2,str.size()-1); 	
			} else {
				tok_space[j] = str.substr(0,1) + "." + str.substr(1,str.size()-1); 	
			}
    	} else {
    		tok_space[j] = str;	
    	}
    	/*
    	if (str.size() > 1 && str.substr(0,1) == "-"){
    		tok_space[j] = str.substr(1,2) + "." + str.substr(2,str.size()-1); 
    	} if (str.size() > 1){
    		tok_space[j] = str.substr(0,1) + "." + str.substr(1,str.size()-1); 
    	} else {
    		tok_space[j] = str;
    	} */
    }

        //code to convert strings to float
    //float pts_arr[tok_space.size()];
    vector <float> pts_arr;
    float float_pt;
    //cout << tok_space.size() << '\n';
    for (int pt = 0; pt < tok_space.size(); pt++){
    	float_pt = strtof((tok_space[pt]).c_str(),0); //string to float
    	pts_arr.push_back(float_pt);
    }
    
    //vector for just the x,y
    vector <float> x_pt;
    vector <float> y_pt;
    for (int a = 0; a < pts_arr.size(); a=a+3){
    	x_pt.push_back(pts_arr[a]);
    	y_pt.push_back(pts_arr[a+1]);
    }

    //vecotr for just the tag bit.
    // for a tag of 0, replace with -1
    vector <float> tag;
    for (int b = 2; b < pts_arr.size(); b=b+3){
    	if (pts_arr[b] == 0){
    		tag.push_back(-1);
    	} else {
    		tag.push_back(1);
    	}
    }
  	
  	Point arr[tag.size()]; // arr is an array of how many points wanted.
  	for ( int i = 0; i < tag.size(); i++){
  		float px = x_pt[i];
  		float py = y_pt[i];
  		arr[i].x_coord = px;
  		arr[i].y_coord = py;
  	}
  	listSize = tag.size();
  	int iteration = 0, output;

  	//3 weights, one for x, y, and bias
  	float weights[3], localErr, globalErr;
  	size_t size = (sizeof(weights))/sizeof(float);
  	
  	for (int w = 0; w < size; w++){
  		weights[w] = randomFloat();
  		//cout << weights[w] << '\n';
  	}
  	
  	do {
  		iteration++;
  		globalErr = 0;
  		for (int in = 0; in < listSize; in++){
  			output = predictOut(weights, x_pt[in], y_pt[in]);

  			localErr = tag[in] - output;
  			
  			//weight for x
  			weights[0] += (LEARNING_RATE * localErr * x_pt[in]);
  			
  			//weight for y
  			weights[1] += (LEARNING_RATE * localErr * y_pt[in]);
  			
  			//weight for bias
  			weights[2] += (LEARNING_RATE * localErr);  			

  			globalErr += (localErr*localErr);

  		}

      //print the error. 
  		/* Root Mean Squared Error */
        printf("\nIteration %d : Error = %.4f\n",
            iteration, sqrt(globalErr/listSize));
  	} while (globalErr > 0);

  	    printf("\nDecision boundary (line) equation: %.2f*x + %.2f*y + %.2f = 0\n",
        weights[0], weights[1], weights[2]);
  
    /*  	
  	for ( int j = 0; j < tok_space.size(); j++ ) {
    	//std::cout << arr[j] << std::endl;
    	cout << tok_space[j] << endl;
   } */
   

//end of all code
	return 0;
}