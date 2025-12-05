#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
    return document[n-1][m-1][k-1];
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return document[m-1][k-1];
}

char*** kth_paragraph(char**** document, int k) {
    return document[k-1];
}

char**** get_document(char* text) {

    int para_count = 1;
    for (int i = 0; text[i]; i++)
        if (text[i] == '\n') para_count++;

    char**** document = malloc(para_count * sizeof(char***));

    char *save_para, *save_sent, *save_word;

    int p = 0;
    char* paragraph_str = strtok_r(text, "\n", &save_para);

    while (paragraph_str != NULL) {

        int sentence_count = 0;
        for (int i = 0; paragraph_str[i]; i++)
            if (paragraph_str[i] == '.') sentence_count++;

        char*** paragraph = malloc(sentence_count * sizeof(char**));

        int s = 0;
        char* sentence_str = strtok_r(paragraph_str, ".", &save_sent);

        while (sentence_str != NULL) {

            int word_count = 1;
            for (int i = 0; sentence_str[i]; i++)
                if (sentence_str[i] == ' ') word_count++;

            char** sentence = malloc(word_count * sizeof(char*));

            int w = 0;
            char* word = strtok_r(sentence_str, " ", &save_word);

            while (word != NULL) {
                sentence[w] = malloc(strlen(word) + 1);
                strcpy(sentence[w], word);
                w++;
                word = strtok_r(NULL, " ", &save_word);
            }

            paragraph[s] = sentence;
            s++;

            sentence_str = strtok_r(NULL, ".", &save_sent);
        }

        document[p] = paragraph;
        p++;

        paragraph_str = strtok_r(NULL, "\n", &save_para);
    }

    return document;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}