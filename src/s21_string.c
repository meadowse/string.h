#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *t = s21_NULL;
    if (str) {
        const char *info = (const char *)str;
        for (s21_size_t i = 0; i < n && t == s21_NULL; i++) {
            if (info[i] == c)
                t = (void *) &info[i];
        }
    }
    return t;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    unsigned char *arr1;
    unsigned char *arr2;
    s21_size_t i;
    i = 0;
    arr1 = (unsigned char *)str1;
    arr2 = (unsigned char *)str2;
    while (i < n) {
        if (arr1[i] != arr2[i]) {
            return (arr1[i] - arr2[i]);
        }
        i++;
    }
    return (0);
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
    for (int i = 0; i < (int)n; ++i)
        *((char*)dest + i) = *((char*)src + i);
    return (char*)dest;
}

void* s21_memmove(void* dest, const void* src, s21_size_t n) {
    char destcpy[1000];
    for (int i = 0; i < (int)n; ++i)
        destcpy[i] = *((char*)src + i);
    for (int i = 0; i < (int)n; ++i)
        *((char*)dest + i) = destcpy[i];
    return (char*)dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char *destcpy;
    destcpy = (char *)str;
    while (n > 0) {
        *destcpy = (char)c;
        destcpy++;
        n--;
    }
    return (str);
}

char *s21_strcat(char *dest, const char *src) {
    int i;
    int length;
    i = 0;
    length = 0;
    while (dest[i] != '\0') {
        length++;
        i++;
    }
    i = 0;
    while (src[i] != '\0') {
        dest[length + i] = src[i];
        i++;
    }
    dest[length + i] = '\0';
    return (dest);
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    if (n != 0) {
        int i = 0;
        char *d = dest;
        const char *s = src;
        while (*d != '\0')
            d++;
        do {
            if ((*d = *(s+i)) == '\0')
                break;
            i++;
               d++;
        } while (--n);
        *d = 0;
    }
    return (dest);
}

char *s21_strchr(const char *str, int c) {
     while (*str) {
         if (*str == (char)c)
             return ((char *)str);
         str++;
     }
     if ((char)c == '\0' && *str == (char)c)
         return ((char *)str);
     return (s21_NULL);
}

int s21_strcmp(const char *str1, const char *str2) {
     for ( ; *str1 && *str1 == *str2; str1++, str2++) {
     }
     return (*str1 - *str2);
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    const char* end = str1+n;
        int result = 0;
    for ( ; result == 0 && str1 != end && (*str1 || *str2); result = *(str1++)-*(str2++)) {
    }
        return result;
}

char *s21_strcpy(char *dest, const char *src) {
    char *r = dest;
    while (*src) {
        *(dest++) = *(src++);
    }
    *dest = '\0';
    return r;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char* ret = dest;
    while (n--) {
        if (*src != '\0') {
            *dest++ = *src++;
        } else {
            *dest++ = '\0';
        }
    }
    return ret;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
     int len1 = s21_strlen(str1);
     int len2 = s21_strlen(str2);
     int i;
     for (i = 0; i < len1; i++)
         for (int j = 0; j < len2; j++)
             if (str1[i] == str2[j]) return i;
     return i;
}

char* s21_strerror(int errnum) {
    char* err[] = ERROR;
    static char resnum[70];
    int max = 133;
    if (*err[0] == 'U')
        max = 107;
    if (errnum > 0 && errnum <= max) {
        s21_strcpy(resnum, err[errnum]);
    } else {
        char num[10] = {0};
        if (errnum < 0) {
            num[0] = '-';
            errnum *= -1;
        }
        s21_strcpy(resnum, "Unknown error: ");
        int i;
        for (i = 8; errnum != 0; errnum /= 10, i--)
            num[i] = errnum % 10 + '0';
        if (num[0] == '-') {
            resnum[15] = '-';
            resnum[16] = '\0';
        }
        s21_strcat(resnum, num + i + 1);
    }
    return resnum;
}

s21_size_t s21_strlen(const char *str) {
    int count = 0;
    while (*str++ != '\0')
        count++;
    return (count);
}

char* s21_strpbrk(const char* str1, const char* str2) {
    int length1 = s21_strlen(str1);
    int length2 = s21_strlen(str2);
    char* index = s21_NULL;
    for (int i = 0; i < length1; i++) {
        if (index != s21_NULL)
            break;
        for (int j = 0; j < length2; j++) {
            if (*(str2 + j) == *(str1 + i))
                index = ((char*)str1 + i);
        }
    }
    return index;
}

char *s21_strrchr(const char *str, int c) {
    s21_size_t i;
    char *temp;
    temp = s21_NULL;
    i = s21_strlen(str);
    if ((char)c == '\0' && str[i] == (char)c)
        return ((char *)str + i);
    while (*str) {
         if (*str == (char)c) {
           temp = (char *)str;
        }
        str++;
    }
    return (temp);
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t i = 0;
    while (str1[i]) {
        if (!s21_strchr(str2, str1[i]))
            break;
        i++;
    }
    return (i);
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *pointer = s21_NULL;
    int needleLen;
    char *hayStack = (char *)haystack;
    needleLen = s21_strlen(needle) - 1;
    for (int i = 0; hayStack[i] != '\0' && pointer == s21_NULL; i++) {
        int flag, j;
        j = 0;
        flag = 1;
        while ((j <= needleLen) && flag) {
            flag = hayStack[i + j] == needle[j];
            j++;
        }
        if (flag && (j > needleLen)) {
            pointer = &(hayStack[i]);
        }
    }
    return pointer;
}

char *s21_strtok(char *str, const char *delim) {
    static char *last = 0;
    char *st = s21_NULL;
    if (str) {
        last = str;
    }
    if (last != 0 && *last != 0) {
        char * c = last;
        while (s21_strchr(delim, *c)) {
            ++c;
        }
        if (*c != 0) {
            st = c;
            while (*c && (s21_strchr(delim, *c) == 0)) {
                ++c;
            }
            if (*c == 0) {
                last = c;
            } else {
                *c = 0;
                last = c + 1;
            }
        }
    }
    return st;
}

void *s21_to_upper(const char *str) {
    char* string;
    if (str != s21_NULL) {
        int lenStr = s21_strlen(str) + 1;
        int i = 0;
        string = (char*)calloc(lenStr, sizeof(char));
        while (i < lenStr) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                string[i] = str[i] - 32;
            } else {
                string[i] = str[i];
            }
            ++i;
        }
    } else {
        string = s21_NULL;
    }
    return string;
}

