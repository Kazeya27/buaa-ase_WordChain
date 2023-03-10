from ctypes import *

dll = WinDLL("./core.dll")


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
    if cnt >= 0:
        rst = [0 for _ in range(cnt+1)]
        rst[0] = str(cnt).encode('utf-8')
        for i in range(1, cnt+1):
            rst[i] = c_rst_ptr[i-1]
    else:
        rst = []
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
    cnt = dll.gen_chain_word(words_ptr,c_len,c_rst_ptr,c_head,c_tail,c_banned,c_loop)
    if cnt >= 0:
        rst = [0 for _ in range(cnt)]
        for i in range(cnt):
            rst[i] = c_rst_ptr[i]
    else:
        rst = []
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
    cnt = dll.gen_chain_char(words_ptr,c_len,c_rst_ptr,c_head,c_tail,c_banned,c_loop)
    if cnt >= 0:
        rst = [0 for _ in range(cnt)]
        for i in range(cnt):
            rst[i] = c_rst_ptr[i]
    else:
        rst = []
    return rst


def test():
    rst = (c_char_p * 10)()
    dll.testStr(rst)
    print(rst[1])


if __name__ == '__main__':
    rst = gen_chain_word(["woo", "oom", "moon", "noox"],'w','0','0',False)
    print(rst)
    # test()
