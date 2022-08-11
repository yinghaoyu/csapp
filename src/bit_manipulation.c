#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

// 归纳论证
// aaaaaaa10000
//      ↓ 取反，a，b之间互相为反
// bbbbbbb01111
//      ↓ 加1
// bbbbbbb10000
//      &
// aaaaaaa10000
//      ↓
// 000000010000
uint64_t lowBit(uint64_t x) {
  // opposite(x) = 1 + (~x)
  // lowBit(x) = x & (-x)
  return x & (1 + (~x));
}

// 设x3 x2 x1 x0为16进制数的位
//
//          x3x2
//          00 01 10 11
//      00  0  0  0  1
// x1x0 01  0  0  0  1    --> 根据卡诺图，可以知道x3 = 1，x2 = 1 该位一定是字符
//      10  0  0  1  1                            x3 = 1, x1 = 1 该位一定是字符
//      11  0  0  1  1                            化简得 x & ( x1 | x2 )

uint64_t hexAllLetters(uint64_t x) {
  // 假设 x = 0x0f0f
  uint64_t x1 = (x & 0x2222222222222222) >> 1;
  uint64_t x2 = (x & 0x4444444444444444) >> 2;
  uint64_t x3 = (x & 0x8888888888888888) >> 3; // 左移是为了让x1，x2，x3同阶

  x = x3 & (x1 | x2); // 这一步让 x = 0x0f0f --> x = 0x0101，1表示该位置是字母
  x = x & (x >> 32); // 两两归并，直到剩余4位就是答案，因为一个16进制占4位
  x = x & (x >> 16);
  x = x & (x >> 8);
  x = x & (x >> 4);
  return x;
}

// 按两位分组，相邻分组两两相加得四位
// 再按四位分组，相邻分组两两相加得八位
// 以此类推直到算出32位的bitCount数量
uint64_t bitCount(uint64_t x) {
  uint64_t c;
  //  0x5555   =     0101 0101 0101 0101    2位一组
  //  0x3333   =     0011 0011 0011 0011    4位一组
  //  0x0f0f   =     0000 ffff 0000 ffff    8位一组
  c = (x & 0x5555555555555555) +
      ((x >> 1) & 0x5555555555555555); // 低位个数和高位个数相加
  c = (c & 0x3333333333333333) + ((c >> 2) & 0x3333333333333333);
  c = (c & 0x0f0f0f0f0f0f0f0f) + ((c >> 4) & 0x0f0f0f0f0f0f0f0f);
  c = (c & 0x00ff00ff00ff00ff) + ((c >> 8) & 0x00ff00ff00ff00ff);
  c = (c & 0x0000ffff0000ffff) + ((c >> 16) & 0x0000ffff0000ffff);
  c = (c & 0x00000000ffffffff) + ((c >> 32) & 0x00000000ffffffff);
  return c;
}

int main() {
  printf("%" PRIu64 "\n", hexAllLetters(0xffffffffffffffff));
  printf("%" PRIu64 "\n", hexAllLetters(0xfffffffffffffff0));
}
