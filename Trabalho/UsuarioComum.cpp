#include "UsuarioComum.h"

UsuarioComum::UsuarioComum():Usuario() {}
UsuarioComum::UsuarioComum(string nome, string id, tm data, string u, char g , string f, StatusRelacionamento s):Usuario(nome, id, data,u)
{
    genero=g;
    formacao=f;
    status=s;
}
char UsuarioComum::getGenero()
{
    return this->genero;
}
void UsuarioComum::setGenero(char genero)
{
    this->genero=genero;
}
string UsuarioComum::getFormacao()
{
    return this->formacao;
}
void UsuarioComum::setFormacao(string formacao)
{
    this->formacao=formacao;
}
UsuarioComum::StatusRelacionamento UsuarioComum::getStatus()
{
    return this->status;
}
void UsuarioComum::setStatus(UsuarioComum::StatusRelacionamento status)
{
    this->status=status;
}
string UsuarioComum::getStringStatus()
{
    switch(this->status)
    {
    case 1:
        return "Solteiro(a)";
    case 2:
        return "Namorando";
    case 3:
        return "Casado(a)";
    default:
        return "";
    }
}
bool UsuarioComum::validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias)
{
    time_t tt;
    time(&tt);
    tm dataAtual = *localtime(&tt); //Pega data atual
    time_t x = mktime(&this->data); //Transforma data de nascimento em segundos
    time_t y = mktime(&dataAtual); //Transforma data atual em segundos
    double diferenca = difftime(y, x); //Compara a diferença de segundos
    diferenca = diferenca/(365*60*60*24); //Transforma  segundos  em  anos, representando a idade do usuário
    if(diferenca>=idadeMinUsuarioAnos)
    {
        return 1;
    }
    return 0;
}
void UsuarioComum::imprimeInfo()
{
    cout << "Nome: " << nome << endl;
    cout << "ID: " << id << endl;
    cout << "Data de nascimento: " << data.tm_mday << "/" << data.tm_mon +1 << "/" << data.tm_year+1900 << endl;
    cout << "Gênero: " << genero << endl;
    cout << "Formação: " << formacao << endl;
    cout << "Status de relacionamento: " << this->getStringStatus() << endl;
}
void UsuarioComum::imprimeNoArquivo(ofstream &o)
{
    o << "C" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << endl;
    o << this->genero << endl;
    o << this->formacao << endl;
    o << this->status << endl;
    o << this->getUrlFoto()<< endl;
    o << seguidores.size() << endl;
    for(int i=0;i<seguidores.size();i++)
    {
        seguidores[i]->imprimeSeguidor(o);
    }
    o << publicacoes.size() << endl;
    for(int i=0;i<publicacoes.size();i++)
    {
        publicacoes[i]->imprimeNoArquivo(o);
    }
    cout << "Usuário comum " << this->nome << " salvo com sucesso!" << endl;
}
void UsuarioComum::imprimeSeguidor(ofstream &o)
{
    o << "C" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << endl;
    o << this->genero << endl;
    o << this->formacao << endl;
    o << this->status << endl;
    o << this->getUrlFoto() << endl;
    cout << "Seguidor " << this->nome << " salvo com sucesso!" << endl;
}
void UsuarioComum::carregaArquivo(ifstream &arqRed)
{
    string tipo,urlll;
    int n,w,d,m,a,opa;
    getline(arqRed, this->nome);
    getline(arqRed, this->id);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data={0,0,0,d,m-1,a-1900};
    arqRed >> this->genero;
    arqRed.ignore();
    getline(arqRed, this->formacao);
    arqRed >> opa;
    arqRed.ignore();
    this->setStatus(UsuarioComum::StatusRelacionamento(opa));
    arqRed >> urlll;
    arqRed.ignore();
    this->setUrlFoto(urlll);
    arqRed >> n; //numero de seguidores
    arqRed.ignore();
    for(int i=0;i<n;i++)
    {
        arqRed >> tipo;
        arqRed.ignore();
        if(tipo=="P")
        {
            Pagina* u;
            u = (Pagina*)new Pagina();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
        else
        {
            UsuarioComum* u;
            u = new UsuarioComum();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
    }
    arqRed >> w; //número de publicações
    arqRed.ignore();
    for(int i=0;i<w;i++)
    {
        Publicacao* p;
        p = new Publicacao();
        p->carregaArquivo(arqRed);
        publicacoes.push_back(p);
    }
    cout << "Usuário comum " << this->nome << " carregado com sucesso!" << endl;
}
void UsuarioComum::carregaSeguidor(ifstream &arqRed)
{
    int d,m,a,opa;
    string urlll;
    getline(arqRed, this->nome);
    getline(arqRed, this->id);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    arqRed >> this->genero;
    arqRed.ignore();
    getline(arqRed, this->formacao);
    arqRed >> opa;
    arqRed.ignore();
    this->setStatus(UsuarioComum::StatusRelacionamento(opa));
    arqRed >> urlll;
    arqRed.ignore();
    this->setUrlFoto(urlll);
    cout << "Seguidor " << this->nome << " do usuário comum carregado com sucesso!" << endl;
}
void UsuarioComum::imprimeNoHtmlPerfil(ofstream &o)
{
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12 text-center\">" << endl;
    o << "<h2>" << this->nome << " (Usuário Comum)</h2>" << endl;
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
    if(this->genero == 'M'){
        o << "<h4>MASCULINO</h4>" << endl;
    } else {
        o << "<h4>FEMININO</h4>" << endl;
    }
    o << "<h4>" << this->getStringStatus() << "</h4>" << endl;
    o << "<h4>" << this->formacao << "</h4>" << endl;
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
    for(int i=0;i<this->publicacoes.size();i++)
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
    for(int i=0;i<this->seguidores.size();i++)
    {
        this->seguidores[i]->imprimeNoHtmlSeguidor(o);
    }
    o << "</div>" << endl;
    o << "</div>" << endl;
}
void UsuarioComum::imprimeNoHtmlSeguidor(ofstream &o)
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
    if(this->genero == 'M'){
        o << "<h4>MASCULINO</h4>" << endl;
    } else {
        o << "<h4>FEMININO</h4>" << endl;
    }
    o << "<h4>" << this->getStringStatus() << "</h4>" << endl;
    o << "<h4>" << this->formacao << "</h4>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
}
