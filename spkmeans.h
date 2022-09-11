#ifndef TEST_SPKMEANS_LIB__SPKMEANS_H_
#define TEST_SPKMEANS_LIB__SPKMEANS_H_
#include "stdio.h"
typedef enum {
  WAM,
  DDG,
  LNORM,
  JACOBI,
  FIT
} Goal;
typedef struct normalized_spectral_clustering {
  /**
   * n: number of data data_points
   * d: data point dimension
   * k: number of required clusters
   */

  double *matrix, *ddg, *inversed_sqrt_ddg, *wam, *l_norm,
      *eigen_vectors, *eigen_values;
  int n, d, i_pivot, j_pivot;
  double s, c, epsilon;
  Goal goal;
} Nsc;

/* standalone client */
void InvalidInput();
void GeneralError();
void PrintMatrix(const double *matrix, int rows, int d);
void AllocateMatrix(double **matrix, int n, int d);
void FreeMatrix(double **matrix);
void ChooseGoal(Nsc *nsc);

/* the spectral clustering API (library functions) */

/* Calculate and output the Weighted Adjacency Matrix as described in 1.1.1. */
void CalculateWeightedAdjacencyMatrix(Nsc *nsc);
/* Calculate and output the Diagonal Degree Matrix as described in 1.1.2. */
void CalculateDiagonalDegreeMatrix(Nsc *nsc);
/* Calculate the Inversed Square root of the Diagonal Degree Matrix*/
void InversedSqrtDiagonalDegreeMatrix(Nsc *nsc);
/* Calculate and output the laplacian matrix */
void CalculateNormalizedGraphLaplacian(Nsc *nsc);
/* Calculate and output the eigenvalues and eighen vectors of a given symetric
 * matrix based on Jacobi itrative method */
void CalculateJacobi(Nsc *nsc);

/* API helper functions */
/* A constructor for Nsc objects */
void ConstructNsc(Nsc *nsc, double *data_points, int n, int d, Goal
goal);
/* A destructor for Nsc objects */
void DestructNsc(Nsc *nsc);
/* Calculat the input dimentions */
void CalculateNandD(const char file_name[], int *n, int *d);
/* Initialize an array with the data points */
void BuildDataPointsMatrix(const char file_name[],
                           double *data_points);
/* */
void CalculateRotationMatrix(const double a[], double p[], int n, Nsc *nsc);
void RunJacobiCalculations(double a[], double a_tag[], double p[], double
v[], int n, Nsc *nsc);
void FindPivot(const double a[], int n,
               double *pivot, int *i_pivot, int *j_pivot);
int Sign(double theta);
double Off(double a[], int n);
void CopyMatrix(double a[], const double b[], int n, int d);
double CalculateWeight(int i, int j, Nsc *nsc);
void CalculateAPrimeEfficient(const double a[], double a_tag[], Nsc *nsc);
int FindK(Nsc *nsc, int k);
void CalculateUMatrix(Nsc *nsc, double *u, int k);
void CalculateTMatrix(double *u, double *t, int n, int k);

/* Math helper functions */
double CalculateEuclideanDistance(double vector_1[], double vector_2[], int d);
void SubTwoMatrices(const double matrix_1[],
                    const double matrix_2[],
                    double sub[],
                    int n);
void MultiplyTwoMatrices(const double matrix_1[],
                         const double matrix_2[],
                         double product[],
                         int n);
void IdentityMatrix(double identity[], int n);
int CheckDiagonal(const double a[], int n);
int IndexOfMinValue(const double *values, int n);
int IndexOfMaxValue(const double *values, int n);
double FindMax(const double *values, int n);
double FindMin(const double *values, int n);
#endif