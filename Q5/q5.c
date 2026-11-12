#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Complete the Code: Counts words separated by one or more spaces (or tabs/whitespace), without string.h */
int word_count(const char s[])
{
    int count = 0, inside = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
            inside = 0;
        } else if (!inside) {
            inside = 1;
            count++;
        }
    }
    return count;
}

/* Complete the Code: Returns 1 if s reads the same both ways, ignoring case and non-letters. */
int is_palindrome(const char s[])
{
    int left = 0, right = 0;
    while (s[right] != '\0') right++;
    right--;

    while (left < right) {
        while (left < right && !isalpha((unsigned char)s[left])) left++;
        while (left < right && !isalpha((unsigned char)s[right])) right--;
        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right])) {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}

/* Manual uppercase and reversal without string.h */
void to_upper_manual(char s[])
{
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (char)(s[i] - ('a' - 'A'));
        }
    }
}

void reverse_manual(char s[])
{
    int len = 0;
    while (s[len] != '\0') len++;
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

/* Library-based (string.h) equivalents */
void process_with_library(const char *input)
{
    char buf[64];
    /* Safe bounded copy instead of unsafe strcpy */
    snprintf(buf, sizeof(buf), "%s", input);

    size_t n = strlen(buf); /* Computed ONCE outside loop */
    for (size_t i = 0; i < n; i++) {
        buf[i] = (char)toupper((unsigned char)buf[i]);
    }
    printf("Library Upper : \"%s\"\n", buf);

    for (size_t i = 0, j = (n > 0 ? n - 1 : 0); i < j; i++, j--) {
        char tmp = buf[i];
        buf[i] = buf[j];
        buf[j] = tmp;
    }
    printf("Library Rev   : \"%s\"\n", buf);
}

int main(void)
{
    /* 1. Prompt Expected Output Test */
    printf("Words: %d\n", word_count(" Meet at the library at 5 PM "));
    printf("%d %d\n\n", is_palindrome("Madam, I'm Adam"), is_palindrome("Hello"));

    /* 2. Tab character, punctuation, and empty string tests */
    printf("Tab Test   (\"Meet\\tat\\t5 PM\") : %d words\n", word_count("Meet\tat\t5 PM"));
    printf("Empty Test (\"\")               : %d words, Palindrome = %d\n\n",
           word_count(""), is_palindrome(""));

    /* 3. Manual vs string.h comparison */
    char msg[] = "  Hello, Campus!  ";
    printf("Original      : \"%s\" (Words = %d)\n", msg, word_count(msg));
    to_upper_manual(msg);
    printf("Manual Upper  : \"%s\"\n", msg);
    reverse_manual(msg);
    printf("Manual Rev    : \"%s\"\n", msg);

    process_with_library("  Hello, Campus!  ");
    return 0;
}