void* s21_to_lower(const char* str) {
    char* string;
    if (str != s21_NULL) {
        int lenStr = s21_strlen(str) + 1;
        int i = 0;
            string = (char*)calloc(lenStr, sizeof(char));
            while (i < lenStr) {
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    string[i] = str[i] + 32;
                } else {
                    string[i] = str[i];
                }
                ++i;
            }
    } else {
        string = s21_NULL;
    }
    return string;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *new_str = NULL;
    if (src && str && s21_strlen(src) >= start_index) {
        new_str = (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) *
                                 sizeof(char));
        if (new_str) {
            s21_strncpy(new_str, src, start_index);
            *(new_str + start_index) = '\0';
            s21_strcat(new_str, str);
            s21_strcat(new_str, src + start_index);
        }
    }
    return (void *)new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *new_str = s21_NULL;
    if (src && trim_chars) {
        char *ptr_str = (char *)src;
        char *end_str = (char *)src + s21_strlen(src);
        for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++) {
        }
        for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
             end_str--) {
        }
        new_str = (char *)malloc((end_str - ptr_str + 1) * sizeof(char));
        if (new_str) {
            s21_strncpy(new_str, ptr_str, end_str - ptr_str);
            *(new_str + (end_str - ptr_str)) = '\0';
        }
    }
    return (void *)new_str;
}

s21_size_t s21_trim_strspn_reverse(const char *str1, const char *str2) {
    s21_size_t str1len = s21_strlen(str1);
    s21_size_t str2len = s21_strlen(str2);
    int is_continue = 0;
    int res = 0;

    for (int i = (int) str1len - 1; i > -1 && is_continue == 0; i--) {
        int inner_res = 0;

        for (s21_size_t j = 0; j < str2len && inner_res == 0; j++) {
            if (str1[i] == str2[j]) {
                inner_res++;
            }
        }

        if (inner_res == 0) {
            is_continue++;
            res--;
        }

        res++;
    }

    return res;
}

// BEGIN s21_sprintf
int s21_sprintf(char *str, const char *format, ...) {
    va_list argList;
    va_start(argList, format);
    s21_size_t i = 0, flag = 0, error = 0;
    char *str_start = str;
    str = s21_strcpy(str, "");
    while (*format && error == 0) {
        FORMAT FFormat = {};
        FFormat.width = FFormat.tolerance = -1;
        FFormat.flag_error = FFormat.flag_sharp = FFormat.flag_zero = FFormat.flag_minus =
                FFormat.flag_space = FFormat.flag_plus = 0;
        if (*format == '%') {
            flag = 1;
            format++;
        } else {
            str[i++] = *(format++);
            str[i] = '\0';
        }

        if (flag == 1 && is_flag(*format))
            while (is_flag(*format))
                s21_set_flag(&FFormat, format++);

        if (flag == 1 && (is_digit(*format) || *format == '*'))
            format = s21_str_to_int(format, &FFormat.width, &argList);

        if (flag == 1 && *format == '.') {
            FFormat.tolerance = 0;
            format = s21_str_to_int(++format, &FFormat.tolerance, &argList);
        }

        if (flag == 1 && is_len(*format))
            FFormat.len = *(format++);

        if (flag == 1 && is_spec(*format))
            FFormat.spec = *(format++);

        if (flag == 1) {
            str = s21_format_param_to_str(str, &i, &FFormat, &argList);
            error = FFormat.flag_error;
        }
        flag = 0;
    }
    va_end(argList);
    if (error != 0) *str_start = '\0';
    return error == 0 ? (int) s21_strlen(str) : -1;
}

void s21_set_flag(FORMAT *FFormat, const char *format) {
    switch (*format) {
        case '-' : FFormat->flag_minus = 1; break;
        case '+' : FFormat->flag_plus = 1; break;
        case ' ' : FFormat->flag_space = 1; break;
        case '#' : FFormat->flag_sharp = 1; break;
        case '0' : FFormat->flag_zero = 1; break;
    }
}

char *s21_format_param_to_str(char *str, s21_size_t *str_len, FORMAT *FFormat, va_list *argList) {
    char *temp_str = s21_NULL;
    temp_str = calloc(1000 + FFormat->width + 2, sizeof (char));
    if (temp_str != s21_NULL) {
        switch (FFormat->spec) {
            case 'd' :
            case 'i' : s21_string_of_d(temp_str, argList, FFormat); break;
            case 'o' : s21_string_of_o(temp_str, argList, FFormat); break;
            case 'u' : s21_string_of_u(temp_str, argList, FFormat); break;
            case 'x' :
            case 'X' : s21_string_of_xX(temp_str, argList, FFormat); break;
            case 'e' :
            case 'E' : s21_string_of_eE(temp_str, argList, FFormat); break;
            case 'f' : s21_string_of_f(temp_str, argList, FFormat); break;
            case 'g' :
            case 'G' : s21_string_of_gG(temp_str, argList, FFormat); break;
            case 'c' : s21_string_of_c(temp_str, argList, FFormat); break;
            case 's' : s21_string_of_s(temp_str, argList, FFormat); break;
            case 'p' : s21_string_of_p(temp_str, argList, FFormat); break;
            case 'n' : s21_string_of_n(str_len, argList); break;
            case '%' : s21_string_of_perc(temp_str, FFormat); break;
        }
        s21_strcat(str, temp_str);
        free(temp_str);
        *str_len = s21_strlen(str);
    }
    return str;
}

void s21_string_of_n(s21_size_t const *str_len, va_list *argList) {
    int *p = va_arg(*argList, int*);
    *p = (int) *str_len;
}

