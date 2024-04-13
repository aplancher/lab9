#include <stdio.h>
#include <stdlib.h>


// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType *head;

};

// Compute the hash function
int hash(int x, int hashSize)
{
	return x% 5;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		printf("Index %d -> ", i);
        struct RecordType *current = pHashArray[i].head;
        while (current != NULL){
            printf("%d %c %d -> ", current->id, current->name, current->order);
            current++;
        }
        printf("\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType hashTable[10];

    for(int i=0;i<10;i++){
        hashTable[i].head= NULL;
    }

    for(int i=0; i< recordSz;i++){
        int index= hash(pRecords[i].id);
        pRecords[i].order= index; 
        struct RecordType *newRecord= (struct RecordType *)malloc(sizeof(struct RecordType));
        *newRecord= pRecords[i];

        // insert at begining of linked list
        if(hashTable[index].head== NULL){
            hashTable[index].head= newRecord;
            newRecord->id= -1; 
        } else{
            struct RecordType *current= hashTable[index].head;
            while (current->id != -1){
                current++;
            }
            current->id= pRecords[i].id;
            current->name= pRecords[i].name;
            current->order= pRecords[i].order;
            current->id= -1; 
        }
    }

    displayRecordsInHash(hashTable, 5);

    free(pRecords);
	free(hashTable);

    return 0;
}