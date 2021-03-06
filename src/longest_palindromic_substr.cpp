/*
 * longest_palindromic_substr.cpp
 *
 *  Created on: Jun 13, 2018
 *      Author: mihir
 */

// https://leetcode.com/problems/longest-palindromic-substring/description/

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        const int n = s.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(n + 1, false));
        for (int i = 0; i < n; ++i) dp[i][i] = true;
        int longest = 0, begin = 0, end = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                cout << "i: " << i << ", j: " << j << "\n";
                dp[i][j] = ((s[i] == s[j]) && (j - i < 2 || dp[i + 1][j - 1]));
                if (dp[i][j] && j - i + 1 > longest)
                {
                    longest = j - i + 1;
                    begin = i; end = j;
                    cout << "begin: " << begin << ", end: " << end << "\n";
                }
            }
        }
        return n ? s.substr(begin, end - begin + 1) : "";
    }
};

using palin_pair = pair<int, int>;

// This function builds upon the initial seed passed from its callee.
// If we are crossing the bounds of the string or the left/right chars
// don't match, then we stop the recursion there. Otherwise, we add the
// left/right char's to the existing seed to build a larger palindrome
// and call recursively to repeat the same steps again.
palin_pair check_palindrome(const string& s, int left, int right)
{
	if (left < 0 || right >= s.length() || s[left] != s[right]) return make_pair(left+1, right-1);
	return check_palindrome(s, left-1, right+1);
}

string longest_palindromic_substr(const string& s)
{
	size_t len = s.length();
	// Handle strings of length 0/1/2 as a special case
	if (len <= 1 || (len == 2 && s[0] == s[1])) return s;
	if (len == 2) return "";

	palin_pair t, r;
	int max_size = 0, left, right;
	for (int i = 1; i < s.length() - 1; ++i)
	{
		// Each char by itself is a palindrome.
		// But we try to be greedy here. Match as many occurances of that char
		// as possible. This becomes the initial seed to our check_palindrome
		// function.
		for (left = i-1; s[left] == s[i]; --left);
		for(right = i+1; s[right] == s[i]; ++right);
		t = check_palindrome(s, left, right);

		// Only store the largest palindrome
		if (1 + t.second - t.first > max_size)
		{
			max_size = 1 + t.second - t.first;
			r = t;
		}
	}

	// if we found a palindrome >0 size, then return it here
	return max_size ? s.substr(r.first, 1 + r.second - r.first) : "";
}

int main()
{
    Solution o;
    string res = o.longestPalindrome("cbbd");
    cout << "res: " << res << "\n";
    return 0;
}
