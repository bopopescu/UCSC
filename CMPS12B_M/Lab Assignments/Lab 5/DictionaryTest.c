/*Seongwoo Choi
 *scho29
 *CMPS12B/M
 *Dictionary ADT test class
 *Laboratory Assignment 5
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Dictionary.h"

#define MAX_LEN 180

int main(int argc, char *argv[])
{
    Dictionary A = newDictionary();
    char *k;
    char *v;
    char *word1[] = {"hana", "dul", "sett", "nett", "dasut", "yeosut", "ilgob", "yeodul", "ahob"};
    char *word2[] = {"uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve"};
    int i;

    printf("%s\n", (isEmpty(A) ? "true" : "false"));

    for (i = 0; i < 9; i++)
    {
        insert(A, word1[i], word2[i]);
    }

    printDictionary(stdout, A);

    for (i = 0; i < 9; i++)
    {
        k = word1[i];
        v = lookup(A, k);
        printf("key=\"%s\" %s\"%s\"\n", k, (v == NULL ? "not found " : "value="), v);
    }

    // insert(A, "hana", "uno"); // error: key collision

    delete(A, "hana");
    delete(A, "yeosut");
    delete(A, "ahob");

    printDictionary(stdout, A);

    for (i = 0; i < 7; i++)
    {
        k = word1[i];
        v = lookup(A, k);
        printf("key=\"%s\" %s\"%s\"\n", k, (v == NULL ? "not found " : "value="), v);
    }

    // delete(A, "ahob");  // error: key not found

    printf("%s\n", (isEmpty(A) ? "true" : "false"));
    printf("%d\n", size(A));
    makeEmpty(A);
    printf("%s\n", (isEmpty(A) ? "true" : "false"));

    freeDictionary(&A);

    return (EXIT_SUCCESS);
}
