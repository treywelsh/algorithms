#!/usr/bin/env python

#
# O((n+m)log(n)) time
# O(n) space
#

class Solution(object):
	def intersection(self, nums1, nums2):
		ret = [] 
		if len(nums2) > len(nums1):
			max_len = nums2
			min_len = nums1
		else:
			max_len = nums1
			min_len = nums2
		s1 = set(min_len)
		for n in list(max_len):
			if n not in s1:
				continue
			s1.remove(n)
			ret.append(n)
		return ret

def test_case(a, b):
    s = Solution()
    print str(a) + " inter " + str(b) + " = " + str(s.intersection(a,b))

if __name__ == '__main__':
    test_case([1, 2, 2, 1], [2, 2])
    test_case([1, 2, 1000, 4, 5, 6], [4, 1000])
    test_case([1], [1])
    test_case([1, 2, 3, 1, 2, 3], [2])
