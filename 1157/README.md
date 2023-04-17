```
Design a data structure that efficiently finds the majority element of a given subarray.

The majority element of a subarray is an element that occurs threshold times or more in the subarray.

Implementing the MajorityChecker class:

MajorityChecker(int[] arr) Initializes the instance of the class with the given array arr.
int query(int left, int right, int threshold) returns the element in the subarray arr[left...right] that occurs at least threshold times, or -1 if no such element exists.
 

Example 1:

Input
["MajorityChecker", "query", "query", "query"]
[[[1, 1, 2, 2, 1, 1]], [0, 5, 4], [0, 3, 3], [2, 3, 2]]
Output
[null, 1, -1, 2]

Explanation
MajorityChecker majorityChecker = new MajorityChecker([1, 1, 2, 2, 1, 1]);
majorityChecker.query(0, 5, 4); // return 1
majorityChecker.query(0, 3, 3); // return -1
majorityChecker.query(2, 3, 2); // return 2
 

Constraints:

1 <= arr.length <= 2 * 104
1 <= arr[i] <= 2 * 104
0 <= left <= right < arr.length
threshold <= right - left + 1
2 * threshold > right - left + 1
At most 104 calls will be made to query.
```

## 题面
计算区间绝对众数

## 摩尔投票
摩尔投票法（Moore Voting Algorithm）是一种用于寻找数组中出现次数超过一半的元素的算法。该算法的基本思想是，假设数组中有一个元素出现次数超过一半，则可以通过遍历数组并对相同的元素进行计数的方式来找到这个元素。

算法的具体实现如下：

1. 初始化候选元素为数组的第一个元素，计数器为1。
2. 遍历数组，对于每个元素，如果它与候选元素相同，则将计数器加1，否则将计数器减1。
3. 如果计数器变为0，则将当前元素设为候选元素，并将计数器设为1。
4. 遍历结束后，所选的候选元素即为出现次数超过一半的元素。
该算法的时间复杂度为 O(n)，空间复杂度为 O(1)。该算法可以应用于需要寻找出现次数超过一半的元素的场景，如多数元素问题、电子投票问题等。

```cpp
int majorityElement(vector<int>& nums) {
    int m = -1, cnt = -1;// m 元素  cnt出现次数
    for (int x : nums) {
        if (x == m) {
            cnt++;
        }
        else {
            cnt--;
            if (cnt <= 0) {
                m = x;
                cnt = 1;
            }
        }
    }
    return m;
}
```

线段树不能维护众数，但是在这里，可以维护绝对众数。

要使用线段树，需要元线段可累加，对这道题目，可以使用摩尔投票法对元线段进行累加。
令元素的值为val，元素的个数为count
```
（val1, count1） + （val2, count2） =
（val1, count1+count2） cond val1 == val2
（val1, count1-count2） cond val1 != val2 && count1 > count2
（val2, count2-count1） cond val1 != val2 && count2 > count1
```
这样建立完树后，就可以使用线段树的查找操作，直接找到区间内的众数的值。

Query查询时，得到某个被包含的子区间，也是将当前区间和之前区间做同样的合并。
如果区间中没有一个绝对众数，那么最后得到的$m$可以理解为是”随机“的。
所以呢,我们得到$m$后，还需要具体的查询$m$在区间中出现了多少次。
那么我们可以利用二分upper_bound 减去 lower_bound 来获得出现次数。