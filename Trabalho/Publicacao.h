#ifndef PUBLICACAO_H_INCLUDED
#define PUBLICACAO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;
class Publicacao
{
private:
    tm data;
    string conteudo;
    string url;
public:
    tm getData();
    void setData(tm data);
    string getConteudo();
    string getUrl();
    void setConteudo(string conteudo);
    Publicacao();
    Publicacao(string a, string u);
    void imprimeInfo();
    void imprimeNoArquivo(ofstream &o);
    void carregaArquivo(ifstream &o);
    void imprimirNoHtml(ofstream &o);
};

#endif // PUBLICACAO_H_INCLUDED
