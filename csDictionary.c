/***********************************************
Name: Jay J. Cruz 
Date: 07/02/2020
Description: Computer Science Dictionary Program
************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include "dictonary.h"
#define PAUSE system("pause")
#define CLS system("cls")
#define FLUSH while(getchar() != '\n')

int main() {
   // declare variables for user input
   int choiceInput;
   char fileChoice, userChoice;
   int size = 0, eSize = 0;

   // allocate disjoint memory array for storing words/definitions
   DICTIONARY **dictionary = NULL;

   size = getNumWords(size);
   dictionary = createDictionary(size);
   checkMemory(dictionary);
   createSizeDictionaryEntries(dictionary, size);

   // start menu system to add, search, delete, view & 
   // read/write dictionary to files
   do {
      displayOptionsMenu();
      switch (getChoiceInput(choiceInput)) {
         case 1:
            addToDictionary(dictionary, &eSize, size);
            sortDictionaryEntriesByTopic(dictionary, size);
            break;
         case 2:  
            searchDictionary(dictionary, size);
            break;
         case 3:
            removeFromDictionary(dictionary, size); 
            break;
         case 4:
            viewDictionary(dictionary, size);
            break;
         case 5:   
            displayAddDictionaryToFileOptions();
            getFileChoiceInput(fileChoice, dictionary, size);
            getReadFileChoice(dictionary);
            break;
         case 6:  
            printf("Exiting CS Dictionary....\n");
            exit(1);
         default:  
            printf("Invalid option selected...\n");
            break;
      }
   } while (choiceInput != 6);

   freeMemory(dictionary, eSize);

   return 0;
}

// Function Definitions 

void displayOptionsMenu() {
   dictionaryTitle();
   printf("\n1. Add CS topics & definitions to the dictionary\n");
   printf("\n2. Search a CS topic & definition from the dictionary\n");
   printf("\n3. Delete a CS topic & definition from the dictionary\n");
   printf("\n4. View CS dictionary\n");
   printf("\n5. View options for adding dictionary to files\n");
   printf("\n6. Exit the program\n");
   printf("\n=================================================\n");

} // end displayMenu

void dictionaryTitle() {
   printf("\n==================CS DICTIONARY=================\n");
} // end dictionaryTitle

int getNumWords(int size) {
   int sizeResult = 0;
   printf("\nWhat size would you like to make the dictionary?\n");
   printf("Add number of topics: ");
   if (inputIsNumber(&size)) {
      sizeResult = size;
   }
   return sizeResult;
} // end getNumWords

int inputIsNumber(int *sizeInput) {
  return (scanf("%i", sizeInput)) == 1; 
} // end inputIsNumber

int getChoiceInput(int choice) {
   scanf("%i", &choice); FLUSH;
   return (int)choice;
} // end getChoiceInput

void displayAddDictionaryToFileOptions() {
   printf("\nChoose from below options:\n");
   printf("Type S to save dictionary to files\n");
   printf("Type A to append dictionary entries to existing files\n");
   printf("Type Q to quit\n");
} // end displayAddDictionaryToFilesOptions

void getFileChoiceInput(char choice, DICTIONARY** dictionary, int size) {
   int validateChoiceInput = 0;

   while (validateChoiceInput == 0) {
      scanf("%c", &choice); FLUSH;
      validateChoiceInput = validateFileChoiceInput(&choice, dictionary, validateChoiceInput, size);
   }
} // getFileChoiceInput

int validateFileChoiceInput(char* choice, DICTIONARY** dictionary, int validate, int size) {
   if (toupper(*choice) == 'S') {
         validate = 1;
         saveDictionaryToFiles(dictionary, size);
      }
      else if (toupper(*choice) == 'A') {
         validate = 1;
         appendDictionaryToFiles(dictionary, size);
      }
      else if (toupper(*choice) == 'Q') {
         validate = 1;
      }
      else {
         printf("Invalid file option selected..\n");
         displayAddDictionaryToFileOptions();
      }
      return validate;
} // end validateFileChoiceInput

void getReadFileChoice(DICTIONARY** dictionary) {
   char readFileChoice;
   int validateChoiceInput = 0;

   while (validateChoiceInput == 0) {
      printf("\nWould you like to read the dictionary from the text file?(Y/N)\n");
      scanf("%c", &readFileChoice); FLUSH;
      validateChoiceInput = validateReadFileInput(&readFileChoice, dictionary, validateChoiceInput);
   }
} // end getReadFileChoice

int validateReadFileInput(char* choice, DICTIONARY** dictionary, int validate) {
   if (toupper(*choice) == 'Y') {
         validate = 1;
         viewDictionaryFromFile(dictionary);
      }
      else if (toupper(*choice) == 'N') {
         validate = 1;
      }
      else {
         printf("Invalid input entered..\n");
      }
      return validate;
} // end validateReadFileInput

void displayDictionaryFileContent(DICTIONARY** dictionary) {
   FILE* readDictFilePtr;
   char dictionaryReader;

   readDictFilePtr = fopen("dictionary.txt", "r");
   checkIfFileIsNull(readDictFilePtr);
   
   while ( (dictionaryReader = getc(readDictFilePtr) ) != EOF) {
      printf("%c", dictionaryReader);
   }
   fclose(readDictFilePtr);
} // end displayDictionaryContent

void addToDictionary(DICTIONARY **dictionary, int *eSize, int size) {
   if (*eSize == size) {
      printf("Dictionary is Full...\n");
      return;
   }

   dictionary[*eSize] = calloc(1, sizeof(DICTIONARY*));
   dictionary[*eSize] = makeDictionaryEntry();

   for (int i = 0; i < size; i++) {
      printf("\nAdd a Computer Science topic: ");
      fscanf(stdin, " "); // skip whitespace
      fgets(dictionary[*eSize]->topic, MAXCHARS, stdin);

      printf("\nAdd the definition: "); 
      fgets(dictionary[*eSize]->definition, MAXWORDS, stdin);
      *eSize = *eSize + 1;
   }
} // end addToDictionary

void searchDictionary(DICTIONARY **dictionary, int size) {
   char topicInput[MAXCHARS];

   printf("Enter a topic to search for: \n");
   fgets(topicInput, MAXCHARS, stdin);

   for (int i = 0; i < size; i++) {
      // determine if entered topic is in dictionary
      if (strcmp(topicInput, dictionary[i]->topic) == 0) {
         printf("Topic: %s\n", dictionary[i]->topic);
         printf("Definition: %s\n", dictionary[i]->definition);
         return;
      } 
      else {
         continue;
      }
   } // end for
} // end searchDictionary

void removeFromDictionary(DICTIONARY **dictionary, int size) {
   char removeTopicInput[MAXCHARS];

   printf("Enter a topic to remove:\n");
   fgets(removeTopicInput, MAXCHARS, stdin);

   for (int i = 0; i < size; i++) {
      // determine if entered topic is in dictionary
      if (strcmp(removeTopicInput, dictionary[i]->topic) == 0) {
         printf("Deleteing dictionary entry for topic: %s", dictionary[i]->topic);
         dictionary[i]->topic[0] = '\0';
         dictionary[i]->definition[0] = '\0';
         return;
      } 
      else {
         continue;
      }
   } // end for
} // removeFromDictionary

void sortDictionaryEntriesByTopic(DICTIONARY** dictionary, int size) {
   // set temp var for storing word
   char tempWord[MAXCHARS];
   char tempDef[MAXWORDS];

   // double for loop to sort dictionary in asc order(alphabetically)
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
         if ( (strcmp(dictionary[i]->topic, dictionary[j]->topic)) < 0 ) {
            strcpy(tempWord, dictionary[i]->topic);
            strcpy(dictionary[i]->topic, dictionary[j]->topic);
            strcpy(dictionary[j]->topic, tempWord);
            strcpy(tempDef, dictionary[i]->definition);
            strcpy(dictionary[i]->definition, dictionary[j]->definition);
            strcpy(dictionary[j]->definition, tempDef);
         }
      }
   }
} // end sortDictionaryEntriesByTopic

void viewDictionary(DICTIONARY** dictionary, int size) {
   for (int i = 0; i < size; i++) {
      displayDictionaryContent(dictionary[i]);
   } 
} // end viewDictionary

void displayDictionaryContent(DICTIONARY* dictionaryEntry) {
   printf("\nTopic: %s\n", dictionaryEntry->topic);
   printf("Definition: %s\n", dictionaryEntry->definition);
} // end displayDictionaryContent

void viewDictionaryFromFile(DICTIONARY** dictionary) {
   dictionaryTitle();
   displayDictionaryFileContent(dictionary);
} // end viewDictionaryFromFile

void saveDictionaryToFiles(DICTIONARY** dictionary, int size) {
   saveToBinaryFile(dictionary, size);
   saveToTextFile(dictionary, size);
} // end saveDictionaryToFiles

void appendDictionaryToFiles(DICTIONARY** dictionary, int size) {
   appendToBinaryFile(dictionary, size);
   appendToTextFile(dictionary, size);
} // end appendDictionaryToFiles

void saveToTextFile(DICTIONARY** dictionary, int size) {
   FILE* dictTxtFilePtr;
   fpos_t dictTxtFilePosition;

   dictTxtFilePtr = fopen("dictionary.txt", "w");
   fgetpos(dictTxtFilePtr, &dictTxtFilePosition);
   checkIfFileIsNull(dictTxtFilePtr);

   fprintf(dictTxtFilePtr, "\n==================CS DICTIONARY=================\n");
   for (int i = 0; i < size; i++) {
      fprintf(dictTxtFilePtr, "Topic: %s\n", dictionary[i]->topic);
      fprintf(dictTxtFilePtr, "Definition: %s\n", dictionary[i]->definition);
   }
   fsetpos(dictTxtFilePtr, &dictTxtFilePosition);
   fclose(dictTxtFilePtr);
} // end saveToTextFile

void saveToBinaryFile(DICTIONARY** dictionary, int size) {
   FILE* dictBinFilePtr;
   fpos_t dictBinFilePosition;

   dictBinFilePtr = fopen("dictionary.bin", "wb");
   fgetpos(dictBinFilePtr, &dictBinFilePosition);
   checkIfFileIsNull(dictBinFilePtr);

   for (int i = 0; i < size; i++) {
      fwrite(&dictionary[i], sizeof(DICTIONARY), 1, dictBinFilePtr);
   }
   fsetpos(dictBinFilePtr, &dictBinFilePosition);
   fclose(dictBinFilePtr);
} // end saveToBinaryFile

void appendToTextFile(DICTIONARY** dictionary, int size) {
   FILE* dictTxtFilePtr;
   fpos_t dictTxtFilePosition;

   dictTxtFilePtr = fopen("dictionary.txt", "a");
   fgetpos(dictTxtFilePtr, &dictTxtFilePosition);
   checkIfFileIsNull(dictTxtFilePtr);

   for (int i = 0; i < size; i++) {
      fprintf(dictTxtFilePtr, "Topic: %s\n", dictionary[i]->topic);
      fprintf(dictTxtFilePtr, "Definition: %s\n", dictionary[i]->definition);
   }
   fsetpos(dictTxtFilePtr, &dictTxtFilePosition);
   fclose(dictTxtFilePtr);
} // end appendToTextFile

void appendToBinaryFile(DICTIONARY** dictionary, int size) {
   FILE* dictBinFilePtr;
   fpos_t dictBinFilePosition;

   dictBinFilePtr = fopen("dictionary.bin", "ab");
   fgetpos(dictBinFilePtr, &dictBinFilePosition);
   checkIfFileIsNull(dictBinFilePtr);

   for (int i = 0; i < size; i++) {
      fwrite(&dictionary[i], sizeof(DICTIONARY), 1, dictBinFilePtr);
   }
   fsetpos(dictBinFilePtr, &dictBinFilePosition);
   fclose(dictBinFilePtr);
} // end appendToBinFile

DICTIONARY** createDictionary(int size) {
   DICTIONARY** dictResult = NULL;

   // allocate size amount of memory space
   dictResult = calloc(size, sizeof(DICTIONARY**));
   // checkMemory(dictResult);

   return dictResult;
} // end createDictionary

void createSizeDictionaryEntries(DICTIONARY **dictionary, int size) {
   for (int i = 0; i < size; i++) {
      dictionary[i] = makeDictionaryEntry();
   }
} // end createSizeDictionaryEntries

DICTIONARY* makeDictionaryEntry() {
   DICTIONARY* dictEntryResult = NULL;

   dictEntryResult = calloc(1, sizeof(DICTIONARY));

   if (dictEntryResult == NULL) {
      printf("Could not allocate enough memory..\n");
      PAUSE;
      exit(1);
   }
   return dictEntryResult;
} // makeDictionaryEntry

void checkIfFileIsNull(FILE* file) {
   if (file == NULL) {
      printf("Could not open file..\n");
      PAUSE;
      exit(1);
   }
} // end checkIfFileIsNull

void checkMemory(DICTIONARY **dictionary) {
   if (dictionary == NULL) {
      printf("Could not allocate enough memory..\n");
      PAUSE;
      exit(1);
   }
} // end checkMemory

void freeMemory(DICTIONARY **dictionary, int eSize) {
   for (int i = 0; i < eSize; i++) {
      free(dictionary[i]);
   }
   free(dictionary);
} // end freeMemory
