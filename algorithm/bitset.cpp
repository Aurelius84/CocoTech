/*
* 描述: 实现一个bitSet数据结构
*/

#include <stdlib.h>
#include <cstring>

using uint32 = unsigned int;

class BitSet {
    private:
     uint32 m_size; // size in bit
     uint32 m_bytes; // size in bytes
     unsigned char* m_bits; //the bits

    public:
    // char是1个字节，8bit
     BitSet(uint32 num_bits) {
         m_bytes = num_bits / 8 + 1; // +1是为了兼容有余数的情况
         m_size = m_bytes * 8;  // 总位数，有buffer
         m_bits = new unsigned char[m_bytes]; // 底层用char来保存
         memset(m_bits, 0, m_bytes);  // 初始化为0
     }

     ~BitSet() { delete[] m_bits; }

    private:
     BitSet(const BitSet&);
     BitSet& operator=(const BitSet&);

    public:
        inline void set(uint32 bit){
          // 如果超过了总位数，则设置无效
          if (bit >= m_size) return;
          uint32 n = bit / 8;
          uint32 off = bit % 8;
          // 10000000 左移2位是 00100000，与之前的值进行或运算
          m_bits[n] |= 128U >> off;
        }

        inline void unset(uint32 bit){
          if (bit >= m_size) return;

          uint32 n = bit / 8;
          uint32 off = bit % 8;
          // 10000000 左移2位再取非 11011111，与之前的值进行与运算
          m_bits[n] &= ~(128U >> off);
        }
};

int main() {
  // 实际会有 16/8 + 1 = 3字节的空间占用
  BitSet bitset(16);
  return 0;
}