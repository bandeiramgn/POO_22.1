#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iterator>
#include <memory>

class Discp;

class Aluno{
    std::string nome;
    std::map<std::string, Discp*> discps;
public:
    Aluno(std::string nome = ""): nome(nome) {};

    std::vector<Discp*> getDiscps();
    std::string getNome();

    void addDisciplina(Discp* discp);
    void rmDisciplina(std::string idDisciplina);

    friend std::ostream& operator<<(std::ostream& os, Aluno& aluno);
    // std::string str()
};

class Discp {
    std::string id;
    std::map<std::string, Aluno*> alunos;
public:
    Discp(std::string nome = ""): id(nome) {};

    void addAluno(Aluno* aluno);
    void rmAluno(std::string idAluno);

    std::string getId();
    std::vector<Aluno*> getAlunos();

    friend std::ostream& operator<<(std::ostream& os, Discp& discp);
    // std::string str();
};

class Sistema {
    std::map<std::string, Discp*> disciplinas;
    std::map<std::string, Aluno*> alunos;
public:
    Sistema(){};

    void addAluno(std::string idAluno);
    void rmAluno(std::string idAluno);
    
    void addDisciplina(std::string idDisciplina);
    void rmDisciplina(std::string idDisciplina);

    void matricular(std::string idAluno, std::string idDisciplina);
    void desmatricular(std::string idAluno, std::string idDisciplina);

    friend std::ostream& operator<<(std::ostream& os, Sistema& sistema);

    // std::string str();
};

// Implementações da classe aluno
// =================================================================
void Aluno::addDisciplina(Discp* discp)
{
    auto it = discps.find(discp->getId());

    if (it != discps.end())
        return;

    this->discps[discp->getId()] = discp;
    discp->addAluno(this);
}

void Aluno::rmDisciplina(std::string idDisciplina)
{
    auto it = discps.find(idDisciplina);    
    if (it == discps.end())
        return;
    
    Discp* disciplina = it->second; // Guarda a disciplina que está no valor dentro do map das disciplinas do aluno

    this->discps.erase(it);
    disciplina->rmAluno(this->nome); // Pega o nome do aluno e chama o método remove do objeto disciplina

}

std::vector<Discp*> Aluno::getDiscps()
{
    std::vector<Discp*> disciplinas;
    for (auto pair: this->discps)
        disciplinas.push_back(pair.second);

    return disciplinas;
}

std::string Aluno::getNome()
{
    return this->nome;
}

// Implementações da classe Disciplina
// =================================================================
void Discp::addAluno(Aluno* aluno)
{
    auto it = alunos.find(aluno->getNome());

    if (it != alunos.end())
        return;

    this->alunos[aluno->getNome()] = aluno;
    aluno->addDisciplina(this);
}

void Discp::rmAluno(std::string nome)
{
    auto it = alunos.find(nome); // Aponta para o mapa caso ache o nome dentro de alunos
    if (it == alunos.end())
        return;
    
    Aluno* aluno = it->second; // Guarda a aluno que está na lista de alunos da disciplina
    
    this->alunos.erase(it);
    aluno->rmDisciplina(this->id);
}

std::vector<Aluno*> Discp::getAlunos()
{
    std::vector<Aluno*> alunos;

    for (auto [key, value] : this->alunos)
        alunos.push_back(value);

    return alunos;
}

std::string Discp::getId() 
{
    return this->id;
}

// Implementação da class sistema
// =================================================================
void Sistema::addAluno(std::string idAluno)
{
    auto it = alunos.find(idAluno);
    if (it != alunos.end())
        return;

    this->alunos[idAluno] = new Aluno(idAluno);
}

void Sistema::rmAluno(std::string idAluno)
{
    auto it = alunos.find(idAluno);
    if (it == alunos.end())
        return;
    
    Aluno* aluno = it->second;
    auto disciplinas_aluno = aluno->getDiscps(); // Chamo o metódo que me retorne todas as disciplinas na qual o aluno faz parte 

    for (auto disciplina : disciplinas_aluno)
        disciplina->rmAluno(idAluno);

    this->alunos.erase(it); // Apago do mapa de alunos do sistea
}

