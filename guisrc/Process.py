from ctypes import *

from WarningView import WarningView

dll = WinDLL("../bin/core.dll")


# dll = WinDLL("./2.dll")

# int gen_chains_all(char* words[], int len, char* result[]);
def gen_chains_all(words):
    length = len(words)
    words_ptr = (c_char_p * length)()
    for i in range(length):
        words_ptr[i] = words[i].encode('utf-8')
    c_len = c_int(length)
    c_rst_ptr = (c_char_p * 20005)()
    cnt = dll.gen_chains_all(words_ptr, c_len, c_rst_ptr)
    # print(c_rst_ptr[0])
    if cnt > 20000:
        rst = []
        WarningView("结果过长，请检查数据")
    elif cnt >= 0:
        rst = [str(cnt).encode('utf-8')]
        for i in range(1, cnt + 1):
            rst.append(c_rst_ptr[i - 1])
    else:
        rst = []
        WarningView("存在单词环，请检查数据或允许单词环")
    return rst


# int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
def gen_chain_word(words, head, tail, banned, enable_loop):
    length = len(words)
    words_ptr = (c_char_p * length)()
    for i in range(length):
        words_ptr[i] = words[i].encode('utf-8')
    c_len = c_int(length)
    c_rst_ptr = (c_char_p * 20005)()
    c_head = c_char(head.encode('utf-8'))
    c_tail = c_char(tail.encode('utf-8'))
    c_banned = c_char(banned.encode('utf-8'))
    c_loop = c_bool(enable_loop)
    cnt = dll.gen_chain_word(words_ptr, c_len, c_rst_ptr, c_head, c_tail, c_banned, c_loop)
    if cnt > 20000:
        rst = []
        WarningView("结果过长，请检查数据")
    elif cnt >= 0:
        rst = []
        for i in range(1, cnt + 1):
            rst.append(c_rst_ptr[i - 1])
    else:
        rst = []
        WarningView("存在单词环，请检查数据或允许单词环")
    return rst


# int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
def gen_chain_char(words, head, tail, banned, enable_loop):
    length = len(words)
    words_ptr = (c_char_p * length)()
    for i in range(length):
        words_ptr[i] = words[i].encode('utf-8')
    c_len = c_int(length)
    c_rst_ptr = (c_char_p * 20005)()
    c_head = c_char(head.encode('utf-8'))
    c_tail = c_char(tail.encode('utf-8'))
    c_banned = c_char(banned.encode('utf-8'))
    c_loop = c_bool(enable_loop)
    cnt = dll.gen_chain_char(words_ptr, c_len, c_rst_ptr, c_head, c_tail, c_banned, c_loop)
    if cnt > 20000:
        rst = []
        WarningView("结果过长，请检查数据")
    elif cnt >= 0:
        rst = []
        for i in range(1, cnt + 1):
            rst.append(c_rst_ptr[i - 1])
    else:
        rst = []
        WarningView("存在单词环，请检查数据或允许单词环")
    return rst


def test():
    rst = (c_char_p * 10)()
    dll.testStr(rst)
    print(rst[1])


if __name__ == '__main__':
    # rst = gen_chains_all(["woo", "oom", "moon", "noox"])
    r = gen_chain_char(["abb", "cdd", "efff", "eff", "ghh"], '\0', '\0', '\0', False)
    # rst = gen_chain_char(["Algebra","Pseudopseudohypoparathyroidism","Apple","Zoo","Elephant","Under","Fox","Dog",
    # "Moon","Leaf","Trick"],'\0','t','\0',False)
    print(r)
    # test()
