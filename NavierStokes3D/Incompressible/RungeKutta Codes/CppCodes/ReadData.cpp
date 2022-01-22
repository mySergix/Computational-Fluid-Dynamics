#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <string>
#include <mpi.h>

#include "/home/sergiogus/Desktop/CFD/Incompressible3D/Codes/HeaderCodes/Memory.h"
#include "/home/sergiogus/Desktop/CFD/Incompressible3D/Codes/HeaderCodes/ReadData.h"
using namespace std;

#define DIRECTORIO "/home/sergiogus/Desktop/CFD/Incompressible3D/InputData/"

//Constructor del lector de datos
ReadData::ReadData(Memory M1){

	GeometryData = M1.AllocateDouble(7, 1, 1, 1); //Datos de la geometría del problema
	ProblemNumericalData = M1.AllocateInt(10, 1, 1, 1); //Datos numéricos del problema
	ProblemData = M1.AllocateDouble(5, 1, 1, 1); //Datos del problema
	ProblemPhysicalData = M1.AllocateDouble(13, 1, 1, 1); //Datos físicos sobre las condiciones del problema
	
}

void ReadData::ReadArrays(string FileName, int TotalData, double *Array){
int i = 0;
stringstream InitialName;
string FinalName;

	InitialName<<DIRECTORIO<<FileName;
	FinalName=InitialName.str();

	ifstream Data(FinalName.c_str());

		if (Data){
        		string line;
        		while (getline(Data, line)){
        	 		istringstream iss(line);
					if(i < TotalData){
						if (iss >> Array[i]){ i++; }	
					}
        		 }
   	 	}
		
    	Data.close();

}

void ReadData::ReadInputs(){

	//Lectura datos en Arrays
	ReadArrays("GeometryData.txt", 7, GeometryData); //Input Datos Geometría del problema
	ReadArrays("ProblemPhysicalData.txt", 13, ProblemPhysicalData);	  //Input Datos físicos de las condiciones del problema

int i = 0;
string FileName;
stringstream InitialName1;
string FinalName1;

	FileName = "ProblemData.txt";

	InitialName1<<DIRECTORIO<<FileName;
	FinalName1=InitialName1.str();
	
	ifstream DatosProblema(FinalName1.c_str());

		if (DatosProblema){
        		string line;
        		while (getline(DatosProblema, line)){
        	 		istringstream iss(line);
					if(i < 10){
						if (iss >> ProblemNumericalData[i]){ i++; }	
					}
					else if(i >= 10 && i < 15){
						if (iss >> ProblemData[i-10]){ i++; }	
					}
					else if(i == 15){
						if (iss >> ConvectiveScheme1){ i++; }	
					}
					else{
						if (iss >> ConvectiveScheme2){ i++; }	
					}
        		 }
   	 	}
			
    	DatosProblema.close();	

}
