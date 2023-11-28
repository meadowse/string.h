#include <check.h>
#include <wchar.h>
#include "s21_string.h"
#include <string.h>

char test1[20] = "Hell0 world\0";
char test2[20] = "Hell0 world\n\0";
char test3[10] = "a\n\0";
char test4[10] = " \n\0";
char test5[10] = " \0";
char test6[10] = "\n\0";
char test7[10] = "\0";

START_TEST(test_s21_memchr_1) {
    ck_assert_ptr_eq(s21_memchr(test1, 'h', 12), memchr(test1, 'h', 12));
    ck_assert_ptr_eq(s21_memchr(test2, 'l', 12), memchr(test2, 'l', 12));
    ck_assert_ptr_eq(s21_memchr(test3, '\n', 4), memchr(test3, '\n', 4));
    ck_assert_ptr_eq(s21_memchr(test4, '\n', 3), memchr(test4, '\n', 3));
    ck_assert_ptr_eq(s21_memchr(test5, ' ', 3), memchr(test5, ' ', 3));
    ck_assert_ptr_eq(s21_memchr(test6, '\n', 2), memchr(test6, '\n', 2));
    ck_assert_ptr_eq(s21_memchr(test7, ' ', 2), memchr(test7, ' ', 2));
}
END_TEST

START_TEST(test_s21_memchr_2) {
    char src1[15] = "1234567890";
    char src2[3] = {'\0', '\0', '\0'};
    void *res1, *res2;

    res1 = s21_memchr(src1, '4', 10);
    res2 = memchr(src1, '4', 10);
    ck_assert_ptr_eq(res1, res2);

    res1 = s21_memchr(src2, '\0', 2);
    res2 = memchr(src2, '\0', 2);
    ck_assert_ptr_eq(res1, res2);

    res1 = s21_memchr("", 'w', 10);
    res2 = memchr("", 'w', 10);
    ck_assert_ptr_eq(res1, res2);

    ck_assert_ptr_eq(s21_memchr("Hello world\0", 'w', 4), memchr("Hello world\0", 'w', 4));
    ck_assert_ptr_eq(s21_memchr("Hello world\n\0", 'o', 10), memchr("Hello world\n\0", 'o', 10));
    ck_assert_ptr_eq(s21_memchr("a\n\0", 'a', 2), memchr("a\n\0", 'a', 2));
    ck_assert_ptr_eq(s21_memchr(" \n\0", ' ', 2), memchr(" \n\0", ' ', 2));
    ck_assert_ptr_eq(s21_memchr(" \0", '0', 2), memchr(" \0", '0', 2));
    ck_assert_ptr_eq(s21_memchr("\n\0", '\n', 2), memchr("\n\0", '\n', 2));
    ck_assert_ptr_eq(s21_memchr("\0", 'r', 100), memchr("\0", 'r', 100));
}
END_TEST

START_TEST(test_s21_memcmp) {
    char src1[7] = "Abc";
    char dst1[7] = "ABC";
    char src2[3] = "\0";
    char dst2[3] = "\0";
    char src3[6] = "12345";
    char dst3[6] = "12345";
    char str1[] = "Hello world\0";
    char str2[] = "Hello world";
    char str3[] = "a\n\0";
    char str4[] = " \n\0";
    char str5[] = "1\0";
    char str6[] = "\n\0";
    char str7[] = "\0";

    ck_assert_int_eq(s21_memcmp(src1, dst1, 1), memcmp(src1, dst1, 1));
    ck_assert_int_eq(s21_memcmp(src2, dst2, 1), memcmp(src2, dst2, 1));
    ck_assert_int_eq(s21_memcmp(src3, dst3, 5), memcmp(src3, dst3, 5));

    ck_assert_int_eq(s21_memcmp(str1, str2, 12), memcmp(str1, str2, 12));
    ck_assert_int_eq(s21_memcmp(str3, "a\n\0", 3), memcmp(str3, "a\n\0", 3));
    ck_assert_int_eq(s21_memcmp(str4, " \n\0", 4), memcmp(str4, " \n\0", 4));
    ck_assert_int_eq(s21_memcmp(str6, str7, 1), memcmp(str6, str7, 1));
    ck_assert_int_eq(s21_memcmp(str5, "0\n", 1), memcmp(str5, "0\n", 1));
    ck_assert_int_eq(s21_memcmp(str7, "", 1), memcmp(str7, "", 1));
}
END_TEST

START_TEST(test_s21_memcpy_1) {
    char destination1[] = "Here w0 are\0";
    char result[] = "Here w0 are\0";
    ck_assert_pstr_eq(s21_memcpy(destination1, test1, 8),
                     memcpy(result, test1, 8));

    char destination2[] = "Here w0 are\n\0";
    char result2[] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_memcpy(destination2, test2, 8),
                     memcpy(result2, test2, 8));

    char destination3[] = "a\n\0";
    char result3[] = "a\n\0";
    ck_assert_pstr_eq(s21_memcpy(destination3, test3, 2),
                     memcpy(result3, test3, 2));

    char destination4[] = " \n\0";
    char result4[] = " \n\0";
    ck_assert_pstr_eq(s21_memcpy(destination4, test4, 2),
                     memcpy(result4, test4, 2));

    char destination5[] = " \0";
    char result5[] = " \0";
    ck_assert_pstr_eq(s21_memcpy(destination5, test5, 2),
                     memcpy(result5, test5, 2));

    char destination6[] = "\n\0";
    char result6[] = "\n\0";
    ck_assert_pstr_eq(s21_memcpy(destination6, test6, 2),
                     memcpy(result6, test6, 2));

    char destination7[] = "\0";
    char result7[] = "aaa\0";
    ck_assert_pstr_eq(s21_memcpy(destination7, test7, 2),
                     memcpy(result7, test7, 2));
}
END_TEST

START_TEST(test_s21_memcpy_2) {
    char src1[15] = "qwert";
    char dst1[3] = "123";
    void *res1, *res2;

    res1 = s21_memcpy(src1, dst1, 3);
    res2 = memcpy(src1, dst1, 3);
    ck_assert_pstr_eq(res1, res2);

    char dest[] = "0000";
    char src[] = "1,2,3,4,5";
    char src0[] = "1,2,3,4,5";
    char dest2[] = "1,2,3,4,5";
    char src5[] = "21212121";
    char src6[] = "\0";
    ck_assert_ptr_eq(s21_memcpy(dest, src, 4), memcpy(dest, src, 4));
    ck_assert_ptr_eq(s21_memcpy(dest, src0, 5), memcpy(dest, src0, 5));
    ck_assert_ptr_eq(s21_memcpy(dest2, src5, 8), memcpy(dest2, src5, 8));
    ck_assert_ptr_eq(s21_memcpy(dest, src6, 1), memcpy(dest, src6, 1));
}
END_TEST

START_TEST(test_s21_memmove_1) {
    char src1[15] = "qwert";
    char dst1[3] = "123";
    char dst2[11] = "1234567890";
    char dst3[3] = "123";
    void *res1, *res2;

    res1 = s21_memmove(src1, dst1, 3);
    res2 = memmove(src1, dst1, 3);
    ck_assert_pstr_eq(res1, res2);

    res1 = s21_memmove(src1, dst2, 10);
    res2 = memmove(src1, dst2, 10);
    ck_assert_pstr_eq(res1, res2);

    res1 = s21_memmove(src1, dst3, 3);
    res2 = memmove(src1, dst3, 3);
    ck_assert_pstr_eq(res1, res2);

    char* dst33 = &dst2[2];
    char* dst4;
    dst4 = dst33 + 3;
    res1 = s21_memmove(dst33, dst4, 2);
    res2 = memmove(dst33, dst4, 2);
    ck_assert_pstr_eq(res1, res2);

    char dest[] = "0000";
    char src[] = "1,2,3,4,5";
    char dest1[5] = {0};
    char src0[] = "1,2,3,4,5";
    char dest2[] = "1,2,3,4,5";
    char src5[] = "21212121";
    char src6[] = "\0";
    ck_assert_ptr_eq(s21_memmove(dest, src, 4), memmove(dest, src, 4));
    ck_assert_ptr_eq(s21_memmove(dest1, src0, 5), memmove(dest1, src0, 5));
    ck_assert_ptr_eq(s21_memmove(dest2, src5, 8), memmove(dest2, src5, 8));
    ck_assert_ptr_eq(s21_memmove(dest, src6, 1), memmove(dest, src6, 1));
}
END_TEST

START_TEST(test_s21_memmove_2) {
    char str1[30] = "teststring";
    char str2[30] = "teststring";
    ck_assert_pstr_eq(s21_memmove(str1 + 2, str1, 10),
                     memmove(str2 + 2, str2, 10));

    char destination2[] = "Here w0 are\n\0";
    char result2[] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_memmove(destination2, test2, 8),
                     memmove(result2, test2, 8));

    char destination3[] = "a\n\0";
    char result3[] = "a\n\0";
    ck_assert_pstr_eq(s21_memmove(destination3, test3, 2),
                     memmove(result3, test3, 2));

    char destination4[] = " \n\0";
    char result4[] = " \n\0";
    ck_assert_pstr_eq(s21_memmove(destination4, test4, 2),
                     memmove(result4, test4, 2));

    char destination5[] = " \0";
    char result5[] = " \0";
    ck_assert_pstr_eq(s21_memmove(destination5, test5, 2),
                     memmove(result5, test5, 2));

    char destination6[] = "\n\0";
    char result6[] = "\n\0";
    ck_assert_pstr_eq(s21_memmove(destination6, test6, 2),
                     memmove(result6, test6, 2));

    char destination7[] = "\0";
    char result7[] = "\0";
    ck_assert_pstr_eq(s21_memmove(destination7, test7, 2),
                     memmove(result7, test7, 2));
}
END_TEST

START_TEST(test_s21_memset_1) {
    char destination[] = "Here w0 are123\0";
    char origin[] = "Here w0 are123\0";
    ck_assert_pstr_eq(s21_memset(destination, '-', 4), memset(origin, '-', 4));

    char destination2[] = "Here w0 are\n\0";
    char origin2[] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_memset(destination2, '-', 4), memset(origin2, '-', 4));

    char destination3[] = "a\n\0";
    char origin3[] = "a\n\0";
    ck_assert_pstr_eq(s21_memset(destination3, '-', 2), memset(origin3, '-', 2));

    char destination4[] = " \n\0";
    char origin4[] = " \n\0";
    ck_assert_pstr_eq(s21_memset(destination4, '-', 2), memset(origin4, '-', 2));

    char destination5[] = " \0";
    char origin5[] = " \0";
    ck_assert_pstr_eq(s21_memset(destination5, '-', 1), memset(origin5, '-', 1));

    char destination6[] = "\n\0";
    char origin6[] = "\n\0";
    ck_assert_pstr_eq(s21_memset(destination6, '-', 1), memset(origin6, '-', 1));

    char origin7[] = "\0";
    char destination7[] = "\0";
    ck_assert_pstr_eq(s21_memset(destination7, '-', 1), memset(origin7, '-', 1));
}
END_TEST

