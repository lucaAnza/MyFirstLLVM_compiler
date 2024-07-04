# Front-End

Given the following compilation stages:

<img src="Teoria/img/toolchain.png" alt="fasi" width=30%></img>

In this part of the project, we will analyze and produce a working example of the first 4 phases (Front-End).
The phases are as follows:

1. Lexical analyzer.
2. Syntax analyzer.
3. Semantic analyzer.
4. Intermediate code generator.

<br>

<b>Front-End structure</b>

<img src="Progetto_Finale/img/struttura_front-end.png" alt="explain img" width=50%>

- <b>Lexer</b> is implemented using [Flex](https://github.com/westes/flex) (open source tool)
- <b>Parser</b> is implemented using [Bison](https://www.gnu.org/software/bison/) (open source tool)
- <b>Code generator</b> is implemented in a file .cpp called `driver.cpp`.


<br><br>

## Dependencies

- <b>flex</b>
    ```bash
    sudo apt install flex
    ```
- <b>llvm-16</b>
    
    ```bash
    #Alternativa-1
    wget https://apt.llvm.org/llvm.sh
    chmod +x llvm.sh
    sudo ./llvm.sh 16
    sudo apt-get install build-essential
    sudo apt-get install libc6-dev
    sudo apt-get install libstdc++-12-dev
    sudo apt-get install g++-multilib
    sudo apt-get install libc++-16-dev libc++abi-16-dev
    ```

## Directory guide 📁

- You can find _source code_ on `/Progetto_Finale`.
- You can find _theoretical concepts_ on `/Teoria`.
- You can find _some exercises_ and _subset construcion algorithm_ on `Laboratorio`.

## Link utili

Drive: https://drive.google.com/drive/u/1/folders/16mBaaH7VP5WH-fU2RXQDZG5Z-GDHRd7d

