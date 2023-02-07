inline char gc() {
    static const int BUF_SIZE = 1 << 22;
    static int Counts = 1 << 23;
    static char Buffer[BUF_SIZE];
    static char *Pointer = Buffer, *End = Buffer;
    if(Pointer == End) {
        if(Counts < BUF_SIZE) {
            return EOF;
        }
        Counts = fread(Buffer, 1, BUF_SIZE, stdin);
        Pointer = Buffer;
        End = Buffer + Counts;
    }
    return *(Pointer++);
}

template<class T>
inline void read(T& x) {
    static char c;
    do {
        c = gc();
    } while(c < '0' && c != '-');
    bool neg = (c == '-');
    if(!neg) {
        x = c - '0';
    } else x = 0;
    while((c = gc()) >= '0') {
        x = (x << 3) + (x << 1) + (c & 15);
    }
    if(neg) {
        x = -x;
    }
}

template<class T, class... U>
inline void read(T& a, U&... b) {
    read(a);
    read(b...);
}

template<class T>
inline void write(T temp, char end = '\n') {
    static short digits[20], P;
    if(temp == 0) {
        putchar_unlocked('0');
        putchar_unlocked(end);
        return;
    }
    if(temp < 0) {
        putchar_unlocked('-');
        write(-temp,end);
        return;
    }
    P = -1;
    while(temp) {
        digits[++P] = temp % 10;
        temp /= 10;
    }
    while(P >= 0) {
        putchar_unlocked(digits[P--] + '0');
    }
    putchar_unlocked(end);
    return;
}
