#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        char S[1001];
        scanf("%s", S);
        
        int sum = 0;
        for (int i = 0; S[i] != '\0'; i++) {
            if (S[i] >= '0' && S[i] <= '9') {
                sum += S[i] - '0';
            }
        }
        printf("%d\n", sum);
    }
    
    return 0;
}
