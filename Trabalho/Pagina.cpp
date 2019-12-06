#include "Pagina.h"

Pagina::Pagina():Usuario()
{
    this->categoria= new Categoria();
}
Pagina::Pagina(string nome, string id, tm data, string u, string c, string s):Usuario(nome, id, data, u)
{
    categoria= new Categoria(c);
    sobre=s;
}
Categoria* Pagina::getCategoria()
{
    return this->categoria;
}
void Pagina::setCategoria(Categoria* categoria)
{
    this->categoria=categoria;
}
string Pagina::getSobre()
{
    return this->sobre;
}
void Pagina::setSobre(string sobre)
{
    this->sobre=sobre;
}
bool Pagina::validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias)
{
    time_t tt;
    time(&tt);
    tm dataAtual=*localtime(&tt); //Pega data atual
    time_t x=mktime(&this->data); //Transforma data de nascimento em segundos
    time_t y=mktime(&dataAtual); //Transforma data atual em segundos
    double diferenca=difftime(y, x); //Compara a diferença de segundos
    diferenca=diferenca/(60*60*24); //Transforma  segundos  em  anos, representando a idade do usuário
    if(diferenca>=idadeMinPaginaDias)
    {
        return 1;
    }
    return 0;
}
void Pagina::imprimeInfo()
{
    cout << "Nome: " << nome << endl;
    cout << "ID: " << id << endl;
    cout << "Data de nascimento: " << data.tm_mday << "/" << data.tm_mon+1 << "/" << data.tm_year+1900 << endl;
    cout << "Categoria: " << categoria->getNome() << endl;
    cout << "Sobre: " << sobre << endl;
}
void Pagina::imprimeNoArquivo(ofstream &o)
{
    o << "P" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" <<this->data.tm_mon+1 << "/" << this->data.tm_year+1900 << endl;
    o << this->categoria->getNome() << endl;
    o << this->sobre << endl;
    o << this->getUrlFoto() << endl;
    o << seguidores.size() << endl;
    for(int i=0; i<seguidores.size(); i++)
    {
        seguidores[i]->imprimeSeguidor(o);
    }
    o << publicacoes.size() << endl;
    for(int i=0; i<publicacoes.size(); i++)
    {
        publicacoes[i]->imprimeNoArquivo(o);
    }
    cout << "Página " << this->nome << " salva com sucesso!" << endl;
}
void Pagina::imprimeSeguidor(ofstream &o)
{
    o << "P" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" <<this->data.tm_mon+1 << "/" << this->data.tm_year+1900 << endl;
    o << this->categoria->getNome() << endl;
    o << this->sobre << endl;
    o << this->getUrlFoto() << endl;
    cout << "Seguidor " << this->nome << " salvo com sucesso!" << endl;
}
void Pagina::carregaArquivo(ifstream &arqRed)
{
    string ups,tipo,urlll;
    int n,w,d,m,a;
    getline(arqRed, this->nome);
    getline(arqRed, this->id);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    getline(arqRed, ups);
    this->categoria->setNome(ups);
    arqRed.ignore();
    getline(arqRed, this->sobre);
    arqRed >> urlll;
    arqRed.ignore();
    this->setUrlFoto(urlll);
    arqRed >> n; // número de seguidores
    arqRed.ignore();
    for(int i=0; i<n; i++)
    {
        arqRed >> tipo;
        arqRed.ignore();
        if(tipo=="P")
        {
            Usuario* u;
            u = new Pagina();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
        else
        {
            Usuario* u;
            u = new UsuarioComum();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
    }
    arqRed >> w; // número de publicações
    arqRed.ignore();
    for(int i=0; i<w; i++)
    {
        Publicacao* p;
        p = new Publicacao();
        p->carregaArquivo(arqRed);
        publicacoes.push_back(p);
    }
    cout << "Página " << this->nome << " carregada com sucesso!" << endl;
}
void Pagina::carregaSeguidor(ifstream &arqRed)
{
    int d,m,a;
    string oops,urlll;
    getline(arqRed, this->nome);
    getline(arqRed, this->id);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    arqRed >> oops;
    arqRed.ignore();
    this->categoria->setNome(oops);
    getline(arqRed, this->sobre);
    arqRed >> urlll;
    arqRed.ignore();
    this->setUrlFoto(urlll);
    cout << "Seguidor " << this->nome << " carregado com sucesso!" << endl;
}
void Pagina::imprimeNoHtmlPerfil(ofstream &o)
{
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12 text-center\">" << endl;
    o << "<h2>" << this->nome << " (Página)</h2>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"perfil\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12\">" << endl;
    o << "<h3>Perfil</h3>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div class=\"bg-img\">" << endl;
    o << "<img src=\"" << this->urlFoto << "\" />" << endl;
    o << "</div>" << endl;
    o << "<div id=\"sobre\">" << endl;
    o << "<h4>" << this->id << "</h4>" << endl;
    o << "<h4>" << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << "</h4>" << endl;
    o << "<h4>" << this->categoria->getNome() << "</h4>" << endl;
    o << "<h4>" << this->sobre << "</h4>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"publicacoes\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12\">" << endl;
    o << "<h3>Publicações</h3>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    if(this->publicacoes.empty())
    {
        o << "<h4 style=\"font-style: italic; text-decoration: underline;\"> Nenhuma publicação até o momento!</h4>" << endl;
    }
    for(int i=0; i<this->publicacoes.size(); i++)
    {
        this->publicacoes[i]->imprimirNoHtml(o);
    }
    o << "</div>" << endl;
    o << "<div id=\"seguidores\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12\">" << endl;
    o << "<h3>Seguidores</h3>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    if(this->seguidores.empty())
    {
        o << "<h4 style=\"font-style: italic; text-decoration: underline;\"> Nenhum seguidor até o momento!</h4>" << endl;
    }
    for(int i=0; i<this->seguidores.size(); i++)
    {
        this->seguidores[i]->imprimeNoHtmlSeguidor(o);
    }
    o << "</div>" << endl;
    o << "</div>" << endl;
}
void Pagina::imprimeNoHtmlSeguidor(ofstream &o)
{
    o << "<div id=\"card\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div id=\"divImage\">" << endl;
    o << "<div class=\"bg-img\">" << endl;
    o << "<img src=\"" << this->urlFoto << "\" />" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"info\">" << endl;
    o << "<h4>" << this->id << "</h4>" << endl;
    o << "<h4>" << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << "</h4>" << endl;
    o << "<h4>" << this->categoria << "</h4>" << endl;
    o << "<h4>" << this->sobre << "</h4>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
}
