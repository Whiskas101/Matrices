#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int* Matrix(int row, int col);
void DisplayMatrix(int * Matrix);
void DisplayMatrix(int * Matrix);
void FillMatrix(int * Matrix, int mode);


//constructor
int* Matrix(int row, int col){

    // we will create an array of size = row * col + 4 bytes, to store the size info within the matrix itself

    //creating a pointer that points to an integer, then assigning a contigous block of sequential memory locations
    int * matrix = (int * )malloc((sizeof (int) * ((row * col)+2)));

    // we are allocating memory for the array, just so that when the function ends, and returns the value, 
    // the compiler will not deallocate matrix (as it would do usually).
    
                        //test cases, because im a noob
                        // *matrix = 1;
                        // *(matrix+1) = 2;

    //-------------------------------------IMPORTANT------------------------------------------
    // we are encoding the row and col size within the first 2 elements of the matrix array;
    
    //first element is the row size
    *(matrix) = row;
    //second element is the col size
    *(matrix+1) = col;

    //returning the STARTING pointer to the matrix              
    return (matrix);

}



//this function fills the matrix, 0 mode for filling it with all ZEROS, 1 for making it an identity matrix, 2 for manual inputs
void FillMatrix(int * Matrix, int mode){
    int row = *Matrix;
    int col = *(Matrix+1);
    int size = row*col;
    switch (mode){
        case 0: printf("\n");
                for(int i = 2; i < size; i++){
                    *(Matrix + i) = 0;
                }
                break;

        case 1: break;

        case 2: break;
    }
}


void DisplayMatrix(int * Matrix){

    // Step 1 : extract the size information
    int row = *Matrix;
    int col = *(Matrix+1);

    // this is done so that we know when to switch to a new line when printing
    // also, this is done so that we can know where exactly the array ends, so we dont end up in infinite loops


    // to make the code more readable
    int size = row*col;
    //int *startPoint = (Matrix+2);

    // Step 2 : iterate using that information we extracted before

    // we are starting at index 2, because index 0 and 1 store the row and col size respectively, 
    // they dont store the actual matrix
    for(int i = 2; i < size; i++){
        if((i-2) % col == 0){
            printf("\n");
        }
        
        printf(" | %d | ", *(Matrix + i));
        
    }

}




int main(){
    
    printf("Start");
    int *matrix;
    
    matrix = Matrix(4,4); //row column format
    
    FillMatrix(matrix, 0);
    DisplayMatrix(matrix);
    

    
    
}