START_TEST(test_s21_memset_2) {
    char src1[15] = "1234567890";
    char src2[11] = "123";
    void *res1, *res2;

    res1 = s21_memset(src1, '1', 11);
    res2 = memset(src1, '1', 11);
    ck_assert_pstr_eq(res1, res2);

    res1 = s21_memset(src2, '\0', 2);
    res2 = memset(src2, '\0', 2);
    ck_assert_pstr_eq(res1, res2);

    res1 = s21_memset(src2, 'w', 2);
    res2 = memset(src2, 'w', 2);
    ck_assert_pstr_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strcat_1) {
    char destination[40] = "Here w0 are123\0";
    char origin[40] = "Here w0 are123\0";
    ck_assert_pstr_eq(s21_strcat(destination, test1), strcat(origin, test1));

    char destination2[40] = "Here w0 are\n\0";
    char origin2[40] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_strcat(destination2, test2), strcat(origin2, test2));

    char destination3[40] = "a\n\0";
    char origin3[40] = "a\n\0";
    ck_assert_pstr_eq(s21_strcat(destination3, test3), strcat(origin3, test3));

    char destination4[40] = " \n\0";
    char origin4[40] = " \n\0";
    ck_assert_pstr_eq(s21_strcat(destination4, test4), strcat(origin4, test4));

    char destination5[40] = " \0";
    char origin5[40] = " \0";
    ck_assert_pstr_eq(s21_strcat(destination5, test5), strcat(origin5, test5));

    char destination6[40] = "\n\0";
    char origin6[40] = "\n\0";
    ck_assert_pstr_eq(s21_strcat(destination6, test6), strcat(origin6, test6));

    char origin7[40] = "\0";
    char destination7[40] = "\0";
    ck_assert_pstr_eq(s21_strcat(destination7, test7), strcat(origin7, test7));
}
END_TEST

START_TEST(test_s21_strcat_2) {
    char str10[10] = "Lol";
    char str20[4] = "Kek";
    char str30[4] = "";
    char *result, *result2;

    result = s21_strcat(str10, str20);
    result2 = strcat(str10, str20);
    ck_assert_pstr_eq(result, result2);

    result = s21_strcat(str10, str30);
    result2 = strcat(str10, str30);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strncat_1) {
    char destination[40] = "Here w0 are123\0";
    char origin[40] = "Here w0 are123\0";
    ck_assert_pstr_eq(s21_strncat(destination, test1, 4),
                     strncat(origin, test1, 4));

    char destination2[40] = "Here w0 are\n\0";
    char origin2[40] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_strncat(destination2, test2, 4),
                     strncat(origin2, test2, 4));

    char destination3[40] = "a\n\0";
    char origin3[40] = "a\n\0";
    ck_assert_pstr_eq(s21_strncat(destination3, test3, 4),
                     strncat(origin3, test3, 4));

    char destination4[40] = " \n\0";
    char origin4[40] = " \n\0";
    ck_assert_pstr_eq(s21_strncat(destination4, test4, 4),
                     strncat(origin4, test4, 4));

    char destination5[40] = " \0";
    char origin5[40] = " \0";
    ck_assert_pstr_eq(s21_strncat(destination5, test5, 4),
                     strncat(origin5, test5, 4));

    char destination6[40] = "\n\0";
    char origin6[40] = "\n\0";
    ck_assert_pstr_eq(s21_strncat(destination6, test6, 4),
                     strncat(origin6, test6, 4));

    char origin7[40] = "\0";
    char destination7[40] = "\0";
    ck_assert_pstr_eq(s21_strncat(destination7, test7, 4),
                     strncat(origin7, test7, 4));
}
END_TEST

START_TEST(test_s21_strncat_2) {
    char str0[8] = "Lol";
    char str20[4] = "Kek";
    char str10[8] = "Lol";
    char *result, *result2;

    result = s21_strncat(str0, str20, 2);
    result2 = strncat(str0, str20, 2);
    ck_assert_pstr_eq(result, result2);

    result = s21_strncat(str10, str20, 2);
    result2 = strncat(str10, str20, 2);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strchr_1) {
    char str1[7] = "School";
    char *result, *result2;
    char str2[50] = "\0";

    result = s21_strchr(str1, 111);
    result2 = strchr(str1, 111);
    ck_assert_pstr_eq(result, result2);

    result = s21_strchr(str2, 1);
    result2 = strchr(str2, 1);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strchr_2) {
    ck_assert_pstr_eq(s21_strchr(test1, 'e'), strchr(test1, 'e'));
    ck_assert_pstr_eq(s21_strchr(test2, 'e'), strchr(test2, 'e'));
    ck_assert_ptr_eq(s21_strchr(test3, 'e'), strchr(test3, 'e'));
    ck_assert_ptr_eq(s21_strchr(test4, 'e'), strchr(test4, 'e'));
    ck_assert_ptr_eq(s21_strchr(test5, 'e'), strchr(test5, 'e'));
    ck_assert_ptr_eq(s21_strchr(test6, 'e'), strchr(test6, 'e'));
    ck_assert_ptr_eq(s21_strchr(test7, 'e'), strchr(test7, 'e'));
}
END_TEST

START_TEST(test_s21_strcmp_1) {
    char str1[] = "Hello world\n\0";
    char str2[] = "Hello world\n\0";
    char str3[] = "a\n\0";
    char str4[] = " \n\0";
    char str5[] = " \0";
    char str6[] = "\n\0";
    char str7[] = "\0";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
    ck_assert_int_eq(s21_strcmp(str3, str4), strcmp(str3, str4));
    ck_assert_int_eq(s21_strcmp(str5, str6), strcmp(str5, str6));
    ck_assert_int_eq(s21_strcmp(str6, str7), strcmp(str6, str7));
    ck_assert_int_eq(s21_strcmp(str1, str7), strcmp(str1, str7));
}
END_TEST

START_TEST(test_s21_strcmp_2) {
    char str20[4] = "Kek";
    int res1, res2;

    res1 = s21_strcmp("Lol", str20);
    res2 = strcmp("Lol", str20);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strcmp_3) {
    char toCompare[] = "Hell0 man";

    ck_assert_int_eq(s21_strcmp(test1, toCompare), strcmp(test1, toCompare));
    ck_assert_int_eq(s21_strcmp(test2, toCompare), strcmp(test2, toCompare));
    ck_assert_int_eq(s21_strcmp(test3, toCompare), strcmp(test3, toCompare));
    ck_assert_int_eq(s21_strcmp(test4, toCompare), strcmp(test4, toCompare));
    ck_assert_int_eq(s21_strcmp(test5, toCompare), strcmp(test5, toCompare));
    ck_assert_int_eq(s21_strcmp(test6, toCompare), strcmp(test6, toCompare));
    ck_assert_int_eq(s21_strcmp(test7, toCompare), strcmp(test7, toCompare));
}
END_TEST

START_TEST(test_s21_strcmp_4) {
    char str1[] = "Hello world\n\0";
    char str2[] = "Hello world\n\0";
    char str3[] = "a\n\0";
    char str4[] = " \n\0";
    char str5[] = " \0";
    char str6[] = "\n\0";
    char str7[] = "\0";
    ck_assert_int_eq(s21_strncmp(str1, str2, 3), strncmp(str1, str2, 3));
    ck_assert_int_eq(s21_strncmp(str3, str4, 2), strncmp(str3, str4, 2));
    ck_assert_int_eq(s21_strncmp(str5, str6, 1), strncmp(str5, str6, 1));
    ck_assert_int_eq(s21_strncmp(str6, str7, 1), strncmp(str6, str7, 1));
    ck_assert_int_eq(s21_strncmp(str1, str7, 1), strncmp(str1, str7, 1));
}
END_TEST

START_TEST(test_s21_strncmp_1) {
    char str11[4] = "Lol";
    char str21[4] = "Kek";
    int res1, res2;

    res1 = s21_strncmp(str11, str21, 2);
    res2 = strncmp(str11, str21, 2);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strncmp_2) {
    char toCompare[] = "Hell0 man";

    ck_assert_int_eq(s21_strncmp(test1, toCompare, 6),
                     strncmp(test1, toCompare, 6));
    ck_assert_int_eq(s21_strncmp(test2, toCompare, 6),
                     strncmp(test2, toCompare, 6));
    ck_assert_int_eq(s21_strncmp(test3, toCompare, 4),
                     strncmp(test3, toCompare, 4));
    ck_assert_int_eq(s21_strncmp(test4, toCompare, 4),
                     strncmp(test4, toCompare, 4));
    ck_assert_int_eq(s21_strncmp(test5, toCompare, 3),
                     strncmp(test5, toCompare, 3));
    ck_assert_int_eq(s21_strncmp(test6, toCompare, 3),
                     strncmp(test6, toCompare, 3));
    ck_assert_int_eq(s21_strncmp(test7, toCompare, 2),
                     strncmp(test7, toCompare, 2));
}
END_TEST

START_TEST(test_s21_strcpy_1) {
    char str1[] = "Hello world\n\0";
    char str2[] = "Hello world\n\0";
    char str3[] = "a\n\0";
    char str4[] = " \n\0";
    char str5[] = " \0";
    char str6[] = "\n\0";
    char str7[] = "\0";
    ck_assert_pstr_eq(s21_strcpy(str1, str2), strcpy(str1, str2));
    ck_assert_pstr_eq(s21_strcpy(str3, str4), strcpy(str3, str4));
    ck_assert_pstr_eq(s21_strcpy(str5, str6), strcpy(str5, str6));
    ck_assert_pstr_eq(s21_strcpy(str6, str7), strcpy(str6, str7));
    ck_assert_pstr_eq(s21_strcpy(str1, str7), strcpy(str1, str7));
}
END_TEST

START_TEST(test_s21_strcpy_2) {
    char str12[4] = "Lol";
    char str22[4] = "Kek";
    char str32[4] = "";
    char str42[1] = "";
    char *result, *result2;

    result = s21_strcpy(str12, str22);
    result2 = strcpy(str12, str22);
    ck_assert_pstr_eq(result, result2);

    result = s21_strcpy(str32, str42);
    result2 = strcpy(str32, str42);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strcpy_3) {
    char destination[] = "Here w0 are\0";
    char result[] = "Here w0 are\0";
    ck_assert_pstr_eq(s21_strcpy(destination, test1), strcpy(result, test1));

    char destination2[] = "Here w0 are\n\0";
    char result2[] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_strcpy(destination2, test2), strcpy(result2, test2));

    char destination3[] = "a\n\0";
    char result3[] = "a\n\0";
    ck_assert_pstr_eq(s21_strcpy(destination3, test3), strcpy(result3, test3));

    char destination4[] = " \n\0";
    char result4[] = " \n\0";
    ck_assert_pstr_eq(s21_strcpy(destination4, test4), strcpy(result4, test4));

    char destination5[] = " \0";
    char result5[] = " \0";
    ck_assert_pstr_eq(s21_strcpy(destination5, test5), strcpy(result5, test5));

    char destination6[] = "\n\0";
    char result6[] = "\n\0";
    ck_assert_pstr_eq(s21_strcpy(destination6, test6), strcpy(result6, test6));

    char destination7[] = "\0";
    char result7[] = "\0";
    ck_assert_pstr_eq(s21_strcpy(destination7, test7), strcpy(result7, test7));
}
END_TEST

