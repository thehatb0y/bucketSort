#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <windows.h>

struct List {
    int value;
    struct List * next;
};

struct Bucket {
    int size;
    struct List * head;
};

void listGen(int *list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        list[i] = rand() % size;
    }
};

void printList(int *list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
};

struct Bucket * createBucket(struct Bucket *bucketList, int BucketSize) {
    int i;
    bucketList = (struct Bucket *) malloc((BucketSize) * sizeof(struct Bucket));
   
    for (i = 0; i < (BucketSize); i++) {
        bucketList[i].size = 0;
    }

return bucketList;
};

int getItemGroup(int number, int BucketSize, int MaxItemSize) {
    int groupSize = MaxItemSize / BucketSize;
    int grupo = (number - 1) / groupSize + 1;

    if (grupo >= 0 && grupo <= BucketSize) {
        return grupo-1;
    } else {
        return -1; // Ou um valor que indique um erro, se necessário
    }
}

void printBucket(struct Bucket *bucketList, int BucketSize) {
    int i;
    struct List * aux;
    for (i = 0; i < BucketSize; i++) {
        printf("Bucket %d: ", i);
        aux = bucketList[i].head;
        while (aux != NULL) {
            printf("%d ", aux->value);
            aux = aux->next;
        }
        printf("\n");
    }
}

void addItem(struct Bucket *bucketList, int number, int BucketSize, int MaxItemSize) {
    int grupo = getItemGroup(number, BucketSize, MaxItemSize);
    struct List * aux;

    if (grupo != -1) {
        if (bucketList[grupo].size == 0) {
            bucketList[grupo].head = (struct List *) malloc(sizeof(struct List));
            bucketList[grupo].head->value = number;
            bucketList[grupo].head->next = NULL;
            bucketList[grupo].size++;
        } else {
            aux = bucketList[grupo].head;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = (struct List *) malloc(sizeof(struct List));
            aux->next->value = number;
            aux->next->next = NULL;
            bucketList[grupo].size++;
        }

    }

}

void fillBucket(struct Bucket *bucketList, int *ItemList, int BucketSize, int MaxItemSize) {
    int i;
    for (i = 0; i < MaxItemSize; i++) {
        addItem(bucketList, ItemList[i], BucketSize, MaxItemSize);
    }
}

int *joinBuckets(struct Bucket *bucketList, int BucketSize, int MaxItemSize, int *auxList) {
    int i;
    int j;
    int k = 0;
    auxList = (int *) malloc(MaxItemSize * sizeof(int));
    for (i = 0; i < BucketSize; i++) {
        struct List * aux;
        aux = bucketList[i].head;
        for (j = 0; j < bucketList[i].size; j++) {
            auxList[k] = aux->value;
            aux = aux->next;
            k++;
        }
    }
    return auxList;
}

void pbubbleSort(struct Bucket *bucketList, int BucketSize) {
    int i, j;
    struct List *auxList;
    struct List *auxList2;

    #pragma omp parallel for private(auxList, auxList2, j) shared(bucketList, BucketSize)
    for (i = 0; i < BucketSize; i++) {
        auxList = bucketList[i].head;
        for (j = 0; j < bucketList[i].size; j++) {
            auxList2 = auxList->next;
            while (auxList2 != NULL) {
                if (auxList->value > auxList2->value) {
                    // Troca os valores
                    int temp = auxList->value;
                    auxList->value = auxList2->value;
                    auxList2->value = temp;
                }
                auxList2 = auxList2->next;
            }
            auxList = auxList->next;
        }
    }

}

void nbubbleSort(struct Bucket *bucketList, int BucketSize) {
    int i, j;
    struct List *auxList;
    struct List *auxList2;

    for (i = 0; i < BucketSize; i++) {
        auxList = bucketList[i].head;
        for (j = 0; j < bucketList[i].size; j++) {
            auxList2 = auxList->next;
            while (auxList2 != NULL) {
                if (auxList->value > auxList2->value) {
                    // Troca os valores
                    int temp = auxList->value;
                    auxList->value = auxList2->value;
                    auxList2->value = temp;
                }
                auxList2 = auxList2->next;
            }
            auxList = auxList->next;
        }
    }
}

void freeBucket(struct Bucket *bucketList, int BucketSize) {
    int i;
    struct List *auxList;
    struct List *auxList2;

    for (i = 0; i < BucketSize; i++) {
        auxList = bucketList[i].head;
        while (auxList != NULL) {
            auxList2 = auxList->next;
            free(auxList);
            auxList = auxList2;
        }
    }
    free(bucketList);
}

int main(int argc, char **argv) {

    int *ItemList;
    int BucketSize = atoi(argv[1]);
    int MaxItemSize = atoi(argv[2]);
    int p = atoi(argv[3]);

    struct Bucket * bucketList = createBucket(bucketList, BucketSize);
    
    int i;
    int j;

    ItemList = (int *) malloc(MaxItemSize * sizeof(int));
    listGen(ItemList, MaxItemSize);
    //printList(ItemList, MaxItemSize);
    printf("BucketSize: %d\n", BucketSize);
    printf("MaxItemSize: %d\n", MaxItemSize);

    fillBucket(bucketList, ItemList, BucketSize, MaxItemSize);
    //printBucket(bucketList, BucketSize);
    
    LARGE_INTEGER start, end, frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    if (p == 1){
        printf("Paralelo\n");
        pbubbleSort(bucketList, BucketSize);
    }
    else{
        printf("Nao Paralelo\n");
        nbubbleSort(bucketList, BucketSize);
    }

    QueryPerformanceCounter(&end);
    printf("Tempo de execucao: %lf ms\n", (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000);

    //printf("BubbleSort: \n");
    //printBucket(bucketList, BucketSize);
    //ItemList = joinBuckets(bucketList, BucketSize, MaxItemSize, ItemList);
    //printList(ItemList, MaxItemSize);

    free(ItemList);
    freeBucket(bucketList, BucketSize);

return 0;   
}
