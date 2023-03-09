//
// Created by Kazeya on 2023/3/9.
//

#ifndef BUAA_ASE_WORDLIST_MAIN_H
#define BUAA_ASE_WORDLIST_MAIN_H

#pragma once
extern "C" __declspec(dllexport) int gen_chain_word(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
extern "C" __declspec(dllexport) int gen_chain_char(char* words[], int len, char* result[], char head, char tail, char banned, bool enable_loop);
extern "C" __declspec(dllexport) int gen_chains_all(char* words[], int len, char* result[]);
extern "C" __declspec(dllexport) void testDll();

#endif //BUAA_ASE_WORDLIST_MAIN_H
