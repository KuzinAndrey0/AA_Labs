import timeit
import random

REP_COUNT = 10000

def print_stats_fancy(count):
    for i in range(0, 32):
        sym = chr(i + ord('А'))
        print(sym, '-', count[i])

def analyze_file(filename):
    count = [0] * 32
    f = open(filename, "r")
    word = f.readline()
    while word:
        count[letter_to_num(word[0])] += 1
        word = f.readline()
    f.close()

    print_stats_fancy(count)


def load_file(filename, words_dicts):
    f = open(filename, "r")
    word = f.readline()
    while word:
        word = word.replace('\n', '')
        if(word[0] == 'ё'):
            word = 'е' + word[1:]
        words_dicts[word] = word
        word = f.readline()
    f.close()

def load_file_segm(filename, words_dicts):
    f = open(filename, "r")
    word = f.readline()
    while word:
        word = word.replace('\n', '')
        if(word[0] == 'ё'):
            word = 'е' + word[1:]
        words_dicts[word[0]][word] = word
        word = f.readline()
    f.close()


def letter_to_num(letter: str) -> int:
    l = letter.lower()
    if l == 'ё':
        l = 'е'
    return ord(l) - ord('а')

def num_to_letter(num):
    return chr(num + ord('а'))

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

def find_word(word_to_find, words_dicts):
    start = timeit.default_timer()
    val = "-1"
    val = words_dicts.get(word_to_find, "-1")
    stop = timeit.default_timer()

    return val, (stop - start)


def get_random_word(filename):
    f = open(filename, "r")
    rng = random.randint(1, 51300)
    for i in range(rng):
        word = f.readline()
    
    word = word.replace('\n', '')
    if(word[0] == 'ё'):
        word = 'е' + word[1:]
    f.close()

    return word
