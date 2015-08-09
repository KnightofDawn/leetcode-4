/*
����˼·��
1. �����ֵǰ�����Щ��û�г�Ϊ���ֵ�Ļ��ᣬ���������ٿ���
2. ���ö�k�������������ֵֻҪ���ϴ����ֵ�ĺ�һ������һ��Ϳ���
3. ƽ��״�����ã������������ϵݼ����У����Ӷ�ΪO(k*n)
*/
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int* res = malloc(sizeof(int) * numsSize);
    (* returnSize) = 0;
    if (k == 0) return res;
    int maxindex = -1, i, j, max;
    for (i = k-1 ; i < numsSize ; i++) {
        if (maxindex != -1 && nums[i] >= nums[maxindex]) {
            max = nums[i];
            maxindex = i;
        }
        if (maxindex < i-k+1) {
            max = INT_MIN;
            for (j = maxindex + 1 ; j <= i ; j++) {
                if (nums[j] >= max) {
                    max = nums[j];
                    maxindex = j;
                }
            }
        }
        
        res[(* returnSize)++] = max;
    }
    return res;
}