# cpp-opengl-tetris

m1 macの、c++とOpenGLで簡易的なテトリスを作りました。

https://user-images.githubusercontent.com/89882017/185777309-9afa6109-ba77-42e9-bd1e-2e37c981b26a.mp4

## 動作環境
- m1 mac

```
❯ uname -a
Darwin mac.local 21.6.0 Darwin Kernel Version 21.6.0:
Sat Jun 18 17:05:47 PDT 2022; root:xnu-8020.140.41~1/RELEASE_ARM64_T8101 arm64

❯ brew config
HOMEBREW_VERSION: 3.5.9
CPU: octa-core 64-bit arm_firestorm_icestorm
Clang: 13.1.6 build 1316
macOS: 12.5-arm64
CLT: 13.4.0.0.1.1651278267
Xcode: 13.4.1
Rosetta 2: false
```

## Install〜実行

### GLFWをインストール

```
brwe install glfw
vim ~/.zshrc
# 下記を追加
export CPATH=/opt/homebrew/include
export LIBRARY_PATH=/opt/homebrew/lib
```

### リポジトリをclone

```
git clone https://github.com/web3ten0/cpp-opengl-tetris.git
```

### binディレクトリ作成、make、実行

```
cd cpp-opengl-tetris
mkdir bin
make
./bin/main
```

#### 実行してみてる動画
- https://www.youtube.com/watch?v=X1YzFl31W7c