char *s21_string_of_perc(char *str, FORMAT *FFormat) {
    FFormat->tolerance = 0;
    s21_strcat(str, "%");
    s21_ll_tolerance(str, FFormat);
    s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_p(char *str, va_list *argList, FORMAT *FFormat) {
    int width = FFormat->width < 15 ? 15 : FFormat->width;
    char *str_start = s21_NULL;
        str_start = str;
        int *p = va_arg(*argList, int*);
        char buf[4] = "x0";
        if (p == s21_NULL) {
            s21_strcpy(buf, "0x0");
        }

        for (int *j = p, k = 0; j && k < width; j = (void *) (((s21_size_t) j) >> 4), k++) {
            unsigned int dig = ((s21_size_t) j) % 0x10;
            if (dig < 10 && FFormat->spec == 'p')
                *(str_start++) = (char) ('0' + dig);
            else
                *(str_start++) = (char) ('a' + (dig - 10));
        }
        *str_start = '\0';
        s21_strcat(str, buf);
        s21_reverse_str(str);
        s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_f(char *str, va_list *argList, FORMAT *FFormat) {
    long double ld_number;
    double d_number;
    double f_number;

    switch (FFormat->len) {
        case 'l' : d_number = (double) va_arg(*argList, double);
            s21_lf_to_str(str, d_number, FFormat);
            break;
        case 'L' : ld_number = va_arg(*argList, long double);
            s21_lf_to_str(str, ld_number, FFormat);
            break;
        default : d_number = va_arg(*argList, double);
            f_number = d_number;
            s21_lf_to_str(str, f_number, FFormat);
    }
    s21_sign_flag(str, FFormat);
    s21_lf_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_eE(char *str, va_list *argList, FORMAT *FFormat) {
    long double ld_number;
    double d_number;
    double f_number;

    switch (FFormat->len) {
        case 'l' : d_number = (double) va_arg(*argList, double);
            s21_leE_to_str(str, d_number, FFormat);
            break;
        case 'L' : ld_number = va_arg(*argList, long double);
            s21_leE_to_str(str, ld_number, FFormat);
            break;
        default : d_number = va_arg(*argList, double);
            f_number = d_number;
            s21_leE_to_str(str, f_number, FFormat);
    }
    s21_sign_flag(str, FFormat);
    s21_lf_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_gG(char *str, va_list *argList, FORMAT *FFormat) {
    long double ld_number;
    double d_number;
    double f_number;

    switch (FFormat->len) {
        case 'l' : d_number = (double) va_arg(*argList, double);
            s21_lgG_to_str(str, d_number, FFormat);
            break;
        case 'L' : ld_number = va_arg(*argList, long double);
            s21_lgG_to_str(str, ld_number, FFormat);
            break;
        default : d_number = va_arg(*argList, double);
            f_number = d_number;
            s21_lgG_to_str(str, f_number, FFormat);
    }
    s21_sign_flag(str, FFormat);
    s21_lf_width_flag(str, FFormat);
    return str;
}

char *s21_leE_to_str(char *str, long double number, FORMAT *FFormat) {
    if (FFormat->tolerance < 0) FFormat->tolerance = 6;
    long double right = 0.0, mantis;
    int pow = 0;

    mantis = modfl(fabsl(number), &right);
    if (fpclassify(number) > 3) {
        while (right >= 10) {
            pow++;
            modfl(right / 10, &right);
        }
        if (pow == 0 && right < 1) {
            while (truncl(mantis * powl(10, pow * -1)) < 1) {
                pow--;
           }
        }
    }

    if (fpclassify(number) > 2) {
        number = number / powl(10, pow);
        s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*Lfe%+.2d" : "%.*Lfe%+.2d",
                    FFormat->tolerance, number, pow);
    } else {
        s21_sprintf(str, "%.*Lf", FFormat->tolerance);
        FFormat->flag_zero = 0;
    }
    if (FFormat->spec == 'E') {
        char *p = s21_NULL;
        p = s21_strchr(str, 'e');
        if (p)
            *p = 'E';
    }
    return str;
}

char *s21_lgG_to_str(char *str, long double number, FORMAT *FFormat) {
    if (FFormat->tolerance < 0) FFormat->tolerance = 6;
    long double right = 0.0;
    int pow = 0, pow_m = 0;

    long double mantis = modfl(fabsl(number), &right);
    if (fpclassify(mantis) > 3 && fpclassify(right) == 3) {
        while (truncl(mantis * powl(10, pow * -1)) < 1) {
            pow--;
        }
    }
    mantis = modfl(fabsl(number), &right);
    if (fpclassify(number) > 3) {
        while (right >= 1 && pow >= 0) {
            pow++;
            modfl(right / 10, &right);
        }
        if (fpclassify(mantis) > 3) {
            for (int i = 0; i < FFormat->tolerance - pow; i++) {
                mantis = modfl(right / 10, &right);
                if (fpclassify(mantis) > 3) {
                    pow_m++;
                }
            }
        }
    }

    int flag;
    int tolerance;
    if (pow - 1 < -4 || pow - 1 > FFormat->tolerance - 1) {
        flag = 1;
        tolerance = FFormat->tolerance > 0 ? FFormat->tolerance - 1 : 0;
    } else {
        flag = 0;
        if (pow < 0)
            tolerance = FFormat->tolerance > 0 ? FFormat->tolerance : 0;
        else
            tolerance = FFormat->tolerance > 0 ? FFormat->tolerance - pow : 0;
    }

    if (flag == 1) {
        if (FFormat->spec == 'G')
            s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*LE" : "%.*LE",
                        tolerance, number);
        else
            s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*Le" : "%.*Le",
                        tolerance, number);
    } else {
        s21_sprintf(str, FFormat->flag_sharp == 1 ? "%#.*Lf" : "%.*Lf",
                    tolerance, number);
    }

    char *p = s21_NULL;
    if (pow < 0 && flag == 1) {
        p = str;
        s21_size_t str_len = s21_strpbrk(str, FFormat->spec == 'G' ? "E" : "e") - p;
        if (str_len > 2 && (int) str_len - 1 >= FFormat->tolerance && *(p + str_len - 1) == '0' &&
        FFormat->flag_sharp == 0) {
            p = p + str_len - 1;
            while (*p == '0') {
                *(p--) = '\0';
            }
            p = str + str_len;
            s21_strcat(str, p);
        }
    }

    p = str;
    p = p + s21_strlen(str) - 1;

    while (*p == '0' && FFormat->flag_sharp != 1) {
        *p-- = '\0';
    }
    if (*p == '.' && FFormat->flag_sharp != 1) {
        *p = '\0';
    }

    return str;
}

char *s21_lf_to_str(char *str, long double number, FORMAT *FFormat) {
    if (FFormat->tolerance < 0) FFormat->tolerance = 6;
    s21_ld_to_a(str, number, FFormat);
    return str;
}

char *s21_string_of_s(char *str, va_list *argList, FORMAT *FFormat) {
    wchar_t *pw = s21_NULL;
    char *p = s21_NULL;

    switch (FFormat->len) {
        case 'l' :
            pw = va_arg(*argList, wchar_t*);
            if (!pw) {
                if (FFormat->tolerance < 6)
                    s21_strncat(str, "(null)", FFormat->tolerance);
                else
                    s21_strcat(str, "(null)");
            } else {
                wch_to_str(str, pw, FFormat->tolerance > -1 ? FFormat->tolerance : 0);
            }
            break;
        default : p = va_arg(*argList, char*);
            if (!p) {
                if (FFormat->tolerance < 6)
                    s21_strncat(str, "(null)", FFormat->tolerance);
                else
                    s21_strcat(str, "(null)");
            } else {
                if (FFormat->tolerance > -1)
                    s21_strncat(str, p, FFormat->tolerance);
                else
                    s21_strcat(str, p);
            }
    }
    s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_c(char *str, va_list *argList, FORMAT *FFormat) {
    wchar_t wchar;
    wchar_t wchar_s[10] = {0};
    switch (FFormat->len) {
        case 'l' :
            wchar = va_arg(*argList, wchar_t);
            wchar_s[0] = wchar;
            wch_to_str(str, wchar_s, 0);
        break;
        default :
            str[0] = va_arg(*argList, int);
            str[1] = '\0';
    }
    s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_u(char *str, va_list *argList, FORMAT *FFormat) {
    unsigned short us_number;
    unsigned long ul_number;
    unsigned int u_number;

    switch (FFormat->len) {
        case 'h' : us_number = (unsigned short) va_arg(*argList, unsigned int);
            s21_ll_to_str(str, us_number);
            break;
        case 'l' : ul_number = (unsigned long) va_arg(*argList, unsigned long);
            s21_ul_to_str(str, ul_number);
            break;
        default : u_number = (unsigned int) va_arg(*argList, unsigned int);
            s21_ll_to_str(str, u_number);
    }

    s21_ll_tolerance(str, FFormat);
    s21_sign_flag(str, FFormat);
    s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_d(char *str, va_list *argList, FORMAT *FFormat) {
    long int ld_number;
    short int sd_number;
    int number;

    switch (FFormat->len) {
        case 'h' : sd_number = (short int) va_arg(*argList, int);
            s21_ll_to_str(str, sd_number);
            break;
        case 'l' : ld_number = (long int) va_arg(*argList, long int);
            s21_ll_to_str(str, ld_number);
            break;
        default : number = va_arg(*argList, int);
            s21_ll_to_str(str, number);
    }
    s21_ll_tolerance(str, FFormat);
    s21_sign_flag(str, FFormat);
    s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_o(char *str, va_list *argList, FORMAT *FFormat) {
    unsigned long int ld_number;
    unsigned short int sd_number;
    unsigned int number;

    switch (FFormat->len) {
        case 'h' : sd_number = (unsigned short int) va_arg(*argList, unsigned  int);
            s21_ol_to_str(str, sd_number, FFormat->flag_sharp);
            break;
        case 'l' : ld_number = (unsigned long int) va_arg(*argList, unsigned long int);
            s21_ol_to_str(str, ld_number, FFormat->flag_sharp);
            break;
        default : number = va_arg(*argList, unsigned int);
            s21_ol_to_str(str, number, FFormat->flag_sharp);
    }
    s21_ll_tolerance(str, FFormat);
    s21_sign_flag(str, FFormat);
    s21_ll_width_flag(str, FFormat);
    return str;
}

char *s21_string_of_xX(char *str, va_list *argList, FORMAT *FFormat) {
    unsigned long int ld_number;
    unsigned short int sd_number;
    unsigned int number;

    switch (FFormat->len) {
        case 'h' : sd_number = (short unsigned int) va_arg(*argList, unsigned int);
            s21_hl_to_str(str, sd_number, FFormat);
            break;
        case 'l' : ld_number = (long unsigned int) va_arg(*argList, unsigned long int);
            s21_hl_to_str(str, ld_number, FFormat);
            break;
        default : number = (unsigned int) va_arg(*argList, unsigned int);
            s21_hl_to_str(str, number, FFormat);
    }
    s21_ll_tolerance(str, FFormat);
    s21_sign_flag(str, FFormat);
    s21_ll_width_flag(str, FFormat);

    return str;
}

char *s21_lf_width_flag(char *str, FORMAT *FFormat) {
    int str_len = (int) s21_strlen(str);
    char *p = s21_NULL, *p2 = s21_NULL;
    p2 = str;
    if (FFormat->width > (int) str_len) {
        char *num_str = calloc(1000 + FFormat->width + 2, sizeof (char));
        if (num_str) {
            p = num_str;
            if (!is_digit(*p2) && FFormat->flag_zero) {
                *(p++) = *(p2++);
            }
            for (int i = 0; i < FFormat->width; i++) {
                if (FFormat->flag_minus == 1) {
                    if (i < str_len) {
                        *(p++) = *(p2++);
                    } else {
                        if (FFormat->flag_zero == 1)
                            *(p++) = '0';
                        else
                            *(p++) = ' ';
                    }
                } else {
                    if (i < FFormat->width - str_len) {
                        if (FFormat->flag_zero == 1)
                            *(p++) = '0';
                        else
                            *(p++) = ' ';
                    } else {
                        *(p++) = *(p2++);
                    }
                }
            }
            num_str[FFormat->width] = '\0';
            str = s21_strcpy(str, num_str);
            free(num_str);
        }
    }
    return str;
}

char *s21_ll_width_flag(char *str, FORMAT *FFormat) {
    int str_len = (int) s21_strlen(str);
    if (FFormat->width > (int) str_len) {
        char *num_str = calloc(1000 + FFormat->width + 2, sizeof (char));
        if (num_str) {
            for (int i = 0; i < FFormat->width; i++) {
                if (FFormat->flag_minus == 1) {
                    if (i < str_len) {
                        num_str[i] = str[i];
                    } else {
                        num_str[i] = ' ';
                    }
                } else {
                    if (i < FFormat->width - str_len) {
                        num_str[i] = ' ';
                    } else {
                        num_str[i] = str[i - (FFormat->width - str_len)];
                    }
                }
            }
            num_str[FFormat->width] = '\0';
            str = s21_strcpy(str, num_str);
            free(num_str);
        }
    }
    return str;
}

char *wch_to_str(char *str, wchar_t *wstr, s21_size_t len) {
    s21_size_t str_len = s21_strlen(str);
    int cnt = len;
    char *p = str + str_len;

    while (*wstr != '\0' && (cnt-- > 0 || len == 0)) {
        *(p++) = (char) *(wstr++);
    }
    *p = '\0';
    return str;
}

char *s21_sign_flag(char *str, FORMAT *FFormat) {
    if (is_digit(*str) || *str == 'i') {
        char num_str[2] = "";
        char *p = s21_NULL;
        p = num_str;
        if (FFormat->flag_plus)
            *(p++) = '+';
        else if (FFormat->flag_space)
            *(p++) = ' ';
        *p = '\0';
        s21_reverse_str(str);
        s21_strcat(str, num_str);
        s21_reverse_str(str);
    }
    return str;
}

char *s21_ll_tolerance(char *str, FORMAT *FFormat) {
    char *num_str = calloc(1000 + FFormat->width + 2, sizeof (char));
    if (num_str) {
        s21_size_t str_len = s21_strlen(str);
        int shift;
        char *p = s21_NULL;
        char *s = s21_NULL;
        p = num_str;
        s = str;

        int sign = *s == '-' ? -1 : 0;
        if (FFormat->flag_zero == 1)
            FFormat->tolerance = (FFormat->tolerance > FFormat->width) ? FFormat->tolerance : FFormat->width;

        FFormat->tolerance = FFormat->tolerance > (int) str_len + sign ? FFormat->tolerance : (int) str_len +
            sign;
        shift = FFormat->spec == 'x' && FFormat->flag_sharp == 1 ? 32 : 0;

        s21_reverse_str(str);
        for (int i = 0; i < FFormat->tolerance; i++) {
            if (i < (int) str_len + sign)
                *(p++) = *(s++);
            else
                *(p++) = '0';
        }

        if (FFormat->flag_sharp == 1 && FFormat->spec == (char) ('X' + shift)) {
            *(p++) = (char) ('X' + shift);
            *(p++) = '0';
        }

        if (sign < 0)
            *(p++) = '-';
        *p = '\0';
        s21_reverse_str(num_str);
        s21_strcpy(str, num_str);
        free(num_str);
    }
    return str;
}

char *s21_ll_to_str(char *str, long long number) {
    char *p = s21_NULL;
    int flag = 1, sign;

    sign = number < 0 ? -1 : 1;
    number *= sign;
    p = str;

    while (flag) {
        int digit;
        if (number >= 10) {
            digit = (int) (number % 10);
            number = (number - digit) / 10;
        } else {
            digit = (int) number;
            flag = 0;
        }
        *(p++) = (char) (digit + '0');
    }

    if (sign < 0) {
        *(p++) = '-';
    }
    *p = '\0';
    s21_reverse_str(str);
    return str;
}

char *s21_ul_to_str(char *str, unsigned long long number) {
    char *p = s21_NULL;
    int flag = 1;

    p = str;

    while (flag) {
        int digit;
        if (number >= 10) {
            digit = (int) (number % 10);
            number = (number - digit) / 10;
        } else {
            digit = (int) number;
            flag = 0;
        }
        *(p++) = (char) (digit + '0');
    }
    *p = '\0';
    s21_reverse_str(str);
    return str;
}

char *s21_ol_to_str(char *str, unsigned long long number, int prefix) {
    char *p = s21_NULL;
    int flag = 1;

    p = str;

    while (flag) {
        unsigned int digit;
        if (number > 7) {
            digit = number % 8;
            number = (number - digit) / 8;
        } else {
            digit = number;
            flag = 0;
        }
        *(p++) = (char) (digit + '0');
    }

    if (prefix == 1)
        *(p++) = '0';
    *p = '\0';
    s21_reverse_str(str);
    return str;
}

char *s21_hl_to_str(char *str, unsigned long long number, FORMAT *FFormat) {
    char *p = s21_NULL;
    int flag = 1, shift;

    p = str;

    shift = FFormat->spec == 'x' ? 32 : 0;

    while (flag) {
        unsigned int digit;
        if (number > 15) {
            digit = number % 16;
            number = (number - digit) / 16;
        } else {
            digit = number;
            flag = 0;
        }
        if (digit < 10)
            *(p++) = (char) (digit + '0');
        else
            *(p++) = (char) (digit + 'A' + shift - 10);
    }
    *p = '\0';
    s21_reverse_str(str);
    return str;
}

char *s21_str_to_int(const char *format, int *number, va_list *argList) {
    *number = 0;
    while (is_digit(*format)) {
        *number = *format - '0' + *number * 10;
        format++;
    }
    if (*format == '*') {
        *number = va_arg(*argList, int);
        format++;
    }
    return (char *) format;
}

char *s21_reverse_str(char *str) {
    s21_size_t str_len = s21_strlen(str);
    char ch;
    for (s21_size_t i = 0; i < str_len / 2; i++) {
        ch = str[i];
        str[i] = str[str_len - 1 - i];
        str[str_len - 1 - i] = ch;
    }
    return str;
}

long double s21_round(long double x, int tolerance) {
    long double right = 0.0;
    long double x1 = modfl(fabsl(x), &right);
    int mul = 0;
    int sign = signbit(x) == 0 ? 1 : -1;
    for (int i = 0; i < tolerance; i++)
        mul--;

    if (roundl(x1 / powl(10, mul)) > truncl(x1 / powl(10, mul))) {
        x = x + (5 * powl(10, mul - 1)) * sign;
    }
    if (tolerance <= 6 && x1 > 0) {
        x = x / powl(10, mul);
        x = truncl(x) * powl(10, mul);
    }
    return x;
}

char *s21_ld_to_a(char *str, long double number, FORMAT *FFormat) {
    char num1_str[1000] = "", *p1 = s21_NULL;
    p1 = num1_str;
    char num2_str[1000] = "", *p2 = s21_NULL;
    p2 = num2_str;
    long double mantis, right = 0.0L, pow = 1.0L, pow_t = 1.0L;
    int sign;
    sign = signbit(number) == 0 ? 1 : -1;

    if (fpclassify(number) < 4) {
        d_class_to_str(num1_str, number, FFormat->tolerance);
        if (sign < 0 && fpclassify(number) != 1)
            s21_strcat(str, "-");
        s21_strcat(str, num1_str);
        FFormat->flag_zero = 0;
    } else {
        number = s21_round(number, FFormat->tolerance);
        mantis = modfl(fabsl(number), &right);

        while (truncl(right / pow) > 0) {
            int digit;
            digit = (int) truncl(fmodl(truncl(right), pow * (long double) 10L) / (pow));
            *(p1++) = (char) (digit + '0');
            pow *= 10L;
        }

        if (sign < 0) *(p1++) = '-';
        *p1 = '\0';

        for (int i = 0; i < FFormat->tolerance; i++) pow_t *= 10;

        mantis = roundl(mantis * pow_t);
        pow = 1.0L;
        while (pow < pow_t) {
            int digit;
            digit = (int) truncl(fmodl(truncl(mantis), pow * (long double) 10L) / (pow));
            *(p2++) = (char) (digit + '0');
            pow *= 10L;
        }
        *p2 = '\0';
        s21_reverse_str(num1_str);
        if  (s21_strlen(num1_str) == 0)
            s21_strcat(str, "0");
        s21_strcat(str, num1_str);
        if (FFormat->tolerance > 0 || FFormat->flag_sharp == 1)
            s21_strcat(str, ".");
        if (FFormat->tolerance > 0) {
            s21_reverse_str(num2_str);
            s21_strcat(str, num2_str);
        }
    }
    return str;
}

char *d_class_to_str(char *str, long double x, int tolerance) {
    switch (fpclassify(x)) {
        case FP_NAN: s21_strcat(str, "nan"); break;
        case FP_INFINITE: s21_strcat(str, "inf"); break;
        case FP_ZERO:
            s21_strcat(str, "0");
            if (tolerance > 0) {
                s21_strcat(str, ".");
                while (tolerance--)
                    s21_strcat(str, "0");
            }
            break;
    }
    return str;
}

// BEGIN SSCANF
int s21_sscanf(const char *str, const char *format, ...) {
    char *string = s21_NULL;
    string = (char *)str;
    char *string_format = (char *)format;
    char buffer_string[1024] = "";
    int buffer_length = 0;
    int is_continue = 0;
    int result = 0;

    va_list args;
    va_start(args, format);

    if (str == s21_NULL || format == s21_NULL ||
        (int)s21_strlen(str) == 0 || (int) s21_strlen(format) ==0) {
        is_continue = 1;
        result = -1;
    }

    while (*string_format && is_continue == 0) {
        if (*string_format == '%') {
            int is_ignoring = 0;
            int width = 0;
            char length = '0';
            if (buffer_length > 0) {
                buffer_string[buffer_length] = '\0';
            }
            string_format++;
            if (*string_format == '*') {
                is_ignoring++;
                string_format++;
            }
            if (is_digit(*string_format)) {
                width = *string_format - '0';
                string_format++;
                while (is_digit(*string_format)) {
                    width = *string_format - '0' + width * 10;
                    string_format++;
                }
            }
            if (is_len(*string_format)) {
                length = *string_format;
                string_format++;
            }
            if (is_spec(*string_format)) {
                char specifier = *string_format;

                char *new_string_pointer = s21_spec(
                    (char *)str, string, buffer_string, buffer_length, args,
                    is_ignoring, width, length, specifier, &is_continue, &result);

                string = new_string_pointer;
                if (specifier != '%' && specifier != 'n' && is_ignoring == 0) {
                    result++;
                }
            }
            if (buffer_length > 0) {
                buffer_string[0] = '\0';
                buffer_length = 0;
            }
        } else {
            buffer_string[buffer_length] = *string_format;
            buffer_length++;
        }

        string_format++;
    }

    va_end(args);

    return result;
}

char *s21_spec(char *str, char *string, char *buffer_string,
                         int buffer_length, va_list args, int is_ignoring,
                         int width, char length, char specifier,
                         int *is_continue, int *result) {
    s21_size_t strspn_res = s21_strspn(buffer_string, " ");
    int whitespace_length = (int) strspn_res;
    int flag = 0;
    if (whitespace_length != buffer_length) {
        int begin_space_number = (int)s21_strspn(string, " ");
        string += begin_space_number;
        int begin_space_number2 = (int)s21_strspn(buffer_string, " ");
        buffer_string += begin_space_number2;
        int end_space_number = (int)s21_trim_strspn_reverse(buffer_string, " ");
        for (int i = 0; i < ((int)s21_strlen(buffer_string) - end_space_number);
             i++) {
            if (buffer_string[i] != string[i]) {
                flag++;
                is_continue += 1;
                *result -= 1;
            }
        }
        if (flag == 0) {
            string += (s21_strlen(buffer_string) - end_space_number);
        }
    } else if (whitespace_length > 0) {
        int begin_space_number = (int)s21_strspn(string, " ");
        string += begin_space_number;
    }
    if (flag == 0) {
        switch (specifier) {
            case 'd': {
                char *new_string_pointer = s21_spec_d(string, args, width, length,
                                                         is_ignoring, is_continue, result);
                string = new_string_pointer;
                break;
            }
            case 'i': {
                char *new_string_pointer = s21_spec_i(string, args, width, length,
                                                         is_ignoring, is_continue, result);
                string = new_string_pointer;
                break;
            }
            case 'u': {
                char *new_string_pointer = s21_spec_u(string, args, width, length,
                                                         is_ignoring, is_continue, result);
                string = new_string_pointer;
                break;
            }
            case 'o': {
                char *new_string_pointer = s21_spec_o(string, args, width, length,
                                                         is_ignoring, is_continue, result);
                string = new_string_pointer;
                break;
            }
            case 'p':
            case 'x':
            case 'X': {
                char *new_string_pointer = s21_spec_x(string, args, width, length, specifier,
                                                         is_ignoring, is_continue, result);
                string = new_string_pointer;
                break;
            }
            case 'e':
            case 'E':
            case 'g':
            case 'G':
            case 'f': {
                char *new_string_pointer = s21_spec_f(string, args, width, length, is_ignoring,
                                                         is_continue, result);
                string = new_string_pointer;
                break;
            }
            case 'c': {
                char *new_string_pointer = s21_spec_c(string, args, length, is_ignoring);
                string = new_string_pointer;
                break;
            }
            case 's': {
                char *new_string_pointer = s21_spec_s(string, args, width, length, is_ignoring);
                string = new_string_pointer;
                break;
            }
            case 'n': {
                char *new_string_pointer = s21_spec_n(string, str, buffer_string, args,
                                                         length, is_ignoring);
                string = new_string_pointer;
                break;
            }
            case '%': {
                int begin_space_number = (int)s21_strspn(string, " ");
                string += begin_space_number;
                if (*string == '%') {
                    string++;
                } else {
                    *is_continue += 1;
                }
                break;
            }
        }
    }
    return string;
}

char *s21_str_into_octal(char *string, unsigned long long int *variable,
                          int width, int is_width_cutted) {
    *variable = 0;
    char temp_string[1024] = "\0";
    int temp_counter = 0;
    if (width > 0) {
        while (is_octal_digit(*string) &&
               temp_counter < width - is_width_cutted) {
            temp_string[temp_counter] = *string;
            temp_counter++;
            string++;
        }
    } else {
        while (is_octal_digit(*string)) {
            temp_string[temp_counter] = *string;
            temp_counter++;
            string++;
        }
    }
    for (int i = temp_counter - 1, j = 1; i > -1; i--, j *= 8) {
        unsigned long long int temp_number = temp_string[i] - '0';
        temp_number *= j;
        *variable += temp_number;
    }
    return string;
}

char *s21_str_into_hex(char *string, unsigned long long int *variable,
                        int width, int is_width_cutted) {
    *variable = 0;
    char temp_string[1024] = "\0";
    int temp_counter = 0;
    if (width > 0) {
        while (is_hex_digit(*string) &&
               temp_counter < width - is_width_cutted) {
            temp_string[temp_counter] = *string;
            temp_counter++;
            string++;
        }
    } else {
        while (is_hex_digit(*string)) {
            temp_string[temp_counter] = *string;
            temp_counter++;
            string++;
        }
    }
    for (int i = temp_counter - 1, j = 1; i > -1; i--, j *= 16) {
        unsigned long long int temp_number = temp_string[i] - '0';
        if (temp_number > 9) {
            switch (temp_string[i]) {
                case 'a':
                case 'A': {
                    temp_number = 10;
                    break;
                }
                case 'b':
                case 'B': {
                    temp_number = 11;
                    break;
                }
                case 'c':
                case 'C': {
                    temp_number = 12;
                    break;
                }
                case 'd':
                case 'D': {
                    temp_number = 13;
                    break;
                }
                case 'e':
                case 'E': {
                    temp_number = 14;
                    break;
                }
                case 'f':
                case 'F': {
                    temp_number = 15;
                    break;
                }
            }
        }
        temp_number *= j;
        *variable += temp_number;
    }
    return string;
}

char *s21_str_into_decimal(char *string, unsigned long long int *variable,
                            int width, int is_width_cutted) {
    if (width > 0) {
        int counter = 0;
        if (is_digit(*string) && counter < width - is_width_cutted) {
            *variable = *string - '0';
            string++;
            counter++;
        }
        while (is_digit(*string) && counter < width - is_width_cutted) {
            *variable = *string - '0' + *variable * 10;
            string++;
            counter++;
        }
    } else {
        *variable = *string - '0';
        string++;
        while (is_digit(*string)) {
            *variable = *string - '0' + *variable * 10;
            string++;
        }
    }
    return string;
}

char *s21_spec_d(char *string, va_list args, int width, char length, int is_ignoring,
                    int *is_continue, int *result) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    int is_width_cutted = 0;
    int is_negative = 0;
    if (*string == '-') {
        is_negative++;
        string++;
        is_width_cutted++;
    } else if (*string == '+') {
        string++;
        is_width_cutted++;
    }
    if (is_digit(*string)) {
        unsigned long long int temp_variable;
        unsigned long long int *variable_pointer = &temp_variable;
        char *new_string_pointer = s21_str_into_decimal(string, variable_pointer, width, is_width_cutted);
        string = new_string_pointer;
        if (is_negative == 1) {
            *variable_pointer *= -1;
        }
        if (is_ignoring == 0) {
            s21_send_to_var(args, variable_pointer, length);
        }
    } else {
        *is_continue = 1;
        if (is_ignoring == 0) {
            *result -= 1;
        }
    }
    return string;
}

char *s21_spec_o(char *string, va_list args, int width, char length, int is_ignoring,
                    int *is_continue, int *result) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    int is_width_cutted = 0;
    int is_negative = 0;
    if (*string == '-') {
        is_negative++;
        string++;
        is_width_cutted++;
    } else if (*string == '+') {
        string++;
        is_width_cutted++;
    }
    if (is_octal_digit(*string)) {
        unsigned long long int temp_variable;
        unsigned long long int *variable_pointer = &temp_variable;
        char *new_string_pointer = s21_str_into_octal(
                string, variable_pointer, width, is_width_cutted);
        string = new_string_pointer;
        if (is_negative == 1) {
            *variable_pointer *= -1;
        }
        if (is_ignoring == 0) {
            s21_send_to_uns_var(args, variable_pointer, length);
        }
    } else {
        *is_continue = 1;
        if (is_ignoring == 0) {
            *result -= 1;
        }
    }
    return string;
}

char *s21_spec_x(char *string, va_list args, int width, char length, char specifier,
                    int is_ignoring, int *is_continue, int *result) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    int is_width_cutted = 0;
    int is_negative = 0;
    int is_start_from_zero = 0;
    if (*string == '-') {
        is_negative++;
        string++;
        is_width_cutted++;
    } else if (*string == '+') {
        string++;
        is_width_cutted++;
    }
    if (*string == '0') {
        string++;
        is_width_cutted++;
        is_start_from_zero++;
        if (*string == 'x' || *string == 'X') {
            string++;
            is_width_cutted++;
        }
    }
    if (is_hex_digit(*string)) {
        unsigned long long int temp_variable;
        unsigned long long int *variable_pointer = &temp_variable;
        char *new_string_pointer = s21_str_into_hex(
                string, variable_pointer, width, is_width_cutted);
        string = new_string_pointer;
        if (is_negative == 1) {
            *variable_pointer *= -1;
        }
        if (is_ignoring == 0) {
            if (specifier == 'p') {
                void **variable = va_arg(args, void **);
                *variable = (void *) (0x0 + *variable_pointer);
            } else {
                s21_send_to_uns_var(args, variable_pointer, length);
            }
        }
    } else if (is_start_from_zero == 1) {
        unsigned long long int temp_variable = 0;
        unsigned long long int *variable_pointer = &temp_variable;
        if (is_ignoring == 0) {
            if (specifier == 'p') {
                void **variable = va_arg(args, void **);
                *variable = (void *) (0x0 + *variable_pointer);
            } else {
                s21_send_to_uns_var(args, variable_pointer, length);
            }
        }
    } else {
        *is_continue = 1;
        if (is_ignoring == 0) {
            *result -= 1;
        }
    }
    return string;
}

char *s21_spec_u(char *string, va_list args, int width, char length, int is_ignoring,
                    int *is_continue, int *result) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    int is_width_cutted = 0;
    int is_negative = 0;
    if (*string == '-') {
        is_negative++;
        string++;
        is_width_cutted++;
    } else if (*string == '+') {
        string++;
        is_width_cutted++;
    }
    if (is_digit(*string)) {
        unsigned long long int temp_variable;
        unsigned long long int *variable_pointer = &temp_variable;
        char *new_string_pointer =
                s21_str_into_decimal(string, variable_pointer, width, is_width_cutted);
        string = new_string_pointer;
        if (is_negative == 1) {
            *variable_pointer *= -1;
        }
        if (is_ignoring == 0) {
            s21_send_to_uns_var(args, variable_pointer, length);
        }
    } else {
        *is_continue = 1;
        if (is_ignoring == 0) {
            *result -= 1;
        }
    }
    return string;
}

char *s21_spec_i(char *string, va_list args, int width, char length, int is_ignoring,
                    int *is_continue, int *result) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    int is_negative = 0;
    int is_width_cutted = 0;
    if (*string == '-') {
        is_negative++;
        string++;
        is_width_cutted++;
    } else if (*string == '+') {
        string++;
        is_width_cutted++;
    }
    if (*string == '0') {
        string++;
        is_width_cutted++;
        if (*string == 'x' || *string == 'X') {
            string++;
            is_width_cutted++;
            if (is_hex_digit(*string)) {
                unsigned long long int temp_variable;
                unsigned long long int *variable_pointer = &temp_variable;
                char *new_string_pointer = s21_str_into_hex(
                        string, variable_pointer, width, is_width_cutted);
                string = new_string_pointer;
                if (is_negative == 1) {
                    *variable_pointer *= -1;
                }
                if (is_ignoring == 0) {
                    s21_send_to_var(args, variable_pointer, length);
                }
            }
        } else if (is_octal_digit(*string)) {
            unsigned long long int temp_variable;
            unsigned long long int *variable_pointer = &temp_variable;
            char *new_string_pointer = s21_str_into_octal(
                    string, variable_pointer, width, is_width_cutted);
            string = new_string_pointer;
            if (is_negative == 1) {
                *variable_pointer *= -1;
            }
            if (is_ignoring == 0) {
                s21_send_to_var(args, variable_pointer, length);
            }
        } else {
            unsigned long long int temp_variable = 0;
            unsigned long long int *variable_pointer = &temp_variable;
            if (is_ignoring == 0) {
                s21_send_to_var(args, variable_pointer, length);
            }
        }
    } else if (is_digit(*string)) {
        unsigned long long int temp_variable;
        unsigned long long int *variable_pointer = &temp_variable;
        char *new_string_pointer =
                s21_str_into_decimal(string, variable_pointer, width, is_width_cutted);
        string = new_string_pointer;
        if (is_negative == 1) {
            *variable_pointer *= -1;
        }
        if (is_ignoring == 0) {
            s21_send_to_var(args, variable_pointer, length);
        }
    } else {
        *is_continue = 1;
        if (is_ignoring == 0) {
            *result -= 1;
        }
    }
    return string;
}

