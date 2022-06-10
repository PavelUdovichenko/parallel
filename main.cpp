#include <stdio.h>
#include <omp.h>
#include <mpi.h>
#include "Tree.h"
#include "Utils.h"
#include <sysinfoapi.h>
#include <sys/time.h>

using namespace std;

double startTime, endTime;
const int level = 2;

void defaultSum(tnode* tree) {
// openmp version
    struct timeval start, end;
    gettimeofday(&start, NULL);
    long sum = getSumOfAllChilds(tree);
    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("[ Default ] Sum: % llu \n", sum);
    printf("[ Default ] Time : %lf\n", time_taken);

}

void pthreadSum(tnode* tree ) {

    int threads = 7;
    pthreadArg arg;
    arg.tree = tree;
    arg.threadCount = threads;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    getSumOfAllChilds_Pthread((void *) &arg);
    gettimeofday(&end, NULL);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e6;
    time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
    printf("[ Pthread ] Sum: % llu \n", arg.tree->sum);
    printf("[ Pthread ] Time : %lf\n", time_taken);
}


int main(int argc, char* argv []) {
    int rank, numprocs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    tnode *tree = makeRandomTree();
    getSumOfAllChilds_MPI(tree, level, rank, numprocs);
    if (rank == 0) {
        defaultSum(tree);
        pthreadSum(tree);
    }
    MPI_Finalize();
    return 0;
}