void Sistema::addDisciplina(std::string idDisciplina)
{
    auto it = disciplinas.find(idDisciplina);
    if (it != disciplinas.end())
        return;

    this->disciplinas[idDisciplina] = new Discp(idDisciplina);
}

void Sistema::rmDisciplina(std::string idDisciplina)
{
    auto it = disciplinas.find(idDisciplina);   
    if (it == disciplinas.end())    // Verifica se existe a disciplina
        return;                     // Se não existe retorna
    
    Discp* disciplina = it->second; 
    auto aluno_da_disciplina = disciplina->getAlunos(); // Recebe um vector dos alunos daquela disciplina

    for (auto aluno : aluno_da_disciplina)  // Para cada aluno da disciplina, remove ela da lista de disciplinas dele
        aluno->rmDisciplina(idDisciplina);
    
    this->disciplinas.erase(it); // Apago a disciplina da lista de disciplinas do sistema
}

void Sistema::matricular(std::string idAluno, std::string idDisciplina)
{
    auto it_aluno = alunos.find(idAluno);
    auto it_disciplina = disciplinas.find(idDisciplina);

    if (it_aluno == alunos.end() || it_disciplina == disciplinas.end())
        return;

    Aluno* aluno = it_aluno->second;
    Discp* disciplina = it_disciplina->second;

    aluno->addDisciplina(disciplina);
}

void Sistema::desmatricular(std::string idAluno, std::string idDisciplina)
{
        auto it_aluno = alunos.find(idAluno);
    auto it_disciplina = disciplinas.find(idDisciplina);

    if (it_aluno == alunos.end() || it_disciplina == disciplinas.end())
        return;

    Aluno* aluno = it_aluno->second;

    aluno->rmDisciplina(idDisciplina);
}


// Chamadas de saída usando o ostream
// ================================================================= 

std::ostream& operator<<(std::ostream& os, Aluno& aluno)
{
    os << aluno.getNome() << " [ ";
    for (auto pair : aluno.discps)
        os << pair.second->getId() << " ";
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, Discp& discp)
{
    os << discp.getId() << " [ ";
    for (auto [key, value] : discp.alunos)
        os << value->getNome() << " ";
    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, Sistema& sistema)
{
    os << "alunos: \n";
    for (auto [key, value] : sistema.alunos)
      os << "    " << *value << '\n';
    os << "discps: \n";
    for (auto [key, value] : sistema.disciplinas)
        os << "    " << *value << '\n';
    return os;
}

// Classe principal da aplicação
int main(){
    std::string line, cmd;
    Sistema sistema;
    while(true){
        try{
            std::getline(std::cin, line);
            std::cout << "$" << line << std::endl;
            std::stringstream ss(line);
            //cria um vetor de strings a partir de line
            std::vector<std::string> ui(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>());
            std::string cmd = ui[0];
            if(cmd == "end"){
                break;
            }else if(cmd == "nwalu"){
                for(std::size_t i = 1; i < ui.size(); i++)
                    sistema.addAluno(ui[i]);
            }else if(cmd == "nwdis"){
                for(std::size_t i = 1; i < ui.size(); i++)
                    sistema.addDisciplina(ui[i]);
            }else if(cmd == "show"){
                std::cout << sistema;
            }else if(cmd == "tie"){
                for(std::size_t i = 2; i < ui.size(); i++)
                    sistema.matricular(ui[1], ui[i]);
            }else if(cmd == "untie"){
                for(size_t i = 2; i < ui.size(); i++)
                    sistema.desmatricular(ui[1], ui[i]);
            }else if(cmd == "rmalu"){
                sistema.rmAluno(ui[1]);
            }else{
                std::cout << "comando invalido " << "[" << cmd << "]\n";
            }
        }catch(std::string e){
            std::cout << e << std::endl;
        }
    }
}
