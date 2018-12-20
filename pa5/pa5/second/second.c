#include"second.h"

// global gates
gate* gateHead;

// global temps
variable* tempHead;

int main(int argc,char** argv){

    if(argc != 2){
        printf("error");
        return 1;
    }

    FILE* fp;
    fp = fopen(argv[1],"r");

    if(fp == NULL){
        printf("error");
        return 1;
    }

    char buff[MAX];
    char buff2[MAX];
    bzero(buff,MAX);
    bzero(buff2,MAX);
    int numInput = 0;
    int numOutput = 0;
    int counter = 0;
    int counter2 = 0;   
  
    // first thing is just the input var and the number of input variables
    fscanf(fp,"%s %d",buff,&numInput);


    // initialize input array
    variable* inputArr = (variable*)malloc(sizeof(variable)*numInput);

    // loop through for all of the input variables
    for(counter = 0;counter<numInput;counter++){
        inputArr[counter].name = (char*)malloc(sizeof(char)*MAX);
        bzero(inputArr[counter].name,MAX);
        
        // initialize value to -1
        inputArr[counter].value = -1;

        // store the variable name in the variable
        fscanf(fp,"%s",inputArr[counter].name);
    }

    fscanf(fp,"%s %d",buff,&numOutput);

    // create the array of output variables
    variable* outputArr = (variable*)malloc(sizeof(variable)*numOutput);

    // loop through for all of hte output variables
    for(counter = 0;counter<numOutput;counter++){
        outputArr[counter].name = (char*)malloc(sizeof(char)*MAX);
        bzero(outputArr[counter].name,MAX);

        // initialize to -1
        outputArr[counter].value = -1;

        // store the variable name in the array
        fscanf(fp,"%s",outputArr[counter].name);
    }

    // linked list of temps?

    

    // loop through the file creating all of the gates
    while(fscanf(fp,"%s",buff) == 1){
        if(strcmp(buff,"NOT") == 0){
            // 1 input 1 output
            gate* temp = (gate*)malloc(sizeof(gate));

            fscanf(fp,"%s %s",buff,buff2);

            // based off of what is stored in buff and buff2
            // either link directly to the previously created input
            // or to the previously created output

            // initialize inputs, outputs, and selectors
            temp->inputVars = (variable*)malloc(sizeof(variable)*1);
            temp->outputVars = (variable*)malloc(sizeof(variable)*1);
            temp->selectors  = (variable*)malloc(sizeof(variable)*0);
            
    
            int tempCheck = 1;

            // loop through all of the inputs and see if it matches any of the names
            for(counter=0;counter<numInput;counter++){
                if(strcmp(buff,inputArr[counter].name) == 0){
                    // link the gate directly to the inputArry of the matching input
                    temp->inputVars[0] = inputArr[counter];
                    tempCheck = 0;
                    break;
                }
            }

            // have to check to make sure its a temp variable
            // if it is, add to the linked list
            if(tempCheck == 1){
                if( buff[0] >= 'a' && buff[0] <= 'z'){
                    // check to see if it already exists
                    if(tempExist(buff) == 0){
                        variable* temp2 = (variable*)malloc(sizeof(variable));
                        temp2->value = -1;
                        temp2->name = (char*)malloc(sizeof(char)*MAX);
                        strcpy(temp2->name,buff);
                        temp2->next = tempHead;
                        tempHead = temp2;
                        temp->inputVars[0] = *temp2;
                    } 
                }
            }else{
                // is it a number?
                temp->inputVars[0] = (variable){buff,atoi(buff)};
                //strcpy(temp->inputVars[0]->name,buff);
                //temp->inputVars[0]->value = atoi(buff);
            }



            // check output name
            fscanf(fp,"%s",buff2);
            // loop through all of outputs and see if it matches any of the names
            tempCheck = 1;
            for(counter=0;counter<numOutput;counter++){
                if(strcmp(buff2,outputArr[counter].name) == 0){
                    temp->outputVars[0] = outputArr[counter];
                    tempCheck = 0;
                    break;
                }
            }

            // have to check to make sure its a temp variable
            // if it is, add to the linked list
            if(tempCheck == 1){
                if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                    // check to see if it already exists
                    if(tempExist(buff2) == 0){
                        variable* temp2 = (variable*)malloc(sizeof(variable));
                        temp2->value = -1;
                        temp2->name = (char*)malloc(sizeof(char)*MAX);
                        strcpy(temp2->name,buff2);
                        temp2->next = tempHead;
                        tempHead = temp2;
                        temp->outputVars[0] = *temp2;
                    }else temp->outputVars[0] = *findTemp(buff2);
                }
            }else{
                // is it a number?
                temp->outputVars[0] = (variable){buff2,atoi(buff2)};
                //strcpy(temp->outputVars[0]->name,buff2);
                //temp->outputVars[0]->value = atoi(buff2);
            }
            
            
            temp->numInputs = 1;
            temp->numOutputs = 1;
            temp->numSelectors = 0;

            // define the gate type
            temp->gateType = NOT;

            // add the gate to the global list
            addToBack(temp);

        }else if(strcmp(buff,"DECODER") == 0){
            // scanf to figure out number of input
            // 2^inputs for the number of outputs
            int tempInputNum = 0;
            fscanf(fp,"%d",&tempInputNum);
            int tempOutputNum = (1 << tempInputNum);
            gate* temp = (gate*)malloc(sizeof(gate));


            // initialize inputs, outputs, and selectors
            temp->inputVars = (variable*)malloc(sizeof(variable)*tempInputNum);
            temp->outputVars = (variable*)malloc(sizeof(variable)*tempOutputNum);
            temp->selectors  = (variable*)malloc(sizeof(variable)*0);



            // loop through all of the inputs
            for(counter=0;counter<tempInputNum;counter++){
                // store input variable name
                fscanf(fp,"%s",buff2);

                int tempCheck = 1;

                // loop through all of the inputs and see if it matches any of the names
                for(counter2=0;counter2<numInput;counter2++){
                    if(strcmp(buff2,inputArr[counter2].name) == 0){
                        // link the gate directly to the inputArry of the matching input
                        temp->inputVars[counter] = inputArr[counter2];
                        tempCheck = 0;
                        break;
                    }
                }

                // have to check to make sure its a temp variable
                // if it is, add to the linked list
                if(tempCheck == 1){
                if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                     // check to see if it already exists
                        if(tempExist(buff2) == 0){
                            variable* temp2 = (variable*)malloc(sizeof(variable));
                           temp2->value = -1;
                            temp2->name = (char*)malloc(sizeof(char)*MAX);
                            strcpy(temp2->name,buff2);
                            temp2->next = tempHead;
                            tempHead = temp2;
                           temp->inputVars[counter] = *temp2;
                        } 
                    }
                }else{
                    // is it a number?
                    temp->inputVars[counter] = (variable){buff2,atoi(buff2)};
                    //strcpy(temp->inputVars[counter]->name,buff2);
                    //temp->inputVars[counter]->value = atoi(buff2);
                }
                

            }



            // loop through all of the outputs
            for(counter=0;counter<tempOutputNum;counter++){
                // store output variable name
                fscanf(fp,"%s",buff2);

                // loop through all of outputs and see if it matches any of the names
                int tempCheck = 1;
                for(counter2=0;counter2<numOutput;counter2++){
                    if(strcmp(buff2,outputArr[counter].name) == 0){
                        temp->outputVars[counter] = outputArr[counter2];
                        tempCheck = 0;
                        break;
                    }
                }

                // have to check to make sure its a temp variable
                // if it is, add to the linked list
               if(tempCheck == 1){
                    if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                        // check to see if it already exists
                        if(tempExist(buff2) == 0){
                            variable* temp2 = (variable*)malloc(sizeof(variable));
                            temp2->value = -1;
                            temp2->name = (char*)malloc(sizeof(char)*MAX);
                            strcpy(temp2->name,buff2);
                          temp2->next = tempHead;
                            tempHead = temp2;
                            temp->outputVars[counter] = *temp2;
                        } 
                    }
                }else{
                    // is it a number?
                    temp->outputVars[counter] = (variable){buff2,atoi(buff2)};
                    //strcpy(temp->outputVars[counter]->name,buff2);
                    //temp->outputVars[counter]->value = atoi(buff2);
                }


            }


            temp->numInputs = tempInputNum;
            temp->numOutputs = (tempOutputNum);
            temp->numSelectors = 0;

            // define the gate type
            temp->gateType = DECODER;
            
            // add the gate to the global list
            addToBack(temp);

        }else if(strcmp(buff, "MULTIPLEXER") == 0){
            // scanf to figure out number of input
            // logbase 2 of that is the number of selectors
            // always 1 output
            int tempInputNum = 0;
            int tempSelectorsNum = 0;
            fscanf(fp,"%d",&tempInputNum);
            tempSelectorsNum = log(tempInputNum) / log(2);
            
            gate* temp = (gate*)malloc(sizeof(gate));


            // initialize inputs, outputs, and selectors
            temp->inputVars = (variable*)malloc(sizeof(variable)*tempInputNum);
            temp->outputVars = (variable*)malloc(sizeof(variable)*1);
            temp->selectors  = (variable*)malloc(sizeof(variable)*tempSelectorsNum);

           
            // loop through all of the inputs
            for(counter=0;counter<tempInputNum;counter++){
                // store input variable name
                fscanf(fp,"%s",buff2);

                int tempCheck = 1;

                // loop through all of the inputs and see if it matches any of the names
                for(counter2=0;counter2<numInput;counter2++){
                    if(strcmp(buff2,inputArr[counter].name) == 0){
                        // link the gate directly to the inputArry of the matching input
                        temp->inputVars[counter] = inputArr[counter2];
                        tempCheck = 0;
                        break;
                    }
                }

                // have to check to make sure its a temp variable
                // if it is, add to the linked list
                if(tempCheck == 1){
                if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                     // check to see if it already exists
                        if(tempExist(buff2) == 0){
                            variable* temp2 = (variable*)malloc(sizeof(variable));
                           temp2->value = -1;
                            temp2->name = (char*)malloc(sizeof(char)*MAX);
                            strcpy(temp2->name,buff2);
                            temp2->next = tempHead;
                            tempHead = temp2;
                           temp->inputVars[counter] = *temp2;
                        } 
                    }
                }else{
                    // is it a number?
                    temp->inputVars[counter] = (variable){buff2,atoi(buff2)};
                    //strcpy(temp->inputVars[counter]->name,buff2);
                    //temp->inputVars[counter]->value = atoi(buff2);
                }
                

            }



            // check output name
            fscanf(fp,"%s",buff2);
            // loop through all of outputs and see if it matches any of the names
            int tempCheck = 1;
            for(counter=0;counter<numOutput;counter++){
                if(strcmp(buff2,outputArr[counter].name) == 0){
                    temp->outputVars[0] = outputArr[counter];
                    tempCheck = 0;
                    break;
                }
            }

            // have to check to make sure its a temp variable
            // if it is, add to the linked list
            if(tempCheck == 1){
                if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                    // check to see if it already exists
                    if(tempExist(buff2) == 0){
                        variable* temp2 = (variable*)malloc(sizeof(variable));
                        temp2->value = -1;
                        temp2->name = (char*)malloc(sizeof(char)*MAX);
                        strcpy(temp2->name,buff2);
                        temp2->next = tempHead;
                        tempHead = temp2;
                        temp->outputVars[0] = *temp2;
                    } 
                }
            }else{
                // is it a number?
                temp->outputVars[0] = (variable){buff2,atoi(buff2)};
                //strcpy(temp->outputVars[0]->name,buff2);
                //temp->outputVars[0]->value = atoi(buff2);
            }
            


            // loop through selectors

 
            temp->numInputs = tempInputNum;
            temp->numOutputs = 1;
            temp->numSelectors = tempSelectorsNum;

            // define the gate type
            temp->gateType = MULTIPLEXER;

            // add the gate to the global list
            temp->next = gateHead;
            gateHead = temp;
        }else{
            // the rest of the gates are all the same except the gateType
            // 2 input 1 output
            gate* temp = (gate*)malloc(sizeof(gate));
            temp->inputVars = (variable*)malloc(sizeof(variable)*2);
            temp->outputVars = (variable*)malloc(sizeof(variable)*1);
            temp->selectors = (variable*)malloc(sizeof(variable)*0);            
    
         

            // loop through all of the inputs
            for(counter=0;counter<2;counter++){
                // store input variable name
                fscanf(fp,"%s",buff2);
                int tempCheck = 1;

                // loop through all of the inputs and see if it matches any of the names
                for(counter2=0;counter2<numInput;counter2++){
                    if(strcmp(buff2,inputArr[counter].name) == 0){
                        // link the gate directly to the inputArry of the matching input
                        temp->inputVars[counter] = inputArr[counter2];
                        tempCheck = 0;
                        break;
                    }
                }

                // have to check to make sure its a temp variable
                // if it is, add to the linked list
                if(tempCheck == 1){
                if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                     // check to see if it already exists
                        if(tempExist(buff2) == 0){
                            variable* temp2 = (variable*)malloc(sizeof(variable));
                           temp2->value = -1;
                            temp2->name = (char*)malloc(sizeof(char)*MAX);
                            strcpy(temp2->name,buff2);
                            temp2->next = tempHead;
                            tempHead = temp2;
                           temp->inputVars[counter] = *temp2;
                        }else{
                            temp->inputVars[counter] = *findTemp(buff2);
                        }
                    }
                }else{
                    // is it a number?
                    temp->inputVars[counter] = (variable){buff2,atoi(buff2)};
                    //strcpy(temp->inputVars[counter]->name,buff2);
                    //temp->inputVars[counter]->value = atoi(buff2);
                }
                

            }


            // check output name
            fscanf(fp,"%s",buff2);
            // loop through all of outputs and see if it matches any of the names
            int tempCheck = 1;
            for(counter=0;counter<numOutput;counter++){
                if(strcmp(buff2,outputArr[counter].name) == 0){
                    temp->outputVars[0] = outputArr[counter];
                    tempCheck = 0;
                    break;
                }
            }

            // have to check to make sure its a temp variable
            // if it is, add to the linked list
            if(tempCheck == 1){
                if( buff2[0] >= 'a' && buff2[0] <= 'z'){
                    // check to see if it already exists
                    if(tempExist(buff2) == 0){
                        variable* temp2 = (variable*)malloc(sizeof(variable));
                        temp2->value = -1;
                        temp2->name = (char*)malloc(sizeof(char)*MAX);
                        strcpy(temp2->name,buff2);
                        temp2->next = tempHead;
                        tempHead = temp2;
                        temp->outputVars[0] = *temp2;
                    }else{
                        temp->outputVars[0] = *(findTemp(buff2));
                    } 
                }
            }else{
                // is it a number?
                temp->outputVars[0] = (variable){buff2,atoi(buff2)};
                //strcpy(temp->outputVars[0]->name,buff2);
                //temp->outputVars[0]->value = atoi(buff2);
            }
            



 
            // define the gate type
            if(strcmp(buff,"AND") == 0){
                temp->gateType = AND;
            }else if(strcmp(buff,"OR") == 0){
                temp->gateType = OR;
            }else if(strcmp(buff,"NAND") == 0){
                temp->gateType = NAND;
            }else if(strcmp(buff,"NOR") == 0){
                temp->gateType = NOR;
            }else if(strcmp(buff,"XOR") == 0){
                temp->gateType = XOR;
            }            

            temp->numInputs = 2;
            temp->numOutputs = 1;
            temp->numSelectors = 0;

            // add the gate to the global list
            addToBack(temp);
        }
    } 

    // Now that we have the global linked list of gates
    // go through the list and find temp variables and shit?

    //temps* tempPtr = tempHead;

