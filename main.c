#include <string.h>
#include "spkmeans.h"
#include "stdlib.h"

int main(int argc, char **argv) {
  /* declarations */
  double *data_points;
  int n, d;
  Goal user_goal; /* Goal is an enum. see header for more info. */
  Nsc nsc; /* Nsc is a struct representing
 * a data structure to support all the possible goals. */

  /* argument processing and validation */
  if (argc != 3) {
    InvalidInput();
    exit(1);
  }
  if (!strcmp(argv[1], "wam")) {
    user_goal = WAM;
  } else if (!strcmp(argv[1], "ddg")) {
    user_goal = DDG;
  } else if (!strcmp(argv[1], "lnorm")) {
    user_goal = LNORM;
  } else if (!strcmp(argv[1], "jacobi")) {
    user_goal = JACOBI;
  } else {
    InvalidInput();
    exit(1);
  }
  /* Parsing the input file and initialize a Nsc data structure */

  CalculateNandD(argv[2], &n, &d);
  AllocateMatrix(&data_points, n, d);
  BuildDataPointsMatrix(argv[2],data_points, n,d);
  ConstructNsc(&nsc,data_points, n, d, user_goal);
  /* run the required calculation based on the given goal */
  ChooseGoal(&nsc);
  /* Used memory de-allocation */
  FreeMatrix(&data_points);
  DestructNsc(&nsc);
  return 0;
}
