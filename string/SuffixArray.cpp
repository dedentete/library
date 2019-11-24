struct SuffixArray{
    int n;
    string s;
    vector<int> sa;
    
    SuffixArray(const string &s) : s(s) {
        s.push_back('$');
        sa.resize(n + 1);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b){ if(s[a] == s[b]) return a > b; return s[a] < s[b]; });
        vector<int> cs(n + 1, 0), rs(n + 1), cnt(n + 1);
        for(int i = 0; i <= n; i++) rs[i] = s[i];
        for(int len = 1; len <= n; len *= 2){
            for(int i = 0; i <= n; i++){
                cs[sa[i]] = i;
                if(i > 0 && rs[sa[i - 1]] == rs[sa[i]] && sa[i - 1] + len <= n && rs[sa[i - 1] + len / 2] == rs[sa[i] + len / 2]) cs[sa[i]] = cs[sa[i - 1]];
            }
            iota(cnt.begin(), cnt.end(), 0);
            copy(sa.begin(), sa.end(), rs.begin());
            for(int i = 0; i <= n; i++){
                int s1 = rs[i] - len;
                if(s1 >= 0) sa[cnt[cs[s1]]++] = s1;
            }
            cs.swap(rs);
        }
    }

    int operator[](int i) const{ return sa[i]; }

    bool lt_substr(string & t, int si = 0, int ti = 0){
        int sn = n, tn = t.size();
        while(si < sn && ti < tn){
            if(s[si] < t[ti]) return true;
            if(s[si] > t[ti]) return false;
            si++;
            ti++;
        }
        return si >= sn && ti < tn;
    }

    int lower_bound(string & t){
        int low = -1, high = n + 1;
        while(high - low > 1){
            int mid = (low + high) / 2;
            if(lt_substr(t, sa[mid])) low = mid;
            else high = mid;
        }
        return high;
    }

    int upper_bound(string & t){
        t.back()++;
        int res = lower_bound(t);
        t.back()--;
        return res;
    }

    int count(string & t){
        return upper_bound(t) - lower_bound(t);
    }
};