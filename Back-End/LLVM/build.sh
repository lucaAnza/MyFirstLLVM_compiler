# Variable
IMG_NAME="CFG_LI.png"
OPT_FILE_NAME="LI_opt.ll"


#Generazione file .ll dal sorgente .c
echo "Generazione file .ll from .c source..."
INSTALL/bin/clang -S -emit-llvm -O0 TEST/source_c/Loop_interchange.c -o LI.ll -Xclang -disable-O0-optnone 

echo "Launch optimization (mem2reg)..."
#Ottimizazione di tipo mem to reg
INSTALL/bin/opt -p=mem2reg LI.ll -o LIm2r.ll
mv LIm2r.ll TEST/source_ll/LIm2r.ll
rm LI.ll
echo "File .ll move on TEST/source_ll/LIm2r.ll path"

echo -e "\nCreazione file .ll ottimizato"
echo -e "\nOUTPUT SPACE -------------------------------------------------- \n\n\n"

#Creazione file bytecode
INSTALL/bin/opt -p loop_interchange TEST/source_ll/LIm2r.ll -o LI.bc

echo -e "\n\n\nOUTPUT SPACE --------------------------------------------------\n"

#Trasformazione file binario in .ll
INSTALL/bin/llvm-dis LI.bc -o $OPT_FILE_NAME
rm LI.bc
echo -e "\e[32m\u2714\e[0m file ottimizato creato con successo  (file_name = $OPT_FILE_NAME)"

#Generazione CFG
echo -e "\nGenerating CFG print with dot..."
INSTALL/bin/opt -p=dot-cfg TEST/source_ll/LIm2r.ll > /dev/null
mv \.loop_interchange_function.dot ./grafo.dot
dot -Tpng grafo.dot -o $IMG_NAME
echo -e "\e[32m\u2714\e[0m   CFG ready  (img_name = $IMG_NAME)"