char *s21_spec_f(char *string, va_list args, int width, char length, int is_ignoring,
                    int *is_continue, int *result) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    int is_negative = 0;
    int is_width_cutted = 0;
    if (*string == '-') {
        is_negative++;
        string++;
        is_width_cutted++;
    }  else if (*string == '+') {
        string++;
        is_width_cutted++;
    }
    long double temp_variable = 0;
    long double *variable_pointer = &temp_variable;
    int width_counter = 0;
    int integer_part_exist = 0;
    if (!(is_digit(*string)) && *string != '.') {
        *is_continue = 1;
        if (is_ignoring == 0) {
            *result -= 1;
        }
    } else {
        if (width > 0) {
            if (is_digit(*string) && width_counter < width - is_width_cutted) {
                *variable_pointer = *string - '0';
                string++;
                width_counter++;
                integer_part_exist++;
            }
            while (is_digit(*string) && width_counter < width - is_width_cutted) {
                *variable_pointer = *string - '0' + *variable_pointer * 10;
                string++;
                width_counter++;
            }
        } else if (is_digit(*string)) {
            *variable_pointer = *string - '0';
            string++;
            integer_part_exist++;

            while (is_digit(*string)) {
                *variable_pointer = *string - '0' + *variable_pointer * 10;
                string++;
            }
        }
        if (*string == '.' && (width == 0 || width_counter < width - is_width_cutted)) {
            int number_length_counter = 0;
            long double number_after_dot;
            width_counter++;
            string++;
            if (width > 0) {
                if (is_digit(*string) && width_counter < width - is_width_cutted) {
                    number_after_dot = *string - '0';
                    string++;
                    number_length_counter++;
                    width_counter++;
                    while (is_digit(*string) && width_counter < width - is_width_cutted) {
                        number_after_dot =
                                *string - '0' + number_after_dot * 10.0;
                        string++;
                        number_length_counter++;
                        width_counter++;
                    }
                    for (int i = 0; i < number_length_counter; i++) {
                        number_after_dot *= 0.1;
                    }
                    *variable_pointer += number_after_dot;
                } else if (integer_part_exist == 0) {
                    *is_continue = 1;
                    if (is_ignoring == 0) {
                        *result -= 1;
                    }
                }
            } else if (is_digit(*string)) {
                number_after_dot = *string - '0';
                string++;
                number_length_counter++;
                while (is_digit(*string)) {
                    number_after_dot =
                            *string - '0' + number_after_dot * 10.0;
                    string++;
                    number_length_counter++;
                }
                for (int i = 0; i < number_length_counter; i++) {
                    number_after_dot *= 0.1;
                }
                *variable_pointer += number_after_dot;
            } else if (integer_part_exist == 0) {
                *is_continue = 1;
                if (is_ignoring == 0) {
                    *result -= 1;
                }
            }
        }
        if ((*string == 'e' || *string == 'E') &&
            (width == 0 || width_counter < width - is_width_cutted)) {
            width_counter++;
            string++;
            if ((*string == '+' || is_digit(*string)) &&
                (width == 0 || width_counter < width - is_width_cutted)) {
                if (*string == '+') {
                    string++;
                    width_counter++;
                }
                int temp_number;
                if (is_digit(*string) &&
                    (width == 0 || width_counter < width - is_width_cutted)) {
                    temp_number = *string - '0';
                    string++;
                    width_counter++;
                    if (width > 0) {
                        while (is_digit(*string) && width_counter < width - is_width_cutted) {
                            temp_number = *string - '0' + temp_number * 10.0;
                            string++;
                            width_counter++;
                        }
                    } else {
                        while (is_digit(*string)) {
                            temp_number = *string - '0' + temp_number * 10;
                            string++;
                        }
                    }
                    for (int i = 0; i < temp_number; i++) {
                        *variable_pointer *= 10;
                    }
                }
            } else if (*string == '-' && (width == 0 || width_counter < width - is_width_cutted)) {
                string++;
                width_counter++;
                int temp_number;
                if (is_digit(*string) &&
                    (width == 0 || width_counter < width - is_width_cutted)) {
                    temp_number = *string - '0';
                    string++;
                    width_counter++;
                    if (width > 0) {
                        while (is_digit(*string) &&
                               width_counter < width - is_width_cutted) {
                            temp_number =
                                    *string - '0' + temp_number * 10.0;
                            string++;
                            width_counter++;
                        }
                    } else {
                        while (is_digit(*string)) {
                            temp_number =
                                    *string - '0' + temp_number * 10;
                            string++;
                        }
                    }
                    for (int i = 0; i < temp_number; i++) {
                        *variable_pointer *= 0.1;
                    }
                }
            }
        }
    }
    if (is_negative == 1) {
        *variable_pointer *= -1;
    }
    if (is_ignoring == 0) {
        if (length == 'L') {
            long double *variable = va_arg(args, long double *);
            *variable = (long double)*variable_pointer;
        } else if (length == 'l') {
            double *variable = va_arg(args, double *);
            *variable = (double)*variable_pointer;
        } else {
            float *variable = va_arg(args, float *);
            *variable = (float)*variable_pointer;
        }
    }
    return string;
}

