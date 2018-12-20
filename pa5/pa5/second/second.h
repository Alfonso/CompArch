#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define MAX 300


/*                                  STRUCTS AND ENUMS                       */

typedef enum _type{NOT=0, AND=1, OR=2, NAND=3, NOR=4, XOR=5, DECODER=6, MULTIPLEXER=7} type;

typedef struct _variable{
    char* name;
    int value;
    struct _variable* next;
}variable;

typedef struct _gate{
    type gateType;
    variable* inputVars;
    int numInputs;
    variable* outputVars;
    int numOutputs;
    variable* selectors;
    int numSelectors;
    struct _gate* next;
}gate;


/*                                  PROTOTYPE FUNCTIONS                                 */
variable* findTemp(char*);

int unsetTemp(gate*,int);

void addToBack(gate*);

int undeclaredTemp(gate*);

int tempExist(char*);

int* int_to_grey(int,int);

void populate(int*,variable*,int);

void process(variable*,variable*,int,int);

void print(variable*,variable*,int,int);

void bitNOT(gate*);

void bitAND(gate*);

void bitOR(gate*);

void bitNAND(gate*);

void bitNOR(gate*);

void bitXOR(gate*);

void bitDECODER(gate*);

void bitMULTIPLEXER(gate*);
