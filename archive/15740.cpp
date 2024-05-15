#include <stdio.h>

const int strlen = 10005;

int main(){
    char a_abs[strlen];
    int a_len = 0;
    bool a_sign = true;

    char b_abs[strlen];
    int b_len = 0;
    bool b_sign = true;

    char result[strlen];
    int result_len = 0;
    bool result_sign;

    char input;
    scanf("%c", &input);
    if(input == '-') {
        a_sign = false;
        scanf("%c", &input);
    }
    while(input >= '0' && input <= '9'){
        a_abs[a_len] = input;
        a_len++;
        scanf("%c", &input);
    }
    scanf("%c", &input);
    if(input == '-') {
        b_sign = false;
        scanf("%c", &input);
    }
    while(input >= '0' && input <= '9'){
        b_abs[b_len] = input;
        b_len++;
        if(scanf("%c", &input) == -1) break;
    }

    if(a_sign == b_sign){
        // add case
        result_sign = a_sign;
        bool carry = false;
        int val;
        while(a_len > 0 && b_len > 0){
            val = (a_abs[a_len-1] - '0') + (b_abs[b_len-1] - '0') + (carry ? 1 : 0);
            if(val > 9){
                carry = true;
                val = val - 10;
            } else carry = false;
            result[result_len] = val;
            result_len++;
            a_len--;
            b_len--;
        }
        while(a_len > 0){
            val = (a_abs[a_len-1] - '0') + (carry ? 1 : 0);
            if(val > 9){
                carry = true;
                val = val - 10;
            } else carry = false;
            result[result_len] = val;
            result_len++;
            a_len--;
        }
        while(b_len > 0){
            val = (b_abs[b_len-1] - '0') + (carry ? 1 : 0);
            if(val > 9){
                carry = true;
                val = val - 10;
            } else carry = false;
            result[result_len] = val;
            result_len++;
            b_len--;
        }
        if(carry){
            result[result_len] = 1;
            result_len++;
        }
    } else {
        // subtract case
        char *bigger, *smaller;
        int biggerPos, smallerPos;
        if(a_len > b_len) {
            bigger = a_abs;
            smaller = b_abs;
            biggerPos = a_len;
            smallerPos = b_len;
            result_sign = a_sign;
        } else if(a_len < b_len) {
            bigger = b_abs;
            smaller = a_abs;
            biggerPos = b_len;
            smallerPos = a_len;
            result_sign = b_sign;
        } else {
            int temp = 0;
            bool different = false;
            while(temp < a_len){
                if(a_abs[temp] != b_abs[temp]){
                    different = true;
                    if(a_abs[temp] > b_abs[temp]){
                        bigger = a_abs;
                        smaller = b_abs;
                        biggerPos = a_len;
                        smallerPos = b_len;
                        result_sign = a_sign;
                    } else if(a_abs[temp] < b_abs[temp]){
                        bigger = b_abs;
                        smaller = a_abs;
                        biggerPos = b_len;
                        smallerPos = a_len;
                        result_sign = b_sign;
                    }
                    break;
                }
                temp++;
            }
            if(!different){ // a = -b
                printf("0\n");
                return 0;
            }
        }

        bool carry = false;
        int val;
        while(smallerPos > 0){
            val = (bigger[biggerPos-1] - '0') - (smaller[smallerPos-1] - '0') + (carry ? -1 : 0);
            if(val < 0){
                carry = true;
                val = val + 10;
            } else carry = false;
            result[result_len] = val;
            result_len++;
            biggerPos--;
            smallerPos--;
        }
        while(biggerPos > 0){
            val = (bigger[biggerPos-1] - '0') + (carry ? -1 : 0);
            if(val < 0){
                carry = true;
                val = val + 10;
            } else carry = false;
            result[result_len] = val;
            result_len++;
            biggerPos--;
        }
    }

    while(result[result_len-1] == 0 && result_len > 0){
        result_len--;
    }

    if(result_len == 0){
        printf("0\n");
        return 0;
    }

    if(!result_sign) printf("-");
    for(int i=result_len - 1; i>=0; i--){
        printf("%d",result[i]);
    }
    printf("\n");
}