/*                      MAIN LOOP                   */    

/*
    gate* testptr = gateHead;
    while(testptr != NULL){
        printf("Gate: %d\n",testptr->gateType);
        testptr = testptr->next;
    }
   
    return 1; 
*/


    for(counter=0;counter<(1 << numInput);counter++){
        int* grey = int_to_grey(counter,numInput);
        
        populate(grey,inputArr,numInput);

        process(inputArr,outputArr,numInput,numOutput);

        print(inputArr,outputArr,numInput,numOutput);
        
    }

    fclose(fp);
    return 0;
}

variable* findTemp(char* name){
    variable* ptr = tempHead;
    while(ptr != NULL){
        if(strcmp(ptr->name,name) == 0)
            return ptr;
        ptr = ptr->next;
    }
   return NULL;
}


void print(variable* input,variable* output,int numInput,int numOutput){
    int counter=0;
    for(counter=0;counter<numInput;counter++)
        printf("%d ",input[counter].value);
    for(counter=0;counter<numOutput;counter++)
        printf("%d ",output[counter].value);
    printf("\n");
    return;
}

void process(variable* inputs,variable* outputs,int numInput,int numOutput){

    int skip = 1;
    gate* ptr = gateHead;

    while(skip == 1){
        skip = 0;
        ptr = gateHead;
        while(ptr != NULL){
            // check to see if the input is a temp variable
            if(unsetTemp(ptr,ptr->numInputs) == 2){
                // skip over doing this gate
                
                printf("skip?\n");
                skip = 1;
            }else{
                // none of the inputs are temps
                if(ptr->gateType == NOT){
                    //printf("not\n");
                    bitNOT(ptr);
                }else if(ptr->gateType == AND){
                    //printf("and\n");
                    bitAND(ptr);
                }else if(ptr->gateType == OR){
                    //printf("Or\n");
                    bitOR(ptr);
                }else if(ptr->gateType == NAND){
                    //printf("nad\n");
                    bitNAND(ptr);
                }else if(ptr->gateType == NOR){
                    //printf("nOr\n");
                    bitNOR(ptr);
                }else if(ptr->gateType == XOR){
                    //printf("xOr\n");
                    bitXOR(ptr);
                }else if(ptr->gateType == DECODER){

                    bitMULTIPLEXER(ptr);
                }
               
            }
            
            ptr = ptr->next;
        }

    }


    return;
}