char *s21_spec_c(char *string, va_list args, char length, int is_ignoring) {
    if (is_ignoring == 0) {
        if (length == 'l' || length == 'L') {
            wchar_t *variable = va_arg(args, wchar_t *);
            *variable = *string;
        } else {
            char *variable = va_arg(args, char *);
            *variable = *string;
        }
    } else {
        if (length == 'l' || length == 'L') {
            wchar_t temp_variable;
            wchar_t *variable = &temp_variable;
            *variable = *string;
        } else {
            char temp_variable;
            char *variable = &temp_variable;
            *variable = *string;
        }
    }
    string++;
    return string;
}

char *s21_spec_s(char *string, va_list args, int width, char length, int is_ignoring) {
    int begin_space_number = (int)s21_strspn(string, " ");
    string += begin_space_number;
    if (length == 'l' || length == 'L') {
        int i = 0;
        wchar_t temp_variable[1024] = L"";
        wchar_t *variable;
        if (is_ignoring == 0) {
            variable = va_arg(args, wchar_t *);
        } else {
            variable = temp_variable;
        }
        if (width > 0) {
            while (*string != ' ' && *string != '\0' && i < width) {
                variable[i] = *string;
                i++;
                string++;
            }
        } else {
            while (*string != ' ' && *string != '\0') {
                variable[i] = *string;
                i++;
                string++;
            }
        }
        variable[i] = '\0';
    } else {
        int i = 0;
        char temp_variable[1024] = "";
        char *variable;
        if (is_ignoring == 0) {
            variable = va_arg(args, char *);
        } else {
            variable = temp_variable;
        }
        if (width > 0) {
            while (*string != ' ' && *string != '\0' && i < width) {
                variable[i] = *string;
                i++;
                string++;
            }
        } else {
            while (*string != ' ' && *string != '\0') {
                variable[i] = *string;
                i++;
                string++;
            }
        }
        variable[i] = '\0';
    }
    return string;
}

