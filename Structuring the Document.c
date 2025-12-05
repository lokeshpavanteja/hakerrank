#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};
static char* my_strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

struct document get_document(char* text) {
    struct document Doc;
    Doc.paragraph_count = 0;
    Doc.data = NULL;

    char *saveptr_para = NULL;
    char *para_token = strtok_r(text, "\n", &saveptr_para);
    while (para_token != NULL) {

        Doc.data = realloc(Doc.data, (Doc.paragraph_count + 1) * sizeof(struct paragraph));
        struct paragraph *para = &Doc.data[Doc.paragraph_count];
        para->data = NULL;
        para->sentence_count = 0;

        char *saveptr_sent = NULL;
        char *sent_token = strtok_r(para_token, ".", &saveptr_sent);
        while (sent_token != NULL) {

            while (*sent_token == ' ') sent_token++;

        
            if (*sent_token != '\0') {
               
                para->data = realloc(para->data, (para->sentence_count + 1) * sizeof(struct sentence));
                struct sentence *sent = &para->data[para->sentence_count];
                sent->data = NULL;
                sent->word_count = 0;

         char *saveptr_word = NULL;
                char *word_token = strtok_r(sent_token, " ", &saveptr_word);
                while (word_token != NULL) {
                    if (*word_token != '\0') {
                        sent->data = realloc(sent->data, (sent->word_count + 1) * sizeof(struct word));
                        sent->data[sent->word_count].data = my_strdup(word_token);
                        sent->word_count++;
                    }
                    word_token = strtok_r(NULL, " ", &saveptr_word);
                }
                para->sentence_count++;
            }
            sent_token = strtok_r(NULL, ".", &saveptr_sent);
        }

        Doc.paragraph_count++;
        para_token = strtok_r(NULL, "\n", &saveptr_para);
    }

    return Doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    struct paragraph p = Doc.data[n-1];
    struct sentence s = p.data[m-1];
    return s.data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
    struct paragraph p = Doc.data[m-1];
    return p.data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}



void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}