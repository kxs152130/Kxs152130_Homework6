/*
Name: Kevin Sanchez
Email: kxs152130@utdallas.edu
Class: CS 3377.002
Homework #6
*/

 #include <iostream>
 #include <fstream>
 #include <iomanip>
 #include <string.h>
 #include <stdio.h>
 #include <stdint.h>
 #include "cdk.h"


 #define MATRIX_WIDTH 3
 #define MATRIX_HEIGHT 5
 #define BOX_WIDTH 20
 #define MATRIX_NAME_STRING "Binary File Contents"

 using namespace std;

class BinaryFileHeader
{
  public:
    uint32_t magicNumber;
    uint32_t versionNumber;
    uint64_t numRecords;
};

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:
  
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

 int main()
 {
   BinaryFileRecord *myRecord = new BinaryFileRecord();
   BinaryFileHeader *myHeader = new BinaryFileHeader();
   ifstream binInfile ("cs3377.bin", ios::in | ios::binary);

   WINDOW	*window;
   CDKSCREEN	*cdkscreen;
   CDKMATRIX     *myMatrix;           // CDK Screen Matrix

   const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c", "d", "e"};
   const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c"};
   int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
   int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED,};
   /*
    * *    * Initialize the Cdk screen.
    * *       *
    * *          * Make sure the putty terminal is large enough
    * *             */
   window = initscr();
   cdkscreen = initCDKScreen(window);
   
   /* Start CDK Colors */
   initCDKColor();

   /*
    * * *    * Create the matrix.  Need to manually cast (const char**) to (char **)
    * * *      */
    myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,  boxTypes, 1, 1, ' ', ROW, true, true, false);

    if (myMatrix ==NULL)
    {
        printf("Error creating Matrix\n");
        _exit(1);
    }
    /* Display the Matrix */
    drawCDKMatrix(myMatrix, true);

    /*
    * *    * Dipslay a message
    * *       */

    binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
    //const char * m =(char *) (uintptr_t)myHeader->magicNumber;
    //setCDKMatrixCell(myMatrix, 1, 1,  m);
    cout <<"Magic: 0x";
    char hexaDeciNum[100];
    int i =0;
    while((myHeader ->magicNumber) != 0)
    {
       int temp = 0;
       //binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));
       temp = myHeader->magicNumber % 16;
       if(temp < 10)
       {
          hexaDeciNum[i] = temp + 48;
	  i++;
       }
       else
       {
          hexaDeciNum[i] = temp + 55;
	  i++;
       }

       myHeader->magicNumber = myHeader->magicNumber/16;
    }
    for(int j=i-1;j>=0;j--)
    	cout<< hexaDeciNum[j];
    //cout << "Magic: " << (myHeader -> magicNumber);
    cout << "       Version: " << myHeader -> versionNumber;
    cout << "             NumRecords: " << myHeader -> numRecords;
    
    //char * strlen = (char *)&myRecord->strLength;
    for(unsigned int count=0; count < myHeader -> numRecords;count++)
    {
       binInfile.read((char *) myRecord, sizeof(BinaryFileRecord));
       const char *len = (char *)(uint16_t *) &myRecord->strLength;
       //setCDKMatrixCell(myMatrix, count+2,1, strlen);
       cout << "strlen:" <<  (uint16_t)myRecord -> strLength<< endl;
       const char * buff = myRecord->stringBuffer;
       setCDKMatrixCell(myMatrix, count+2,2, buff);
       //const char * len = (char *) sizeof(&buff);
       setCDKMatrixCell(myMatrix, count+2, 1, len);
    }
    
    drawCDKMatrix(myMatrix, true);    /* required  */

    /* so we can see results */
    unsigned char x;
    cin >> x;
    binInfile.close();

    // Cleanup screen
    endCDK();
}
															   //
