#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct
{
    double **M;
    double **T;
    double **I;
    int t;
} mat;

void creerMat(mat *m, int n);
mat *lireMatrice(FILE *f);
void freeHuitfi(mat *m);
void multiMat(mat *d, double **m, double **n);
void transpo(mat *m);
mat *ata(mat *m);
mat *cpyDemiMat(double **m, int dl, int fl, int dc, int fc);
mat *inversion(mat *m);
mat *addMat(mat *o, double **m, double **n);
mat *subMat(mat *o, double **m, double **n);
void init(mat *B, double **m, int dl, int fl, int dc, int fc);
void creerFichier(const char *nomFichier, mat *m, double **M);

int main(int argc, char *argv[])
{
    mat *m;
    FILE *f = fopen(argv[1], "rb");
    m = lireMatrice(f);
    transpo(m);
    fclose(f);
    mat *ATA = (mat *)malloc(sizeof(mat));
    creerMat(ATA, m->t);
    ATA = ata(m);
    ATA = inversion(ATA); // le code marche parfaitement 
    mat *AI = (mat *)malloc(sizeof(mat));
    creerMat(AI, m->t);
    multiMat(AI, ATA->I, m->T);

    printf("taille matrice: %d\n", m->t);
    for (int i = 0; i < m->t; i++)
    {
        for (int j = 0; j < m->t; j++)
        {
            printf("%lf ", AI->M[i][j]);
        }
        printf("\n");
    }

    freeHuitfi(m);
    freeHuitfi(ATA);
    freeHuitfi(AI);
    return EXIT_SUCCESS;
}

void creerMat(mat *m, int n)
{
    m->t = n;
    m->M = (double **)malloc(m->t * sizeof(double *));
    m->T = (double **)malloc(m->t * sizeof(double *));
    m->I = (double **)malloc(m->t * sizeof(double *));
    for (int i = 0; i < m->t; i++)
    {
        m->M[i] = (double *)malloc(m->t * sizeof(double));
        m->T[i] = (double *)malloc(m->t * sizeof(double));
        m->I[i] = (double *)malloc(m->t * sizeof(double));
    }
}

mat *lireMatrice(FILE *f)
{
    mat *m = (mat *)malloc(sizeof(mat));
    int n;
    fscanf(f, "%d", &n);
    int i, j;
    double d;
    creerMat(m, n);
    for (i = 0; i < m->t; i++)
    {
        for (j = 0; j < m->t; j++)
        {
            fscanf(f, "%lf", &d);
            m->M[i][j] = d;
        }
    }
    return m;
}

void freeHuitfi(mat *m)
{
    for (int i = 0; i < m->t; i++)
    {
        free(m->M[i]);
        free(m->T[i]);
        free(m->I[i]);
    }
    free(m->M);
    free(m->T);
    free(m->I);
    free(m);
}

void multiMat(mat *d, double **m, double **n)
{
    for (int i = 0; i < d->t; i++)
    {
        for (int j = 0; j < d->t; j++)
        {
            d->M[i][j] = 0.0;
            for (int k = 0; k < d->t; k++)
            {
                d->M[i][j] += m[i][k] * n[k][j];
            }
        }
    }
}

void transpo(mat *m)
{
    for (int i = 0; i < m->t; i++)
    {
        for (int j = 0; j < m->t; j++)
        {
            m->T[j][i] = m->M[i][j];
        }
    }
}

mat *ata(mat *m)
{
    mat *n = (mat *)malloc(sizeof(mat));
    creerMat(n, m->t);
    multiMat(n, m->T, m->M);
    return n;
}

mat *cpyDemiMat(double **m, int dl, int fl, int dc, int fc)
{
    mat *n = (mat *)malloc(sizeof(mat));
    creerMat(n, fl - dl);

    for (int i = dl; i < fl; ++i)
    {
        for (int j = dc; j < fc; ++j)
        {
            n->M[i - dl][j - dc] = m[i][j];
        }
    }
    return n;
}

