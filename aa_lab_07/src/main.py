from dict import *

REP_COUNT = 10000

def calc_time(words_dicts, filename):

    time = 0
    
    for i in range(REP_COUNT):
        word = get_random_word(filename)
        w, t = find_word(word, words_dicts)
        time += t
        if(i % 100 == 0):
            print(i)
    return time# / REP_COUNT

def calc_time_segm(words_dicts, filename):

    time = 0
    
    for i in range(REP_COUNT):
        word = get_random_word(filename)
        w, t = find_word_segm(word, words_dicts)
        time += t
        if(i % 100 == 0):
            print(i)
    return time# / REP_COUNT

words_dicts = {}
words_dicts_segm = {}
for i in range(0, 32):
    words_dicts_segm[num_to_letter(i)] = {}
    
load_file_segm("russian_nouns.txt", words_dicts_segm)
load_file("russian_nouns.txt", words_dicts)


option = -1
while True:
    print('0 - Выход')
    print()
    print('1 - Поиск и замеры по ключу')
    print('2 - Замеры в обычном словаре')
    print('3 - Замеры в сегментированном словаре')

    option = int(input())

    if(option == 1):
        word_to_find = input("Введите слово: ")
        t1 = 0
        t2 = 0
        for i in range(REP_COUNT):
            out, t = find_word(word_to_find, words_dicts)
            t1 += t
        #t1 /= REP_COUNT

        print("Найдено в обычном слваре: ", out)
        for i in range(REP_COUNT):
            out, t = find_word_segm(word_to_find, words_dicts_segm)
            t2 += t
        #t2 /= REP_COUNT

        print("Найдено в сегментированном словаре: ", out)
        print("Время в обычном словаре:", t1)
        print("Время в сегментированном словаре:", t2)

    if(option == 2):
        t = calc_time(words_dicts, "russian_nouns.txt")    
        print("Среднее время поиска в обычном словаре:", '{:f}'.format(t))

    if(option == 3):
        t = calc_time_segm(words_dicts_segm, "russian_nouns.txt")    
        print("Среднее время поиска в сегментированном словаре:", '{:f}'.format(t))        
    if(option == 0):
        break


# 0.009083
# 0.008135

# Время в обычном словаре: 0.00451335395064234
# Время в сегментированном словаре: 0.002911660993959231
    

# Время в обычном словаре: 0.0034573949524201453
# Время в сегментированном: 0.012576682090184477
