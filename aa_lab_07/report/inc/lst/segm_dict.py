def find_word_segm(word_to_find, words_dicts):
    segm = words_dicts.get(word_to_find[0].lower())
    val = "-1"
    if(segm != None):
        start = timeit.default_timer()
        val = segm.get(word_to_find, "-1")
        stop = timeit.default_timer()
    else:
        stop, start = 0, 0
    

    return val, (stop - start)
