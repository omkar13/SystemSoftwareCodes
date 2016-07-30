/*
 *  * binread.c
 *   */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 1024

unsigned int input_data[MAX_ELEMENTS];

unsigned int convertFromBEToLE(unsigned int big){


printf("in function , input value:%u " , big);

unsigned char *p = (unsigned char*) &big;

// unsigned int little = (unsigned int)*p | ((unsigned int) p[1])<<8 | ((unsigned int) p[2])<<16 | ((unsigned int) p[3])<<24;


unsigned int mask1 = 0xff000000;
unsigned int mask2 = 0x00ff0000;
unsigned int mask3 = 0x0000ff00;
unsigned int mask4 = 0x000000ff;

unsigned int val1 = mask1 & big ; 
unsigned int val2 = mask2 & big ;
unsigned int val3 = mask3 & big ;
unsigned int val4 = mask4 & big ;

unsigned int little = val1 >> 24 | val2 >> 8 | val3<<8 | val4 << 24 ; 

printf("in function , return value:%u " ,little );

return little;
}


int main(int argc, char **argv)
{
  unsigned int size_from_file;
  unsigned int how_many_read;
  FILE *fp;
  unsigned int i;

  if (argc != 2) {
    fprintf(stderr, "syntax for command should be: %s filename\n", argv[0]);
    exit(1);
  }

  /* The mode "rb" means read a binary file.  The "b" is
 *    * not necessary in Linux systems, but is needed in
 *       * MS Windows and various other OSes. */
  if ((fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "failed to open file %s for input\n", argv[1]);
    exit(1);
  }

  printf("\nAttempting to read array stored in %s ...\n", argv[1]);
  
  how_many_read = fread(&size_from_file, sizeof(unsigned int), 1, fp);
	
  if (how_many_read != 1) {
    fprintf(stderr, 
            "Not enough bytes in %s to form an element count.\n",
            argv[1]);
    exit(1);
  }
 
 unsigned int size_from_file_BE = convertFromBEToLE(size_from_file);

  printf("Number of elements stated in file: %u\n",size_from_file_BE );


  if (size_from_file_BE > MAX_ELEMENTS) {
    fprintf(stderr, 
            "This program can't handle an array of over %u elements.\n",
            (unsigned int) MAX_ELEMENTS);
    exit(1);
  }

  how_many_read = fread(input_data, sizeof(unsigned int), size_from_file_BE, fp);
  if (how_many_read != size_from_file_BE) {
    fprintf(stderr, 
            "Read error occurred before %u elements could be read from %s.\n",
            size_from_file_BE,
            argv[1]);
    exit(1);
  }

  for (i = 0; i < size_from_file_BE; i++)
    printf("Element %d: %u\n", i, convertFromBEToLE(input_data[i]));

  if (fclose(fp) != 0) {
    fprintf(stderr,
            "Error detected closing %s; something weird happened.\n",
            argv[1]);
    exit(1);
  }

  return 0;
}




