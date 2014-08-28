#define MS(x, y) memset(x, y, sizeof(x))
#define FOR(i, x, y) for(int i=x; i<=y; i++)
#define rFOR(i, x, y) for(int i=x; i>=y; i--)

struct bigint
{
    int s[maxn];

    bigint() {MS(s, 0);}
    bigint(int num) {*this = num;}
    bigint(const char* num) {*this = num;}

    bigint operator = (const char* num)
    {
        MS(s, 0);
        if (num[0] == '-')
        {
            num = num + 1;
            s[0] = -1;
        }
        else s[0] = 1;
        while (num[0] == '0') num = num + 1;
        s[0] = s[0] * strlen(num);
        int len = abs(s[0]);
        FOR(i, 1, len) s[i] = num[len - i] - 48;
        return *this;
    }
    bigint operator = (int num)
    {
        char s[maxn];
        sprintf(s, "%d", num);
        *this = s;
        return *this;
    }

    string str() const
    {
        string res = "";
        FOR(i, 1, abs(s[0])) res = (char)(s[i] + 48) + res;
        if (res == "") return res = "0";
        if (s[0] < 0) res = '-' + res;
        return res;
    }

    bool operator < (const bigint& b) const
    {
        if (s[0] != b.s[0]) return s[0] < b.s[0];
        int len = abs(s[0]);
        rFOR(i, len, 1)
        if (s[i] != b.s[i])
            return (s[i] < b.s[i]) ^ (s[0] < 0);
        return false;
    }
    bool operator > (const bigint& b) const {return b < *this;}
    bool operator <= (const bigint& b) const {return !(b < *this);}
    bool operator >= (const bigint& b) const {return !(*this < b);}
    bool operator != (const bigint& b) const {return b < *this || *this < b;}
    bool operator == (const bigint& b) const {return !(b < *this) && !(*this < b);}

    friend bigint abs(bigint b)
    {
        b.s[0] = abs(b.s[0]);
        return b;
    }
    friend bigint _add(const bigint& a, const bigint& b)
    {
        bigint c;
        c.s[0] = max(a.s[0], b.s[0]);
        FOR(i, 1, c.s[0]) c.s[i] = a.s[i] + b.s[i];
        FOR(i, 1, c.s[0])
        if (c.s[i] >= 10)
        {
            c.s[i + 1]++;
            c.s[i] -= 10;
        }
        if (c.s[c.s[0] + 1]) ++c.s[0];
        return c;
    }
    friend bigint _sub(const bigint& a, const bigint& b)
    {
        bigint c;
        c.s[0] = a.s[0];
        FOR(i, 1, c.s[0]) c.s[i] = a.s[i] - b.s[i];
        FOR(i, 1, c.s[0])
        if (c.s[i] < 0)
        {
            c.s[i + 1]--;
            c.s[i] += 10;
        }
        while (!c.s[c.s[0]] && c.s[0]) --c.s[0];
        return c;
    }
    bigint operator + (const bigint& b) const
    {
        if (s[0] >= 0 && b.s[0] >= 0) return _add(*this, b);
        if (b.s[0] < 0) return *this - abs(b);
        if (s[0] < 0) return b - abs(*this);
    }
    bigint operator - (const bigint& b) const
    {
        if (s[0] >= 0 && b.s[0] >= 0)
        {
            bigint c;
            if (*this >= b) return _sub(*this, b);
            c = _sub(b, *this);
            c.s[0] = -c.s[0];
            return c;
        }
        if (b.s[0] < 0) return *this + abs(b);
        if (s[0] < 0)
        {
            bigint c;
            c = abs(*this) + b;
            c.s[0] = -c.s[0];
            return c;
        }
    }
    bigint operator * (const bigint
                       & b) const
    {
        bigint c;
        c.s[0] = abs(s[0]) + abs(b.s[0]);
        FOR(i, 1, abs(s[0]))
        FOR(j, 1, abs(b.s[0]))
        c.s[i + j - 1] += s[i] * b.s[j];
        FOR(i, 1, c.s[0])
        {
            c.s[i + 1] += c.s[i] / 10;
            c.s[i] %= 10;
        }
        while (!c.s[c.s[0]] && c.s[0]) --c.s[0];
        if ((s[0] > 0) != (b.s[0] > 0)) c.s[0] = -c.s[0];
        return c;
    }
    bigint operator / (const bigint& _b) const
    {
        bigint c, t;
        bigint b = abs(_b);
        c.s[0] = abs(s[0]);
        rFOR(i, c.s[0], 1)
        {
            rFOR(j, t.s[0], 1) t.s[j + 1] = t.s[j];
            t.s[1] = s[i];
            if (t.s[t.s[0] + 1])t.s[0]++;

            while (t >= b)
            {
                ++c.s[i];
                t -= b;
            }
        }
        while (!c.s[c.s[0]] && c.s[0]) --c.s[0];
        if ((s[0] > 0) != (b.s[0] > 0)) c.s[0] = -c.s[0];
        return c;
    }
    bigint operator % (const bigint& _b) const
    {
        bigint c, t;
        bigint b = abs(_b);
        rFOR(i, abs(s[0]), 1)
        {
            rFOR(j, t.s[0], 1) t.s[j + 1] = t.s[j];
            t.s[1] = s[i];
            if (t.s[t.s[0] + 1])t.s[0]++;

            while (t >= b) t -= b;
        }
        if ((s[0] < 0)) t.s[0] = -t.s[0];
        return t;
    }

    bigint operator += (const bigint& b) {*this = *this + b; return *this;}
    bigint operator -= (const bigint& b) {*this = *this - b; return *this;}
    bigint operator *= (const bigint& b) {*this = *this * b; return *this;}
    bigint operator /= (const bigint& b) {*this = *this / b; return *this;}
    bigint operator %= (const bigint& b) {*this = *this % b; return *this;}

    friend bigint operator + (int& a, const bigint& b) {return (bigint)a + b;}
    friend bigint operator - (int& a, const bigint& b) {return (bigint)a - b;}
    friend bigint operator * (int& a, const bigint& b) {return (bigint)a * b;}
    friend bigint operator / (int& a, const bigint& b) {return (bigint)a / b;}
    friend bigint operator % (int& a, const bigint& b) {return (bigint)a % b;}

    friend bigint operator <  (int& a, const bigint& b) {return (bigint)a < b;}
    friend bigint operator <= (int& a, const bigint& b) {return (bigint)a <= b;}
    friend bigint operator >  (int& a, const bigint& b) {return (bigint)a > b;}
    friend bigint operator >= (int& a, const bigint& b) {return (bigint)a >= b;}
    friend bigint operator == (int& a, const bigint& b) {return (bigint)a == b;}
    friend bigint operator != (int& a, const bigint& b) {return (bigint)a != b;}
};
istream& operator >> (istream &in, bigint& x)
{
    string s;
    in >> s;
    x = s.c_str();
    return in;
}
ostream& operator << (ostream &out, const bigint& x)
{
    out << x.str();
    return out;
}

