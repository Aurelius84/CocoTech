/*
* 描述：用1D的array实现一下2D array的基本操作
*      包括：row、col、元素访问等
*/
#include <iostream>

using uint32 = unsigned int;

template <typename T=char>
class Array2D {
    private:
     uint32 NR;    // rows
     uint32 NC;    // cols
     T* m_data;

    public:
     Array2D(uint32 nrow, uint32 ncol) : NR(nrow), NC(ncol) {
       m_data = new T[nrow * ncol];
     }

        ~Array2D() { delete[] m_data; }

    private:
     Array2D(const Array2D&); // 不允许复制和赋值构造
     Array2D& operator=(const Array2D&);

    public:
     // 声明为const func const
     const inline uint32 row() const { return NR; }
     const inline uint32 col() const { return NC; }

     const inline uint32 numel() const { return NR * NC; }

     //这里应该做一些越界检查
     inline int& operator()(int row, int col) { return m_data[row * NC + col]; }
     // 这里的设计有点不友好，x(2, 3) = 4 不如 x[2, 3] = 4
     const inline int& operator()(int row, int col) const {
       return m_data[row * NC + col];
     }

     // 返回某一行数据头指针
     inline int* operator[](int row) { return &(m_data[row * NC]); }

     const inline T* operator[](int row) const { return &(m_data[row * NC]); }

     void clear(const int& value) {
       // overflow??
       for (uint32 i = 0; i < NC * NR; i++) {
         m_data[i] = value;
       }
     }
};

int main() {
    Array2D<int> x(3, 5);
    std::cout << x.row()<< "\n";
    x.clear(3);
    std::cout << x(2, 3)<<"\n";
    x(2, 3) = 4;
    std::cout << x(2, 3)<<"\n";
    return 0;
}