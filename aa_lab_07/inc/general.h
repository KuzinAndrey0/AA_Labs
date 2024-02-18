#pragma once

#include <iostream>
#include <iomanip>

#define MODE_INTERACTIVE 0
#define MODE_CALC 1

#define MODE MODE_INTERACTIVE

#include "../inc/general.h"
#include "../inc/csr_matrix.h"

#include <random>
#include <vector>
#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <ctime>
#include <mutex>

#define THREADS 3
#define STEP_SIZE 1
#define STEP_COUNT 5

struct queues_s {
    std::queue<matrix_t> q1;
    std::queue<matrix_t> q2;
    std::queue<matrix_t> q3;
};

using queues_t = struct queues_s;


void logLinear(matrix_t &matrix, int task, int stage, \
    void (*func)(matrix_t &), bool needPrinting);

void logConway(matrix_t &matrix, int task, int stage, \
    void (*func)(matrix_t &), bool needPrinting);


void stage1Linear(matrix_t &matrix, int task, bool needPrinting);

void stage2Linear(matrix_t &matrix, int task, bool needPrinting);

void stage3Linear(matrix_t &matrix, int task, bool needPrinting);

void parseLinear(int count, size_t size, bool needPrinting);

void stage1Parallel(std::queue<matrix_t> &q1, std::queue<matrix_t> &q2, \
    std::queue<matrix_t> &q3, bool needPrinting);

void stage2Parallel(std::queue<matrix_t> &q1, std::queue<matrix_t> &q2, \
    std::queue<matrix_t> &q3, bool needPrinting);


void stage3Parallel(std::queue<matrix_t> &q1, std::queue<matrix_t> &q2, \
    std::queue<matrix_t> &q3, bool needPrinting);

void parseParallel(int count, size_t size, bool needPrinting);

void timeMessage(void);