// returns 1 if there are any temp variables with value -1
// returns 0 if otherwise
int unsetTemp(gate* ptr,int numInput){
    int counter=0;
    for(counter=0;counter<numInput;counter++){
        if(ptr->inputVars[counter].value == -1){
            // is temp that is unset
            return 1;
        }
    }


    return 0;
}

void addToBack(gate* new_gate){
    if(gateHead == NULL){
        new_gate->next = NULL;
        gateHead = new_gate;
    }else{
        gate* ptr = gateHead;

        while(ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = new_gate;
        new_gate->next = NULL;
    }


    return;
}

// puts values of grey into input
void populate(int* grey,variable* input,int numInput){

    int counter=0;
    for(counter=0;counter<numInput;counter++){
        input[counter].value = grey[counter];
    }
/*
    for(counter=0;counter<numInput;counter++){
        printf("%d\t",input[counter].value);
    }

    printf("\n");
  */  
    // makes temp variables values equal to -1
    variable* ptr = tempHead;

    while(ptr != NULL){
        ptr->value = -1;
        ptr = ptr->next;
    }

    return;
}


int* int_to_grey(int in,int inputNum){
    int* bin = (int*)malloc(sizeof(int)*inputNum);

    unsigned int mask = 1U << (inputNum - 1);

    int counter=0;
    for(counter=0;counter<inputNum;counter++){
        bin[counter] = (in & mask) ? 1 : 0;
        in <<= 1;
    }

    // binary values stored in bin
    // convert to grey and store in ret_val

    int* ret_val = (int*)malloc(sizeof(int)*inputNum);

    // first val is the same
    ret_val[0] = bin[0];
    

    for(counter=1;counter<inputNum;counter++){
        ret_val[counter] = bin[counter] ^ bin[counter-1];
    }


    return ret_val;
}

// arguments is the name
// it is a temp variable
// returns 1 if it already exists
// returns 0 if it does not
int tempExist(char* name){
    variable* ptr = tempHead;
    while(ptr != NULL){
        if(strcmp(name,ptr->name) == 0){
            return 1;
        }
        ptr = ptr->next;
    }


    return 0;
}

void bitNOT(gate* ptr){
    ptr->outputVars[0].value = ptr->inputVars[0].value ^ 1;
    return;
}

void bitAND(gate* ptr){
    ptr->outputVars[0].value = ptr->inputVars[1].value & ptr->inputVars[0].value;
    return;
}

void bitOR(gate* ptr){
    ptr->outputVars[0].value = ptr->inputVars[1].value | ptr->inputVars[0].value;
    return;
}

void bitNAND(gate* ptr){
    ptr->outputVars[0].value = (ptr->inputVars[1].value & ptr->inputVars[0].value) ^ 1;
    return;
}

void bitNOR(gate* ptr){
    ptr->outputVars[0].value = (ptr->inputVars[1].value | ptr->inputVars[0].value) ^ 1;
    return;
}

void bitXOR(gate* ptr){
    ptr->outputVars[0].value = (ptr->inputVars[1].value ^ ptr->inputVars[0].value);
    return;
}

void bitDECODER(gate* ptr){

    return;
}

void bitMULTIPLEXER(gate* ptr){

    return;
}