char *s21_spec_n(char *string, char *str, char *buffer_string, va_list args,
                    char length, int is_ignoring) {
    unsigned long long int temp_variable;
    unsigned long long int *variable_pointer = &temp_variable;
    int buffer_length = (int)s21_strlen(buffer_string);
    *variable_pointer = string - str;
    if (*string == ' ' && buffer_string[buffer_length - 1] == ' ') {
        *variable_pointer += 1;
    }
    if (is_ignoring == 0) {
        s21_send_to_var(args, variable_pointer, length);
    }
    return string;
}

void s21_send_to_var(va_list args, unsigned long long int *variable_pointer, char length) {
    if (length == 'h') {
        short int *variable = va_arg(args, short int *);
        *variable = (short int)*variable_pointer;
    } else if (length == 'l') {
        long int *variable = va_arg(args, long int *);
        *variable = (long int)*variable_pointer;
    } else {
        int *variable = va_arg(args, int *);
        *variable = (int)*variable_pointer;
    }
}

void s21_send_to_uns_var(va_list args, unsigned long long int *variable_pointer, char length) {
    if (length == 'h') {
        unsigned short int *variable =
        va_arg(args, unsigned short int *);
        *variable = (unsigned short int)*variable_pointer;
    } else if (length == 'l') {
        unsigned long int *variable =
        va_arg(args, unsigned long int *);
        *variable = (unsigned long int)*variable_pointer;
    } else {
        unsigned int *variable = va_arg(args, unsigned int *);
        *variable = (unsigned int)*variable_pointer;
    }
}
