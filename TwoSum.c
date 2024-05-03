#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);

int main(){
    int nums[] = {2, 7, 11, 15};
    int numsSize = 4;
    int targuet = 9;
    int returnSize[2];
    int *result;
    result = twoSum(nums, numsSize, targuet, returnSize);

    printf("%d", result[0]);
    printf("%d\n", result[1]);
    
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *output;
    output = (int *)malloc(2 * (sizeof(int)));
    if(output != NULL){
        for(int i = 0; i < numsSize - 1; i++){
            for(int j = i + 1; j < numsSize; j++){
                if(nums[i] + nums[j] == target){
                    output[0] = i;
                    output[1] = j;
                    break;
                }
            }
        }
    }else{
        printf("Nao foi encontrada memoria!");
    }
    *returnSize = 2;
    return output;
}