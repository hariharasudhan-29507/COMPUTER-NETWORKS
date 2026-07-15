int findMaximumXOR(int* nums, int numsSize) {
    int max = 0;

    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            int temp = nums[i] ^ nums[j];
            if (temp > max)
                max = temp;
        }
    }

    return max;
};
