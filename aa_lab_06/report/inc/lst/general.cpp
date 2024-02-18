void logLinear(matrix_t &matrix, int task, int stage, \
    void (*func)(matrix_t &), bool needPrinting) {

    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    double resultStartTime = currentTime, resultTime = 0;

    startTime = std::chrono::system_clock::now();
    func(matrix);
    endTime = std::chrono::system_clock::now();

    resultTime = (std::chrono::duration_cast<std::chrono::nanoseconds>
            (endTime - startTime).count()) / 1e9;

    currentTime = resultStartTime + resultTime;

    if (needPrinting)
        printf("Задача: %3d, Этап: %3d, Начало: %.6f, Конец: %.6f, Длительность: %.6f\n",
            task, stage, resultStartTime, resultStartTime + resultTime, resultTime);
}

void logConway(matrix_t &matrix, int task, int stage, \
    void (*func)(matrix_t &), bool needPrinting) {
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    double resultTime = 0;

    startTime = std::chrono::system_clock::now();
    func(matrix);
    endTime = std::chrono::system_clock::now();

    resultTime = (std::chrono::duration_cast<std::chrono::nanoseconds>
            (endTime - startTime).count()) / 1e9;

    double resultStartTime;

    if (stage == 1) {
        resultStartTime = t1[task - 1];
        t1[task] = resultStartTime + resultTime;
        t2[task - 1] = t1[task];
    } else if (stage == 2) {
        resultStartTime = t2[task - 1];
        t2[task] = resultStartTime + resultTime;
        t3[task - 1] = t2[task];
    } else if (stage == 3) {
        resultStartTime = t3[task - 1];
    }

    currentTime = resultStartTime + resultTime;
    if (needPrinting)
        printf("Задача: %3d, Этап: %3d, Начало: %.6f, Конец: %.6f, Длительность: %.6f\n",
            task, stage, resultStartTime, resultStartTime + resultTime, resultTime);

}


void stage1Linear(matrix_t &matrix, int task, bool needPrinting) {
    logLinear(matrix, task, 1, convertToCSRNew, needPrinting);
}

void stage2Linear(matrix_t &matrix, int task, bool needPrinting) {
    logLinear(matrix, task, 2, calcDetermNew, needPrinting);
}


void stage3Linear(matrix_t &matrix, int task, bool needPrinting) {
    logLinear(matrix, task, 3, makeDumpNew, needPrinting);
}

void parseLinear(int count, size_t size, bool needPrinting) {
    currentTime = 0;
    std::queue<matrix_t> q1;
    std::queue<matrix_t> q2;
    std::queue<matrix_t> q3;

    queues_t queues = {.q1 = q1, .q2 = q2, .q3 = q3};

    for (int i = 0; i < count; i++) {
        matrix_t res = generateMatrix(size);

        queues.q1.push(res);
    }

    for (int i = 0; i < count; i++) {
        matrix_t matrix = queues.q1.front();
        stage1Linear(matrix, i + 1, needPrinting);
        queues.q1.pop();
        queues.q2.push(matrix);

        matrix = queues.q2.front();
        stage2Linear(matrix, i + 1, needPrinting);
        queues.q2.pop();
        queues.q3.push(matrix);

        matrix = queues.q3.front();
        stage3Linear(matrix, i + 1, needPrinting);
        queues.q3.pop();
    }
}


void stage1Parallel(std::queue<matrix_t> &q1, std::queue<matrix_t> &q2, \
    std::queue<matrix_t> &q3, bool needPrinting) {

    int task = 1;
    std::mutex m;
    while(!q1.empty()) {
        m.lock();
        matrix_t matrix = q1.front();
        m.unlock();

        logConway(matrix, task++, 1, convertToCSRNew, needPrinting);

        m.lock();
        q2.push(matrix);
        q1.pop();
        m.unlock();
    }
}


void stage2Parallel(std::queue<matrix_t> &q1, std::queue<matrix_t> &q2, \
    std::queue<matrix_t> &q3, bool needPrinting) {

    int task = 1;
    std::mutex m;
    do {
        m.lock();
        bool is_q2empty = q2.empty();
        m.unlock();

        if (!is_q2empty) {
            m.lock();
            matrix_t matrix = q2.front();
            m.unlock();

            logConway(matrix, task++, 2, calcDetermNew, needPrinting);

            m.lock();
            q3.push(matrix);
            q2.pop();
            m.unlock();
        }
    } while (!q1.empty() || !q2.empty());
}


void stage3Parallel(std::queue<matrix_t> &q1, std::queue<matrix_t> &q2, \
    std::queue<matrix_t> &q3, bool needPrinting) {

    int task = 1;
    std::mutex m;

    do {
        m.lock();
        bool is_q3empty = q3.empty();
        m.unlock();

        if (!is_q3empty) {
            m.lock();
            matrix_t matrix = q3.front();
            m.unlock();

            logConway(matrix, task++, 3, makeDumpNew, needPrinting);

            m.lock();
            q3.pop();
            m.unlock();
        }
    } while (!q1.empty() || !q2.empty() || !q3.empty());
}


void parseParallel(int count, size_t size, bool needPrinting) {
    t1.resize(count + 1);
    t2.resize(count + 1);
    t3.resize(count + 1);

    for (int i = 0; i < count + 1; i++) {
        t1[i] = 0;
        t2[i] = 0;
        t3[i] = 0;
    }

    std::queue<matrix_t> q1;
    std::queue<matrix_t> q2;
    std::queue<matrix_t> q3;

    queues_t queues = {.q1 = q1, .q2 = q2, .q3 = q3};


    for (int i = 0; i < count; i++) {
        matrix_t res = generateMatrix(size);
        q1.push(res);
    }

    std::thread threads[THREADS];

    threads[0] = std::thread(stage1Parallel, std::ref(q1), std::ref(q2), std::ref(q3), needPrinting);
    threads[1] = std::thread(stage2Parallel, std::ref(q1), std::ref(q2), std::ref(q3), needPrinting);
    threads[2] = std::thread(stage3Parallel, std::ref(q1), std::ref(q2), std::ref(q3), needPrinting);

    for (int i = 0; i < THREADS; i++)
        threads[i].join();
}