START_TEST(test_s21_strncpy_1) {
    char str1[] = "Hello world\n\0";
    char str2[] = "Hello world\n\0";
    char str3[] = "a\n\0";
    char str4[] = " \n\0";
    char str5[] = " \0";
    char str6[] = "\n\0";
    char str7[] = "\0";
    ck_assert_pstr_eq(s21_strncpy(str1, str2, 2), strncpy(str1, str2, 2));
    ck_assert_pstr_eq(s21_strncpy(str3, str4, 2), strncpy(str3, str4, 2));
    ck_assert_pstr_eq(s21_strncpy(str5, str6, 1), strncpy(str5, str6, 1));
    ck_assert_pstr_eq(s21_strncpy(str6, str7, 1), strncpy(str6, str7, 1));
    ck_assert_pstr_eq(s21_strncpy(str1, str7, 1), strncpy(str1, str7, 1));
}
END_TEST

START_TEST(test_s21_strncpy_2) {
    char destination[] = "Here w0 are\0";
    char result[] = "Here w0 are\0";
    ck_assert_pstr_eq(s21_strncpy(destination, test1, 4),
                     strncpy(result, test1, 4));

    char destination2[] = "Here w0 are\n\0";
    char result2[] = "Here w0 are\n\0";
    ck_assert_pstr_eq(s21_strncpy(destination2, test2, 8),
                     strncpy(result2, test2, 8));

    char destination3[] = "a\n\0";
    char result3[] = "a\n\0";
    ck_assert_pstr_eq(s21_strncpy(destination3, test3, 2),
                     strncpy(result3, test3, 2));

    char destination4[] = " \n\0";
    char result4[] = " \n\0";
    ck_assert_pstr_eq(s21_strncpy(destination4, test4, 2),
                     strncpy(result4, test4, 2));

    char destination5[] = " \0";
    char result5[] = " \0";
    ck_assert_pstr_eq(s21_strncpy(destination5, test5, 2),
                     strncpy(result5, test5, 2));

    char destination6[] = "\n\0";
    char result6[] = "\n\0";
    ck_assert_pstr_eq(s21_strncpy(destination6, test6, 2),
                     strncpy(result6, test6, 2));

    char destination7[] = "\0";
    char result7[] = "\0";
    ck_assert_pstr_eq(s21_strncpy(destination7, test7, 2),
                     strncpy(result7, test7, 2));
}
END_TEST

START_TEST(test_s21_strncpy_3) {
    char str12[4] = "Lol";
    char str22[4] = "Kek";
    char str32[4] = "";
    char str42[1] = "";
    char *result, *result2;

    result = s21_strncpy(str12, str22, 2);
    result2 = strncpy(str12, str22, 2);
    ck_assert_pstr_eq(result, result2);

    result = s21_strncpy(str32, str42, 1);
    result2 = strncpy(str32, str42, 1);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strcspn_1) {
    s21_size_t res1, res2;

    res1 = s21_strcspn("123456789", "9876");
    res2 = strcspn("123456789", "9876");
    ck_assert_int_eq(res1, res2);

    res1 = s21_strcspn("", "9876");
    res2 = strcspn("", "9876");
    ck_assert_int_eq(res1, res2);

    res1 = s21_strcspn("123456789", "");
    res2 = strcspn("123456789", "");
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strcspn_2) {
    char toCompare[] = "0a \n";

    ck_assert_uint_eq(s21_strcspn(test1, toCompare), strcspn(test1, toCompare));
    ck_assert_uint_eq(s21_strcspn(test2, toCompare), strcspn(test2, toCompare));
    ck_assert_uint_eq(s21_strcspn(test3, toCompare), strcspn(test3, toCompare));
    ck_assert_uint_eq(s21_strcspn(test4, toCompare), strcspn(test4, toCompare));
    ck_assert_uint_eq(s21_strcspn(test5, toCompare), strcspn(test5, toCompare));
    ck_assert_uint_eq(s21_strcspn(test6, toCompare), strcspn(test6, toCompare));
    ck_assert_uint_eq(s21_strcspn(test7, toCompare), strcspn(test7, toCompare));
}
END_TEST

START_TEST(test_s21_strerror) {
    char *src, *src1;
    src = s21_strerror(1);
    ck_assert_pstr_eq(src, strerror(1));

    src1 = s21_strerror(70);
    ck_assert_pstr_eq(src1, strerror(70));
}
END_TEST

START_TEST(test_s21_strlen_1) {
    s21_size_t res1, res2;

    res1 = s21_strlen("Lol");
    res2 = strlen("Lol");
    ck_assert_int_eq(res1, res2);

    res1 = s21_strlen("");
    res2 = strlen("");
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strlen_2) {
    ck_assert_uint_eq(s21_strlen(test1), strlen(test1));
    ck_assert_uint_eq(s21_strlen(test2), strlen(test2));
    ck_assert_uint_eq(s21_strlen(test3), strlen(test3));
    ck_assert_uint_eq(s21_strlen(test4), strlen(test4));
    ck_assert_uint_eq(s21_strlen(test5), strlen(test5));
    ck_assert_uint_eq(s21_strlen(test6), strlen(test6));
    ck_assert_uint_eq(s21_strlen(test7), strlen(test7));
}
END_TEST

START_TEST(test_s21_strpbrk_1) {
    char str1[7] = "School";
    char str2[4] = "Hole";
    char *result, *result2;

    result = s21_strpbrk(str1, str2);
    result2 = strpbrk(str1, str2);
    ck_assert_pstr_eq(result, result2);

    result = s21_strpbrk("", str2);
    result2 = strpbrk("", str2);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strpbrk_2) {
    char toCompare[] = "aeou";

    ck_assert_pstr_eq(s21_strpbrk(test1, toCompare), strpbrk(test1, toCompare));
    ck_assert_pstr_eq(s21_strpbrk(test2, toCompare), strpbrk(test2, toCompare));
    ck_assert_pstr_eq(s21_strpbrk(test3, toCompare), strpbrk(test3, toCompare));
    ck_assert_ptr_eq(s21_strpbrk(test4, toCompare), strpbrk(test4, toCompare));
    ck_assert_ptr_eq(s21_strpbrk(test5, toCompare), strpbrk(test5, toCompare));
    ck_assert_ptr_eq(s21_strpbrk(test6, toCompare), strpbrk(test6, toCompare));
    ck_assert_ptr_eq(s21_strpbrk(test7, toCompare), strpbrk(test7, toCompare));
}
END_TEST

START_TEST(test_s21_strrchr_1) {
    char str1[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    char *result, *result2;

    result = s21_strrchr(str1, 111);
    result2 = strrchr(str1, 111);
    ck_assert_pstr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strrchr_2) {
    ck_assert_pstr_eq(s21_strrchr(test1, 'o'), strrchr(test1, 'o'));
    ck_assert_pstr_eq(s21_strrchr(test2, 'l'), strrchr(test2, 'l'));
    ck_assert_pstr_eq(s21_strrchr(test3, '\n'), strrchr(test3, '\n'));
    ck_assert_pstr_eq(s21_strrchr(test4, ' '), strrchr(test4, ' '));
    ck_assert_pstr_eq(s21_strrchr(test5, ' '), strrchr(test5, ' '));
    ck_assert_pstr_eq(s21_strrchr(test6, '\0'), strrchr(test6, '\0'));
    ck_assert_ptr_eq(s21_strrchr(test7, ' '), strrchr(test7, ' '));
}
END_TEST

START_TEST(test_s21_strspn_1) {
    s21_size_t res1, res2;

    res1 = s21_strspn("123456789", "312");
    res2 = strspn("123456789", "312");
    ck_assert_int_eq(res1, res2);

    res1 = s21_strspn("", "312");
    res2 = strspn("", "312");
    ck_assert_int_eq(res1, res2);

    res1 = s21_strspn("123456789", "");
    res2 = strspn("123456789", "");
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_strspn_2) {
    char sym[] = "el";

    ck_assert_uint_eq(s21_strspn(test1, sym), strspn(test1, sym));
    ck_assert_uint_eq(s21_strspn(test2, sym), strspn(test2, sym));
    ck_assert_uint_eq(s21_strspn(test3, sym), strspn(test3, sym));
    ck_assert_uint_eq(s21_strspn(test4, sym), strspn(test4, sym));
    ck_assert_uint_eq(s21_strspn(test5, sym), strspn(test5, sym));
    ck_assert_uint_eq(s21_strspn(test6, sym), strspn(test6, sym));
    ck_assert_uint_eq(s21_strspn(test7, sym), strspn(test7, sym));
}
END_TEST

START_TEST(test_s21_strstr_1) {
    char str[] = "ro\0";
    char* str1 = "I am Groot\0";
    char* str2 = "I am Groot\n\0";
    char* str3 = "a\n\0";
    char* str4 = " \n\0";
    char* str5 = " \0";
    char* str6 = "\n\0";
    char* str7 = "\0";
    ck_assert_str_eq(s21_strstr(str1, str), strstr(str1, str));
    ck_assert_str_eq(s21_strstr(str2, str), strstr(str2, str));
    ck_assert_ptr_eq(s21_strstr(str3, str), strstr(str3, str));
    ck_assert_ptr_eq(s21_strstr(str4, str), strstr(str4, str));
    ck_assert_ptr_eq(s21_strstr(str5, str), strstr(str5, str));
    ck_assert_ptr_eq(s21_strstr(str6, str), strstr(str6, str));
    ck_assert_ptr_eq(s21_strstr(str7, str), strstr(str7, str));
}
END_TEST

START_TEST(test_s21_strstr_2) {
    char str[] = "ro\0";
    char* str1 = "I am Groot\0";
    char* str2 = "I am Groot\n\0";
    char* str3 = "a\n\0";
    char* str4 = " \n\0";
    char* str5 = " \0";
    char* str6 = "\n\0";
    char* str7 = "\0";
    ck_assert_str_eq(s21_strstr(str1, str), strstr(str1, str));
    ck_assert_str_eq(s21_strstr(str2, str), strstr(str2, str));
    ck_assert_ptr_eq(s21_strstr(str3, str), strstr(str3, str));
    ck_assert_ptr_eq(s21_strstr(str4, str), strstr(str4, str));
    ck_assert_ptr_eq(s21_strstr(str5, str), strstr(str5, str));
    ck_assert_ptr_eq(s21_strstr(str6, str), strstr(str6, str));
    ck_assert_ptr_eq(s21_strstr(str7, str), strstr(str7, str));
}
END_TEST

START_TEST(test_s21_strtok_1) {
    char str[] = "School-21";
    char *tok1 = s21_strtok(str, "-");
    char *tok2 = strtok(str, "-");
    char *tok3 = s21_strtok(str, "");
    char *tok4 = strtok(str, "");
    char *tok5 = s21_strtok(str, "oo");
    char *tok6 = strtok(str, "oo");
    char *tok7 = s21_strtok(str, "Sc");
    char *tok8 = strtok(str, "Sc");
    char *tok9 = s21_strtok(str, "21");
    char *tok10 = strtok(str, "21");

    ck_assert_pstr_eq(tok1, tok2);
    ck_assert_pstr_eq(tok3, tok4);
    ck_assert_pstr_eq(tok5, tok6);
    ck_assert_pstr_eq(tok7, tok8);
    ck_assert_pstr_eq(tok9, tok10);
}
END_TEST

START_TEST(test_s21_strtok_2) {
    char arr1[100] = "My name is Root. Hello world!", *parr1 = arr1,
         arr2[100] = "My name is Root. Hello world!", *parr2 = arr2;
    s21_strtok(parr1, " .");
    strtok(parr2, " .");
    ck_assert_str_eq(parr1, parr2);

    parr1 = s21_strtok(NULL, " .");
    parr2 = strtok(NULL, " .");
    ck_assert_str_eq(parr1, parr2);

    parr1 = s21_strtok(parr1, "x");
    parr2 = strtok(parr2, "x");
    ck_assert_str_eq(parr1, parr2);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    short h = 34;
    long l = 2353423523424;
    int r1 = sprintf(
            str1, "%-25.10d%-30.2d%10.12d%11d%.8d%7.5d%+-25.8d%+10.2ld%-11.8hd", 253,
            335, 1234, 34, 10, 25, 666, l, h);
    int r2 = s21_sprintf(
            str2, "%-25.10d%-30.2d%10.12d%11d%.8d%7.5d%+-25.8d%+10.2ld%-11.8hd", 253,
            335, 1234, 34, 10, 25, 666, l, h);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    short h = 34;
    long l = 2353423523424;
    int r1 =
            sprintf(str1, "%+50.i%-10.20i%10.i%12i%7.5i%-10.8i%+10.1li%8.25hi",
                    34567, 225, 5230, 125, 10, 5, l, h);
    int r2 =
            s21_sprintf(str2, "%+50.i%-10.20i%10.i%12i%7.5i%-10.8i%+10.1li%8.25hi",
                        34567, 225, 5230, 125, 10, 5, l, h);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    wchar_t c1 = 'T', c2 = 'Z';
    int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%8c%2c%8c%lc%-50lc", 'a',
                     'f', 'R', 'Q', 10, 'P', 'L', 20, c1, c2);
    int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%8c%2c%8c%lc%-50lc", 'a',
                         'f', 'R', 'Q', 10, 'P', 'L', 20, c1, c2);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    unsigned short h = 115;
    unsigned long l = 123325242342;
    int r1 =
            sprintf(str1, "%u %15u %-20u %10u %-15.10u %20.8u %7.5u %8.10u %-20.12lu %19hu",
                    (unsigned)4321, (unsigned)34567, (unsigned)12346, (unsigned)234542,
                     (unsigned)10, (unsigned)10, (unsigned)5, (unsigned)2432, l, h);
    int r2 = s21_sprintf(
            str2, "%u %15u %-20u %10u %-15.10u %20.8u %7.5u %8.10u %-20.12lu %19hu",
            (unsigned)4321, (unsigned)34567, (unsigned)12346, (unsigned)234542,
                     (unsigned)10, (unsigned)10, (unsigned)5, (unsigned)2432, l, h);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
    int r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.8s%7.5s%8s%15ls%15.3ls",
                     "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA",
                     "QWERTY", "AAAAABOOOOOBAAA", "ABOBAAAAA", s, s);
    int r2 =
            s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.8s%7.5s%8s%15ls%15.3ls",
                        "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA",
                        "QWERTY", "AAAAABOOOOOBAAA", "ABOBAAAAA", s, s);
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST


