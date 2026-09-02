int totalHammingDistance(int* nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < 31; i++) {
        int c = 0;
        for (int j = 0; j < numsSize; j++) {
            c += (nums[j] >> i) & 1;
        }
        total += c * (numsSize - c);
    }
    return total;
}
