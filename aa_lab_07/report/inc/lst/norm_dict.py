def find_word(word_to_find, words_dicts):
    start = timeit.default_timer()
    val = "-1"
    val = words_dicts.get(word_to_find, "-1")
    stop = timeit.default_timer()

    return val, (stop - start)