mat *inversion(mat *m)
{
    if (m->t == 1) // cas de base si la matrice est alors un scalaire
    {
        assert(m->M[0][0] != 0);

        if (m->M[0][0] > 0)
        {
            m->I[0][0] = 1.0 / m->M[0][0];
        }
        else
        {
            m->I[0][0] = -1.0 / m->M[0][0];
        }
        return m;
    }
    else
    {
	// allocation mémoire puis opération nécessaire juste après
        mat *B = (mat *)malloc(sizeof(mat));
        init(B, m->M, 0, m->t / 2, 0, m->t / 2);
        B = inversion(B);

        mat *C = (mat *)malloc(sizeof(mat));
        init(C, m->M, m->t / 2, m->t, 0, m->t / 2);
        transpo(C);

        mat *D = (mat *)malloc(sizeof(mat));
        init(D, m->M, m->t / 2, m->t, m->t / 2, m->t);

        mat *CBi = (mat *)malloc(sizeof(mat));
        creerMat(CBi, (m->t) / 2);

        multiMat(CBi, C->M, B->I);
		transpo(CBi);

        mat *CBiCt = (mat *)malloc(sizeof(mat));
        creerMat(CBiCt, (m->t) / 2);

        multiMat(CBiCt, CBi->M, C->T);

        mat *S = (mat *)malloc(sizeof(mat));
        creerMat(S, (m->t) / 2);

        S = subMat(S, D->M, CBiCt->M);
        S = inversion(S);

        mat *SiCBi = (mat *)malloc(sizeof(mat));
        creerMat(SiCBi, (m->t) / 2);

        multiMat(SiCBi, S->I, CBi->M);

        mat *BiCtSi = (mat *)malloc(sizeof(mat));
        creerMat(BiCtSi, (m->t) / 2);

        multiMat(BiCtSi, CBi->T, S->I);

        mat *BiCtSiCBi = (mat *)malloc(sizeof(mat));
        creerMat(BiCtSiCBi, (m->t) / 2);

        multiMat(BiCtSiCBi, CBi->T, SiCBi->M);

        mat *BpBiCtSiCBi = (mat *)malloc(sizeof(mat));
        creerMat(BpBiCtSiCBi, (m->t) / 2);

        BpBiCtSiCBi = addMat(BpBiCtSiCBi, B->I, BiCtSiCBi->M);

        // formation de l'inverse
        for (int i = 0; i < m->t; i++)
        {
            for (int j = 0; j < m->t; j++)
            {
                if (i < m->t / 2)
                {
                    if (j < m->t / 2)
                    {
                        m->I[i][j] = BpBiCtSiCBi->M[i][j];
                    }
                    else
                    {
                        m->I[i][j] = -1 * BiCtSi->M[i][j - m->t / 2];
                    }
                }
                else
                {
                    if (j < m->t / 2)
                    {
                        m->I[i][j] = -1 * SiCBi->M[i - m->t / 2][j];
                    }
                    else
                    {
                        m->I[i][j] = S->I[i - m->t / 2][j - m->t / 2];
                    }
                }
            }
        }

        freeHuitfi(B);
        freeHuitfi(C);
        freeHuitfi(D);
        freeHuitfi(CBi);
        freeHuitfi(CBiCt);
        freeHuitfi(S);
        freeHuitfi(SiCBi);
        freeHuitfi(BiCtSiCBi);
        freeHuitfi(BpBiCtSiCBi);
        freeHuitfi(BiCtSi);
    }
    return m;
}

mat *addMat(mat *o, double **m, double **n)
{
    for (int i = 0; i < o->t; i++)
    {
        for (int j = 0; j < o->t; j++)
        {
            o->M[i][j] = m[i][j] + n[i][j];
        }
    }
    return o;
}

mat *subMat(mat *o, double **m, double **n)
{
    for (int i = 0; i < o->t; i++)
    {
        for (int j = 0; j < o->t; j++)
        {
            o->M[i][j] = m[i][j] - n[i][j];
        }
    }
    return o;
}

void init(mat *B, double **m, int dl, int fl, int dc, int fc)
{
    creerMat(B, fl - dl);
    for (int i = dl; i < fl; ++i)
    {
        for (int j = dc; j < fc; ++j)
        {
            B->M[i - dl][j - dc] = m[i][j];
        }
    }
}

