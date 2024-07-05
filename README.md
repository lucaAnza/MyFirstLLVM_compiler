# My First LLVM Compiler

In this repository you can find the implementation of a compiler. <br>
The compiler is divided into <b>Front-End</b> and <b>Middle-End</b>. <br>
The <b>Back-End</b> part is not implemented 🚫 


## Introduction

### What is the purpose of a compiler?

A compiler translates code written in a high-level programming language into machine code that a computer can understand. In more detail, a compiler is a special type of software that serves as a translator between the programmer and the computer.


### Anatomy of a compiler

<table>
    <tr>
        <td><img src="Front-End/Teoria/img/toolchain.png"></td>
        <td><img src="Front-End/Teoria/img/istruction_translate.png"></td>
    </tr>
</table>


### Compiler toolchain

<img src="Front-End/Teoria/img/toolchain2.png"></td>

<br>

## Dependencies ⚙️
The Front-End and Middle-End have different versions of LLVM and different dependencies. <br>
- Each project directory contains a <span style="color:orange">README.md</span> file that specifies the requirements.

<br>

## Middle-end 📁

In this directory you can find some optimizations on IR Code.<br>
Each optimization is made modifying LLVM source code or creating a new pass.<br>
<br>

_middle-end function:_

<img src="Back-End/Slide/img/compiler_anatomy.png" width=50%></img>

<img src="Back-End/Slide/img/compiler_anatomy2.png" width=50%></img>

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

<br><br>

## Front-End 📁

Given the following compilation stages:

<img src="Front-End/Teoria/img/toolchain.png" alt="fasi" width=30%></img>

In this part of the project, we will analyze and produce a working example of the first 4 phases (Front-End).
The phases are as follows:

1. Lexical analyzer.
2. Syntax analyzer.
3. Semantic analyzer.
4. Intermediate code generator.

<br>

<b>Front-End structure</b>

<img src="Front-End/Progetto_Finale/img/struttura_front-end.png" alt="explain img" width=50%>

- <b>Lexer</b> is implemented using [Flex](https://github.com/westes/flex) (open source tool)
- <b>Parser</b> is implemented using [Bison](https://www.gnu.org/software/bison/) (open source tool)
- <b>Code generator</b> is implemented in a file .cpp called `driver.cpp`.


<br><br>

ℹ️ More details of the programming language implemented is on `/Front-End/Progetto_finale/`








