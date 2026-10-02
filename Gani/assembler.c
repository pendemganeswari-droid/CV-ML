#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#define MAX 100 
struct Symbol { char name[20];
     int address; 
    }; 
     struct Opcode {
        char mnemonic[20]; 
        char code[10];
     };
      struct Symbol symtab[MAX]; 
      int symCount = 0;
       struct Opcode optab[] = { {"LDA", "00"}, {"STA", "0C"}, {"ADD", "18"}, {"SUB", "1C"}, {"MUL", "20"}, {"DIV", "24"}, {"MOVER", "04"}, {"MOVEM", "08"}, {"COMP", "28"}, {"BC", "30"}, {"READ", "3C"}, {"PRINT", "40"}, {"STOP", "0F"}
     };
      int opcodeCount = sizeof(optab) / sizeof(optab[0]);
       int searchOpcode(char opcode[]) {
         int i; 
         for (i = 0; i < opcodeCount; i++) 
         if (strcmp(optab[i].mnemonic, opcode) == 0)
          return i;
           return-1;
         } int searchSymbol(char symbol[]) {
             int i;
              for (i = 0; i < symCount; i++)
               if (strcmp(symtab[i].name, symbol) == 0)
                return symtab[i].address; 
                return-1;
            }
             void addSymbol(char symbol[], int address) {
                 if (symbol[0] != '\0' && searchSymbol(symbol) ==-1) {
                     strcpy(symtab[symCount].name, symbol);
                      symtab[symCount].address = address;
                       symCount++;
                     } 
                    }
                     int main() {
                         FILE *source, *intermediate;
                          char label[20], opcode[20], operand[20];
                           char line[100]; 
                           int lc = 0, startAddress = 0; 
                           int index, address;
                            source = fopen("input.txt", "r");
                             if (source == NULL) {
                                 printf("Error: input.txt not found.\n");
                                  return 1;
                                 }
                                  intermediate = fopen("intermediate.txt", "w");
                                   if (intermediate == NULL) { 
                                    printf("Error creating intermediate file.\n"); 
                                    fclose(source);
                                     return 1;
                                     } 
                /* PASS 1*/
                printf("\n========== PASS 1 ==========\n"); 
                while (fgets(line, sizeof(line), source)) { 
                    label[0] = opcode[0] = operand[0] = '\0'; 
                    sscanf(line, "%s %s %s", label, opcode, operand); 
                    if (strcmp(opcode, "START") == 0) { 
                        startAddress = atoi(operand);
                         lc = startAddress;
                          fprintf(intermediate, "%d\t%s\t%s\t%s\n", lc, label, opcode, operand);
                           continue;
                         } 
                         if (strcmp(opcode, "END") == 0) {
                             fprintf(intermediate, "%d\t%s\t%s\t%s\n", lc, label, opcode, operand);
                              break; 
                            } 
                            if (searchOpcode(label) !=-1 || strcmp(label, "WORD") == 0 || strcmp(label, "RESW") == 0 || strcmp(label, "RESB") == 0) { strcpy(operand, opcode);
                                 strcpy(opcode, label);
                                  label[0] = '\0';
                                 }
                                  if (label[0] != '\0') addSymbol(label, lc);
                                  fprintf(intermediate, "%d\t%s\t%s\t%s\n", lc, label, opcode, operand);
                                   index = searchOpcode(opcode);
                                    if (index !=-1)
                                     lc += 3;
                                     else if (strcmp(opcode, "WORD") == 0)
                                      lc += 3;
                                       else if (strcmp(opcode, "RESW") == 0)
                                        lc += 3 * atoi(operand);
                                         else if (strcmp(opcode, "RESB") == 0)
                                          lc += atoi(operand);
                                         } fclose(source);
                                          fclose(intermediate);
                                           printf("\nSYMBOL TABLE\n");
                                            printf("----------------------\n");
                                             printf("%-15s %s\n", "Symbol", "Address");
                                              for (int i = 0; i < symCount; i++)
                                               printf("%-15s %04d\n", symtab[i].name, symtab[i].address);
                                                /* PASS 2*/
                                                 intermediate = fopen("intermediate.txt", "r");
                                                  if (intermediate == NULL) {
                                                     printf("Error opening intermediate file.\n");
                                                      return 1;
                                                  }
                                                  printf("\n========== PASS 2 ==========\n");
                                                   printf("\nObject Code\n"); 
                                                   printf("----------------------\n");
                                                    printf("%-8s %-15s\n", "Address", "Object Code"); 
                                                    while (fgets(line, sizeof(line), intermediate)) { 
                                                        int currentAddress;
                                                         label[0] = opcode[0] = operand[0] = '\0';
                                                          sscanf(line, "%d %s %s %s", &currentAddress, label, opcode, operand);
                                                           if (strcmp(opcode, "START") == 0 || strcmp(opcode, "END") == 0) 
                                                           continue;
                                                            index = searchOpcode(opcode);
                                                             if (index !=-1) {
                                                                 address = searchSymbol(operand);
                                                                  if (address ==-1)
                                                                   address = atoi(operand);
                                                                    printf("%04d %s%04d\n", currentAddress, optab[index].code, address);
                                                                 }
                                                                 
                                                                 else if (strcmp(opcode, "WORD") == 0) {
                                                                     printf("%04d %06d\n", currentAddress, atoi(operand));
                                                                 }
                                                                 elseif(strcmp(opcode,"RESW")==0|| strcmp(opcode,"RESB")==0){
                                                                     printf("%04d---\n",currentAddress);
                                                                    }
                                                                 }
                                                                  fclose(intermediate);
                                                                   printf("\nProgramcompletedsuccessfully.\n");
                                                                    return0;
                                                                }                                