void creerFichier(const char *nomFichier, mat *m, double **M)
{
    FILE *fichier = fopen(nomFichier, "w");
    for (int i = 0; i < m->t; i++)
    {
        for (int j = 0; j < m->t; j++)
        {
            fprintf(fichier, "%lf ", M[i][j]);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
    printf("Fichier créé avec succès : %s\n", nomFichier);
}



/*mat *strassen(mat *A, double** M, double** N) {											//strassen ne marche pas et fais automatiquement une segmentation fault.
    if (A->t == 1) {
        mat *C = (mat *)malloc(sizeof(mat));
        creerMat(C, 1);
        C->M[0][0] =M[0][0] * N[0][0];
        return C;
    }

    mat* A11 = cpyDemiMat(M, 0, A->t / 2, 0, A->t / 2);
    mat* A12 = cpyDemiMat(M, 0, A->t / 2, A->t / 2, A->t);
    mat* A21 = cpyDemiMat(M, A->t / 2, A->t, 0, A->t / 2);
    mat* A22 = cpyDemiMat(M, A->t / 2, A->t, A->t / 2, A->t);

    mat* B11 = cpyDemiMat(N, 0, A->t / 2, 0, A->t / 2);
    mat* B12 = cpyDemiMat(N, 0, A->t / 2, A->t / 2, A->t);
    mat* B21 = cpyDemiMat(N, A->t / 2, A->t, 0, A->t / 2);
    mat* B22 = cpyDemiMat(N, A->t / 2, A->t, A->t / 2, A->t);
    
    mat* B12mB22;//= (mat *)malloc(sizeof(mat));
    mat* A11pA12;//= (mat *)malloc(sizeof(mat));
    mat* A21pA22;//= (mat *)malloc(sizeof(mat));
    mat* B21mB11;//= (mat *)malloc(sizeof(mat));
    mat* A11pA22;//= (mat *)malloc(sizeof(mat));
    mat* B11pB22;//= (mat *)malloc(sizeof(mat));
    mat* A12mA22;//= (mat *)malloc(sizeof(mat));
    mat* B21pB22;//= (mat *)malloc(sizeof(mat));
    mat* A11mA21;//= (mat *)malloc(sizeof(mat));
    mat* B11pB12;//= (mat *)malloc(sizeof(mat));
    
    printf("malloc");
    fflush(NULL);

    mat *M1 =  (mat *)malloc(sizeof(mat));
	M1=strassen(M1, A11->M, subMat(B12mB22, B12->M, B22->M)->M);
    mat *M2 = (mat *)malloc(sizeof(mat));
	M2=strassen(M2, addMat(A11pA12, A11->M, A12->M)->M, B22->M);
    mat *M3 =  (mat *)malloc(sizeof(mat));
	M3=strassen(M3, addMat(A21pA22, A21->M, A22->M)->M, B11->M);
    mat *M4 =  (mat *)malloc(sizeof(mat));
	M4=strassen(M4, A22->M, subMat(B21mB11, B21->M, B11->M)->M);
    mat *M5 =  (mat *)malloc(sizeof(mat));
	M5=strassen(M5, addMat(A11pA22, A11->M, A22->M)->M, addMat(B11pB22, B11->M, B22->M)->M);
    mat *M6 =  (mat *)malloc(sizeof(mat));
	M6=strassen(M6, subMat(A12mA22, A12->M, A22->M)->M, addMat(B21pB22, B21->M, B22->M)->M);
    mat *M7 =  (mat *)malloc(sizeof(mat));
	M7=strassen(M7, subMat(A11mA21, A11->M, A21->M)->M, addMat(B11pB12, B11->M, B12->M)->M);

	mat* M5pM4 = (mat *)malloc(sizeof(mat));
	mat* Ad1pM6= (mat *)malloc(sizeof(mat));
	mat* Ad2mM2= (mat *)malloc(sizeof(mat));
	mat* M1pM2 = (mat *)malloc(sizeof(mat));
	mat* M3pM4 = (mat *)malloc(sizeof(mat));
	mat* M5pM1 = (mat *)malloc(sizeof(mat));
	mat* Ad3mM3= (mat *)malloc(sizeof(mat));
	mat* Ad4mM7= (mat *)malloc(sizeof(mat));

    mat *C11 = subMat(Ad2mM2, addMat(Ad1pM6, addMat(M5pM4,M5->M, M4->M)->M, M6->M)->M, M2->M);
    mat *C12 = addMat(M1pM2, M1->M, M2->M);
    mat *C21 = addMat(M3pM4, M3->M, M4->M);
    mat *C22 = subMat(Ad4mM7, subMat(Ad3mM3, addMat(M5pM1, M5->M, M1->M)->M, M3->M)->M, M7->M);

    mat *C = (mat *)malloc(sizeof(mat));
    creerMat(C, A->t);

    for (int i = 0; i < A->t / 2; i++) {
        for (int j = 0; j < A->t / 2; j++) {
            C->M[i][j] = C11->M[i][j];
            C->M[i][j + A->t / 2] = C12->M[i][j];
            C->M[i + A->t / 2][j] = C21->M[i][j];
            C->M[i + A->t / 2][j + A->t / 2] = C22->M[i][j];
        }
    }


    freeHuitfi(A11);
    freeHuitfi(A12);
    freeHuitfi(A21);
    freeHuitfi(A22);
    freeHuitfi(B11);
    freeHuitfi(B12);
    freeHuitfi(B21);
    freeHuitfi(B22);
    freeHuitfi(M1);
    freeHuitfi(M2);
    freeHuitfi(M3);
    freeHuitfi(M4);
    freeHuitfi(M5);
    freeHuitfi(M6);
    freeHuitfi(M7);
    freeHuitfi(C11);
    freeHuitfi(C12);
    freeHuitfi(C21);
    freeHuitfi(C22);
    freeHuitfi(B12mB22);
    freeHuitfi(A11pA12);
    freeHuitfi(A21pA22);
    freeHuitfi(B21mB11);
    freeHuitfi(A11pA22);
    freeHuitfi(B11pB22);
    freeHuitfi(A12mA22);
    freeHuitfi(B21pB22);
    freeHuitfi(A11mA21);
    freeHuitfi(B11pB12);
    freeHuitfi(M5pM4 );
	freeHuitfi(Ad1pM6);
	freeHuitfi(Ad2mM2);
	freeHuitfi(M1pM2 );
	freeHuitfi(M3pM4 );
	freeHuitfi(M5pM1 );
	freeHuitfi(Ad3mM3);
	freeHuitfi(Ad4mM7);


    return C;
}*/






































