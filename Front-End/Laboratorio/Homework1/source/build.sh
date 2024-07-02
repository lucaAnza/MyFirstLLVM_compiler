echo -e "Compilazione del file postorder.cpp..."
g++ -o post.exe postorder.cpp
echo -e "Compilazione completata \e[32m✓\e[0m\n"

echo -e "Compilazione del file subset_construction.cpp..."
g++ -o subset.exe subset_construction.cpp
echo -e "Compilazione completata \e[32m✓\e[0m\n"

echo -e "\nEsecuzione homework!\n"
echo -e "OUTPUT:\n"
echo -e "----------------------------"

./post.exe tree1.txt | ./subset.exe


echo -e "----------------------------"
echo -e "\nPulizia file eseguibili🧹"
rm post.exe
echo -e "   post.exe deleted!"
rm subset.exe
echo -e "   subset.exe deleted!"


