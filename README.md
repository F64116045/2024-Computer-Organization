# 2024計算機組織作業紀錄
環境使用 **Ubuntu 22.04**，並安裝下列工具：

- [`riscv-gnu-toolchain`](https://github.com/riscv-collab/riscv-gnu-toolchain)
- [`riscv-isa-sim`](https://github.com/riscv-software-src/riscv-isa-sim)
- [`riscv-pk`](https://github.com/riscv-software-src/riscv-pk)

測試指令example：
```bash
$ riscv64-unknown-linux-gnu-gcc -static -o hello hello.c
$ spike --isa=RV64GC /opt/riscv/riscv64-unknown-linux-gnu/bin/pk hello
```

## Homework 1 
μRISC-V: An Enhanced RISC-V Processor Design using Spike
### `1.c` - 基本除法運算
讀入兩整數 `a, b`，透過 RISC-V 的 `div` 指令完成 `a / b`：


### `2.c` - 陣列元素除法
執行 `c[i] = a[i] / b[i]`，使用指標與組語進行迴圈計算與遞增：


### `3.c` - 矩陣乘向量（內層迴圈）
以三層巢狀迴圈實作矩陣 `h[3x3]` 乘向量 `x[2x3]`，輸出為 `y[3x2]`，僅將最內層乘加運算改為 inline assembly，並透過標籤與 `beq` 實現分支邏輯與條件跳轉。


### `4.c` - 矩陣乘向量（完整迴圈）
完全以 inline assembly 取代三層巢狀迴圈邏輯，包括 index 變數初始化、條件判斷、記憶體位移與加總操作：
```asm
li %[i], 0
loop1:
  ...
  bne %[i], t5, loop1
```
學習以組語完整模擬 C 語言控制流程。

## Homework 2
Performance Modeling for the μRISC-V Processor
透過撰寫 inline assembly 並插入計數器，統計各類指令數量並計算週期與 CPU 時間，進一步判斷程式為 CPU-bound 或 Memory-bound。
### `pi.c`
- 以 RV64I 組語實作 Gregory-Leibniz π 計算迴圈。

### `arraymul_baseline.c`
- 以 RV64I 組語實作逐項陣列乘法 `y[i] = h[i] * x[i] + id`。
- 每次迴圈處理一筆資料，為 baseline（未加速）版本。
- 記錄指令計數以分析效能瓶頸。

### `arraymul_improved_version1.c`
- 使用 RISC-V V extension（vlen=128）向量化處理。
- 同步處理多筆陣列資料以加速乘法與加法。
- 利用 `vle16.v`, `vmul.vv`, `vadd.vv`, `vse16.v` 等向量指令。

### `arraymul_improved_version2.c`
- 延續 version1 實作，但使用 vlen=256 配置。

## Homework 3
Reducing Memory Access Overhead for the μRISC-V Processor
##  FIFO Cache Replacement Policy

- 修改 `cachesim.h` 與 `cachesim.cc`
- 原本使用亂數（LFSR）替換策略
- 改為每個 set 維護一個 FIFO queue（`std::vector<std::queue<size_t>>`）
- `victimize()` 中總是替換最早進入的 way


##  Q1: Convolution - `conv2d-better.S`

> RV64I ，改寫 2D 卷積計算流程
原本的 `conv2d.S` 的 i/j 迴圈順序為 j 外、i 內（不利於 row-major 的資料排列）
- 重寫整體迴圈結構，明確以 `i` 為外層、`j` 為內層迴圈，更符合 cache-friendly 存取
有助於減少 cache miss。

## Q2： Matrix Multiplication - `mm-better.c`

### `mm.c`
- 一般 triple loop：x, y, z
- 每次都整個 row × col，cache reuse 效果差
- 沒有 blocking，造成 memory 重複 load

### `mm-better.c`
- 利用區塊操作增加資料 reuse 機會
- 減少跨 row 與 col 的 cache line reload
- Blocking 範圍依 cache 尺寸調整 (這邊定BLOCK_SIZE = 8 )
