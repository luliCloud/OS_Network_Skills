#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < n; i++) {
            if (board[0][i] == 'O') {
                floodEdge(board, 0, i);
            }
            if (board[m - 1][i] == 'O') {
                floodEdge(board, m - 1, i);
            }
        }
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') {
                floodEdge(board, i, 0);
            }
            if (board[i][n - 1] == 'O') {
                floodEdge(board, i, n - 1);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    flood(board, i, j);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'I') {
                    board[i][j] = 'O';
                }
            }
        }
    }

    void floodEdge(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return;
        }

        if (board[i][j] == 'I' || board[i][j] == 'X') {
            return;
        }

        board[i][j] = 'I';
        floodEdge(board, i + 1, j);
        floodEdge(board, i - 1, j);
        floodEdge(board, i, j + 1);
        floodEdge(board, i, j - 1);
    }

    void flood(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
            return;
        }

        if (board[i][j] == 'I' || board[i][j] == 'X') {
            return;
        }

        board[i][j] = 'X';
        flood(board, i + 1, j);
        flood(board, i - 1, j);
        flood(board, i, j + 1);
        flood(board, i, j - 1);
    }
};

int main() {
    vector<vector<char>> board = {
        {'X','O','X','O','X','O'},
        {'O','X','O','X','O','X'},
        {'X','O','X','O','X','O'},
        {'O','X','O','X','O','X'}
    };

    Solution s;
    s.solve(board);
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
/**
 * 注意每一行往后翻到最后才是程序对应的每一行（向右移动滚轴）
 * Ir (Instruction Read)
表示从内存中读取指令的次数。

I1mr (L1 Instruction Cache Miss Read)
表示读取指令时一级指令缓存（L1 Instruction Cache）未命中的次数。

ILmr (LL Instruction Cache Miss Read)
表示读取指令时最后级指令缓存（通常是L2或L3缓存）未命中的次数。

Dr (Data Read)
表示从内存中读取数据（非指令）的次数。

D1mr (L1 Data Cache Miss Read)
表示读取数据时一级数据缓存（L1 Data Cache）未命中的次数。
DLmr (LL Data Cache Miss Read)
表示读取数据时最后级数据缓存未命中的次数。

Dw (Data Write)
表示向内存写入数据的次数。
D1mw (L1 Data Cache Miss Write)
表示写入数据时一级数据缓存未命中的次数。
DLmw (LL Data Cache Miss Write)
表示写入数据时最后级数据缓存未命中的次数。


读取指令（Instruction Read）
定义：读取指令是指处理器从内存中读取执行代码的操作。这些代码包含了告诉处理器应该执行什么操作的指令。
用途：指令读取是程序执行的基础，每个执行的程序指令通常都需要从内存中读取。
处理流程：指令读取涉及指令缓存（如 L1i 缓存），处理器会尽量从缓存中读取指令，以减少访问主内存的延迟。如果缓存未命中，处理器会从更高级的缓存或最终从主内存中拉取指令。
优化：现代处理器设计中通常包括预取机制和指令缓存，以预测和加速接下来将执行的指令的加载过程。
读取数据（Data Read）
定义：读取数据指的是处理器为了执行指令而从内存中获取必要的数据（如变量、数组元素、对象属性等）的操作。
用途：数据读取支持处理器执行指令所需的数据操作，例如计算、条件判断、数据传递等。
处理流程：数据读取涉及数据缓存（如 L1d 缓存），处理器尝试从缓存中获取所需数据。如果缓存中没有数据，就会触发缓存未命中，然后从更高级的缓存或主内存中获取数据。
优化：为了减少缓存未命中和提高数据访问效率，开发者需要关注数据结构的设计和内存访问模式，如避免大规模的随机访问和优化数据局部性。
 * -- Auto-annotated source: /home/lu/greenpear/OSlearn/leetcode/flood_edge.cpp
--------------------------------------------------------------------------------
从内存读取指令次数 
Ir             I1mr        ILmr        Dr           D1mr       DLmr       Dw           D1mw       DLmw       

    .           .           .            .          .          .            .          .          .           #include <iostream>
    .           .           .            .          .          .            .          .          .           #include <string>
    .           .           .            .          .          .            .          .          .           #include <vector>
    .           .           .            .          .          .            .          .          .           using namespace std;
    .           .           .            .          .          .            .          .          .           
    .           .           .            .          .          .            .          .          .           class Solution {
    .           .           .            .          .          .            .          .          .           public:
    6 ( 0.00%)  0           0            0          0          0            3 ( 0.00%) 0          0               void solve(vector<vector<char>>& board) {
   11 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)   2 ( 0.00%) 0          0            5 ( 0.00%) 0          0                   int m = board.size(), n = board[0].size();
   29 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  20 ( 0.00%) 0          0            1 ( 0.00%) 0          0                   for (int i = 0; i < n; i++) {
   90 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  18 ( 0.00%) 0          0           12 ( 0.01%) 0          0                       if (board[0][i] == 'O') {
   21 ( 0.00%)  0           0            9 ( 0.00%) 0          0            3 ( 0.00%) 0          0                           floodEdge(board, 0, i);
    .           .           .            .          .          .            .          .          .                       }
  108 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  24 ( 0.00%) 0          0           12 ( 0.01%) 0          0                       if (board[m - 1][i] == 'O') {
   27 ( 0.00%)  0           0           12 ( 0.00%) 0          0            3 ( 0.00%) 0          0                           floodEdge(board, m - 1, i);
    .           .           .            .          .          .            .          .          .                       }
    .           .           .            .          .          .            .          .          .                   }
   21 ( 0.00%)  2 ( 0.09%)  2 ( 0.09%)  14 ( 0.00%) 0          0            1 ( 0.00%) 0          0                   for (int i = 0; i < m; i++) {
   56 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  12 ( 0.00%) 0          0            8 ( 0.00%) 0          0                       if (board[i][0] == 'O') {
    6 ( 0.00%)  0           0            3 ( 0.00%) 0          0            1 ( 0.00%) 0          0                           floodEdge(board, i, 0);
    .           .           .            .          .          .            .          .          .                       }
   72 ( 0.00%)  0           0           16 ( 0.00%) 0          0            8 ( 0.00%) 0          0                       if (board[i][n - 1] == 'O') {
    7 ( 0.00%)  0           0            4 ( 0.00%) 0          0            1 ( 0.00%) 0          0                           floodEdge(board, i, n - 1);
    .           .           .            .          .          .            .          .          .                       }
    .           .           .            .          .          .            .          .          .                   }
   21 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  14 ( 0.00%) 0          0            1 ( 0.00%) 0          0                   for (int i = 0; i < m; i++) {
  116 ( 0.00%)  0           0           80 ( 0.01%) 0          0            4 ( 0.00%) 0          0                       for (int j = 0; j < n; j++) {
  408 ( 0.02%)  0           0           96 ( 0.02%) 0          0           48 ( 0.02%) 0          0                           if (board[i][j] == 'O') {
   24 ( 0.00%)  0           0           16 ( 0.00%) 0          0            4 ( 0.00%) 0          0                               flood(board, i, j);
    .           .           .            .          .          .            .          .          .                           }
    .           .           .            .          .          .            .          .          .                       }
    .           .           .            .          .          .            .          .          .                   }
   21 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  14 ( 0.00%) 0          0            1 ( 0.00%) 0          0                   for (int i = 0; i < m; i++) {
  116 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  80 ( 0.01%) 0          0            4 ( 0.00%) 0          0                       for (int j = 0; j < n; j++) {
  408 ( 0.02%)  0           0           96 ( 0.02%) 0          0           48 ( 0.02%) 0          0                           if (board[i][j] == 'I') {
  104 ( 0.00%)  0           0           24 ( 0.00%) 0          0           24 ( 0.01%) 0          0                               board[i][j] = 'O';
    .           .           .            .          .          .            .          .          .                           }
    .           .           .            .          .          .            .          .          .                       }
    .           .           .            .          .          .            .          .          .                   }
    4 ( 0.00%)  0           0            2 ( 0.00%) 0          0            0          0          0               }
    .           .           .            .          .          .            .          .          .           
  360 ( 0.02%)  1 ( 0.05%)  1 ( 0.05%)   0          0          0          240 ( 0.12%) 0          0               void floodEdge(vector<vector<char>>& board, int i, int j) {
  849 ( 0.04%)  1 ( 0.05%)  1 ( 0.05%) 211 ( 0.04%) 0          0           99 ( 0.05%) 0          0                   if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
   20 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)   0          0          0            0          0          0                       return;
    .           .           .            .          .          .            .          .          .                   }
    .           .           .            .          .          .            .          .          .           
1,012 ( 0.04%)  2 ( 0.09%)  2 ( 0.09%) 240 ( 0.04%) 0          0          120 ( 0.06%) 0          0                   if (board[i][j] == 'I' || board[i][j] == 'X') {
   22 ( 0.00%)  0           0            0          0          0            0          0          0                       return;
    .           .           .            .          .          .            .          .          .                   }
    .           .           .            .          .          .            .          .          .           
  104 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  24 ( 0.00%) 0          0           24 ( 0.01%) 0          0                   board[i][j] = 'I';
   72 ( 0.00%)  0           0           32 ( 0.01%) 0          0            8 ( 0.00%) 0          0                   floodEdge(board, i + 1, j);
   72 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  32 ( 0.01%) 0          0            8 ( 0.00%) 0          0                   floodEdge(board, i - 1, j);
   56 ( 0.00%)  0           0           32 ( 0.01%) 0          0            8 ( 0.00%) 0          0                   floodEdge(board, i, j + 1);
   64 ( 0.00%)  0           0           32 ( 0.01%) 0          0            8 ( 0.00%) 0          0                   floodEdge(board, i, j - 1);
  120 ( 0.01%)  0           0          120 ( 0.02%) 0          0            0          0          0               }
    .           .           .            .          .          .            .          .          .           
  180 ( 0.01%)  0           0            0          0          0          120 ( 0.06%) 0          0               void flood(vector<vector<char>>& board, int i, int j) {
  480 ( 0.02%)  2 ( 0.09%)  2 ( 0.09%) 120 ( 0.02%) 0          0           60 ( 0.03%) 0          0                   if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()) {
    .           .           .            .          .          .            .          .          .                       return;
    .           .           .            .          .          .            .          .          .                   }
    .           .           .            .          .          .            .          .          .           
  676 ( 0.03%)  1 ( 0.05%)  1 ( 0.05%) 160 ( 0.03%) 0          0           80 ( 0.04%) 0          0                   if (board[i][j] == 'I' || board[i][j] == 'X') {
   16 ( 0.00%)  0           0            0          0          0            0          0          0                       return;
    .           .           .            .          .          .            .          .          .                   }
    .           .           .            .          .          .            .          .          .           
   52 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  12 ( 0.00%) 0          0           12 ( 0.01%) 0          0                   board[i][j] = 'X';
   36 ( 0.00%)  0           0           16 ( 0.00%) 0          0            4 ( 0.00%) 0          0                   flood(board, i + 1, j);
   36 ( 0.00%)  1 ( 0.05%)  1 ( 0.05%)  16 ( 0.00%) 0          0            4 ( 0.00%) 0          0                   flood(board, i - 1, j);
   28 ( 0.00%)  0           0           16 ( 0.00%) 0          0            4 ( 0.00%) 0          0                   flood(board, i, j + 1);
   32 ( 0.00%)  0           0           16 ( 0.00%) 0          0            4 ( 0.00%) 0          0                   flood(board, i, j - 1);
   60 ( 0.00%)  0           0           60 ( 0.01%) 0          0            0          0          0               }
    .           .           .            .          .          .            .          .          .           };
    .           .           .            .          .          .            .          .          .           
   12 ( 0.00%)  0           0            1 ( 0.00%) 0          0            7 ( 0.00%) 0          0           int main() {
    .           .           .            .          .          .            .          .          .               vector<vector<char>> board = {
    .           .           .            .          .          .            .          .          .                   {'X','O','X','O','X','O'},
    .           .           .            .          .          .            .          .          .                   {'O','X','O','X','O','X'},
    .           .           .            .          .          .            .          .          .                   {'X','O','X','O','X','O'},
    .           .           .            .          .          .            .          .          .                   {'O','X','O','X','O','X'}
  157 ( 0.01%) 10 ( 0.45%) 10 ( 0.47%)   6 ( 0.00%) 0          0           49 ( 0.02%) 0          0               };
    .           .           .            .          .          .            .          .          .           
    .           .           .            .          .          .            .          .          .               Solution s;
    5 ( 0.00%)  0           0            0          0          0            1 ( 0.00%) 0          0               s.solve(board);
   51 ( 0.00%)  2 ( 0.09%)  2 ( 0.09%)   9 ( 0.00%) 0          0            6 ( 0.00%) 0          0               for (int i = 0; i < board.size(); i++) {
  368 ( 0.02%)  2 ( 0.09%)  2 ( 0.09%)  52 ( 0.01%) 0          0           60 ( 0.03%) 0          0                   for (int j = 0; j < board[0].size(); j++) {
  552 ( 0.02%)  0           0           72 ( 0.01%) 0          0           96 ( 0.05%) 0          0                       cout << board[i][j] << " ";
    .           .           .            .          .          .            .          .          .                   }
   20 ( 0.00%)  0           0            4 ( 0.00%) 0          0            4 ( 0.00%) 0          0                   cout << endl;
    .           .           .            .          .          .            .          .          .               }
    1 ( 0.00%)  0           0            0          0          0            0          0          0               return 0;
   36 ( 0.00%)  4 ( 0.18%)  3 ( 0.14%)  15 ( 0.00%) 1 ( 0.01%) 0            6 ( 0.00%) 0          0           }
--------------------------------------------------------------------------------
The following files chosen for auto-annotation could not be found:
--------------------------------------------------------------------------------
  ./elf/../sysdeps/generic/dl-protected.h
  ./elf/../sysdeps/generic/ldsodefs.h
  ./elf/../sysdeps/x86/dl-cacheinfo.h
  ./elf/../sysdeps/x86_64/dl-machine.h
  ./elf/../sysdeps/x86_64/dl-trampoline.h
  ./elf/./elf/dl-cache.c
  ./elf/./elf/dl-load.c
  ./elf/./elf/dl-lookup.c
  ./elf/./elf/dl-misc.c
  ./elf/./elf/dl-reloc.c
  ./elf/./elf/dl-runtime.c
  ./elf/./elf/dl-tunables.c
  ./elf/./elf/dl-tunables.h
  ./elf/./elf/dl-version.c
  ./elf/./elf/do-rel.h
  ./string/../sysdeps/x86_64/strcmp.S
  ./wcsmbs/./wcsmbs/btowc.c
  ./wcsmbs/./wcsmbs/wctob.c

--------------------------------------------------------------------------------
Ir              I1mr        ILmr        Dr             D1mr       DLmr       Dw             D1mw       DLmw       
--------------------------------------------------------------------------------
18,639 ( 0.79%) 90 ( 4.06%) 87 ( 4.13%) 6,154 ( 1.08%) 1 ( 0.01%) 0          3,745 ( 1.80%) 1 ( 0.04%) 1 ( 0.06%)  events annotated
*/