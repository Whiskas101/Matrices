#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int* Matrix(int row, int col);
void DisplayMatrix(int * Matrix);
void DisplayMatrix(int * Matrix);
void FillMatrix(int * Matrix, int mode);
int * AddMatrix(int * MatrixA, int * MatrixB, int multiplier);
int RowSize(int* Matrix);
int ColSize(int* Matrix);
int * Multiply(int * MatrixA, int * MatrixB);

//-----------------------------------------FUNCTION--WALL--START------------------------------------------------------------------------------

int RowSize(int* Matrix){
    return *(Matrix);
}
int ColSize(int* Matrix){
    return *(Matrix+1);
}

//constructor -> int* Your_Matrix_VariableName = Matrix(row, col);
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
    // we are storing the row and col size within the first 2 elements of the matrix array;
    
    //first element is the row size
    *(matrix) = row;
    //second element is the col size
    *(matrix+1) = col;

    //returning the STARTING pointer to the matrix              
    return (matrix);

}



//this function fills the matrix, 0 mode for filling it with all ZEROS, 1 for making it an identity matrix, 2 for manual inputs
void FillMatrix(int * Matrix, int mode){

    //extracting data relevant to performing operations
    int row = RowSize(Matrix);
    int col = ColSize(Matrix);
    int size = row*col+2;
    switch (mode){

        //assigning zero to all elements, base case ig
        case 0: 
                printf("\n");
                for(int i = 2; i < size; i++){
                    *(Matrix + i) = 0;
                }
                printf("\n Initialised matrix [ %d x %d ] with zeroes", row, col);
                break;

        //creating identity matrix
        case 1: 
                printf("\n");

                //if we get a non square matrix, we just point out the error and fill it up with zeros instead
                if (row != col){
                    printf("\nUnitary matrices do not exist for non square matrices !!!");
                    FillMatrix(Matrix, 0);
                    break;
                }

                //if we do get a square matrix, we return a unitary matrix
                int target = 2;
                for(int i = 2; i < size; i++){
                    *(Matrix + i) = 0;
                    
                    if(i == target){
                        *(Matrix + i) = 1;
                        target += col+1;
                    }
                    
                }
                printf("\n Filled as unitary matrix[ %d x %d ]", row, col);
                break;

                
        // Manual input for each element
        case 2: 
                printf("\n");
                //initialised user input to zero, incase the user presses enter accidentally, avoids garbage value being stored.
                int USER_INPUT_VAL = 0;
                //row and col indexes, only meant to make it clearer for the user when entering inputs
                int tempRow = 0;
                int tempCol = 0;
                for(int i = 2; i < size; i++){
                    printf("\n Enter value for %d row, %d col : --> ", tempRow + 1, tempCol + 1);
                    scanf("%d", &USER_INPUT_VAL);
                    *(Matrix + i) = USER_INPUT_VAL;
                    tempCol = (tempCol+1)%col;
                    if(tempCol == 0){
                        tempRow++;
                    }
                    
                }
                printf("\n Filled matrix [ %d x %d ]", row, col);
                DisplayMatrix(Matrix);
                break;
    }
    
}


void DisplayMatrix(int * Matrix){

    // Step 1 : extract the size information
    int row = RowSize(Matrix);
    int col = ColSize(Matrix);

    // this is done so that we know when to switch to a new line when printing
    // also, this is done so that we can know where exactly the array ends, so we dont end up in infinite loops


    // to make the code more readable
    int size = (row*col) + 2;
    //int *startPoint = (Matrix+2);

    // Step 2 : iterate using that information we extracted before

    // we are starting at index 2, because index 0 and 1 store the row and col size respectively, 
    // they dont store the actual matrix
    for(int i = 2; i < size; i++){
        if((i-2) % col == 0){ //i -2 to offset the counter, accounting for the first 2 size elements (row & col)
            printf("\n");
        }
        printf(" | %d | ", *(Matrix + i));
    }

}

//simplest function out here
void DeleteMatrix(int *Matrix){
    printf("\nDeleted matrix \n");
    free(Matrix);
}




// takes 2 matrices (A & B), and 3rd argument is just there to convert this to a subtractor, 
// set to -1 if you wish to subtract B from A
int * AddMatrix(int * MatrixA, int * MatrixB, int multiplier){
    multiplier = multiplier/abs(multiplier); // just to ensure we dont multiply by anything other than 1, 0, or -1 accidentally

    //extracting size data for both matrices
    int row_A = RowSize(MatrixA);
    int col_A = ColSize(MatrixA);
    int row_B = RowSize(MatrixB);
    int col_B = ColSize(MatrixB);

    //resulting matrix is created here, initialised to zero
    int *ResultMatrix = Matrix(row_A, col_A); 
    

    FillMatrix(ResultMatrix, 0);


    //Matrix addition can only be done with matrices of the same dimension, so we check for that here.
    //if matrix dimensions do not match, we return an empty matrix with dimensions same as the first matrix (matrix A)
    if (row_A != row_B || col_A != col_B){
        printf("\n Error, your matrix dimensions do not match \n");
    }else{
        //if matrix dimensions match, then we can proceed without worry.
        //the matrices are essentially stored as a linear array, so the addition is just simply iterating and adding over
        //each index value.
        int size = (row_A * col_A) + 2; //row and col of both matrices are equal, so we can chose either.

        for(int i = 2; i < size; i++){
            *(ResultMatrix + i) = (*(MatrixA + i) + *(MatrixB + i) * multiplier);
            
        }
        printf("\n Addition completed \n");
        DisplayMatrix(ResultMatrix);

    }

    return ResultMatrix;
}
// this is not the way we are supposed to handle addition or any other operation
// a more general and more user friendly input system will be implemented



int * Multiply(int * MatrixA, int * MatrixB){
    //extracting data
    int row_A = RowSize(MatrixA);
    int col_A = ColSize(MatrixA);
    int row_B = RowSize(MatrixB);
    int col_B = ColSize(MatrixB);


    //resultmatrix
    int *ResultMatrix;
    ResultMatrix = Matrix(row_A, col_B);

    //checking if the matrices are valid for multiplication.
    if(col_A != row_B){
        printf("\n Multiplication cannot be performed on matrices with different ROW and COL sizes !!! \n");
        FillMatrix(ResultMatrix, 0);
    }else{
        
        int sum = 0;
        


        

    }


    
}


int * Transpose(int * inputMatrix){
    //extracting row and col size
    int row = RowSize(inputMatrix);
    int col = ColSize(inputMatrix);

    //swapping dimensions
    int temp;
    temp = row;
    row = col;
    col = temp;

    //intializing a matrix that is of the dimensions of the transpose of the inputMatrix
    int * ResultMatrix;
    ResultMatrix = Matrix(row, col);

    return ResultMatrix;
}



//----------------------------------------------FUNCTION-WALL-END------------------------------------------------------------------------------
// all instances exist here, will be converted to a proper usable library when all testing is done, and code is 100% bug free
// and practically applicable

int main(){

    //testing if recently implemented functions are working
    printf("\n Start \n");
    int *matrix1;
    int *matrix2;

    matrix1 = Matrix(2,2); //row column format
    matrix2 = Matrix(2,2);
    
    FillMatrix(matrix1, 2);
    FillMatrix(matrix2, 2);
    
    int *matrix3;

    matrix3 = AddMatrix(matrix1, matrix2, 1);

    DeleteMatrix(matrix1);
    DeleteMatrix(matrix2);
    DeleteMatrix(matrix3);
    

}