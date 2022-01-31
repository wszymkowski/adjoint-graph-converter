#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <list>
using namespace std;

list<int> verticesList;

int numberOfVertex=0;
int numberOfVertexMulti;
int **adjacencyMatrix;
int **transformMatrix;
int **verticesMatrix;

void CheckSizeOfArray(){
    string line;
    ifstream myfile ("in5.txt");
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            numberOfVertex++;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    numberOfVertexMulti=numberOfVertex*2;
}

void AllocateMemory(){
    adjacencyMatrix=new int*[numberOfVertex];
    for(int i=0;i<numberOfVertex;i++){
        adjacencyMatrix[i]=new int[numberOfVertex];
    }

    verticesMatrix=new int*[numberOfVertex];
    for(int k=0;k<numberOfVertex;k++){
        verticesMatrix[k]=new int[2];
    }
    transformMatrix=new int*[numberOfVertexMulti];
    for(int j=0;j<numberOfVertexMulti;j++){
        transformMatrix[j]=new int[numberOfVertexMulti];
    }
}

void ResetMatrix(){
    for (int i = 0; i<numberOfVertex; i++){
        for (int j = 0; j<numberOfVertex; j++){
            adjacencyMatrix[i][j] = 0;
        }
    }

    for(int i=0;i<numberOfVertex;i++){
        for(int j=0;j<2;j++){
            verticesMatrix[i][j]=0;
        }
    }

    for(int i=0;i<numberOfVertexMulti;i++){
        for(int j=0;j<numberOfVertexMulti;j++){
            transformMatrix[i][j]=0;
        }
    }
}

void CheckMatrixADJ(int **matrix){
    for(int i=0;i<numberOfVertex;i++){
        for(int j=0;j<numberOfVertex;j++){
            cout<<matrix[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void CheckMatrixVERT(int **matrix){
    for(int i=0;i<numberOfVertex;i++){
        for(int j=0;j<2;j++){
            cout<<matrix[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void CheckMatrixTRANS(int **matrix){
    for(int i=0;i<2*numberOfVertex;i++){
        for(int j=0;j<2*numberOfVertex;j++){
            cout<<matrix[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void LoadMatrix(){
    string line;
    ifstream myfile ("in5.txt");
    if(myfile.is_open()){
        while(getline(myfile,line)){
            bool ifFirst=true;
            istringstream ss(line);
            int number;
            int currentNumber=0;
            while(ss>>number){
                if(ifFirst){
                    ifFirst=false;
                    currentNumber=number;
                    char colon;
                    ss>>colon;
                }else{
                    if(adjacencyMatrix[currentNumber][number]==1){
                        cout<<"Graph is a multigraph"<<endl;
                        system("pause");
                        exit(0);
                    }
                    adjacencyMatrix[currentNumber][number]=1;
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

bool CheckIfAdjoint(){
    for(int i=0; i<numberOfVertex; i++){
        for(int j=i+1; j<numberOfVertex; j++){
            for (int k=0; k<numberOfVertex; k++){
                if(adjacencyMatrix[i][k] && adjacencyMatrix[j][k]){
                    for(int l=0; l<numberOfVertex; l++){
                        if((!adjacencyMatrix[i][l] && adjacencyMatrix[j][l])||(adjacencyMatrix[i][l] && !adjacencyMatrix[j][l])){
                            cout<<"Graph is not adjointed"<<endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    cout<<"Graph is adjointed"<<endl;
    return true;
}

bool CheckIfLinear(){
    for(int i=0;i<numberOfVertex-1;i++){
        for(int j=i+1;j<numberOfVertex;j++){
            for(int k=0;k<numberOfVertex;k++){
                if(adjacencyMatrix[i][k]!=0 && adjacencyMatrix[j][k]!=0){
                    for(int l=0;l<numberOfVertex;l++){
                        if(adjacencyMatrix[l][i]!=0 && adjacencyMatrix[l][j]!=0){
                            cout<<"Graph is not linear"<<endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    cout<<"Graph is linear"<<endl;
    return true;
}

void FillVerticesMatrix(){
    int value=0;
    for(int i=0;i<numberOfVertex;i++){
        for(int j=0;j<2;j++){
            verticesMatrix[i][j]=value;
            value++;
        }
    }
}

void TransformMatrix(){
    for(int i=0;i<numberOfVertex;i++){
        for(int j=0;j<numberOfVertex;j++){
            if(adjacencyMatrix[j][i]==1){
                verticesMatrix[j][1]=verticesMatrix[i][0];
            }

            if(adjacencyMatrix[i][j]==1){
                verticesMatrix[j][0]=verticesMatrix[i][1];
            }
        }
    }
}

int id=0;
void ChangeToLowest(){
    bool checker=false;
    for(int i=0;i<numberOfVertex*2;i++){
        checker=false;
        for(int j=0;j<numberOfVertex;j++){
            for(int k=0;k<2;k++){
                if(verticesMatrix[j][k]==i){
                    verticesMatrix[j][k]=id;
                    checker=true;
                }
            }
        }
        if(checker==true){
            id++;
        }
    }

    for(int a=0;a<numberOfVertex;a++){
        if(transformMatrix[verticesMatrix[a][0]][verticesMatrix[a][1]]==1){
            transformMatrix[verticesMatrix[a][0]][verticesMatrix[a][1]]=2;
        }else{
            transformMatrix[verticesMatrix[a][0]][verticesMatrix[a][1]]=1;
        }
    }
}

void SaveMatrix(){
    ofstream myfile;
    myfile.open("out5.txt");
    for(int i=0;i<id;i++){
        myfile<<i<<": ";
        for(int j=0;j<numberOfVertexMulti;j++){
            if(transformMatrix[i][j]==1){
                myfile<<j<<" ";
            }else if(transformMatrix[i][j]==2){
                myfile <<j<<" "<<j<<" ";
            }
        }

        myfile<<"\n";
    }
    myfile.close();
}

main(){
    CheckSizeOfArray();
    cout<<"Number of vertex: "<<numberOfVertex<<endl;
    AllocateMemory();
    cout<<"Memory allocated.\n"<<endl;

    ResetMatrix();
    LoadMatrix();
    cout<<"Matrix of inserted graph: "<<endl;
    CheckMatrixADJ(adjacencyMatrix);

    cout<<"\n\nInformation about graph: "<<endl;
    CheckIfAdjoint();
    if(!CheckIfAdjoint()){
        system("pause");
        exit(0);
    }
    CheckIfLinear();


    cout<<"\n\nOriginal graph (Matrix of vertices): "<<endl;
    FillVerticesMatrix();
    TransformMatrix();
    CheckMatrixVERT(verticesMatrix);

    cout<<"Matrix changed to lowest ids possible: "<<endl;
    ChangeToLowest();
    CheckMatrixVERT(verticesMatrix);

    cout<<"Matrix of original graph: "<<endl;
    CheckMatrixTRANS(transformMatrix);



    SaveMatrix();



}
