#ifndef H_MODULE
#define H_MODULE

#include <vector>
#include <fstream>

using namespace std;

#define BUF_LEN 256
#ifdef _WIN32
#define ENDL_OFFSET 2
#endif
#ifdef linux 
#define ENDL_OFFSET 1
#endif

typedef struct {
    int row_number;
    int row_length;
} row_desc_t;

void process(const char *inputFile);
bool compare(row_desc_t left, row_desc_t right);
void outputSorted(const char *outputFile, const char *inputFile,\
vector <row_desc_t> rowsDescr, vector <row_desc_t> sortedRowsDescr);
bool getNextLine(char *buf, const char* inputFile, vector <row_desc_t> rowsDescr, int rowNumber);

#endif