START_TEST(s21_sprintf_test_percent) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    ck_assert_pstr_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_arthur) {
    char c[255] = {0}, d[255] = {0}, x1 = 't';
    int n = 2100, n1 = 0, n2 = -21;
    short sh = 123, sh1 = -123;
    long int lg = 12345678912345, lg1 = -12345678912345;
    s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1, lg1);
    sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%10d %+3d %+10d %+-10d %+-10d % -10d %-10d %-10d", n,
                212121, 2121, n2, n, 21, 55, -55);
    sprintf(d, "%10d %+3d %+10d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
            2121, n2, n, 21, 55, -55);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%-10d %10d %10d %10d %2d", 21, n2, n, n, n2);
    sprintf(d, "%-10d %10d %10d %10d %2d", 21, n2, n, n, n2);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%.50d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d", 10,
            n, n2, 42, 21, n, n2, -21, x1, 21, -42);
    sprintf(d, "%.50d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
            10, n, n2, 42, 21, n, n2, -21, x1, 21, -42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX,
                SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
            USHRT_MAX, LONG_MAX, LONG_MIN);
}
END_TEST

START_TEST(s21_sprintf_test_aslan) {
    char c[255] = {0}, d[255] = {0}, x1 = 't';
    int n = 2100, n1 = 0, n2 = -21;
    short sh = 123, sh1 = -123;
    long int lg = 12345678912345, lg1 = -12345678912345;
    s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg,
                lg1, lg1);
    sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1,
            lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%10d %+3d %+10d %+-10d %+-10d % -10d %-10d %-10d", n,
                212121, 2121, n2, n, 21, 55, -55);
    sprintf(d, "%10d %+3d %+10d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
            2121, n2, n, 21, 55, -55);
    ck_assert_str_eq(c, d);
    s21_sprintf(
            c, "[%.8d] [%3.10d] [%.d] [%-+.5d] [%-+10.5d] [%.10d] [%.10d] [%2.2d] [%.d] [% d] [%.0d]", 10,
            n, n2, 42, 21, n, n2, -21, x1, 21, -42);
    sprintf(d, "[%.8d] [%3.10d] [%.d] [%-+.5d] [%-+10.5d] [%.10d] [%.10d] [%2.2d] [%.d] [% d] [%.0d]",
            10, n, n2, 42, 21, n, n2, -21, x1, 21, -42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX,
                SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
            USHRT_MAX, LONG_MAX, LONG_MIN);
}
END_TEST

char s21_str[300] = {0};
char str[300] = {0};

START_TEST(s21_sprintf_test_shahzod) {
        s21_sprintf(s21_str, "qwerty");
        sprintf(str, "qwerty");
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "qwerty %c %c %c", '$', '/', '!');
        sprintf(str, "qwerty %c %c %c", '$', '/', '!');
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "qwerty %s qwe", "qwerty");
        sprintf(str, "qwerty %s qwe", "qwerty");
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %u abc", 166);
        sprintf(str, "abc %u abc", 166);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %d abc", -166);
        sprintf(str, "abc %d abc", -166);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %3c abc", '*');
        sprintf(str, "abc %3c abc", '*');
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %-3c abc", '*');
        sprintf(str, "abc %-3c abc", '*');
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %3i abc", 5);
        sprintf(str, "abc %3i abc", 5);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %+i abc", 5);
        sprintf(str, "abc %+i abc", 5);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %+.4f abc", 166.087);
        sprintf(str, "abc %+.4f abc", 166.087);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %.5i abc", 5);
        sprintf(str, "abc %.5i abc", 5);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc % 5i abc", 5);
        sprintf(str, "abc % 5i abc", 5);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %8d", 5);
        sprintf(str, "abc %8d", 5);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %.8f", 50.897);
        sprintf(str, "abc %.8f", 50.897);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %ld", 58787878958);
        sprintf(str, "abc %ld", 58787878958);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %d", 87878958);
        sprintf(str, "abc %d", 87878958);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %hd", 87878958);
        sprintf(str, "abc %hd", 87878958);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %.f", 58787.878958);
        sprintf(str, "abc %.f", 58787.878958);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %.10f", 587.00089);
        sprintf(str, "abc %.10f", 587.00089);
        ck_assert_str_eq(s21_str, str);


        s21_sprintf(s21_str, "abc %hu", 17);
        sprintf(str, "abc %hu", 17);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %lu", (long unsigned)1712312100000);
        sprintf(str, "abc %lu", (long unsigned)1712312100000);
        ck_assert_str_eq(s21_str, str);

        s21_sprintf(s21_str, "abc %%");
        sprintf(str, "abc %%");
        ck_assert_str_eq(s21_str, str);
}
END_TEST

START_TEST(s21_sprintf_test1) {
    char str1[300] = {0};
    char str2[300] = {0};
    int r1 = sprintf(str1, "%d%s%c%i%f%u%%%s", 25, "aboba", 'a', 123, 4325.23434, 12345u, "hello my friend");
    int r2 = s21_sprintf(str2, "%d%s%c%i%f%u%%%s", 25, "aboba", 'a',
    123, 4325.23434, 12345u, "hello my friend");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
    char str1[100] = {0};
    char str2[100] = {0};
    int r1 = sprintf(str1, "%-15.20i%20u", 4567899, 43252342u);
    int r2 = s21_sprintf(str2, "%-15.20i%20u", 4567899, 43252342u);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
    char str3[50] = {0};
    char str4[100] = {0};
    int r3 = sprintf(str3, "%20.0f",  25432.34345);
    int r4 = s21_sprintf(str4, "%20.0f", 25432.34345);
    ck_assert_str_eq(str3, str4);
    ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    short h = 34;
    int r1 = sprintf(str1, "%-25.10d%-30.2d%10.12d%11d%8d%8.8d%+-25.8ld%+10.2d%-11.8hd",
                     253, 335, 1234, 34, 10, 25, 456789l, 5, h);
    int r2 = s21_sprintf(str2, "%-25.10d%-30.2d%10.12d%11d%8d%8.8d%+-25.8ld%+10.2d%-11.8hd",
                         253, 335, 1234, 34, 10, 25, 456789l, 5, h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    short h = 34;
    long l = 2353423523424;
    int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%12i%8.8i%-10.8i%+10.1li%8.25hi",
                     34567, 225, 5230, 125, 10, 66, l, h);
    int r2 = s21_sprintf(str2, "%+50.i%-10.20i%10.i%12i%8.8i%-10.8i%+10.1li%8.25hi",
                         34567, 225, 5230, 125, 10, 66, l, h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    wchar_t c1 = 'T', c2 = 'Z';
    int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%8c%2c%8c%lc%-50lc",
                     'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, c1, c2);
    int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%8c%2c%8c%lc%-50lc",
                         'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, c1, c2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    int r1 = sprintf(str1, "%+-10.5f%+10.2f%15.16f%+8.10f%8.16f%-10.8f%25.8f%25.f%+10.f%8.5f",
                     2546.4324, 3452.4325, 5678.43256, 456789.243242, 3456789123.43245, 12345.6788,
                     34.4325432, 4325678.43242, 34567.2345432, 34567.43244);
    int r2 = s21_sprintf(str2, "%+-10.5f%+10.2f%15.16f%+8.10f%8.16f%-10.8f%25.8f%25.f%+10.f%8.5f",
                         2546.4324, 3452.4325, 5678.43256, 456789.243242, 3456789123.43245, 12345.6788,
                         34.4325432, 4325678.43242, 34567.2345432, 34567.43244);
    ck_assert_int_eq(r1, r2);
    char s21_buffer3[256] = {0};
    char buffer3[256] = {0};
    s21_sprintf(s21_buffer3, "%lg %lG %#lg %le", 234243.234, 8427348.234, 123.0, 155.2);
    sprintf(buffer3, "%lg %lG %#lg %le", 234243.234, 8427348.234, 123.0, 155.2);
    ck_assert_str_eq(s21_buffer3, buffer3);
}
END_TEST

