/**
 * ICPC REFERENCE SHEET: std::bitset & Optimizations
 * Target: ICPC Regional / National
 * Complexity: Bitwise operations run in O(N / 64) on 64-bit architectures
 * Indexing: 0-indexed from RIGHT (LSB) to LEFT (MSB)
 */

#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// 1. CÚ PHÁP CƠ BẢN VÀ CÁC METHOD
// ============================================================================
void bitset_cheat_sheet() {
    const int N = 8;

    // --- Khởi tạo (Initialization) ---
    bitset<N> b1;                    // [00000000] Mặc định toàn 0
    bitset<N> b2(42);                // [00101010] Khởi tạo từ số nguyên
    bitset<N> b3(0b00101010);        // [00101010] Binary literal (C++14)
    bitset<N> b4(string("1011"));    // [00001011] Khởi tạo từ chuỗi std::string
    bitset<N> b5("1011");            // [00001011] Khởi tạo từ const char*

    // --- Truy cập & Kiểm tra (Access & Check) ---
    b2[0] = 1;                       // Gán/đọc bit tại index 0 (không bounds check)
    bool val = b2.test(2);           // Đọc bit 2 (ném std::out_of_range nếu tràn)
    int total_bits = b2.size();      // 8
    int set_bits   = b2.count();     // Đếm số lượng bit 1 (popcount)
    bool is_all    = b2.all();       // true nếu tất cả bit đều là 1
    bool is_any    = b2.any();       // true nếu có ít nhất một bit 1
    bool is_none   = b2.none();      // true nếu toàn bộ bit đều là 0

    // --- Thay đổi giá trị (Modifiers) ---
    b1.set();                        // Bật toàn bộ thành 1
    b1.set(3, false);                // Đặt bit 3 thành 0
    b1.reset();                      // Tắt toàn bộ về 0
    b1.reset(2);                     // Đặt bit 2 về 0
    b1.flip();                       // Đảo toàn bộ bit (0 <-> 1)
    b1.flip(1);                      // Đảo riêng bit 1

    // --- Chuyển đổi (Conversion) ---
    string s = b2.to_string();       // Chuyển thành string "00101011"
    unsigned long ul = b2.to_ulong();// Ép kiểu số nguyên (ném overflow nếu > 32/64 bit)
    unsigned long long ull = b2.to_ullong();

    // --- Nhập/Xuất & Toán tử (Operators & I/O) ---
    // cin >> b1; cout << b1 << '\n';
    bitset<N> res_and = b2 & b4;     // AND
    bitset<N> res_or  = b2 | b4;     // OR
    bitset<N> res_xor = b2 ^ b4;     // XOR
    bitset<N> res_not = ~b2;         // NOT (tạo bản sao)
    bitset<N> shift_l = b2 << 2;     // Dịch trái 2 bit
    bitset<N> shift_r = b2 >> 1;     // Dịch phải 1 bit
    bool eq = (b2 == b4);            // So sánh bằng/khác (không hỗ trợ < > <= >=)
}

// ============================================================================
// 2. MẸO DUYỆT BIT 1 SIÊU TỐC TRONG ICPC (GCC EXTENSIONS)
// ============================================================================
void fast_iteration_example() {
    bitset<100> b;
    b.set(5); b.set(20); b.set(88);

    // _Find_first() và _Find_next(i) chạy ở mức bit-level, nhảy qua các block 64 bit
    for (int i = b._Find_first(); i < (int)b.size(); i = b._Find_next(i)) {
        // Xử lý các index có bit 1: 5, 20, 88
        // cout << i << " ";
    }
}

// ============================================================================
// 3. ỨNG DỤNG 1: TỐI ƯU 0/1 KNAPSACK / SUBSET SUM (O(N * W / 64))
// ============================================================================
// Cho mảng các phần tử, kiểm tra những tổng nào <= MAX_W có thể tạo được.
const int MAX_W = 1000005;
bitset<MAX_W> dp;

void knapsack_optimization(const vector<int>& weights) {
    dp.reset();
    dp[0] = 1; // Tổng = 0 luôn tạo được

    for (int w : weights) {
        dp |= (dp << w); // Dịch toàn bộ bitset sang trái w và OR lại
    }

    // dp[X] == 1 nghĩa là có thể tạo được tổng bằng X
}

// ============================================================================
// 4. ỨNG DỤNG 2: SÀNG NGUYÊN TỐ TIẾT KIỆM BỘ NHỚ
// ============================================================================
// bitset<1e8> chỉ tốn ~12 MB RAM (vector<bool> tốn nhiều overhead hơn)
const int MAX_PRIME = 100000000;
bitset<MAX_PRIME + 1> is_prime;

void bitset_sieve() {
    is_prime.set(); // Giả định tất cả là số nguyên tố
    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; 1LL * i * i <= MAX_PRIME; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_PRIME; j += i) {
                is_prime[j] = 0;
            }
        }
    }
}

// ============================================================================
// 5. ỨNG DỤNG 3: ĐẾM ĐƯỜNG ĐI ĐỘ DÀI 3 / TAM GIÁC TRÊN ĐỒ THỊ (O(V^3 / 64))
// ============================================================================
const int MAX_V = 2005;
bitset<MAX_V> adj[MAX_V]; // Ma trận kề bằng bitset

long long count_triangles(int n) {
    long long triangles = 0;
    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (adj[u][v]) {
                // Đếm số đỉnh w kề với cả u và v trong O(V / 64)
                triangles += (adj[u] & adj[v]).count();
            }
        }
    }
    return triangles / 3; // Mỗi tam giác bị đếm 3 lần
}

int main() {
    // Tối ưu I/O chuẩn cho ICPC
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bitset_cheat_sheet();
    fast_iteration_example();

    return 0;
}