#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char *id;
    int weight;
} Package;

typedef struct {
    Package *packages; 
    int size;
    int cap;
    int minw;
    int maxw;
} PostOffice;


typedef struct {
    char *name;
    PostOffice *offices; 
    int offices_count;
} Town;


static char *strdup_safe(const char *s) {
    size_t n = strlen(s);
    char *p = (char *)malloc(n + 1);
    if (!p) exit(1);
    memcpy(p, s, n + 1);
    return p;
}

static void ensure_pkg_cap(PostOffice *po, int need) 
{
    if (po->cap >= need) return;
    int newcap = po->cap ? po->cap * 2 : 4;
    while (newcap < need) newcap *= 2;
    po->packages = (Package *)realloc(po->packages, sizeof(Package) * newcap);
    if (!po->packages) exit(1);
    po->cap = newcap;
}


static void po_append_move(PostOffice *po, Package pkg) {
    ensure_pkg_cap(po, po->size + 1);
    po->packages[po->size++] = pkg;
}


static int read_int() {
    int x;
    if (scanf("%d", &x) != 1) exit(1);
    return x;
}


static int find_town_index(Town *towns, int towns_count, const char *name) {
    for (int i = 0; i < towns_count; ++i) {
        if (strcmp(towns[i].name, name) == 0) return i;
    }
    return -1;
}

/* Print town packages in required format */
static void print_town(Town *town) {
    printf("%s:\n", town->name);
    for (int i = 0; i < town->offices_count; ++i) {
        PostOffice *po = &town->offices[i];
        printf("\t%d:\n", i);
        for (int j = 0; j < po->size; ++j) {
            printf("\t\t%s\n", po->packages[j].id);
        }
    }
}

/* Perform transaction: send all packages from srcPo to dstPo.
   Accepted packages (by dstPo min/max) are appended to dstPo tail preserving order.
   Rejected packages remain in srcPo preserving order. */
static void transact(PostOffice *srcPo, PostOffice *dstPo) {
    if (srcPo->size == 0) return;

    /* Prepare temporary arrays for accepted and rejected packages */
    Package *accepted = NULL;
    int acc_size = 0, acc_cap = 0;
    Package *rejected = NULL;
    int rej_size = 0, rej_cap = 0;

    for (int i = 0; i < srcPo->size; ++i) {
        Package pkg = srcPo->packages[i]; /* struct copy, id pointer preserved */
        if (pkg.weight >= dstPo->minw && pkg.weight <= dstPo->maxw) {
            /* accepted */
            if (acc_size + 1 > acc_cap) {
                acc_cap = acc_cap ? acc_cap * 2 : 4;
                accepted = (Package *)realloc(accepted, sizeof(Package) * acc_cap);
                if (!accepted) exit(1);
            }
            accepted[acc_size++] = pkg;
        } else {
            /* rejected */
            if (rej_size + 1 > rej_cap) {
                rej_cap = rej_cap ? rej_cap * 2 : 4;
                rejected = (Package *)realloc(rejected, sizeof(Package) * rej_cap);
                if (!rejected) exit(1);
            }
            rejected[rej_size++] = pkg;
        }
    }

    /* Free old srcPo->packages array memory (but NOT the id strings; they moved to accepted/rejected) */
    free(srcPo->packages);

    /* Set srcPo to contain only rejected packages */
    srcPo->packages = rejected;
    srcPo->size = rej_size;
    srcPo->cap = rej_cap;

    /* Append accepted packages to dstPo (move ownership) */
    for (int i = 0; i < acc_size; ++i) {
        po_append_move(dstPo, accepted[i]);
    }

    free(accepted);
}

/* Count total packages in a town */
static int count_town_packages(Town *town) {
    int total = 0;
    for (int i = 0; i < town->offices_count; ++i) total += town->offices[i].size;
    return total;
}

/* Free everything (good practice) */
static void free_all(Town *towns, int towns_count) {
    for (int t = 0; t < towns_count; ++t) {
        Town *town = &towns[t];
        for (int j = 0; j < town->offices_count; ++j) {
            PostOffice *po = &town->offices[j];
            for (int k = 0; k < po->size; ++k) free(po->packages[k].id);
            free(po->packages);
        }
        free(town->offices);
        free(town->name);
    }
    free(towns);
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Town *towns = (Town *)malloc(sizeof(Town) * n);
    if (!towns) return 1;

    for (int i = 0; i < n; ++i) {
        char namebuf[256];
        if (scanf("%s", namebuf) != 1) return 1;
        towns[i].name = strdup_safe(namebuf);

        int m;
        if (scanf("%d", &m) != 1) return 1;
        towns[i].offices_count = m;
        towns[i].offices = (PostOffice *)calloc(m, sizeof(PostOffice));
        if (!towns[i].offices) return 1;

        for (int j = 0; j < m; ++j) {
            int p, mn, mx;
            if (scanf("%d %d %d", &p, &mn, &mx) != 3) return 1;
            towns[i].offices[j].minw = mn;
            towns[i].offices[j].maxw = mx;
            towns[i].offices[j].size = 0;
            towns[i].offices[j].cap = 0;
            towns[i].offices[j].packages = NULL;

            for (int k = 0; k < p; ++k) {
                char idbuf[256];
                int w;
                if (scanf("%s", idbuf) != 1) return 1;
                if (scanf("%d", &w) != 1) return 1;
                Package pkg;
                pkg.id = strdup_safe(idbuf);
                pkg.weight = w;
                po_append_move(&towns[i].offices[j], pkg);
            }
        }
    }

    /* queries */
    int q;
    if (scanf("%d", &q) != 1) return 1;
    for (int qi = 0; qi < q; ++qi) {
        int type;
        if (scanf("%d", &type) != 1) return 1;
        if (type == 1) {
            char townName[256];
            if (scanf("%s", townName) != 1) return 1;
            int idx = find_town_index(towns, n, townName);
            print_town(&towns[idx]);
        } else if (type == 2) {
            char s1[256], s2[256];
            int i1, i2;
            if (scanf("%s %d %s %d", s1, &i1, s2, &i2) != 4) return 1;
            int idx1 = find_town_index(towns, n, s1);
            int idx2 = find_town_index(towns, n, s2);
            PostOffice *src = &towns[idx1].offices[i1];
            PostOffice *dst = &towns[idx2].offices[i2];
            transact(src, dst);
        } else if (type == 3) {
            /* find town with maximum packages, first in order if tie */
            int best = 0;
            int bestIdx = 0;
            for (int t = 0; t < n; ++t) {
                int cnt = count_town_packages(&towns[t]);
                if (t == 0 || cnt > best) {
                    best = cnt;
                    bestIdx = t;
                }
            }
            printf("Town with the most number of packages is %s\n", towns[bestIdx].name);
        } else {
            /* invalid type - but per statement won't occur */
        }
    }

    free_all(towns, n);
    return 0;
}
