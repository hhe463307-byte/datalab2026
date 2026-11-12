/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitAnd - x & y using only ~ and |
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}


/*
 * bitXor - x ^ y using only ~ and &
 */
int bitXor(int x, int y) {
    return(~(~x&~y)&~(x&y)) ;
}


/*
 * samesign - 判断两个整数是否同号
 */
int samesign(int x, int y) {

    // x,y符号位
    int sx = x >> 31;
    int sy = y >> 31;

    /*
     * 0特殊处理：
     * 0和正数不同号
     * 0和负数不同号
     * 0和0同号
     */

    if (!x)
        return !y;

    if (!y)
        return 0;

    return !(sx ^ sy);
}


/*
 * logtwo - 求最高位1的位置
 * v > 0
 *
 * 例如:
 * 32 = 100000
 * 返回5
 */
int logtwo(int v) {

    int result = 0;
    int shift;


    shift = ((v >> 16) > 0) << 4;
    result = result | shift;
    v = v >> shift;


    shift = ((v >> 8) > 0) << 3;
    result = result | shift;
    v = v >> shift;


    shift = ((v >> 4) > 0) << 2;
    result = result | shift;
    v = v >> shift;


    shift = ((v >> 2) > 0) << 1;
    result = result | shift;
    v = v >> shift;


    shift = (v >> 1) > 0;
    result = result | shift;


    return result;
}
int byteSwap(int x, int n, int m) {

    int nShift = n << 3;
    int mShift = m << 3;

    int byteN = (x >> nShift) & 0xff;
    int byteM = (x >> mShift) & 0xff;

    int maskN = 0xff << nShift;
    int maskM = 0xff << mShift;

    x = x & ~maskN & ~maskM;

    x = x | (byteN << mShift)
          | (byteM << nShift);

    return x;
}
/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {

    unsigned mask1 = 0x55555555;
    unsigned mask2 = 0x33333333;
    unsigned mask3 = 0x0F0F0F0F;
    unsigned mask4 = 0x00FF00FF;

    // 交换相邻1 bit
    v = ((v >> 1) & mask1) |
        ((v & mask1) << 1);


    // 交换相邻2 bit
    v = ((v >> 2) & mask2) |
        ((v & mask2) << 2);


    // 交换相邻4 bit
    v = ((v >> 4) & mask3) |
        ((v & mask3) << 4);


    // 交换相邻8 bit
    v = ((v >> 8) & mask4) |
        ((v & mask4) << 8);


    // 交换左右16bit
    v = (v >> 16) |
        (v << 16);


    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {

    int shifted = x >> n;

    int mask = ~(((1 << 31) >> n) << 1);

    return shifted & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x)
{
    int count = 0;
    int n;
    int all;

    all = !(~x);

    n = !(~(x >> 16) & 0xFFFF) << 4;
    count = count + n;
    x = x << n;

    n = !(~(x >> 24) & 0xFF) << 3;
    count = count + n;
    x = x << n;

    n = !(~(x >> 28) & 0xF) << 2;
    count = count + n;
    x = x << n;

    n = !(~(x >> 30) & 0x3) << 1;
    count = count + n;
    x = x << n;

    n = !(~(x >> 31) & 1);
    count = count + n;

    return count + all;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000;
    unsigned abs = x;
    if (x < 0) abs = -x;
    if (!abs) return 0;

    int e = 31;
    while (!(abs >> e)) e = e - 1;

    unsigned exp = (e + 127) << 23;
    unsigned frac;

    if (e > 23) {
        int shift = e - 23;
        frac = (abs >> shift) & 0x7FFFFF;
        unsigned dropped = abs & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);

        if (dropped + (frac & 1) > half)
            frac = frac + 1;

        if (frac >> 23) {
            frac = 0;
            exp = exp + 0x800000;
        }
    } else {
        frac = (abs << (23 - e)) & 0x7FFFFF;
    }

    return sign | exp | frac;
}
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf)
{
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;


    // NaN / INF
    if (exp == 255)
        return uf;


    // 非规格化
    if (exp == 0) {
        frac <<= 1;
        return sign | frac;
    }


    // 普通浮点
    exp++;

    // exponent溢出变INF
    if (exp == 255)
        frac = 0;


    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2)
{
    int sign;
    int exp;
    int E;

    unsigned frac_high;
    unsigned frac_low;


    sign = uf2 >> 31;

    exp = (uf2 >> 20) & 0x7FF;

    E = exp - 1023;


    frac_high = uf2 & 0xFFFFF;
    frac_low = uf1;


    // 小于1
    if (E < 0)
        return 0;


    // 溢出
    if (E > 31)
        return 0x80000000;


    /*
     * 52位fraction + 隐藏1
     *
     * 根据E决定右移多少
     */


    unsigned result;


    if (E >= 32)
        return 0x80000000;


    if (E >= 52) {

        /*
         * 实际不会进入正常int范围
         */
        return 0x80000000;

    }
    else if (E >= 20) {


        /*
         * 高20位进入整数
         */

        result = frac_high | 0x100000;

        result = result << (E - 20);


    }
    else {


        /*
         * 只需要高部分右移
         */

        result = frac_high | 0x100000;

        result = result >> (20 - E);

    }


    if (sign)
        return -result;

    return result;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x)
{
    // 情况1：太大，超过float最大指数
    if (x > 127) {
        // +INF:
        // sign = 0
        // exp = 255
        // frac = 0
        return 0x7F800000;
    }


    // 情况2：规格化数
    // -126 <= x <= 127
    if (x >= -126) {

        /*
         * float:
         *
         * sign | exponent | fraction
         *
         * exponent = x + 127
         * fraction = 0
         */

        unsigned exp = x + 127;

        return exp << 23;
    }


    // 情况3：非规格化数
    // -149 <= x <= -127
    if (x >= -149) {

        /*
         * 非规格化：
         *
         * 0.fraction × 2^-126
         *
         * exponent = 0
         *
         * 需要让：
         *
         * fraction × 2^-126 = 2^x
         *
         */

        unsigned frac = 1 << (x + 149);

        return frac;
    }


    // 情况4：太小
    // x < -149

    return 0;
}
