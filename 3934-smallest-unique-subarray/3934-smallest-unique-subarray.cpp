using ll = long long;

class Solution {
    static pair<int, int> kmpBounds(const vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> rev(nums.rbegin(), nums.rend());
        vector<int> pi(n, 0);
        int longest = 0;
        int matched = 0;

        for (int i = 1; i < n; ++i) {
            int val = rev[i];
            while (matched > 0 && val != rev[matched]) {
                matched = pi[matched - 1];
            }
            if (val == rev[matched]) {
                ++matched;
            }
            pi[i] = matched;
            if (matched > longest) {
                longest = matched;
            }
        }

        int period = n - pi.back();
        int first = (n > 2 * period) ? (n - 2 * period + 2) : 2;
        int upper = min(longest + 1, max(period, first));
        return {first, upper};
    }

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        constexpr ll MOD = 1000000007LL;
        constexpr ll BASE = 911382323LL;

        int n = (int)nums.size();
        
        unordered_map<int, int> freq;
        freq.reserve(n);
        for (int x : nums) {
            ++freq[x];
        }
        for (const auto& [_, count] : freq) {
            if (count == 1) {
                return 1;
            }
        }

        auto [first, upper] = kmpBounds(nums);
        if (first >= upper) {
            return first;
        }

        vector<ll> h(n + 1);
        vector<ll> p(n + 1);
        p[0] = 1;

        
        for (int i = 0; i < n; ++i) {
            h[i + 1] = (h[i] * BASE + nums[i]) % MOD;
            p[i + 1] = p[i] * BASE % MOD;
        }

        auto check = [&](int len) {
            unordered_map<ll, int> cnt;

            for (int l = 0; l + len <= n; ++l) {
                int r = l + len;

                ll key = (h[r] - h[l] * p[len] % MOD + MOD) % MOD;
                ++cnt[key];
            }

            for (auto& [key, times] : cnt) {
                if (times == 1) {
                    return true;
                }
            }
            return false;
        };

        int lo = first, hi = upper;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return lo;
    }
};