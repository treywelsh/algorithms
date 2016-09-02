#!/usr/bin/env python


def permute(nums):
    for i in range(len(nums)-1):
                
            for j in range(i+1, len(nums)):
                numscpy = nums[:]
                numscpy[j], numscpy[i] = numscpy[i], numscpy[j]
                print numscpy

if __name__=="__main__":
    permute([1, 2, 3])
