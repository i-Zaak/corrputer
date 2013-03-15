#include <stdlib.h>
#include <iostream>
#include <fftw3.h>

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "FFTtest test 1" << std::endl;
    
    int N;
    fftw_complex *in, *out;
    fftw_plan my_plan;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*N);
    my_plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(my_plan);
    fftw_destroy_plan(my_plan);
    fftw_free(in);
    fftw_free(out);
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% FFTtest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (FFTtest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (FFTtest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

