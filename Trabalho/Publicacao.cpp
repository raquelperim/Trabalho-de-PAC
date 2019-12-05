#include "Publicacao.h"

Publicacao::Publicacao() {}
Publicacao::Publicacao(string a, string u)
{
    conteudo=a;
    time_t tt;
    time(&tt);
    data=*localtime(&tt);
    url=u;
}
void Publicacao::imprimeInfo()
{
    cout << "Data da publicação: " << data.tm_mday << "/" << data.tm_mon+1 << "/" << data.tm_year+1900 << endl;
    cout << "Conteúdo: " << conteudo << endl;
}
tm Publicacao::getData()
{
    return this->data;
}
void Publicacao::setData(tm date)
{
    this->data=date;
}
string Publicacao::getConteudo()
{
    return this->conteudo;
}
void Publicacao::setConteudo(string conteudo)
{
    this->conteudo=conteudo;
}
void Publicacao::imprimeNoArquivo(ofstream &o)
{
    o<< this->conteudo << endl;
    o<< this->url << endl;
    o << data.tm_mday << "/" << data.tm_mon+1 << "/" << data.tm_year+1900 << endl;
    cout << "Publicação salva com sucesso!" << endl;
}
void Publicacao::carregaArquivo(ifstream &arqRed)
{
    int d,m,a;
    getline(arqRed, this->conteudo);
    getline(arqRed, this->url);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    cout << "Publicação carregada com sucesso!" << endl;
}
void Publicacao::imprimirNoHtml(ofstream &o)
{
    o << "<div id=\"card\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div id=\"divImage\">" << endl;
    o << "<div class=\"bg-img\">" << endl;
    o << "<img src=\"" << this->url << "\" />" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"info\">" << endl;
    o << "<div>" << endl;
    o << "<h3>" << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << "</h3>" << endl;
    o << "</div>" << endl;
    o << "<h4>" << this->conteudo << "</h4>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
}
