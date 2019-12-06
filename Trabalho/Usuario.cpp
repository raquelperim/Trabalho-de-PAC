#include "Usuario.h"

Usuario::Usuario() {}
Usuario::Usuario(string n, string c, tm dn, string u)
{
    nome=n;
    id=c;
    data=dn;
    urlFoto=u;
}
void Usuario::imprimirPublicacoes()
{
    if(publicacoes.size()==0)
    {
        //cout << "Não existe publicação cadastrada." << endl;   //  Quando imprime todas as publicações, caso algum usuario não tenha(publicacoes), essa msg aparecerá
    }
    else
    {
        int i;
        for(i=0; i<publicacoes.size(); i++)
        {
            cout << "Publicação: " << i <<endl;
            publicacoes[i]->imprimeInfo();
            cout << endl;
        }
    }
}
void Usuario::imprimirSeguidores()
{
    if(seguidores.size() == 0)
    {
        cout << "Não existe nenhum seguidor." << endl;
    }
    else
    {
        int i;
        for(i=0; i<seguidores.size(); i++)
        {
            cout << "Seguidor: " << i << endl;
            seguidores[i]->imprimeInfo();
        }
    }
}
void Usuario::novoSeguidor(Usuario* u)
{
    if(u->id == this->id)
    {
        cout << "Você não pode seguir você mesmo." << endl;
        return;
    }
    int i;
    for(i=0; i<seguidores.size(); i++)
    {
        if(seguidores[i]->id == u->id)
        {
            cout << "Você já segue esse usuário." << endl;
            return;
        }
    }
    seguidores.push_back(u);
    cout << "O usuário " << u->id << " agora está seguindo " << this->id << "." << endl;
}
void Usuario::removerSeguidor()
{
    int pos;
    this->imprimirSeguidores();
    if(!this->seguidores.empty())
    {
        do
        {
            cout << "Informe a posição do seguidor: ";
            cin >> pos;
        }
        while (pos<0 || pos>=this->seguidores.size());
        cout << "O usuário " << seguidores[pos]->id << " deixou de seguir " << this->id << " com sucesso." << endl;
        seguidores.erase(seguidores.begin()+pos);
    }
}
void Usuario::criarPublicacao()
{
    Publicacao* p;
    cout << "Informe o conteúdo da publicação: ";
    string s,u;
    cin.ignore();
    getline(cin,s);
    cout << "Informe a url da publicação: ";
    cin.ignore();
    getline(cin,u);
    p= new Publicacao(s,u);
    publicacoes.push_back(p);
    cout << "Publicação criada com sucesso!\n";
}
void Usuario::editarPublicacao()
{
    int pos,he;
    string s;
    this->imprimirPublicacoes();
    if(publicacoes.empty())
    {
        return;
    }
    do
    {
        cout << "Informe a posição da publicação: ";
        cin >> pos;
    }
    while(pos<0 || pos>=this->publicacoes.size());
    cout << "Digite o novo conteúdo da publicação: ";
    cin.ignore();
    getline(cin,s);
marca:
    cout << "Deseja mesmo alterar o conteúdo da publicação???\n1.Sim\n2.Não" << endl;
    cin >> he;
    if(he==1)
    {
        this->publicacoes[pos]->setConteudo(s);
        cout << "Publicação editada com sucesso!" << endl;
    }
    else if(he==2)
    {
        return;
    }
    else
    {
        goto marca;
    }
}
void Usuario::excluirPublicacao()
{
    int pos;
    this->imprimirPublicacoes();
    if(publicacoes.empty())
    {
        return;
    }
    do
    {
        cout << "Informe a posição da publicação: ";
        cin >> pos;
    }
    while(pos<0 || pos>=this->publicacoes.size());
    publicacoes.erase(publicacoes.begin()+pos);
    cout << "A publicação selecionada foi excluída com sucesso." << endl;
}
void Usuario::imprimeQtdUsuarios()
{
    cout << "Quantidade de usuários em todas as redes sociais: " << Usuario::qtdUsuarios << endl;
}
string Usuario::getId()
{
    return this->id;
}
void Usuario::setId(string id)
{
    this->id=id;
}
string Usuario::getNome()
{
    return this->nome;
}
void Usuario::setNome(string name)
{
    this->nome=name;
}
tm Usuario::getData()
{
    return this->data;
}
void Usuario::setData(tm date)
{
    this->data=date;
}
string Usuario::getUrlFoto()
{
    return this->urlFoto;
}
void Usuario::setUrlFoto(string url)
{
    this->urlFoto=url;
}
vector<Usuario*> Usuario::getSeguidores()
{
    return this->seguidores;
}
vector<Publicacao*> Usuario::getPublicacoes()
{
    return this->publicacoes;
}
