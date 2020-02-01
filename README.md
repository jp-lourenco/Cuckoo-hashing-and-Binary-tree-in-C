# Cuckoo-hashing-and-Binary-tree-in-C
In this repository two search strategies (Cuckoo Hashing and Binary Tree) are presented together in a program capable of locating records, searched according to a value given by the user that corresponds to the 'naochave' field of the struct 'registro', informing an estimate of the time spent at the end of the run.

Neste repositório são apresentadas duas estratégias de busca (Árvore Binária de Pesquisa e Cuckoo Hashing) conjuntas em um programa capaz de localizar registros, pesquisados conforme um valor dado pelo usuário que corresponde ao campo ‘naochave’ da struct ‘registro’, informando uma estimativa do tempo gasto no final da execução.

base.bin https://drive.google.com/open?id=1WfF9OPCMQULkTG-pJBTncpZ1HSOYxuXN  4 gb (4.000.000 records)

Example:

joao@JP-Ubuntu: gcc Main.c
joao@JP-Ubuntu:~$ ./a.out

|_________________Menu_________________|
| Digite [1]:Cuckoo hash               |
| Digite [2]:Arvore Binaria de Pesquisa|
| Digite [0]:Sair                      |
|______________________________________|

Digite a entrada: 1

Construindo tabela hash....

Digite o numero que deseja buscar: 18446744073132421059

Chave: 3999999
NaoChave: 18446744073132421059
Outros: EGb8!MD*+2t(*ec?#O&(n.n,p/95I-R*SPAT|~]BKmJTS.row4vfAe-2/EFrR4{@cWszpl>=t#,bJ:RBMJ))JO:YtyLaHb",T1B_8y7-{Cn`\A$D&FLPu!D&y+"]l#h[MEU~?lFU057'pTJ15u`+u%J+/Kg6hk,PKaPjNuZ]F,}7_Hat>C:Na~r,Ju[3{#}GcNLL^(D%3BU.i8=Btp+po|{;.rg*teQrN|?.?b2l?#y):Qd/B*~3A7gODiX9jD,9Bd`za.g!0{CcMB-+KF=k\?;!)/S.Rxa/wB+YO-sx*Q\prhzX0RE'pyB5)0\[*>%"`/uJ<i^_V;PI?f=hSa*_[Ks~[jt~*x;%)1h^6GX'|Ci<*'?]gH=^/K]%6R$YKX]miGf:m?@jb*A'1_}3)UpQ!hUQUX+"K$*5J,hRJCXGgxh3sfE7WQgqT=C+0h,Z'O+PZ.=@Qt"S*%e8'EN]16Oel.o716p7d6"ZDX50hPbqob*u(qm9B=}Idm_0>jF#"av_;Fn$2k0"NS2oE~CfVAJ<I*Kfs-%0)6nCvwF)}oDfCUWgTyhEV3`:VG"Km@tuo~Tfv5*1&MvH=NK,cNQTaLmR.n|zI.-:-`;$tENy-FCd/)oqVAFR)O&6X=2#JXVV9pt.PCCwh!\w)f%^Ce2K57`lm-*9dyn8kcFVBhh+$_=,G\%i\6O,f03UWWm<QvTWu5/882\;q5F9,d=#zkH{6ZklLsD}k3U{G}Nx1E4=YsU~X-"mwI&.?p6jeYhkkYgMqPF#tY?Og/hZ;jIMNN[(Y,r?duEji-8\\]xlQ9<Sa?.8DpdrYZy4e(lJ}3OgYf^QDX>0,sbl3p?W{%dV^^%_"pD:>s<wZzc:S"I^t-eB8&44Dw%#q){r5A-R5bd*]HCKIlDX4+6eJI4m\9+N[([ob#CvdB;]j^)NeM(xqW^<!-DvEhE"+;,l=h}=,:yuw#Dwiep[=i2XuoOVY0qcJ|k#fi?q>S#PoFHZGSPcWbVhl'?FPKEyHK{

Tempo gasto (milisegundos) para pesquisar: 0.081000
 ____________________________
|__________Menu Hash_________|
| Digite [1]:Buscar novamente|
| Digite [0]:Sair            |
|____________________________|

Digite a entrada: 0

-------------------------------------------------------------------

RECORDS FOR SEARCH


Chave 0
Nao  Chave 18446744072924990197

Chave 1
Nao  Chave 18446744073705518210

Chave 2
Nao  Chave 18446744071606539659

Chave 3
Nao  Chave 564929546

Chave 4
Nao  Chave 152112058

Chave 5
Nao  Chave 18446744073677208512

Chave 6
Nao  Chave 18446744072101982738

....


