# How to install LLVM last version ? 

### 1. Scarica zip -> https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.6  
### 2. Creare una gerarchia di cartelle fatte in questo modo :   

    ./  
    ../  
    **BUILD/**  
    **INSTALL/**  
    setup.sh  
    **SRC/**  
    **TEST/**  

### 3. Inserire il file zip scompattato nella directory **/SRC**

### 4.Vai nella cartella BUILD.

### 5. Esportare la variabile d'ambiente :  
`export ROOT=<directory desiderata>`     

-- Example :  
`export ROOT=/media/luke/data/MyFirstLLVM_compiler/Back-End/LLVM` )

### 6. Sposta il file CMakeLists.txt in /SRC     ( DOVE TROVO QUESTO FILE ? )

### 7. Manda il seguente comando :  
`cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$ROOT/INSTALL $ROOT/SRC`

### 8. Manda il segutente comando :  
`make -j <numero core`

