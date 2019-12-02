#ifndef USUARIOCOMUM_H_INCLUDED
#define USUARIOCOMUM_H_INCLUDED
#include "Usuario.h"

class UsuarioComum: public Usuario
{
public:
    enum StatusRelacionamento
    {
        Solteiro=1,
        Namorando=2,
        Casado=3
    };
private:
    char genero;
    string formacao,urlFoto;
    StatusRelacionamento status;
public:
    UsuarioComum();
    UsuarioComum(string nome, string id, tm data, char genero, string formacao, StatusRelacionamento status, string urlFoto);
    void setGenero(char genero);
    char getGenero();
    void setFormacao(string formacao);
    string getFormacao();
    StatusRelacionamento getStatus();
    void setStatus(StatusRelacionamento status);
    string getStringStatus();
    bool validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias);
    void imprimeInfo();
    void imprimenoArquivo(ofstream &o);
    void imprimeSeguidor(ofstream &o);
    void carregaArquivo(ifstream &arqRed);
    void carregaSeguidor(ifstream &arqRed);
    void imprimeNoHtmlPerfil(ofstream &o);
    void imprimeNoHtmlSeguidor(ofstream &o);
};

#endif // USUARIOCOMUM_H_INCLUDED