START_TEST(s21_sprintf_test_s_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
    int r1 = sprintf(str1,
                     "%s%23s%-15s%10.s%15.2s%16.8s%8.8s%8s%15ls%15.3ls",
                     "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", "QWERTY",
                     "AAAAABOOOOOBAAA", "ABOBAAAAA", s, s);
    int r2 = s21_sprintf(str2,
                         "%s%23s%-15s%10.s%15.2s%16.8s%8.8s%8s%15ls%15.3ls",
                         "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", "QWERTY",
                         "AAAAABOOOOOBAAA", "ABOBAAAAA", s, s);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent_s) {
    char str1[1000] = {0};
    char str2[1000] = {0};
    int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(c_1) {
    char c[200] = {0};
    ck_assert_int_eq(s21_sprintf(c, "%c", '0'), sprintf(c, "%c", '0'));
    ck_assert_int_eq(s21_sprintf(c, " %c ", '0'), sprintf(c, " %c ", '0'));
    ck_assert_int_eq(s21_sprintf(c, "10%c", '0'), sprintf(c, "10%c", '0'));
    ck_assert_int_eq(s21_sprintf(c, "%10c", '0'), sprintf(c, "%10c", '0'));
    ck_assert_int_eq(s21_sprintf(c, "-10%c", '0'), sprintf(c, "-10%c", '0'));
    ck_assert_int_eq(s21_sprintf(c, "%-10c", '0'), sprintf(c, "%-10c", '0'));
    ck_assert_int_eq(s21_sprintf(c, "%-10c", '0'), sprintf(c, "%-10c", '0'));
    ck_assert_int_eq(s21_sprintf(c, "%-10c*", '0'), sprintf(c, "%-10c*", '0'));
    ck_assert_int_eq(s21_sprintf(c, "%c%c%c*", '0', '1', '2'), sprintf(c, "%c%c%c*", '0', '1', '2'));
}
END_TEST

START_TEST(s_1) {
    char c[200] = {0};
    ck_assert_int_eq(s21_sprintf(c, "%s", ""), sprintf(c, "%s", ""));
    ck_assert_int_eq(s21_sprintf(c, "%s", "0"), sprintf(c, "%s", "0"));
    ck_assert_int_eq(s21_sprintf(c, "%s %s", "", ""), sprintf(c, "%s %s", "", ""));
    ck_assert_int_eq(s21_sprintf(c, "%s %s", "0", "1"), sprintf(c, "%s %s", "0", "1"));
    ck_assert_int_eq(s21_sprintf(c, " %s %s ", "0", "1"), sprintf(c, " %s %s ", "0", "1"));
    ck_assert_int_eq(s21_sprintf(c, " %s %s ", "", ""), sprintf(c, " %s %s ", "", ""));
    ck_assert_int_eq(s21_sprintf(c, " %1s %1s ", "123", "4567"),
    sprintf(c, " %1s %1s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %4s %4s ", "123", "4567"),
    sprintf(c, " %4s %4s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %-4s %4s ", "123", "4567"),
    sprintf(c, " %-4s %4s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %4s %-4s ", "123", "4567"),
    sprintf(c, " %4s %-4s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %-4s %-4s ", "123", "4567"),
    sprintf(c, " %-4s %-4s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %-4s %-4s ", "123", "4567"),
    sprintf(c, " %-4s %-4s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %10.s %1.s ", "123", "4567"),
    sprintf(c, " %10.s %1.s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %.s %2.s ", "123", "4567"),
    sprintf(c, " %.s %2.s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %.s %.s ", "123", "4567"),
    sprintf(c, " %.s %.s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %3.3s %3.3s ", "123", "4567"),
    sprintf(c, " %3.3s %3.3s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, " %4.3s %-4.3s ", "123", "4567"),
    sprintf(c, " %4.3s %-4.3s ", "123", "4567"));
    ck_assert_int_eq(s21_sprintf(c, "%.s", ""), sprintf(c, "%.s", ""));
    ck_assert_int_eq(s21_sprintf(c, "%.0s", ""), sprintf(c, "%.0s", ""));
    ck_assert_int_eq(s21_sprintf(c, "%.1s", ""), sprintf(c, "%.1s", ""));
    ck_assert_int_eq(s21_sprintf(c, " %4.2s %-4.2s ", "123", "4567"),
    sprintf(c, " %4.2s %-4.2s ", "123", "4567"));
}
END_TEST

START_TEST(u_1) {
    char c[200] = {0};
    ck_assert_int_eq(s21_sprintf(c, " %u ", 0), sprintf(c, " %u ", 0));
    ck_assert_int_eq(s21_sprintf(c, " %+i ", 0), sprintf(c, " %+i ", 0));
    ck_assert_int_eq(s21_sprintf(c, " %+f ", 0.0), sprintf(c, " %+f ", 0.0));
}
END_TEST

START_TEST(s21_sprintf_test) {
    char c[20] = {0};
    int s = -789;
    char strin[5] = {0};
    int st = '6';
    char r[100] = {0};
    char res[100] = {0};
    char st_s[10] = "qwey";
    unsigned int st_u = 1234;

    ck_assert_int_eq(s21_sprintf(c, "%d", s), sprintf(c, "%d", s));
    ck_assert_int_eq(s21_sprintf(c, "%16d", s), sprintf(c, "%16d", s));
    ck_assert_int_eq(s21_sprintf(c, "%+16d", s), sprintf(c, "%+16d", s));
    ck_assert_int_eq(s21_sprintf(c, "%-16d", s), sprintf(c, "%-16d", s));

    s = 00123;

    ck_assert_int_eq(s21_sprintf(c, "%i", s), sprintf(c, "%i", s));
    ck_assert_int_eq(s21_sprintf(c, "%16i", s), sprintf(c, "%16i", s));
    ck_assert_int_eq(s21_sprintf(c, "%+16i", s), sprintf(c, "%+16i", s));
    ck_assert_int_eq(s21_sprintf(c, "%-16i", s), sprintf(c, "%-16i", s));
    ck_assert_int_eq(s21_sprintf(c, "%016i", s), sprintf(c, "%016i", s));
    ck_assert_int_eq(s21_sprintf(c, "% 16i", s), sprintf(c, "% 16i", s));

    s = 0x123fa;

    ck_assert_int_eq(s21_sprintf(c, "%i", s), sprintf(c, "%i", s));
    ck_assert_int_eq(s21_sprintf(c, "%16i", s), sprintf(c, "%16i", s));
    ck_assert_int_eq(s21_sprintf(c, "%+16i", s), sprintf(c, "%+16i", s));
    ck_assert_int_eq(s21_sprintf(c, "%-16i", s), sprintf(c, "%-16i", s));
    ck_assert_int_eq(s21_sprintf(c, "%016i", s), sprintf(c, "%016i", s));
    ck_assert_int_eq(s21_sprintf(c, "% 16i", s), sprintf(c, "% 16i", s));

    double s1 = -78.8;
    ck_assert_int_eq(s21_sprintf(c, "%f", s1), sprintf(c, "%f", s1));
    ck_assert_int_eq(s21_sprintf(c, "%16f", s1), sprintf(c, "%16f", s1));
    ck_assert_int_eq(s21_sprintf(c, "%+16f", s1), sprintf(c, "%+16f", s1));
    ck_assert_int_eq(s21_sprintf(c, "%-16f", s1), sprintf(c, "%-16f", s1));
    ck_assert_int_eq(s21_sprintf(c, "%016f", s1), sprintf(c, "%016f", s1));
    ck_assert_int_eq(s21_sprintf(c, "% 16f", s1), sprintf(c, "% 16f", s1));

    ck_assert_int_eq(s21_sprintf(strin, "%c", st), sprintf(c, "%c", s));
    ck_assert_int_eq(s21_sprintf(strin, "%-7c", st), sprintf(c, "%-7c", s));

    ck_assert_int_eq(s21_sprintf(res, "%s", st_s), sprintf(res, "%s", st_s));

    unsigned int st_u1 = 123;
    unsigned long int st_u11 = 1234;
    unsigned short int st_u12 = 1234;
    ck_assert_int_eq(s21_sprintf(r, "%u", st_u1), sprintf(r, "%u", st_u1));
    ck_assert_int_eq(s21_sprintf(r, "%16.5u", st_u1), sprintf(r, "%16.5u", st_u1));
    ck_assert_int_eq(s21_sprintf(r, "%+16.5lu", st_u11), sprintf(r, "%-16.5lu", st_u11));
    ck_assert_int_eq(s21_sprintf(r, "%-16.5hu", st_u12), sprintf(r, "%-16.5hu", st_u12));

    ck_assert_int_eq(s21_sprintf(r, "%u", st_u), sprintf(r, "%u", st_u));
    ck_assert_int_eq(s21_sprintf(r, "%16.5u", st_u), sprintf(r, "%16.5u", st_u));
    ck_assert_int_eq(s21_sprintf(r, "%+16.5u", st_u), sprintf(r, "%-16.5u", st_u));
    ck_assert_int_eq(s21_sprintf(r, "%-16.5u", st_u), sprintf(r, "%-16.5u", st_u));


    ck_assert_int_eq(s21_sprintf(r, "%s", st_s), sprintf(r, "%s", st_s));

    ck_assert_int_eq(s21_sprintf(r, "%%"), sprintf(r, "%%"));
}
END_TEST

START_TEST(s21_sprintf_July_test_1) {
    char c_21[100] = {0};
    char c_lib[100] = {0};
    int ds = 43;
    char *stroka = "arriba";
    s21_sprintf(c_21, "Hola amigo %d como estas %s", ds, stroka);
    sprintf(c_lib, "Hola amigo %d como estas %s", ds, stroka);
    ck_assert_pstr_eq(c_21, c_lib);

    s21_sprintf(c_21, "Hola amigo %1d como estas %3s", ds, stroka);
    sprintf(c_lib, "Hola amigo %1d como estas %3s", ds, stroka);
    ck_assert_pstr_eq(c_21, c_lib);

    s21_sprintf(c_21, "Hola amigo %-12.3d como estas %-10s", ds, stroka);
    sprintf(c_lib, "Hola amigo %-12.3d como estas %-10s", ds, stroka);
    ck_assert_pstr_eq(c_21, c_lib);

    s21_sprintf(c_21, "Hola amigo %+.8d como estas %1s", ds, stroka);
    sprintf(c_lib, "Hola amigo %+.8d como estas %1s", ds, stroka);
    ck_assert_pstr_eq(c_21, c_lib);

    s21_sprintf(c_21, "Hola amigo % d como estas %s", ds, stroka);
    sprintf(c_lib, "Hola amigo % d como estas %s", ds, stroka);
    ck_assert_pstr_eq(c_21, c_lib);
}
END_TEST

START_TEST(s21_sprintf_July_test_2) {
char c_21[100] = {0};
char c[100] = {0};
char c_lib[100] = {0};
int ds = 43;
short int dsh = 33;
char* stroka = "";
wchar_t* strokaW = L"a";
s21_sprintf(c_21, "Hola amigo %d como estas %ls", ds, strokaW);
sprintf(c_lib, "Hola amigo %d como estas %ls", ds, strokaW);
ck_assert_pstr_eq(c_21, c_lib);

strokaW = L"abcd";
s21_sprintf(c_21, "Hola amigo %d como estas %ls", ds, strokaW);
sprintf(c_lib, "Hola amigo %d como estas %ls", ds, strokaW);
ck_assert_pstr_eq(c_21, c_lib);

s21_sprintf(c_21, "Hola amigo %hd. como estas %s", dsh, stroka);
sprintf(c_lib, "Hola amigo %hd. como estas %s", dsh, stroka);
ck_assert_pstr_eq(c_21, c_lib);

int d = 43;
//  1.  w>pr>count
ck_assert_int_eq(s21_sprintf(c, "%d", d), sprintf(c, "%d", d));
ck_assert_int_eq(s21_sprintf(c, "%4d", d), sprintf(c, "%4d", d));
ck_assert_int_eq(s21_sprintf(c, "%.3d", d), sprintf(c, "%.3d", d));
ck_assert_int_eq(s21_sprintf(c, "%4.3d", d), sprintf(c, "%4.3d", d));
ck_assert_int_eq(s21_sprintf(c, "%-4.3d", d), sprintf(c, "%-4.3d", d));
ck_assert_int_eq(s21_sprintf(c, "%+4.3d", d), sprintf(c, "%+4.3d", d));
ck_assert_int_eq(s21_sprintf(c, "% 4.3d", d), sprintf(c, "% 4.3d", d));  //  flag space
ck_assert_int_eq(s21_sprintf(c, "%-+4.3d", d), sprintf(c, "%-+4.3d", d));
ck_assert_int_eq(s21_sprintf(c, "%+-4.3d", d), sprintf(c, "%+-4.3d", d));
//  2.  w>(pr=count)
ck_assert_int_eq(s21_sprintf(c, "%d", d), sprintf(c, "%d", d));
ck_assert_int_eq(s21_sprintf(c, "%4d", d), sprintf(c, "%4d", d));
ck_assert_int_eq(s21_sprintf(c, "%.2d", d), sprintf(c, "%.2d", d));
ck_assert_int_eq(s21_sprintf(c, "%4.2d", d), sprintf(c, "%4.2d", d));
ck_assert_int_eq(s21_sprintf(c, "%-4.2d", d), sprintf(c, "%-4.2d", d));
ck_assert_int_eq(s21_sprintf(c, "%+4.2d", d), sprintf(c, "%+4.2d", d));
ck_assert_int_eq(s21_sprintf(c, "% 4.2d", d), sprintf(c, "% 4.2d", d));  //  flag space
ck_assert_int_eq(s21_sprintf(c, "%-+4.2d", d), sprintf(c, "%-+4.2d", d));
ck_assert_int_eq(s21_sprintf(c, "%+-4.2d", d), sprintf(c, "%+-4.2d", d));
//  3.  (w=pr)>count
ck_assert_int_eq(s21_sprintf(c, "%d", d), sprintf(c, "%d", d));
ck_assert_int_eq(s21_sprintf(c, "%4d", d), sprintf(c, "%4d", d));
ck_assert_int_eq(s21_sprintf(c, "%.4d", d), sprintf(c, "%.4d", d));
ck_assert_int_eq(s21_sprintf(c, "%4.4d", d), sprintf(c, "%4.4d", d));
ck_assert_int_eq(s21_sprintf(c, "%-4.4d", d), sprintf(c, "%-4.4d", d));
ck_assert_int_eq(s21_sprintf(c, "%+4.4d", d), sprintf(c, "%+4.4d", d));
ck_assert_int_eq(s21_sprintf(c, "% 4.4d", d), sprintf(c, "% 4.4d", d));  //  flag space
ck_assert_int_eq(s21_sprintf(c, "%-+4.4d", d), sprintf(c, "%-+4.4d", d));
ck_assert_int_eq(s21_sprintf(c, "%+-4.4d", d), sprintf(c, "%+-4.4d", d));

char* s = "55555";
long int dl = 55555;
ck_assert_int_eq(s21_sprintf(c, "%.2s", s), sprintf(c, "%.2s", s));
ck_assert_int_eq(s21_sprintf(c, "%+-4.4ld", dl), sprintf(c, "%+-4.4ld", dl));
}
END_TEST

START_TEST(s21_sprintf_test_p_f) {
    char str1[1000];
    char str2[1000];
    void *p1 = (void *)0x123456789;
    void *p2 = (void *)4325234;
    void *p3 = (void *)0x123f324b;
    void *p4 = (void *)432520;
    int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                     10, p3, p1, 10, p4);
    int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                         p2, 10, p3, p1, 10, p4);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o_f) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 253;
    unsigned long l = 4325234324242l;
    int r1 =
        sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
    int r2 = s21_sprintf(
        str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo", 12345,
        6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x_f) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 345;
    unsigned long l = 52342353242l;
    int r1 =
        sprintf(str1,
                "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                "x%#10.*x%*.5hx%10.25lx",
                235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452, 8,
                23452, 10, 34254, 3, 33334, 10, h, l);
    int r2 =
        s21_sprintf(str2,
                    "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                    "20.*x%#10.*x%*.5hx%10.25lx",
                    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                    8, 23452, 10, 34254, 3, 33334, 10, h, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_e) {
    float e1 = 0, e2 = 0;
    int r1 = 0, r2 = 0;

    r1 = sscanf("123e34", "%e", &e1);
    r2 = s21_sscanf("123e34", "%e", &e2);
    ck_assert_msg(e1 == e2, "float not equals");
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("12e34", "%e", &e1);
    r2 = s21_sscanf("12e34", "%e", &e2);
    ck_assert_msg(e1 == e2, "float not equals");
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_l) {
    int r1 = 0, r2 = 0;
    wchar_t lc1, lc2;

    r1 = sscanf("a", "%lc", &lc1);
    r2 = s21_sscanf("a", "%lc", &lc2);
    ck_assert_int_eq(lc1, lc2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("ab", "%*c%lc", &lc1);
    r2 = s21_sscanf("ab", "%*c%lc", &lc2);
    ck_assert_int_eq(lc1, lc2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_L) {
    int r1 = 0, r2 = 0;
    long double Lf1 = 0, Lf2 = 0;

    r1 = sscanf("123.45", "%Lf", &Lf1);
    r2 = s21_sscanf("123.45", "%Lf", &Lf2);
    ck_assert_msg((int)Lf1 == (int)Lf2, "floats not equals");
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_u) {
    int r1 = 0, r2 = 0;
    unsigned u1 = 0, u2 = 0;

    r1 = sscanf("", "%u", &u1);
    r2 = s21_sscanf("", "%u", &u2);
    ck_assert_int_eq(u1, u2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("-0x123", "%u", &u1);
    r2 = s21_sscanf("-0x123", "%u", &u2);
    ck_assert_int_eq(u1, u2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("123.456", "%u", &u1);
    r2 = s21_sscanf("123.456", "%u", &u2);
    ck_assert_msg(u1 == u2, "floats not equals");
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_h) {
    int r1 = 0, r2 = 0;
    unsigned short hu1 = 0, hu2 = 0;

    r1 = sscanf("12345", "%hu", &hu1);
    r2 = s21_sscanf("12345", "%hu", &hu2);
    ck_assert_int_eq(hu1, hu2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_s) {
    int r1 = 0, r2 = 0;
    char s1[100] = {0}, s2[100] = {0};

    r1 = sscanf("werty kraken", "%*s%2s", s1);
    r2 = s21_sscanf("werty kraken", "%*s%2s", s2);
    ck_assert_str_eq(s1, s2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("\nwerty kraken", "%*s%10s", s1);
    r2 = s21_sscanf("\nwerty kraken", "%*s%10s", s2);
    ck_assert_str_eq(s1, s2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_f) {
    int r1 = 0, r2 = 0;
    float f1 = 0, f2 = 0;

    r1 = sscanf("12e-3", "%f", &f1);
    r2 = s21_sscanf("12e-3", "%f", &f2);
    ck_assert_int_eq(f1, f2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("12e11", "%5f", &f1);
    r2 = s21_sscanf("12e11", "%5f", &f2);
    ck_assert_int_eq(f1, f2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("-12e-3", "%f", &f1);
    r2 = s21_sscanf("-12e-3", "%f", &f2);
    ck_assert_int_eq(f1, f2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_o) {
    int r1 = 0, r2 = 0;
    unsigned o1 = 0, o2 = 0;

    r1 = sscanf("12345678", "%3o", &o1);
    r2 = s21_sscanf("12345678", "%3o", &o2);
    ck_assert_int_eq(o1, o2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("+12345678", "%3o", &o1);
    r2 = s21_sscanf("+12345678", "%3o", &o2);
    ck_assert_int_eq(o1, o2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_x) {
    int r1 = 0, r2 = 0;
    unsigned x1 = 0, x2 = 0;

    r1 = sscanf("0x12345", "%2x", &x1);
    r2 = s21_sscanf("0x12345", "%2x", &x2);
    ck_assert_uint_eq(x1, x2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("abcdef", "%x", &x1);
    r2 = s21_sscanf("abcdef", "%x", &x2);
    ck_assert_int_eq(x1, x2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_i) {
    int r1 = 0, r2 = 0;
    short int i7, i8, i9, i10, i11, i12;
    long int i20, i21, i22, i23, i24, i25;

    // short int
    r1 = sscanf("0x9 001  777", "%hi %hi %hi", &i7, &i9, &i11);
    r2 = s21_sscanf("0x9 001  777", "%hi %hi %hi", &i8, &i10, &i12);
    ck_assert_int_eq(i7, i8); ck_assert_int_eq(i9, i10); ck_assert_int_eq(i11, i12);
    ck_assert_int_eq(r1, r2);

    // long int
    r1 = sscanf("-0x80000001 017777777777 2234234234234", "%li %li %li", &i20, &i22, &i24);
    r2 = s21_sscanf("-0x80000001 017777777777 2234234234234", "%li %li %li", &i21, &i23, &i25);
    ck_assert_int_eq(i20, i21); ck_assert_int_eq(i22, i23); ck_assert_int_eq(i24, i25);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_proc) {
    int r1 = 0, r2 = 0;
    char proc1[100] = {0}, proc2[100] = {0};

    r1 = sscanf("%123.456", "%%%9s", proc1);
    r2 = s21_sscanf("%123.456", "%%%9s", proc2);
    ck_assert_str_eq(proc1, proc2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("123.456", "%%%9s", proc1);
    r2 = s21_sscanf("123.456", "%%%9s", proc2);
    ck_assert_str_eq(proc1, proc2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_p) {
    int r1 = 0, r2 = 0;
    void *p1 = 0, *p2 = 0;

    r1 = sscanf("0x123", "%4p", &p1);
    r2 = s21_sscanf("0x123", "%4p", &p2);
    ck_assert_ptr_eq(p1, p2);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("0xz123", "%4p", &p1);
    r2 = s21_sscanf("0xz123", "%4p", &p2);
    ck_assert_ptr_eq(p1, p2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_n) {
    int r1 = 0, r2 = 0;
    short int n3 = 0, n4 = 0;
    long int n5 = 0, n6 = 0;

    r1 = sscanf("123.456", "123%hn", &n3);
    r2 = s21_sscanf("123.456", "123%hn", &n4);
    ck_assert_int_eq(n3, n4);
    ck_assert_int_eq(r1, r2);

    r1 = sscanf("123123.456", "123%ln", &n5);
    r2 = s21_sscanf("123123.456", "123%ln", &n6);
    ck_assert_int_eq(n5, n6);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_d) {
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0, res1 = 0, res2 = 0;
    short int d7 = 0, d8 = 0, d9 = 0, d10 = 0;
    long int d11 = 0, d12 = 0, d13 = 0, d14 = 0;

    //  test %d
    res1 = s21_sscanf("0123 456 789", "%d %*d %002d", &d1, &d2);
    res2 = sscanf("0123 456 789", "%d %*d %002d", &d3, &d4);
    ck_assert_int_eq(res1, res2); ck_assert_int_eq(d1, d3); ck_assert_int_eq(d2, d4);

    // short int
    res1 = s21_sscanf("12 +123", "%hd %3hd", &d7, &d9);
    res2 = sscanf("12 +123", "%hd %3hd", &d8, &d10);
    ck_assert_int_eq(d7, d8);
    ck_assert_int_eq(d9, d10);
    ck_assert_int_eq(res1, res2);

    // long int
    res1 = s21_sscanf("123456678 +1231234567", "%ld %8ld", &d11, &d13);
    res2 = sscanf("123456678 +1231234567", "%ld %8ld", &d12, &d14);
    ck_assert_int_eq(d11, d12);
    ck_assert_int_eq(d13, d14);
    ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(part_5_s21_to_upper_test) {
    char* function;
    function = s21_to_upper("Hello, 123!");
    ck_assert_pstr_eq(function, "HELLO, 123!");
    free(function);
    function = s21_to_upper("hello, 123!");
    ck_assert_pstr_eq(function, "HELLO, 123!");
    free(function);
    function = s21_to_upper("HELLO, 123!");
    ck_assert_pstr_eq(function, "HELLO, 123!");
    free(function);
    function = s21_to_upper("");
    ck_assert_pstr_eq(function, "");
    free(function);
    function = s21_to_upper(s21_NULL);
    ck_assert_pstr_eq(s21_to_upper(s21_NULL), s21_NULL);
    free(function);
    function = s21_to_upper("123!");
    ck_assert_pstr_eq(function, "123!");
    free(function);
}
END_TEST

START_TEST(test_s21_to_upper) {
    char *res = s21_to_upper("test");
    ck_assert_str_eq(res, "TEST");
    free(res);

    res = s21_to_upper(" t e s t");
    ck_assert_str_eq(res, " T E S T");
    free(res);

    res = s21_to_upper("test001");
    ck_assert_str_eq(res, "TEST001");
    free(res);

    res = s21_to_upper("!test!");
    ck_assert_str_eq(res, "!TEST!");
    free(res);

    res = s21_to_upper(" ");
    ck_assert_str_eq(res, " ");
    free(res);

    res = s21_to_upper("!*_*!");
    ck_assert_str_eq(res, "!*_*!");
    free(res);
}
END_TEST

START_TEST(toupper_test) {
    char *result = s21_to_upper("lol");
    ck_assert_pstr_eq(result, "LOL");
    free(result);
}
END_TEST

START_TEST(part_5_s21_to_lower_test) {
    char* function;
    function = s21_to_lower("Hello, 123!");
    ck_assert_pstr_eq(function, "hello, 123!");
    free(function);
    function = s21_to_lower("hello, 123!");
    ck_assert_pstr_eq(function, "hello, 123!");
    free(function);
    function = s21_to_lower("HELLO, 123!");
    ck_assert_pstr_eq(function, "hello, 123!");
    free(function);
    function = s21_to_lower("");
    ck_assert_pstr_eq(function, "");
    free(function);
    function = s21_to_lower(s21_NULL);
    ck_assert_pstr_eq(function, s21_NULL);
    free(function);
    function = s21_to_lower("123!");
    ck_assert_pstr_eq(function, "123!");
    free(function);
}
END_TEST

START_TEST(s21_to_lower_f) {
    char destination[] = "HERE W0 ARE123\0";
    char *test01 = s21_to_lower(destination);
    ck_assert_pstr_eq(test01, "here w0 are123");
    free(test01);

    char destination2[] = "HERE W0 ARE\n\0";
    char *test02 = s21_to_lower(destination2);
    ck_assert_pstr_eq(test02, "here w0 are\n");
    free(test02);

    char destination3[] = "A\n\0";
    char *test03 = s21_to_lower(destination3);
    ck_assert_pstr_eq(test03, "a\n");
    free(test03);

    char destination4[] = " \n\0";
    char *test04 = s21_to_lower(destination4);
    ck_assert_pstr_eq(test04, " \n");
    free(test04);

    char destination5[] = " \0";
    char *test05 = s21_to_lower(destination5);
    ck_assert_pstr_eq(test05, " ");
    free(test05);

    char destination6[] = "\n\0";
    char *test06 = s21_to_lower(destination6);
    ck_assert_pstr_eq(test06, "\n");
    free(test06);

    char destination7[] = "\0";
    char *test07 = s21_to_lower(destination7);
    ck_assert_pstr_eq(test07, "");
    free(test07);
}
END_TEST

START_TEST(tolower_test) {
    char *result = s21_to_lower("LOL");
    ck_assert_pstr_eq(result, "lol");
    free(result);
}
END_TEST

START_TEST(part_5_s21_insert_test) {
    char* function;
    function = s21_insert("13", "2", 1);
    ck_assert_pstr_eq(function, "123");
    free(function);
    function = s21_insert("", "2", 2);
    ck_assert_ptr_null(function);
    free(function);
    function = s21_insert("hello", "", 0);
    ck_assert_pstr_eq(function, "hello");
    free(function);
    function = s21_insert("hello", "", 2);
    ck_assert_pstr_eq(function, "hello");
    free(function);
    function = s21_insert("hello", "", 6);
    ck_assert_ptr_null(function);
    free(function);
    function = s21_insert("", "", 6);
    ck_assert_ptr_null(function);
    free(function);
    function = s21_insert(s21_NULL, "", 0);
    ck_assert_ptr_null(function);
    free(function);
    function = s21_insert("", s21_NULL, 0);
    ck_assert_ptr_null(function);
    free(function);
    function = s21_insert(" 12", s21_NULL, 0);
    ck_assert_ptr_null(function);
    free(function);
    function = s21_insert(s21_NULL, "12 ", 0);
    ck_assert_ptr_null(function);
    free(function);
}
END_TEST

START_TEST(s21_insert_f) {
    char dest[] = "Hello\0";
    char insert[] = "Man\0";
    char *test01 = s21_insert(dest, insert, 2);
    ck_assert_pstr_eq(test01, "HeManllo\0");
    free(test01);

    char dest2[] = "Hello\n\0";
    char insert2[] = "Man\n\0";
    char *test02 = s21_insert(dest2, insert2, 1);
    ck_assert_pstr_eq(test02, "HMan\nello\n\0");
    free(test02);

    char dest3[] = "a\0";
    char insert3[] = "man\0";
    char *test03 = s21_insert(dest3, insert3, 1);
    ck_assert_pstr_eq(test03, "aman");
    free(test03);

    char dest4[] = " s\0";
    char insert4[] = " s\0";
    char *test04 = s21_insert(dest4, insert4, 1);
    ck_assert_pstr_eq(test04, "  ss");
    free(test04);

    char dest5[100] = "\n\0";
    char insert5[100] = "\n\0";
    char *test05 = s21_insert(dest5, insert5, 1);
    ck_assert_pstr_eq(test05, "\n\n");
    free(test05);

    char dest6[] = " \0";
    char insert6[] = " \0";
    char *test06 = s21_insert(dest6, insert6, 1);
    ck_assert_pstr_eq(test06, "  ");
    free(test06);

    char dest7[] = "\0";
    char insert7[] = "\0";
    char *test07 = s21_insert(dest7, insert7, 1);
    ck_assert_ptr_eq(test07, s21_NULL);
}
END_TEST

START_TEST(insert_test) {
    char *str1 = "Aboba";
    char *str2 = "kek";
    char *result = s21_NULL;

    result = s21_insert(str1, str2, 2);
    ck_assert_pstr_eq(result, "Abkekoba");
    free(result);
}
END_TEST

START_TEST(part_5_s21_trim_test_1) {
    char *res = s21_trim("testc", "c");
    ck_assert_str_eq(res, "test");
    free(res);

    res = s21_trim(" test ", " ");
    ck_assert_str_eq(res, "test");
    free(res);

    res = s21_trim(" ", " ");
    ck_assert_str_eq(res, "");
    free(res);

    res = s21_trim("*te*st*", "*");
    ck_assert_str_eq(res, "te*st");
    free(res);

    res = s21_trim(" te st001", " ");
    ck_assert_str_eq(res, "te st001");
    free(res);

    res = s21_trim(" /*()", ")(/ *");
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST


START_TEST(part_5_s21_trim_test_2) {
    char* function;
    function = s21_trim(" 13331 ", " 1");
    ck_assert_pstr_eq(function, "333");
    free(function);
}
END_TEST

START_TEST(trim_test) {
    char *str1 = "aboba";
    char *str2 = "ao";
    char *str3 = "abo";
    void *result, *result1;

    result = s21_trim(str1, str2);
    ck_assert_pstr_eq(result, "bob");
    free(result);

    result = s21_trim(str1, str3);
    result1 = "";
    ck_assert_pstr_eq(result, result1);
    free(result);
}
END_TEST

START_TEST(s21_trim_f_1) {
    char dest[] = "-=Hello=-\0";
    char *test01 = s21_trim(dest, "-");
    ck_assert_pstr_eq(test01, "=Hello=\0");
    free(test01);

    char dest2[] = "-Hello\n\0";
    char *test02 = s21_trim(dest2, "-");
    ck_assert_pstr_eq(test02, "Hello\n\0");
    free(test02);

    char dest3[] = "a\0";
    char *test03 = s21_trim(dest3, "a");
    ck_assert_pstr_eq(test03, "");
    free(test03);

    char dest4[] = " \n\0";
    char *test04 = s21_trim(dest4, "\n");
    ck_assert_pstr_eq(test04, " ");
    free(test04);
}
END_TEST

START_TEST(s21_trim_f_2) {
    char *res = s21_trim("testc", "c");
    ck_assert_str_eq(res, "test");
    free(res);

    res = s21_trim(" test ", " ");
    ck_assert_str_eq(res, "test");
    free(res);

    res = s21_trim(" ", " ");
    ck_assert_str_eq(res, "");
    free(res);

    res = s21_trim("*te*st*", "*");
    ck_assert_str_eq(res, "te*st");
    free(res);

    res = s21_trim(" te st001", " ");
    ck_assert_str_eq(res, "te st001");
    free(res);

    res = s21_trim(" /*()", ")(/ *");
    ck_assert_str_eq(res, "");
    free(res);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);

    //  memchr
    TCase *tc_memchr;
    tc_memchr = tcase_create("memchr func");
    suite_add_tcase(s1, tc_memchr);
    tcase_add_test(tc_memchr, test_s21_memchr_1);

    //  memcpy
    TCase *tc_memcpy;
    tc_memcpy = tcase_create("memcpy func");
    suite_add_tcase(s1, tc_memcpy);
    tcase_add_test(tc_memcpy, test_s21_memcpy_1);

    //  memmove
    TCase *tc_memmove;
    tc_memmove = tcase_create("memmove func");
    suite_add_tcase(s1, tc_memmove);
    tcase_add_test(tc_memmove, test_s21_memmove_1);

    //  memset
    TCase *tc_memset;
    tc_memset = tcase_create("memset func");
    suite_add_tcase(s1, tc_memset);
    tcase_add_test(tc_memset, test_s21_memset_1);

    //  strcat
    TCase *tc_strcat;
    tc_strcat = tcase_create("strcat func");
    suite_add_tcase(s1, tc_strcat);
    tcase_add_test(tc_strcat, test_s21_strcat_1);

    //  strncat
    TCase *tc_strncat;
    tc_strncat = tcase_create("strncat func");
    suite_add_tcase(s1, tc_strncat);
    tcase_add_test(tc_strncat, test_s21_strncat_1);

    //  strchr
    TCase *tc_strchr;
    tc_strchr = tcase_create("strchr func");
    suite_add_tcase(s1, tc_strchr);
    tcase_add_test(tc_strchr, test_s21_strchr_2);

    //  strcmp
    TCase *tc_strcmp;
    tc_strcmp = tcase_create("strcmp func");
    suite_add_tcase(s1, tc_strcmp);
    tcase_add_test(tc_strcmp, test_s21_strcmp_3);

    //  strncmp
    TCase *tc_strncmp;
    tc_strncmp = tcase_create("strncmp func");
    suite_add_tcase(s1, tc_strncmp);
    tcase_add_test(tc_strncmp, test_s21_strncmp_2);

    //  strcpy
    TCase *tc_strcpy;
    tc_strcpy = tcase_create("strcpy func");
    suite_add_tcase(s1, tc_strcpy);
    tcase_add_test(tc_strcpy, test_s21_strcpy_3);

    //  strncpy
    TCase *tc_strncpy;
    tc_strncpy = tcase_create("strncpy func");
    suite_add_tcase(s1, tc_strncpy);
    tcase_add_test(tc_strncpy, test_s21_strncpy_2);

    //  strcspn
    TCase *tc_strcspn;
    tc_strcspn = tcase_create("strcspn func");
    suite_add_tcase(s1, tc_strcspn);
    tcase_add_test(tc_strcspn, test_s21_strcspn_2);

    //  strlen
    TCase *tc_strlen;
    tc_strlen = tcase_create("strlen func");
    suite_add_tcase(s1, tc_strlen);
    tcase_add_test(tc_strlen, test_s21_strlen_2);

    //  strpbrk
    TCase *tc_strpbrk;
    tc_strpbrk = tcase_create("strpbrk func");
    suite_add_tcase(s1, tc_strpbrk);
    tcase_add_test(tc_strpbrk, test_s21_strpbrk_2);

    //  strrchr
    TCase *tc_strrchr;
    tc_strrchr = tcase_create("strrchr func");
    suite_add_tcase(s1, tc_strrchr);
    tcase_add_test(tc_strrchr, test_s21_strrchr_2);

    //  strspn
    TCase *tc_strspn;
    tc_strspn = tcase_create("strspn func");
    suite_add_tcase(s1, tc_strspn);
    tcase_add_test(tc_strspn, test_s21_strspn_2);

    //  strstr
    TCase *tc_strstr;
    tc_strstr = tcase_create("strstr func");
    suite_add_tcase(s1, tc_strstr);
    tcase_add_test(tc_strstr, test_s21_strstr_2);

    //  strtok
    TCase *tc_strtok;
    tc_strtok = tcase_create("strtok func");
    suite_add_tcase(s1, tc_strtok);
    tcase_add_test(tc_strtok, test_s21_strtok_2);

    //  to_upper
    TCase *tc_to_upper;
    tc_to_upper = tcase_create("to_upper func");
    suite_add_tcase(s1, tc_to_upper);
    tcase_add_test(tc_to_upper, test_s21_to_upper);

    //  to_lower
    TCase *tc_to_lower;
    tc_to_lower = tcase_create("to_lower func");
    suite_add_tcase(s1, tc_to_lower);
    tcase_add_test(tc_to_lower, s21_to_lower_f);

    //  insert
    TCase *tc_insert;
    tc_insert = tcase_create("insert func");
    suite_add_tcase(s1, tc_insert);
    tcase_add_test(tc_insert, s21_insert_f);

    //  trim
    TCase *tc_trim;
    tc_trim = tcase_create("trim func");
    suite_add_tcase(s1, tc_trim);
    tcase_add_test(tc_trim, s21_trim_f_1);
    tcase_add_test(tc_trim, s21_trim_f_2);


    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_s21_strcmp_1);
    tcase_add_test(tc1_1, test_s21_strcmp_4);
    tcase_add_test(tc1_1, test_s21_strcpy_1);
    tcase_add_test(tc1_1, test_s21_strncpy_1);
    tcase_add_test(tc1_1, part_5_s21_to_upper_test);
    tcase_add_test(tc1_1, part_5_s21_to_lower_test);
    tcase_add_test(tc1_1, part_5_s21_insert_test);
    tcase_add_test(tc1_1, part_5_s21_trim_test_1);
    tcase_add_test(tc1_1, part_5_s21_trim_test_2);

    tcase_add_test(tc1_1, s21_sprintf_test);
    tcase_add_test(tc1_1, s21_sprintf_July_test_1);
    tcase_add_test(tc1_1, s21_sprintf_July_test_2);

    tcase_add_test(tc1_1, test_s21_memchr_2);
    tcase_add_test(tc1_1, test_s21_memcmp);
    tcase_add_test(tc1_1, test_s21_memcpy_2);
    tcase_add_test(tc1_1, test_s21_memmove_2);
    tcase_add_test(tc1_1, test_s21_memset_2);
    tcase_add_test(tc1_1, test_s21_strlen_1);
    tcase_add_test(tc1_1, test_s21_strcmp_2);
    tcase_add_test(tc1_1, test_s21_strncmp_1);
    tcase_add_test(tc1_1, test_s21_strcpy_2);
    tcase_add_test(tc1_1, test_s21_strncpy_3);
    tcase_add_test(tc1_1, test_s21_strcat_2);
    tcase_add_test(tc1_1, test_s21_strncat_2);
    tcase_add_test(tc1_1, test_s21_strchr_1);
    tcase_add_test(tc1_1, test_s21_strrchr_1);
    tcase_add_test(tc1_1, test_s21_strpbrk_1);
    tcase_add_test(tc1_1, test_s21_strerror);
    tcase_add_test(tc1_1, test_s21_strtok_1);
    tcase_add_test(tc1_1, test_s21_strspn_1);
    tcase_add_test(tc1_1, test_s21_strcspn_1);
    tcase_add_test(tc1_1, test_s21_strstr_1);
    tcase_add_test(tc1_1, tolower_test);
    tcase_add_test(tc1_1, toupper_test);
    tcase_add_test(tc1_1, trim_test);
    tcase_add_test(tc1_1, insert_test);

    tcase_add_test(tc1_1, s21_sprintf_test_d);
    tcase_add_test(tc1_1, s21_sprintf_test_i);
    tcase_add_test(tc1_1, s21_sprintf_test_c);
    tcase_add_test(tc1_1, s21_sprintf_test_u);
    tcase_add_test(tc1_1, s21_sprintf_test_s);
    tcase_add_test(tc1_1, s21_sprintf_test_percent);

    tcase_add_test(tc1_1, s21_sprintf_test_arthur);
    tcase_add_test(tc1_1, s21_sprintf_test_aslan);
    tcase_add_test(tc1_1, s21_sprintf_test_shahzod);
    tcase_add_test(tc1_1, s21_sprintf_test_c_s);
    tcase_add_test(tc1_1, s21_sprintf_test_d_s);
    tcase_add_test(tc1_1, s21_sprintf_test_i_s);
    tcase_add_test(tc1_1, s21_sprintf_test_f_s);
    tcase_add_test(tc1_1, s21_sprintf_test_s_s);
    tcase_add_test(tc1_1, s21_sprintf_test_percent_s);
    tcase_add_test(tc1_1, s21_sprintf_test1);
    tcase_add_test(tc1_1, s21_sprintf_test4);
    tcase_add_test(tc1_1, s21_sprintf_test_p_f);
    tcase_add_test(tc1_1, s21_sprintf_test_o_f);
    tcase_add_test(tc1_1, s21_sprintf_test_x_f);

    tcase_add_test(tc1_1, c_1);
    tcase_add_test(tc1_1, s_1);
    tcase_add_test(tc1_1, u_1);

    tcase_add_test(tc1_1, sscanf_test_e);
    tcase_add_test(tc1_1, sscanf_test_l);
    tcase_add_test(tc1_1, sscanf_test_L);
    tcase_add_test(tc1_1, sscanf_test_u);
    tcase_add_test(tc1_1, sscanf_test_h);
    tcase_add_test(tc1_1, sscanf_test_s);
    tcase_add_test(tc1_1, sscanf_test_f);
    tcase_add_test(tc1_1, sscanf_test_o);
    tcase_add_test(tc1_1, sscanf_test_x);
    tcase_add_test(tc1_1, sscanf_test_i);
    tcase_add_test(tc1_1, sscanf_test_proc);
    tcase_add_test(tc1_1, sscanf_test_p);
    tcase_add_test(tc1_1, sscanf_test_n);
    tcase_add_test(tc1_1, sscanf_test_d);

    srunner_run_all(sr, CK_ENV);
    srunner_free(sr);

    return 0;
}
