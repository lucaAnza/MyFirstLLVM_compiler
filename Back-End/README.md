# Middle-end optimizations

In this directory you can find some optimizations on IR Code.<br>
Each optimization is made modifying LLVM source code or creating a new pass.<br>
<br>

_middle-end function:_

<img src="Slide/img/compiler_anatomy.png" width=50%></img>

<img src="Slide/img/compiler_anatomy2.png" width=50%></img>

---

### Which optimizations or analysis?

#### Assignment1(optimization-LLVM)

- Algebric Identity.
- Strengh Reduction.
- Multi Instructions opt.

#### Assignment2(analiysis)

->Data Flow Analysis on three different case:

- Constant Propagation.
- Dominator Analysis.
- Very Busy Expressions.

#### Assignment3(optimization-LLVM)

- LICM (Loop Invariant Code Motion).

#### Assignment4(optimization-LLVM)

- LI (Loop Fusion).




<br><br><br>

# How to install LLVM last version ? 

### 1. Scarica zip -> https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.6

- Scaricare <b> Source Code </b> (.zip / .tar.gz)

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
`export ROOT=/media/luke/data/MyFirstLLVM_compiler/Back-End/LLVM` 


### 6. Manda il seguente comando :  

`cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROOT/INSTALL -DLLVM_ENABLE_PROJECTS="clang" -DLLVM_TARGETS_TO_BUILD=host $ROOT/SRC/llvm-project-llvmorg-17.0.6/llvm/`  
· ATTENZIONE : Se restituisce qualche errore cancellare tutti i file all'interno di /BUILD e riprovare.

### 7. Manda il segutente comando :  
`make -j <numero core>`

### 8. Manda il seguente comando : 
`make install`
