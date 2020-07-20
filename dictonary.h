#include <stdio.h>
#define MAXCHARS 50
#define MAXWORDS 500

typedef struct {
   char topic[MAXCHARS];
   char definition[MAXWORDS];
} DICTIONARY;

// Function Prototypes 

void displayOptionsMenu();
void dictionaryTitle();
void validateInput(char**);
int getNumWords(int);
int inputIsNumber(int*);
int getChoiceInput(int);
void validateNumInput(int);
DICTIONARY **createDictionary(int); 
DICTIONARY *makeDictionaryEntry();
void createSizeDictionaryEntries(DICTIONARY**, int);
void addToDictionary(DICTIONARY**, int*, int);
void removeFromDictionary(DICTIONARY**, int);
void searchDictionary(DICTIONARY**, int);
void viewDictionary(DICTIONARY**, int);
void displayDictionaryContent(DICTIONARY*);
void sortDictionaryEntriesByTopic(DICTIONARY**, int);
void displayAddDictionaryToFileOptions();
void getFileChoiceInput(char, DICTIONARY**, int);
void getReadFileChoice(DICTIONARY**);
int validateFileChoiceInput(char*, DICTIONARY**, int, int);
int validateReadFileInput(char*, DICTIONARY**, int);
void viewDictionaryFromFile(DICTIONARY**);
void saveToBinaryFile(DICTIONARY**, int);
void saveToTextFile(DICTIONARY**, int);
void appendToBinaryFile(DICTIONARY**, int);
void appendToTextFile(DICTIONARY**, int);
void saveDictionaryToFiles(DICTIONARY**, int);
void appendDictionaryToFiles(DICTIONARY**, int);
void checkIfDictionaryFull(int*, int);
void checkIfFileIsNull(FILE*);
void checkMemory(DICTIONARY**);
void freeMemory(DICTIONARY**, int);