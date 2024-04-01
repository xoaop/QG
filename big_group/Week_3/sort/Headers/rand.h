
#define _MIN 0
#define _MAX 10000000

int* generate_testdata(int size,int min,int max);
void generate_and_save(int size,int min,int max,char* filename,int c);
void save_data(int *arr, int size,char* filename,int c);
int* read_data(int size,char* filename);