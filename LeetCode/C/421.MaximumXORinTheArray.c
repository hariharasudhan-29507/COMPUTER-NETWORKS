typedef struct Node {
    struct Node *child[2];
} Node;

Node* createNode() {
    Node *node = malloc(sizeof(Node));
    node->child[0] = NULL;
    node->child[1] = NULL;
    return node;
}

void insert(Node *root, int num) {
    Node *cur = root;

    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;

        if (cur->child[bit] == NULL)
            cur->child[bit] = createNode();

        cur = cur->child[bit];
    }
}

int findMaximumXOR(int* nums, int numsSize) {
    Node *root = createNode();

    for (int i = 0; i < numsSize; i++)
        insert(root, nums[i]);

    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        Node *cur = root;
        int value = 0;

        for (int j = 31; j >= 0; j--) {
            int bit = (nums[i] >> j) & 1;

            if (cur->child[1 - bit]) {
                value |= (1 << j);
                cur = cur->child[1 - bit];
            } else {
                cur = cur->child[bit];
            }
        }

        if (value > ans)
            ans = value;
    }

    return ans;
}
